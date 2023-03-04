#include "arbitrary_precision_int.hpp"
#include <sstream>
#include <utility>

namespace {

auto order_vectors(std::vector<std::uint8_t> const& lhs, std::vector<std::uint8_t> const& rhs)
{
    std::vector<std::uint8_t> const* shorter = nullptr;
    std::vector<std::uint8_t> const* longer = nullptr;
    if (lhs.size() <= rhs.size()) {
        shorter = &lhs;
        longer = &rhs;
    } else {
        shorter = &rhs;
        longer = &lhs;
    }
    return std::make_tuple(shorter, longer);
}

void trim_vector(std::vector<std::uint8_t>& vec)
{
    if (vec.empty()) {
        return;
    }
    while (vec.back() == 0u) {
        vec.pop_back();
        if (vec.empty()) {
            return;
        }
    }
}

} // namespace

api::API::API(std::vector<std::uint8_t> const& values)
    : m_data { values }
{
    trim();
}

api::API::API(std::vector<std::uint8_t>&& values)
    : m_data { std::move(values) }
{
    trim();
}

std::vector<std::uint8_t> const& api::API::get_data() const { return m_data; }

void api::API::trim() { trim_vector(m_data); }

bool api::operator==(api::API const& lhs, api::API const& rhs)
{
    return lhs.get_data() == rhs.get_data();
}

bool api::operator!=(api::API const& lhs, API const& rhs) { return !(lhs == rhs); }

api::API api::operator+(api::API const& lhs, api::API const& rhs)
{
    auto const new_size = (lhs.get_data().size() > rhs.get_data().size() ? lhs.get_data().size()
                                                                         : rhs.get_data().size())
        + 1u;
    std::vector<std::uint8_t> result(new_size, 0u);
    for (auto i = 0u; i != new_size - 1; ++i) {
        // perform calculation in bigger type to be able to check for overflows
        std::uint16_t const left_value = (i < lhs.get_data().size()) ? lhs.get_data().at(i) : 0u;
        std::uint16_t const right_value = (i < rhs.get_data().size()) ? rhs.get_data().at(i) : 0u;

        std::uint16_t const sum = left_value + right_value + result.at(i);
        result.at(i) = static_cast<std::uint8_t>(sum);
        // deal with carry
        if (sum > static_cast<std::uint16_t>(std::numeric_limits<std::uint8_t>::max())) {
            result.at(i + 1u) = 1u;
        }
    }
    trim_vector(result);
    return api::API { std::move(result) };
}

api::API api::operator-(api::API const& lhs, api::API const& rhs)
{
    if (rhs == api::from_int(0u)) {
        return lhs;
    }
    auto const compare_result = api::compare(lhs, rhs);
    if (compare_result == -1) {
        return api::from_int(0u);
    }
    auto const new_size = (lhs.get_data().size() > rhs.get_data().size() ? lhs.get_data().size()
                                                                         : rhs.get_data().size());
    std::vector<std::uint8_t> result(new_size, 0u);
    std::int32_t carry = 0u;
    for (auto i = 0u; i != new_size; ++i) {

        std::int32_t left_value
            = (i < lhs.get_data().size()) ? static_cast<std::int32_t>(lhs.get_data().at(i)) : 0;
        std::int32_t const right_value
            = (i < rhs.get_data().size()) ? static_cast<std::int32_t>(rhs.get_data().at(i)) : 0;

        std::int32_t const difference = left_value - right_value + carry;
        if (difference < 0) {
            carry = -1;
            result.at(i) = 256u + difference;
        } else {
            carry = 0;
            result.at(i) = static_cast<std::uint8_t>(difference);
        }
    }
    trim_vector(result);
    return api::API { std::move(result) };
}

api::API api::operator*(api::API const& lhs, api::API const& rhs)
{
    std::vector<std::uint8_t> result;

    std::vector<std::uint8_t> tmp = lhs.get_data();
    for (auto i = 0u; i != rhs.get_data().size(); ++i) {
        for (auto j = 0u; j != rhs.get_data().at(i); ++j) {
            result = (api::API { result } + api::API { tmp }).get_data();
        }
        tmp.insert(tmp.begin(), 0u); // effectively shifting all bytes one place to the right.
    }
    return api::API { std::move(result) };
}

