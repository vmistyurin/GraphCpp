#include "core/utils.h"
#include "gtest/gtest.h"

using namespace graphcpp;

namespace
{
	bool equal_permutaions(const std::vector<std::pair<msize, msize>>& first, const std::vector<std::pair<msize, msize>>& second)
	{
		RETURN_IF(first.size() != second.size(), false);
		for (std::vector<std::pair<msize, msize>>::size_type i = 0; i < first.size(); i++)
		{
			RETURN_IF(std::find(first.cbegin(), first.cend(), second[i]) == first.cend(), false);
			RETURN_IF(std::find(second.cbegin(), second.cend(), first[i]) == second.cend(), false);
		}
		return true;
	}
}

TEST(UtilsTests, ToTranspositionTest)
{
	std::vector<msize> permutation{ 8,2,7,6,3,5,4,9,0,1 };
	std::vector<std::pair<msize,msize>> expected_transpositions =
	{
		{1,2},
		{1,7},
		{1,9},
		{3,6},
		{3,4},
		{0,8}
	};

	EXPECT_TRUE(equal_permutaions(expected_transpositions, to_transpositions(permutation)));
}