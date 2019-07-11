#include <iostream>
#include "gtest/gtest.h"
#include "cpp.h"

using namespace std;

// Tests that two plus two is four.
TEST(Fibonacci, Fib40) {
	int n = 40;
	int expected_result = 102334155;

	int actual_result = cpp_fibonacci(n);

  	ASSERT_EQ(actual_result, expected_result); // fib(40) is supposed to be 102334155
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}