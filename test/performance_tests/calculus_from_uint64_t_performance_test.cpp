#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <benchmark/benchmark.h>

static void BM_AllOperators_from_uint64_t(benchmark::State& state)
{
    api::API const api_1 { api::from_uint64(std::numeric_limits<std::uint64_t>::max()) };
    api::API api_2 { api::from_uint64(std::numeric_limits<std::uint64_t>::max()) };

    for (auto _ : state) {
        for (auto i = 0; i != state.range(0); ++i) {

            api_2 = api_1 * api_2;
            api_2 = api_1 + api_2;

            auto const result = api_2 % api_1;
            auto const result_2 = api_2 / result;

            std::string const str = api_2.to_string();
        }
    }
}

BENCHMARK(BM_AllOperators_from_uint64_t)
    ->Unit(benchmark::kMillisecond)
    ->RangeMultiplier(2)
    ->Range(2, 6);
