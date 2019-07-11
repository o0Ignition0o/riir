#include <iostream>
#include <benchmark/benchmark.h>
#include "riir.h"
#include "cpp.h"

using namespace std;

static void CPPFib40(benchmark::State& state) {
	int n = 40;
	while (state.KeepRunning())
		benchmark::DoNotOptimize(cpp_fibonacci(n));
}

static void RustFib40(benchmark::State& state) {
	int n = 40;
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_fibonacci(n));
}


BENCHMARK(CPPFib40);
BENCHMARK(RustFib40);


BENCHMARK_MAIN();