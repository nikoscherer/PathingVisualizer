#include "Test.h"

bool Test::TEST(int value, int expected) {
	if (value == expected) return true;

	std::cout << "Test Error! Test Expected: " << expected << "   But returned: " << value << "!" << std::endl;

	return false;
}