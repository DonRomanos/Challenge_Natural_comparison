#pragma once

#include "challenge.hpp"

#include "benchmark/benchmark.h"

// Benchmark factors I think can be considered
// string length
// how many numbers
// how many letters
// --> compare strings of length 2 - 1024 always same content, once with numbers only, once with letters only.

/***************************************************************/

template <char Character, ChallengeSignature T> void BM_Comparison_of_character(benchmark::State& state)
{
    std::string s1( state.range(0), Character);
    std::string s2( state.range(0), Character);
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(T(s1,s2));
    }
    state.SetComplexityN(state.range(0));
}

/***************************************************************/
#ifdef BUILD_REFERENCE
BENCHMARK_TEMPLATE(BM_Comparison_of_character, 'a', reference::natural_compare)->RangeMultiplier(2)->Range(2, 2 << 10)->Complexity();
BENCHMARK_TEMPLATE(BM_Comparison_of_character, '1', reference::natural_compare)->RangeMultiplier(2)->Range(2, 2 << 10)->Complexity();
#endif
BENCHMARK_TEMPLATE(BM_Comparison_of_character, 'a', natural_compare)->RangeMultiplier(2)->Range(2, 2 << 10)->Complexity();
BENCHMARK_TEMPLATE(BM_Comparison_of_character, '1', natural_compare)->RangeMultiplier(2)->Range(2, 2 << 10)->Complexity();

BENCHMARK_MAIN();