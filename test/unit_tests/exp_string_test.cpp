#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <string>

class ArbitraryPrecisionIntExpStringTestFixture
    : public ::testing::TestWithParam<std::tuple<std::vector<std::uint16_t>, std::string>> { };

TEST_P(ArbitraryPrecisionIntExpStringTestFixture, IsEqual)
{
    api::API const api { std::get<0>(GetParam()) };
    std::string const expected_string { std::get<1>(GetParam()) };
    auto const result = api.to_exp_string();
    ASSERT_EQ(result, expected_string);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntExpStringTest,
    ArbitraryPrecisionIntExpStringTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint16_t>{}, "0"),
        std::make_tuple(std::vector<std::uint16_t>{1}, "1"),
        std::make_tuple(std::vector<std::uint16_t>{9}, "9"),
        std::make_tuple(std::vector<std::uint16_t>{10}, "10"),
        std::make_tuple(std::vector<std::uint16_t>{11}, "11"),
        std::make_tuple(std::vector<std::uint16_t>{99}, "99"),
        std::make_tuple(std::vector<std::uint16_t>{100}, "100"),
        std::make_tuple(api::from_uint64(999).get_data(), "999"),
        std::make_tuple(api::from_uint64(1000).get_data(), "1.00e3"),
        std::make_tuple(api::from_uint64(1001).get_data(), "1.00e3"),
        std::make_tuple(api::from_uint64(1009).get_data(), "1.00e3"),
        std::make_tuple(api::from_uint64(1010).get_data(), "1.01e3"),
        std::make_tuple(api::from_uint64(1011).get_data(), "1.01e3"),
        std::make_tuple(api::from_uint64(9999).get_data(), "9.99e3"),
        std::make_tuple(api::from_uint64(10000).get_data(), "1.00e4"),
        std::make_tuple((api::from_uint64(10000)*api::from_uint64(20000)).get_data(), "2.00e8"),
        std::make_tuple((api::from_uint64(1000000)*api::from_uint64(4000000)).get_data(), "4.00e12")
        // clang-format on
        ));
