#include "unit.tests/utils/comparators.h"
#include "gtest/gtest.h"

using namespace graphcpp_testing;

TEST(VectorOfEdgesComparator, VectorOfEdgesEquality)
{
    std::vector<Edge> v1 
	{ Edge(1,2,2),
      Edge(4,5,1),
      Edge(2,4,1) };
    std::vector<Edge> v2 
	{ Edge(4,5,1),
	  Edge(1,2,2),
      Edge(2,4,1) };

    EXPECT_TRUE(IsVectorOfEdgesAreEqual(v1,v2));
}

TEST(VectorOfEdgesComparator, VectorOfEdgesNonEquality)
{
    std::vector<Edge> tested_list 
	{ Edge(1,2,2),
	  Edge(4,5,1),
	  Edge(4,2,1) };

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
	{Edge(1,2,2),
	 Edge(4,5,2) };

    EXPECT_FALSE(IsVectorOfEdgesAreEqual(tested_list, different_weight));
    EXPECT_FALSE(IsVectorOfEdgesAreEqual(tested_list, different_node));
    EXPECT_FALSE(IsVectorOfEdgesAreEqual(tested_list, more_edges));
	EXPECT_FALSE(IsVectorOfEdgesAreEqual(tested_list, less_edges));
}