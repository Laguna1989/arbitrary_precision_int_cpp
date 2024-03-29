#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <gtest/gtest.h>
#include <tuple>

class ArbitraryPrecisionIntCalculusTestFixture
    : public ::testing::TestWithParam<std::tuple<std::vector<std::uint8_t>,
          std::vector<std::uint8_t>, std::vector<std::uint8_t>>> { };

using ArbitraryPrecisionIntCalculusAddTestFixture = ArbitraryPrecisionIntCalculusTestFixture;

namespace api {
// If you can't declare the function in the class it's important that the
// << operator is defined in the SAME namespace that defines Bar.  C++'s look-up
// rules rely on that.
std::ostream& operator<<(std::ostream& os, const api::API& api)
{
    os << "(";
    for (auto const& v : api.get_data()) {
        os << static_cast<int>(v) << ", ";
    }
    os << ")";
    return os;
}
} // namespace api

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
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0, 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0, 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0, 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0, 3 }, std::vector<std::uint8_t> { 0, 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 2 }, std::vector<std::uint8_t> { 0, 3 }, std::vector<std::uint8_t> { 0, 0, 6 }),
        std::make_tuple(std::vector<std::uint8_t> { 100 }, std::vector<std::uint8_t> { 2 }, api::from_uint64(100*2).get_data()),
        std::make_tuple(std::vector<std::uint8_t> { 100 }, std::vector<std::uint8_t> { 3 }, api::from_uint64(100*3).get_data()),
        std::make_tuple(api::from_uint64(1337).get_data(), api::from_uint64(42).get_data(), api::from_uint64(1337*42).get_data())
        // clang-format on
        ));

using ArbitraryPrecisionIntCalculusDivTestFixture = ArbitraryPrecisionIntCalculusTestFixture;

TEST_P(ArbitraryPrecisionIntCalculusDivTestFixture, DivisionReturnsCorrectResult)
{
    auto const lhs = api::API { std::get<0>(GetParam()) };
    auto const rhs = api::API { std::get<1>(GetParam()) };

    auto const result = lhs / rhs;
    auto const expected_result = api::API { std::get<2>(GetParam()) };
    ASSERT_EQ(result, expected_result);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntDivTest, ArbitraryPrecisionIntCalculusDivTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 6 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 6 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 255 }),

        std::make_tuple(std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 5 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 8 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 2 }),

        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 96 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 48 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 8 }, std::vector<std::uint8_t> { 24 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 16 }, std::vector<std::uint8_t> { 12 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 32 }, std::vector<std::uint8_t> { 6 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 64 }, std::vector<std::uint8_t> { 3 }),

        std::make_tuple(std::vector<std::uint8_t> { 243 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 81 }),
        std::make_tuple(std::vector<std::uint8_t> { 243 }, std::vector<std::uint8_t> { 9 }, std::vector<std::uint8_t> { 27 }),
        std::make_tuple(std::vector<std::uint8_t> { 243 }, std::vector<std::uint8_t> { 27 }, std::vector<std::uint8_t> { 9 }),

        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0, 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 128 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 64 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 8 }, std::vector<std::uint8_t> { 32 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 16 }, std::vector<std::uint8_t> { 16 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 32 }, std::vector<std::uint8_t> { 8 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 64 }, std::vector<std::uint8_t> { 4 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 128 }, std::vector<std::uint8_t> { 2 }),

        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 2 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 255 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 255 }),

        std::make_tuple(std::vector<std::uint8_t> { 30 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 31 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 32 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 33 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 34 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 35 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 36 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 37 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 38 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 39 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),

        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 1, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 10, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 100, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 200, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 255, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 })

        // clang-format on
        ));

using ArbitraryPrecisionIntCalculusModTestFixture = ArbitraryPrecisionIntCalculusTestFixture;

TEST_P(ArbitraryPrecisionIntCalculusModTestFixture, ModReturnsCorrectResult)
{
    auto const lhs = api::API { std::get<0>(GetParam()) };
    auto const rhs = api::API { std::get<1>(GetParam()) };

    auto const result = lhs % rhs;
    auto const expected_result = api::API { std::get<2>(GetParam()) };
    ASSERT_EQ(result, expected_result);
}

INSTANTIATE_TEST_SUITE_P(ArbitraryPrecisionIntModTest, ArbitraryPrecisionIntCalculusModTestFixture,
    ::testing::Values(
        // clang-format off
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 6 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 6 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 255 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),

        std::make_tuple(std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 5 }, std::vector<std::uint8_t> { 0}),
        std::make_tuple(std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 8 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 2 }),

        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 8 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 16 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 32 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 192 }, std::vector<std::uint8_t> { 64 }, std::vector<std::uint8_t> { 0 }),

        std::make_tuple(std::vector<std::uint8_t> { 243 }, std::vector<std::uint8_t> { 3 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 243 }, std::vector<std::uint8_t> { 9 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 243 }, std::vector<std::uint8_t> { 27 }, std::vector<std::uint8_t> { 0 }),

        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 2 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 4 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 8 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 16 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 32 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 64 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 128 }, std::vector<std::uint8_t> { 0 }),

        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 2 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 0, 255 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0 }),

        std::make_tuple(std::vector<std::uint8_t> { 30 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 31 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 32 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 2 }),
        std::make_tuple(std::vector<std::uint8_t> { 33 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 3 }),
        std::make_tuple(std::vector<std::uint8_t> { 34 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 4 }),
        std::make_tuple(std::vector<std::uint8_t> { 35 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 5 }),
        std::make_tuple(std::vector<std::uint8_t> { 36 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 6 }),
        std::make_tuple(std::vector<std::uint8_t> { 37 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 7 }),
        std::make_tuple(std::vector<std::uint8_t> { 38 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 8 }),
        std::make_tuple(std::vector<std::uint8_t> { 39 }, std::vector<std::uint8_t> { 10 }, std::vector<std::uint8_t> { 9 }),

        std::make_tuple(std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 0 }),
        std::make_tuple(std::vector<std::uint8_t> { 1, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 1 }),
        std::make_tuple(std::vector<std::uint8_t> { 10, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 10 }),
        std::make_tuple(std::vector<std::uint8_t> { 100, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 100 }),
        std::make_tuple(std::vector<std::uint8_t> { 200, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 200 }),
        std::make_tuple(std::vector<std::uint8_t> { 255, 1 }, std::vector<std::uint8_t> { 0, 1 }, std::vector<std::uint8_t> { 255 })

        // clang-format on
        ));
