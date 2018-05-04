#include "gtest/gtest.h"

#include "core/all.hpp"

using namespace graphcpp;

class EdgeTests : public ::testing::Test
{
protected:
	static void SetUpTestCase()
	{
	}
};

TEST_F(EdgeTests, GettersTest)
{
	Edge edge(1, 10, 3);

	EXPECT_EQ(1, edge.v1());
	EXPECT_EQ(10, edge.v2());
	EXPECT_EQ(3, edge.weight);
}

TEST_F(EdgeTests, EqualityEdges)
{
	Edge edge(3, 10, 1);
	Edge equal_edge(3, 10, 1);
	Edge first_vertex_different(4, 10, 1);
	Edge second_vertex_different(3, 9, 1);
	Edge weight_different(3, 10, 2);

	EXPECT_EQ(edge, edge);
	EXPECT_EQ(edge, equal_edge);
	EXPECT_NE(edge, first_vertex_different);
	EXPECT_NE(edge, second_vertex_different);
	EXPECT_NE(edge, weight_different);
}