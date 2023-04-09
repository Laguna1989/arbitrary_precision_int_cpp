#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <benchmark/benchmark.h>

static void BM_ToString(benchmark::State& state)
{
    std::vector<std::uint16_t> data1;
    data1.resize(static_cast<std::size_t>(state.range(0)), 123u);
    for (auto _ : state) {
        // construction is done inside the loop because the API class caches the to_string result
        api::API const api_1 { data1 };
        auto const result = api_1.to_string();
    }
}

static void BM_ToExpString(benchmark::State& state)
{
    std::vector<std::uint16_t> data1;
    data1.resize(static_cast<std::size_t>(state.range(0)), 123u);
    for (auto _ : state) {
        // construction is done inside the loop because the API class caches the to_exp_string
        // result
        api::API const api_1 { data1 };
        auto const result = api_1.to_exp_string();
    }
}

BENCHMARK(BM_ToString)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->Range(2, 200);
BENCHMARK(BM_ToExpString)->Unit(benchmark::kMillisecond)->RangeMultiplier(2)->Range(2, 200);
