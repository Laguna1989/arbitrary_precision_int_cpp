#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <benchmark/benchmark.h>

static void BM_Multiplication(benchmark::State& state)
{
    std::vector<std::uint8_t> data1;
    data1.resize(state.range(0), 123u);

    std::vector<std::uint8_t> data2;
    data2.resize(state.range(1), 123u);
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
