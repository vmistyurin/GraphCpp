#include "unit.tests/macroses.hpp"
#include "core/utils.hpp"
#include "gtest/gtest.h"

using namespace graphcpp;

#ifdef USE_UTILS_TESTS
	TEST(UtilsTests, CheckSymmetricalMatrixTests)
	{
		const std::vector<std::vector<mcontent>> symmetrical_matrix
		{ { 0, 1, 5 },
		{ 1, 0, 0 },
		{ 5, 0, 0 } };

		const std::vector<std::vector<mcontent>> x_dimensional_non_symmetrical_matrix
		{ { 0, 1, 5 },
		{ 1, 0, 0, 5 },
		{ 5, 0, 0 } };

		const std::vector<std::vector<mcontent>> y_dimensional_non_symmetrical_matrix
		{ { 0, 1, 5 },
		{ 1, 0, 0 },
		{ 5, 0, 0 },
		{ 0, 0, 0 } };

		const std::vector<std::vector<mcontent>> content_non_symmetrical_matrix
		{ { 0, 1, 5 },
		{ 1, 0, 3 },
		{ 5, 4, 0 } };

		EXPECT_TRUE(check_symmetrical_matrix(symmetrical_matrix));
		EXPECT_FALSE(check_symmetrical_matrix(x_dimensional_non_symmetrical_matrix));
		EXPECT_FALSE(check_symmetrical_matrix(y_dimensional_non_symmetrical_matrix));
		EXPECT_FALSE(check_symmetrical_matrix(content_non_symmetrical_matrix));
	}
#endif // USE_UTILS_TESTS

