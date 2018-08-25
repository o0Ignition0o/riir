#include <iostream>
#include <benchmark/benchmark.h>
#include "riir.h"
#include "cpp.h"

using namespace std;

static void CPPIsValidIPV4LocalHost(benchmark::State& state) {
    const char ip[] = { '1', '2', '7', '.', '0', '.', '0', '.', '1', '\0' };
    while (state.KeepRunning())
        benchmark::DoNotOptimize(net_IsValidIPv4Addr(ip, 9));
}

static void CPPIsValidIPV48888(benchmark::State& state) {
	char ip[] = { '8','.','8','.','8','.','8','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(net_IsValidIPv4Addr(ip, 7));
}

static void CPPIsValidIPV40000(benchmark::State& state) {
	char ip[] = { '0','.','0','.','0','.','0','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(net_IsValidIPv4Addr(ip, 7));
}

static void CPPIsValidIPV4FullDigits(benchmark::State& state) {
	char ip[] = { '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(net_IsValidIPv4Addr(ip, 15));
}

static void CPPIsValidIPV4EarlyFail(benchmark::State& state) {
	char ip[] = { '.', '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(net_IsValidIPv4Addr(ip, 16));
}

static void CPPIsValidIPV4LateFail(benchmark::State& state) {
	char ip[] = { '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7', '2', '\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(net_IsValidIPv4Addr(ip, 16));
}

static void RustIsValidIPV4LocalHost(benchmark::State& state) {
	const char ip[] = { '1','2','7','.','0','.','0','.','1','\0' };

	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr(ip, 9));
}

static void RustIsValidIPV40000(benchmark::State &state) {
	char ip[] = { '0','.','0','.','0','.','0','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr(ip, 7));
}


static void RustIsValidIPV48888(benchmark::State &state) {
	char ip[] = { '8','.','8','.','8','.','8','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr(ip, 7));
}

static void RustIsValidIPV4FullDigits(benchmark::State& state) {
	char ip[] = { '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7','\0' };

	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr(ip, 15));
}

static void RustIsValidIPV4EarlyFail(benchmark::State& state) {
	char ip[] = { '.', '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr(ip, 16));
}

static void RustIsValidIPV4LateFail(benchmark::State& state) {
	char ip[] = { '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7', '2', '\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr(ip, 16));
}


static void RustIsValidIPV4LocalHostReadable(benchmark::State& state) {
	const char ip[] = { '1','2','7','.','0','.','0','.','1','\0' };

	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr_readable(ip, 9));
}

static void RustIsValidIPV40000Readable(benchmark::State &state) {
	char ip[] = { '0','.','0','.','0','.','0','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr_readable(ip, 7));
}


static void RustIsValidIPV48888Readable(benchmark::State &state) {
	char ip[] = { '8','.','8','.','8','.','8','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr_readable(ip, 7));
}

static void RustIsValidIPV4FullDigitsReadable(benchmark::State& state) {
	char ip[] = { '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7','\0' };

	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr_readable(ip, 15));
}

static void RustIsValidIPV4EarlyFailReadable(benchmark::State& state) {
	char ip[] = { '.', '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7','\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr_readable(ip, 16));
}

static void RustIsValidIPV4LateFailReadable(benchmark::State& state) {
	char ip[] = { '1','9','2','.','1','6','8','.','1','2','0','.','1','9','7', '2', '\0' };
	while (state.KeepRunning())
		benchmark::DoNotOptimize(rust_net_is_valid_ipv4_addr_readable(ip, 16));
}

// Register the functions as a benchmark
BENCHMARK(CPPIsValidIPV4LocalHost);
BENCHMARK(CPPIsValidIPV40000);
BENCHMARK(CPPIsValidIPV48888);
BENCHMARK(CPPIsValidIPV4FullDigits);
BENCHMARK(CPPIsValidIPV4EarlyFail);
BENCHMARK(CPPIsValidIPV4LateFail);

BENCHMARK(RustIsValidIPV4LocalHost);
BENCHMARK(RustIsValidIPV40000);
BENCHMARK(RustIsValidIPV48888);
BENCHMARK(RustIsValidIPV4FullDigits);
BENCHMARK(RustIsValidIPV4EarlyFail);
BENCHMARK(RustIsValidIPV4LateFail);

BENCHMARK(RustIsValidIPV4LocalHostReadable);
BENCHMARK(RustIsValidIPV40000Readable);
BENCHMARK(RustIsValidIPV48888Readable);
BENCHMARK(RustIsValidIPV4FullDigitsReadable);
BENCHMARK(RustIsValidIPV4EarlyFailReadable);
BENCHMARK(RustIsValidIPV4LateFailReadable);

BENCHMARK_MAIN();