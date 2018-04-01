#include "unit.tests/macroses.hpp"
#include "core/utils.hpp"
#include "gtest/gtest.h"

using namespace graphcpp;

#ifdef USE_UTILS_TESTS
	TEST(UtilsTests, IsPermutationTests)
	{
		std::vector<msize> permutation{ 1, 0, 2, 3, 4 };
		std::vector<msize> no_permutation{ 1, 1, 2, 3, 4 };

		EXPECT_TRUE(is_permutation(permutation));
		EXPECT_FALSE(is_permutation(no_permutation));
	}
#endif //USE_UTILS_TESTS