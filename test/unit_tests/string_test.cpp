#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <gtest/gtest.h>
#include <limits>
#include <string>

class ArbitraryPrecisionIntStringTestFixture : public ::testing::TestWithParam<std::uint64_t> { };

TEST_P(ArbitraryPrecisionIntStringTestFixture, IsEqual)
{
    api::API const api { api::from_uint64(GetParam()) };
    std::string const expected_string { std::to_string(GetParam()) };
    ASSERT_EQ(api.to_string(), expected_string);
}
/*
TEST_P(ArbitraryPrecisionIntStringTestFixture, CallToStringTwice)
{
    api::API const api { std::get<0>(GetParam()) };
    std::string const expected_string { std::get<1>(GetParam()) };
    ASSERT_EQ(api.to_string(), expected_string);
    // calling to_string a second time results in the same string (preferably cached)
    ASSERT_EQ(api.to_string(), expected_string);
}*/

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntStringTest, ArbitraryPrecisionIntStringTestFixture,
    ::testing::Values(
        // clang-format off
        0u,
        1u,
        9u,
        10u,
        11u,
        255u,
        256u,
        512u,
        65535u,
        65536u,
        999999999999999u,
        std::numeric_limits<std::uint64_t>::max() - 1,
        std::numeric_limits<std::uint64_t>::max()
        // clang-format on
        ));
