#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit.tests/macroses.hpp"
#include "unit.tests/utils/comparators.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

#ifdef USE_UTILS_TESTS
	TEST(UtilsTests, ToTranspositionTest)
	{
		std::vector<msize> permutation{ 8,2,7,6,3,5,4,9,0,1 };
		std::vector<std::pair<msize, msize>> expected_transpositions =
		{
			{ 1,2 },
			{ 1,7 },
			{ 1,9 },
			{ 3,6 },
			{ 3,4 },
			{ 0,8 }
		};

		EXPECT_TRUE(compare_vectors_without_order(expected_transpositions, to_transpositions(permutation)));
	}
#endif // USE_UTILS_TESTS

