#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <string>

class ArbitraryPrecisionIntStringTestFixture
    : public ::testing::TestWithParam<std::tuple<std::vector<std::uint8_t>, std::string>> { };

TEST_P(ArbitraryPrecisionIntStringTestFixture, IsEqual)
{
    api::API const api { std::get<0>(GetParam()) };
    std::string const expected_string { std::get<1>(GetParam()) };
    ASSERT_EQ(api::to_string(api), expected_string);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntStringTest, ArbitraryPrecisionIntStringTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t>{}, "0"),
        std::make_tuple(std::vector<std::uint8_t>{1}, "1"),
        std::make_tuple(std::vector<std::uint8_t>{9}, "9"),
        std::make_tuple(std::vector<std::uint8_t>{10}, "10"),
        std::make_tuple(std::vector<std::uint8_t>{11}, "11"),
        std::make_tuple(std::vector<std::uint8_t>{255}, "255"),
        std::make_tuple(std::vector<std::uint8_t>{0, 1}, "256"),
        std::make_tuple(std::vector<std::uint8_t>{0, 2}, "512"),
        std::make_tuple(api::from_uint64(999999999999999).get_data(), std::to_string(999999999999999)),
        std::make_tuple(api::from_uint64(std::numeric_limits<std::uint64_t>::max()).get_data(), std::to_string(std::numeric_limits<std::uint64_t>::max()))
        // clang-format on
        ));
