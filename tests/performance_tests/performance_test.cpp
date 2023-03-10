#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <benchmark/benchmark.h>

static void BM_Addition(benchmark::State& state)
{
    std::vector<std::uint8_t> data1;
    data1.resize(static_cast<std::size_t>(state.range(0)), 123u);

    std::vector<std::uint8_t> data2;
    data2.resize(static_cast<std::size_t>(state.range(1)), 123u);
    api::API const api_1 { data1 };
    api::API const api_2 { data2 };
    for (auto _ : state) {
        auto const result = api_1 + api_2;
    }
}

BENCHMARK(BM_Addition)
    ->Unit(benchmark::kMillisecond)
    ->ArgsProduct({ benchmark::CreateRange(100, 1600, /*multi=*/4),
        benchmark::CreateRange(100, 1600, /*multi=*/4) });

static void BM_Subtraction(benchmark::State& state)
{
    std::vector<std::uint8_t> data1;
    data1.resize(static_cast<std::size_t>(state.range(0)), 123u);

    std::vector<std::uint8_t> data2;
    data2.resize(static_cast<std::size_t>(state.range(1)), 123u);
    api::API const api_1 { data1 };
    api::API const api_2 { data2 };
    for (auto _ : state) {
        auto const result = api_1 - api_2;
    }
}

BENCHMARK(BM_Subtraction)
    ->Unit(benchmark::kMillisecond)
    ->ArgsProduct({ benchmark::CreateRange(100, 1600, /*multi=*/4),
        benchmark::CreateRange(100, 1600, /*multi=*/4) });

static void BM_Multiplication(benchmark::State& state)
{
    std::vector<std::uint8_t> data1;
    data1.resize(static_cast<std::size_t>(state.range(0)), 123u);

    std::vector<std::uint8_t> data2;
    data2.resize(static_cast<std::size_t>(state.range(1)), 123u);
    api::API const api_1 { data1 };
    api::API const api_2 { data2 };
    for (auto _ : state) {
        auto const result = api_1 * api_2;
    }
}

BENCHMARK(BM_Multiplication)
    ->Unit(benchmark::kMillisecond)
    ->ArgsProduct({ benchmark::CreateRange(2, 100, /*multi=*/4),
        benchmark::CreateRange(2, 100, /*multi=*/4) });

static void BM_Division(benchmark::State& state)
{
    std::vector<std::uint8_t> data1;
    data1.resize(static_cast<std::size_t>(state.range(0)), 123u);

    std::vector<std::uint8_t> data2;
    data2.resize(static_cast<std::size_t>(state.range(1)), 123u);
    api::API const api_1 { data1 };
    api::API const api_2 { data2 };
    for (auto _ : state) {
        auto const result = api_1 / api_2;
    }
}

BENCHMARK(BM_Division)
    ->Unit(benchmark::kMillisecond)
    ->ArgsProduct({ benchmark::CreateRange(2, 100, /*multi=*/4),
        benchmark::CreateRange(2, 100, /*multi=*/4) });
