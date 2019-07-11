#include <iostream>
#include "gtest/gtest.h"
#include "cpp.h"
#include "riir.h"

using namespace std;

// Tests that two plus two is four.
TEST(Fibonacci, CPPFib40) {
	// SETUP PHASE
	int n = 40;
	int expected_result = 102334155;
	// RUN PHASE
	int actual_result = cpp_fibonacci(n);
	// ASSERT PHASE
  	ASSERT_EQ(actual_result, expected_result); // fib(40) is supposed to be 102334155
}

// Tests that two plus two is four in Rust.
TEST(Fibonacci, RustFib40) {
	// SETUP PHASE
	int n = 40;
	int expected_result = 102334155;
	// RUN PHASE
	int actual_result = rust_fibonacci(n);
	// ASSERT PHASE
    ASSERT_EQ(actual_result, expected_result); // fib(40) is supposed to be 102334155
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}