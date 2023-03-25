#include "arbitrary_precision_int.hpp"
#include <limits>
#include <sstream>
#include <tuple>
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

void trim_vector_in_place(std::vector<std::uint8_t>& vec)
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

void to_stringstream(api::API const& api, std::stringstream& stream)
{
    static api::API const tenAsAPI = api::from_uint64(10);
    if (api::compare(api, tenAsAPI) == -1) {
        stream << api::to_uint64(api);
    } else {
        auto const [div, mod] = api::div_mod(api, tenAsAPI);
        to_stringstream(div, stream);
        to_stringstream(mod, stream);
    }
}

std::string to_string(api::API const& api)
{
    std::stringstream sstream {};
    to_stringstream(api, sstream);
    return sstream.str();
}

std::string to_exp_string(api::API const& api)
{
    auto str = api.to_string();
    if (str.size() <= 3) {
        return str;
    }
    std::string exp_str;
    auto const exponent_as_string = std::to_string(str.size() - 1);
    // a magic number of 5 is needed here. example:
    // 1.02e
    // 01234 => size = 5
    //
    exp_str.resize(5 + exponent_as_string.size());
    exp_str[0] = str[0];
    exp_str[1] = '.';

    exp_str[2] = str[1];
    exp_str[3] = str[2];

    exp_str[4] = 'e';

    for (auto i = 0u; i != exponent_as_string.size(); ++i) {
        exp_str[5 + i] = exponent_as_string[i];
    }
    return exp_str;
}

} // namespace

api::API::API()
    : m_data {}
{
}

api::API::API(std::vector<std::uint8_t> const& values)
    : m_data { values }
{
    trim_vector_in_place(m_data);
}

api::API::API(std::vector<std::uint8_t>&& values)
    : m_data { std::move(values) }
{
    trim_vector_in_place(m_data);
}

std::vector<std::uint8_t> const& api::API::get_data() const { return m_data; }

std::string api::API::to_string() const
{
    if (m_string_representation.empty()) {
        m_string_representation = ::to_string(*this);
    }
    return m_string_representation;
}
std::string api::API::to_exp_string() const
{
    if (m_exp_string_representation.empty()) {
        m_exp_string_representation = ::to_exp_string(*this);
    }
    return m_exp_string_representation;
}

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
    trim_vector_in_place(result);
    return api::API { std::move(result) };
}

api::API api::operator-(api::API const& lhs, api::API const& rhs)
{
    if (rhs == api::from_uint64(0u)) {
        return lhs;
    }
    auto const compare_result = api::compare(lhs, rhs);
    if (compare_result <= 0) {
        return api::from_uint64(0u);
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
    trim_vector_in_place(result);
    return api::API { std::move(result) };
}

api::API api::operator*(api::API const& lhs, api::API const& rhs)
{
    api::API result = api::from_uint64(0);

    auto const [shorter, longer] = order_vectors(lhs.get_data(), rhs.get_data());

    std::vector<std::uint8_t> tmp = *longer;
    for (auto i = 0u; i != shorter->size(); ++i) {
        for (auto j = 0u; j != shorter->at(i); ++j) {
            result = api::API { result } + api::API { tmp };
        }
        tmp.insert(tmp.begin(), 0u); // effectively shifting all bytes one place to the right.
    }
    return result;
}

api::API api::operator/(api::API const& lhs, api::API const& rhs)
{
    auto const [q, _] = api::div_mod(lhs, rhs);
    return q;
}

api::API api::mod(api::API const& lhs, api::API const& rhs)
{
    auto const [_, r] = api::div_mod(lhs, rhs);
    return r;
}

std::pair<api::API, api::API> api::div_mod(api::API const& lhs, api::API const& rhs)
{
    static api::API const zero_as_api = api::from_uint64(0);
    static api::API const one_as_api = api::from_uint64(1);
    if (rhs == zero_as_api) {
        return std::make_pair(zero_as_api, zero_as_api);
    }
    if (rhs == one_as_api) {
        return std::make_pair(lhs, zero_as_api);
    }

    auto const compare_result = api::compare(lhs, rhs);
    if (compare_result == -1) {
        return std::make_pair(zero_as_api, zero_as_api);
    } else if (compare_result == 0) {
        return std::make_pair(one_as_api, zero_as_api);
    }

    std::vector<std::uint8_t> q {};
    q.resize(lhs.get_data().size());
    auto r = std::vector<std::uint8_t> {};

    for (auto i = static_cast<std::int64_t>(lhs.get_data().size()) - 1; i != -1; --i) {
        r.insert(r.begin(), lhs.get_data()[i]); // effectively shifting all bytes one place to the
                                                // right. Equals a multiplication by 256

        api::API r_api { r };
        while (api::compare(rhs, r_api) <= 0) {
            r_api = r_api - rhs;
            q.at(i) += 1;
        }
        r = r_api.get_data();
    }

    return std::make_pair(api::API { std::move(q) }, api::API { std::move(r) });
}

api::API api::from_uint64(std::uint64_t number)
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
    auto const [shorter, longer] = order_vectors(lhs.get_data(), rhs.get_data());
    auto const length_shorter = static_cast<std::int64_t>(shorter->size());
    auto const length_longer = static_cast<std::int64_t>(longer->size());

    for (auto i = static_cast<std::int64_t>(length_longer) - 1; i != -1; --i) {
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

std::uint64_t api::to_uint64(api::API const& api)
{
    if (api.get_data().size() > 8) {
        return std::numeric_limits<std::uint64_t>::max();
    }
    std::uint64_t return_value = 0u;
    for (auto i = 0u; i != api.get_data().size(); ++i) {
        return_value += (api.get_data().at(i) << (i * 8));
    }
    return return_value;
}
