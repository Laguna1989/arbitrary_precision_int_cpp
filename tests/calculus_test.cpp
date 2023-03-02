#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <gtest/gtest.h>

class ArbitraryPrecisionIntCalculusTestFixture
    : public ::testing::TestWithParam<std::tuple<std::vector<std::uint8_t>,
          std::vector<std::uint8_t>, std::vector<std::uint8_t>>> { };

using ArbitraryPrecisionIntCalculusAddTestFixture = ArbitraryPrecisionIntCalculusTestFixture;

TEST_P(ArbitraryPrecisionIntCalculusAddTestFixture, AddReturnsCorrectResult)
{
    auto const lhs = api::API { std::get<0>(GetParam()) };
    auto const rhs = api::API { std::get<1>(GetParam()) };

    auto const sum = lhs + rhs;
    auto const expected_sum = api::API { std::get<2>(GetParam()) };
    ASSERT_EQ(sum, expected_sum);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntAddTest, ArbitraryPrecisionIntCalculusAddTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 255 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0, 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1, 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 200 }, std::vector<std::uint8_t> { 100 }, std::vector<std::uint8_t> { 44, 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0, 0, 0, 1 }, std::vector<std::uint8_t> { 1,0,0,1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 0, 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1,0,0,1 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 255, 255, 255, 1 }, std::vector<std::uint8_t> { 0, 0, 0, 2 })
        // clang-format on
        ));

using ArbitraryPrecisionIntCalculusSubTestFixture = ArbitraryPrecisionIntCalculusTestFixture;

TEST_P(ArbitraryPrecisionIntCalculusSubTestFixture, SubtractionReturnsCorrectResult)
{
    auto const lhs = api::API { std::get<0>(GetParam()) };
    auto const rhs = api::API { std::get<1>(GetParam()) };

    auto const difference = lhs - rhs;
    auto const expected_difference = api::API { std::get<2>(GetParam()) };
    ASSERT_EQ(difference, expected_difference);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntSubTest, ArbitraryPrecisionIntCalculusSubTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 255 }),
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 100 }, std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 255 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 254 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 253 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 0, 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 255, 255,255 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 0, 0, 1 }, std::vector<std::uint8_t> { 1, 0, 1 }, std::vector<std::uint8_t> { 255, 255,254 })
        // clang-format on
        ));

using ArbitraryPrecisionIntCalculusMulTestFixture = ArbitraryPrecisionIntCalculusTestFixture;

TEST_P(ArbitraryPrecisionIntCalculusMulTestFixture, SubtractionReturnsCorrectResult)
{
    auto const lhs = api::API { std::get<0>(GetParam()) };
    auto const rhs = api::API { std::get<1>(GetParam()) };

    auto const result = lhs * rhs;
    auto const expected_result = api::API { std::get<2>(GetParam()) };
    ASSERT_EQ(result, expected_result);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntMulTest, ArbitraryPrecisionIntCalculusMulTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 10 }),
        std::make_tuple(std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 10 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 4 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 6 }),
        std::make_tuple(std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 6 }),
        std::make_tuple(std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 12 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0,1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0,2 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0,2 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0, 3 }, std::vector<std::uint8_t> { 0,3 }),
        std::make_tuple(std::vector<std::uint8_t> { 100 }, std::vector<std::uint8_t> { 2 }, api::from_int(100*2).get_data()),
        std::make_tuple(std::vector<std::uint8_t> { 100 }, std::vector<std::uint8_t> { 3 }, api::from_int(100*3).get_data()),
        std::make_tuple(api::from_int(1337).get_data(), api::from_int(42).get_data(), api::from_int(1337*42).get_data())

        // clang-format on
        ));
