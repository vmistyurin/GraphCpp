#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/macroses.hpp"

using namespace graphcpp;

#ifdef USE_UTILS_TESTS
TEST(UtilsTests, ApplyPermutationWithTranspositionsTest)
{
	std::vector<mcontent> target = { 3, 4, 2, 10, 55 };
	const std::vector<msize> permutation = { 4, 3, 1, 0, 2 };
	const std::vector<mcontent> expected_vector = { 10, 2, 55, 4 ,3 };

	apply_permutation_with_transpositions(target, permutation);

	EXPECT_EQ(target, expected_vector);
}

TEST(UtilsTests, ApplyPermutationWithAlloc)
{
	const std::vector<mcontent> target = { 3, 4, 2, 10, 55 };
	const std::vector<msize> permutation = { 4, 3, 1, 0, 2 };
	const std::vector<mcontent> expected_vector = { 10, 2, 55, 4, 3 };

	const auto result = apply_permutation_alloc(target, permutation);

	EXPECT_EQ(result, expected_vector);
}
#endif // USE_UTILS_TESTS

