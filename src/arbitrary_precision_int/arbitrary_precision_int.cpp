#include "arbitrary_precision_int.hpp"
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

} // namespace

api::API::API(std::vector<std::uint8_t> const& values)
    : m_data { values }
{
}

api::API::API(std::vector<std::uint8_t>&& values)
    : m_data { std::move(values) }
{
}

std::vector<std::uint8_t> const& api::API::get_data() const { return m_data; }

bool api::operator==(api::API const& lhs, api::API const& rhs)
{
    auto const [shorter, longer] = order_vectors(lhs.get_data(), rhs.get_data());
    std::size_t max_index = 0u;
    // if they differ in any byte, return false
    for (auto index = 0u; index != shorter->size(); ++index) {
        if (lhs.get_data().at(index) != rhs.get_data().at(index)) {
            return false;
        }
        max_index = index;
    }
    // if any of the "leading" bytes is non-zero, return false
    if (shorter->size() != longer->size()) {
        for (std::size_t index = max_index; index != longer->size(); ++index) {
            if (longer->at(index) != 0u) {
                return false;
            }
        }
    }
    return true;
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
    if (result.back() == 0u) {
        result.pop_back();
    }
    return result;
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
            result.at(i) = 255u + difference + 1;
        } else {
            carry = 0;
            result.at(i) = static_cast<std::uint8_t>(difference);
        }
    }
    if (result.back() == 0) {
        result.pop_back();
    }
    return result;
}

api::API api::operator*(api::API const& lhs, api::API const& rhs)
{
    std::vector<std::uint8_t> result;

    std::vector<std::uint8_t> tmp = lhs.get_data();
    for (auto i = 0u; i != rhs.get_data().size(); ++i) {
        for (auto j = 0u; j != rhs.get_data().at(i); ++j) {
            result = (result + tmp).get_data();
        }
        tmp.insert(tmp.begin(), 0u); // effectively shifting all bytes one place to the right.
    }
    return result;
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
