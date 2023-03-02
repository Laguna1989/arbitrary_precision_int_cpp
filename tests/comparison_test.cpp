#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <gtest/gtest.h>
#include <limits>

using namespace ::testing;

class ArbitraryPrecisionIntEqualTestFixture
    : public ::testing::TestWithParam<std::tuple<std::uint64_t, std::vector<std::uint8_t>>> { };

TEST_P(ArbitraryPrecisionIntEqualTestFixture, IsEqual)
{
    auto const abi = api::from_int(std::get<0>(GetParam()));
    api::API const expected_abi { std::get<1>(GetParam()) };
    ASSERT_TRUE(abi == expected_abi);
    ASSERT_FALSE(abi != expected_abi);
}

TEST_P(ArbitraryPrecisionIntEqualTestFixture, FromInt)
{
    auto const abi = api::from_int(std::get<0>(GetParam()));

    auto const expected_value = std::get<1>(GetParam());
    ASSERT_EQ(abi.get_data(), expected_value);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntEqualTest, ArbitraryPrecisionIntEqualTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(0, std::vector<std::uint8_t> { }),
        std::make_tuple(1, std::vector<std::uint8_t> { 1u }),
        std::make_tuple(2, std::vector<std::uint8_t> { 2u }),
        std::make_tuple(16, std::vector<std::uint8_t> { 16u }),
        std::make_tuple(std::numeric_limits<std::uint8_t>::max(), std::vector<std::uint8_t> { std::numeric_limits<std::uint8_t>::max() }),
        std::make_tuple(std::numeric_limits<std::uint8_t>::max()+1u, std::vector<std::uint8_t> { 0u, 1u }),
        std::make_tuple(std::numeric_limits<std::uint8_t>::max()+2u, std::vector<std::uint8_t> { 1u, 1u }),
        std::make_tuple(std::numeric_limits<std::uint8_t>::max()+100u, std::vector<std::uint8_t> { 99u, 1u }),
        std::make_tuple((std::numeric_limits<std::uint8_t>::max()+1u)*2u, std::vector<std::uint8_t> { 0, 2u }),
        std::make_tuple((std::numeric_limits<std::uint8_t>::max()+1u)*4u, std::vector<std::uint8_t> { 0, 4u }),
        std::make_tuple((std::numeric_limits<std::uint8_t>::max()+1u)*100u, std::vector<std::uint8_t> { 0, 100u }),
        std::make_tuple((std::numeric_limits<std::uint8_t>::max()+1u)*200u, std::vector<std::uint8_t> { 0, 200u }),
        std::make_tuple((std::numeric_limits<std::uint8_t>::max()+1u)*254u, std::vector<std::uint8_t> { 0, 254u }),
        std::make_tuple((256)*255, std::vector<std::uint8_t> { 0u , 255u }),
        std::make_tuple((256)*(256), std::vector<std::uint8_t> { 0, 0, 1u })
        // clang-format on
        ));

class ArbitraryPrecisionIntUnEqualTestFixture
    : public ::testing::TestWithParam<std::tuple<std::uint64_t, std::uint64_t>> { };
TEST_P(ArbitraryPrecisionIntUnEqualTestFixture, Unequal)
{
    auto const first = api::from_int(std::get<0>(GetParam()));
    auto const second = api::from_int(std::get<1>(GetParam()));
    ASSERT_NE(first, second);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntUnEqualTest, ArbitraryPrecisionIntUnEqualTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(0u, 1u),
        std::make_tuple(0u, 2u),
        std::make_tuple(1u, 0u),
        std::make_tuple(2u, 0u),
        std::make_tuple(1u, 2u),
        std::make_tuple(255u, 256u),
        std::make_tuple(0u, 256u),
        std::make_tuple(256u, 257u),
        std::make_tuple(256u * 256u, 256u * 256u + 1u),
        std::make_tuple(256u * 256u, 256u * 256u - 1u)
        // clang-format on
        ));

class ArbitraryPrecisionIntComparisonTestFixture
    : public ::testing::TestWithParam<
          std::tuple<std::vector<std::uint8_t>, std::vector<std::uint8_t>, int>> { };

TEST_P(ArbitraryPrecisionIntComparisonTestFixture, CompareReturnsCorrectResult)
{
    auto const left_vec = std::get<0>(GetParam());
    auto const right_vec = std::get<1>(GetParam());
    auto const expected_comparison_result = std::get<2>(GetParam());

    auto const lhs = api::API { left_vec };
    auto const rhs = api::API { right_vec };

    auto const compare_value = api::compare(lhs, rhs);
    ASSERT_EQ(compare_value, expected_comparison_result);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntComparisonTest,
    ArbitraryPrecisionIntComparisonTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t> { }, std::vector<std::uint8_t> { }, 0),
        std::make_tuple(std::vector<std::uint8_t> { 0u }, std::vector<std::uint8_t> { 0u }, 0),
        std::make_tuple(std::vector<std::uint8_t> { 0u }, std::vector<std::uint8_t> { 1u }, -1),
        std::make_tuple(std::vector<std::uint8_t> { 1u }, std::vector<std::uint8_t> { 0u }, 1),
        std::make_tuple(std::vector<std::uint8_t> { 255u }, std::vector<std::uint8_t> { 255u }, 0),
        std::make_tuple(std::vector<std::uint8_t> { 254u }, std::vector<std::uint8_t> { 255u }, -1),
        std::make_tuple(std::vector<std::uint8_t> { 255u }, std::vector<std::uint8_t> { 254u }, 1),
        std::make_tuple(std::vector<std::uint8_t> { 1u, 1u }, std::vector<std::uint8_t> { 0u }, 1),
        std::make_tuple(std::vector<std::uint8_t> { 0u }, std::vector<std::uint8_t> { 1u, 1u }, -1),
        std::make_tuple(std::vector<std::uint8_t> { 1u, 1u }, std::vector<std::uint8_t> { 1u, 1u }, 0),
        std::make_tuple(std::vector<std::uint8_t> { 1u }, std::vector<std::uint8_t> { 1u, 0u }, 0),
        std::make_tuple(std::vector<std::uint8_t> { 1u, 100u }, std::vector<std::uint8_t> { 1u, 100u }, 0),
        std::make_tuple(std::vector<std::uint8_t> { 0u, 100u }, std::vector<std::uint8_t> { 99u }, 1),
        std::make_tuple(std::vector<std::uint8_t> { 99u }, std::vector<std::uint8_t> { 0u, 100u }, -1),
        std::make_tuple(std::vector<std::uint8_t> { 100u, 0u }, std::vector<std::uint8_t> { 99u }, 1),
        std::make_tuple(std::vector<std::uint8_t> { 99u }, std::vector<std::uint8_t> { 100u, 0u }, -1),
        std::make_tuple(std::vector<std::uint8_t> { 100u }, std::vector<std::uint8_t> { 99u, 0u }, 1),
        std::make_tuple(std::vector<std::uint8_t> { 99u, 0u }, std::vector<std::uint8_t> { 100u }, -1)
        // clang-format on
        ));