api::API api::operator/(api::API const& lhs, api::API const& rhs)
{
    if (rhs == api::from_int(0)) {
        return api::from_int(0);
    }

    auto const compare_result = api::compare(lhs, rhs);
    if (compare_result == -1) {
        return api::from_int(0);
    } else if (compare_result == 0) {
        return api::from_int(1);
    }

    std::vector<std::uint8_t> q {};
    q.resize(lhs.get_data().size());
    auto r = std::vector<std::uint8_t> {};

    for (auto i = lhs.get_data().size() - 1; i != -1; --i) {
        r.insert(r.begin(), lhs.get_data()[i]); // effectively shifting all bytes one place to the
                                                // right. Equals a multiplication by 256

        api::API r_api { r };
        while (api::compare(rhs, r_api) <= 0) {
            r_api = r_api - rhs;
            q.at(i) += 1;
        }
    }
    return api::API { q };
}

api::API api::mod(api::API const& lhs, api::API const& rhs)
{
    if (rhs == api::from_int(0)) {
        return api::from_int(0);
    }

    auto const compare_result = api::compare(lhs, rhs);
    if (compare_result == -1) {
        return api::from_int(0);
    } else if (compare_result == 0) {
        return api::from_int(0);
    }

    std::vector<std::uint8_t> q {};
    q.resize(lhs.get_data().size());
    auto r = std::vector<std::uint8_t> {};

    for (auto i = lhs.get_data().size() - 1; i != -1; --i) {
        r.insert(r.begin(), lhs.get_data()[i]); // effectively shifting all bytes one place to the
                                                // right. Equals a multiplication by 256

        api::API r_api { r };
        while (api::compare(rhs, r_api) <= 0) {
            r_api = r_api - rhs;
            q.at(i) += 1;
        }
        r = r_api.get_data();
    }
    return api::API { r };
}

api::API api::from_int(std::uint64_t number)
{
    std::vector<std::uint8_t> data;
    while (true) {
        if (number == 0) {
            break;
        }
        auto const max = std::numeric_limits<std::uint8_t>::max();
        if (number == max) {
            data.push_back(max);
            break;
        }
        auto const max_plus_one = static_cast<std::uint16_t>(max) + 1u;
        std::uint64_t const divisor = number / max_plus_one;
        std::uint64_t const remainder = number % max_plus_one;

        data.push_back(static_cast<std::uint8_t>(remainder));
        number = divisor;
    }
    return API { std::move(data) };
}

int api::compare(api::API const& lhs, api::API const& rhs)
{
    auto [shorter, longer] = order_vectors(lhs.get_data(), rhs.get_data());
    std::size_t const length_shorter = shorter->size();
    std::size_t const length_longer = longer->size();

    for (auto i = length_longer - 1; i != -1; --i) {
        if (i >= length_shorter) {
            if (longer->at(i) != 0) {
                return &lhs.get_data() == shorter ? -1 : 1;
            }
        } else {
            if (longer->at(i) > shorter->at(i)) {
                return &lhs.get_data() == shorter ? -1 : 1;
            } else if (longer->at(i) < shorter->at(i)) {
                return &lhs.get_data() == shorter ? 1 : -1;
            }
        }
    }
    return 0;
}

void to_stringstream(api::API const& api, std::stringstream& stream)
{
    static api::API const tenAsAPI = api::from_int(10);
    if (api::compare(api, tenAsAPI) == -1) {
        stream << api::to_uint64(api);
    } else {
        to_stringstream(api / tenAsAPI, stream);
        to_stringstream(api::mod(api, tenAsAPI), stream);
    }
}

std::string api::to_string(api::API const& api)
{
    std::stringstream sstream {};
    to_stringstream(api, sstream);
    return sstream.str();
}

std::uint64_t api::to_uint64(api::API const& api)
{
    if (api.get_data().size() > 8) {
        return std::numeric_limits<std::uint64_t>::max();
    }
    std::uint64_t retval = 0u;
    for (auto i = 0u; i != api.get_data().size(); ++i) {
        retval += (api.get_data().at(i) << (i * 8));
    }
    return retval;
}
