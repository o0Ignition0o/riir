#include <iostream>
#include <benchmark/benchmark.h>
#include "riir.h"
#include "cpp.h"
#include <string.h>

using namespace std;

static void CPPToLowerCase(benchmark::State& state) {
	char c = 'C';

	while (state.KeepRunning())
		ToLower(c);

}

static void RustToLowerCase(benchmark::State& state) {
	char c = 'C';

	while (state.KeepRunning())
		to_lower(c);

}

static void CPPToLowerCaseString(benchmark::State& state) {
	char actual_slice[] = { 'H', 'e', 'L', 'l', 'O', ' ', 'W', 'o', 'R', 'l', 'D' , '\0'};
	size_t len = strlen(actual_slice);

	while (state.KeepRunning())
		net_ToLowerCase(actual_slice, len);

}

static void RustToLowerCaseString(benchmark::State& state) {
	char actual_slice[] = { 'H', 'e', 'L', 'l', 'O', ' ', 'W', 'o', 'R', 'l', 'D' , '\0'};
	size_t len = strlen(actual_slice);

	while (state.KeepRunning())
		net_to_lower_case(actual_slice, len);

}

BENCHMARK(RustToLowerCase);
BENCHMARK(CPPToLowerCase);
BENCHMARK(RustToLowerCaseString);
BENCHMARK(CPPToLowerCaseString);


BENCHMARK_MAIN();