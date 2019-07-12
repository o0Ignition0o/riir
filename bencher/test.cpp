#include <iostream>
#include "gtest/gtest.h"
#include "cpp.h"
#include "riir.h"

using namespace std;

TEST(ToLowerTest, ValidUpperCaseCharacter) {
	// SETUP PHASE
	char c = 'C';
	char expected_result = 'c';

	// RUN PHASE
	ToLower(c);

	// ASSERT PHASE
    ASSERT_EQ(c, expected_result);
}

TEST(ToLowerTest, ValidLowerCaseCharacter) {
	// SETUP PHASE
	char c = 'e';
	char expected_result = 'e';

	// RUN PHASE
	ToLower(c);

	// ASSERT PHASE
    ASSERT_EQ(c, expected_result);
}

TEST(ToLowerTest, InvalidCharacter) {
	// SETUP PHASE
	char c = '1';
	char expected_result = '1';

	// RUN PHASE
	ToLower(c);

	// ASSERT PHASE
    ASSERT_EQ(c, expected_result);
}

TEST(RustToLowerTest, ValidUpperCaseCharacter) {
	// SETUP PHASE
	char c = 'C';
	char expected_result = 'c';

	// RUN PHASE
	to_lower(c);

	// ASSERT PHASE
    ASSERT_EQ(c, expected_result);
}

TEST(RustToLowerTest, ValidLowerCaseCharacter) {
	// SETUP PHASE
	char c = 'e';
	char expected_result = 'e';

	// RUN PHASE
	to_lower(c);

	// ASSERT PHASE
    ASSERT_EQ(c, expected_result);
}

TEST(RustToLowerTest, InvalidCharacter) {
	// SETUP PHASE
	char c = '1';
	char expected_result = '1';

	// RUN PHASE
	to_lower(c);

	// ASSERT PHASE
    ASSERT_EQ(c, expected_result);
}

TEST(ToLowerCase, HeLlOWoRlD) {
	char actual_slice[] = { 'H', 'e', 'L', 'l', 'O', ' ', 'W', 'o', 'R', 'l', 'D' , '\0'};
	char expected_slice[] = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0' };
	int len = strlen(actual_slice);

	net_to_lower_case(actual_slice, len);
	ASSERT_STREQ(actual_slice, expected_slice);
}

TEST(ToLowerCase, NullPtr) {
	char* actual_slice = nullptr;
	int len = 20;

	net_to_lower_case(actual_slice, len);
	// ASSERT_STREQ(actual_slice, actual_slice);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}