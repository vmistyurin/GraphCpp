#include "unit.tests/macroses.hpp"
#include "unit.tests/utils/comparators.hpp"
#include "core/edge.hpp"
#include "gtest/gtest.h"

using namespace graphcpp;
using namespace graphcpp_testing;

#ifdef USE_HELPERS_TESTS
	TEST(HelpersTests, CompareVectorsOfIntWithoutOrder)
	{
		std::vector<int> test_vector = { 1,2,3,4,5 };
		std::vector<int> permutated_test_vector = { 1,2,4,5,3 };
		std::vector<int> different_size = { 1,2,3,4 };
		std::vector<int> different_content = { 1,2,3,4,6 };
		
		EXPECT_TRUE(compare_vectors_without_order(test_vector, test_vector));
		EXPECT_TRUE(compare_vectors_without_order(test_vector, permutated_test_vector));
		EXPECT_FALSE(compare_vectors_without_order(test_vector, different_size));
		EXPECT_FALSE(compare_vectors_without_order(test_vector, different_content));
	}

	TEST(HelpersTests, CompareVectorsOfEdgesWithoutOrder)
	{
		std::vector<Edge> test_vector
		{ Edge(1,2,2),
			Edge(4,5,1),
			Edge(2,4,1) };

		std::vector<Edge> equal_to_test_vector
		{ Edge(4,5,1),
			Edge(1,2,2),
			Edge(2,4,1) };

		std::vector<Edge> different_weight
		{ Edge(1,2,2),
			Edge(4,5,2),
			Edge(4,2,1) };

		std::vector<Edge> different_node
		{ Edge(1,2,2),
			Edge(4,5,2),
			Edge(4,2,1) };

		std::vector<Edge> more_edges
		{ Edge(1,2,2),
			Edge(4,5,1),
			Edge(4,2,1),
			Edge(5,6,5) };

		std::vector<Edge> less_edges
		{ Edge(1,2,2),
			Edge(4,5,2) };

		EXPECT_TRUE(compare_vectors_without_order(test_vector, equal_to_test_vector));
		EXPECT_FALSE(compare_vectors_without_order(test_vector, different_weight));
		EXPECT_FALSE(compare_vectors_without_order(test_vector, different_node));
		EXPECT_FALSE(compare_vectors_without_order(test_vector, more_edges));
		EXPECT_FALSE(compare_vectors_without_order(test_vector, less_edges));
	}

	TEST(HelpersTests, CompareListsWithoutOrder)
	{
		std::list<int> test_list = { 1,2,3,4,5 };
		std::list<int> permutated_test_list = { 1,2,4,5,3 };
		std::list<int> different_size = { 1,2,3,4 };
		std::list<int> different_content = { 1,2,3,4,6 };

		EXPECT_TRUE(compare_lists_without_order(test_list, test_list));
		EXPECT_TRUE(compare_lists_without_order(test_list, permutated_test_list));
		EXPECT_FALSE(compare_lists_without_order(test_list, different_size));
		EXPECT_FALSE(compare_lists_without_order(test_list, different_content));
	}
#endif // USE_HELPERS_TESTS

