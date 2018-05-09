#include "gtest/gtest.h"

#include "core/all.hpp"

using namespace graphcpp;

class SymmetricalEdgeTests : public ::testing::Test 
{
protected:
	static void SetUpTestCase() 
	{
	}
};

TEST_F(SymmetricalEdgeTests, GettersTest)
{
	SymmetricalEdge edge(1, 10, 3);

	EXPECT_EQ(1, edge.v1());
	EXPECT_EQ(10, edge.v2());
	EXPECT_EQ(3, edge.weight);
}
TEST_F(SymmetricalEdgeTests, InvertEdge)
{
	SymmetricalEdge edge(10, 3, 1);

	EXPECT_EQ(edge.v1(), 3);
	EXPECT_EQ(edge.v2(), 10);
	EXPECT_EQ(edge.weight, 1);
}

TEST_F(SymmetricalEdgeTests, EqualityEdges)
{
	SymmetricalEdge edge(3, 10, 1);
	SymmetricalEdge equal_edge(3, 10, 1);
	SymmetricalEdge first_vertex_different(4, 10, 1);
	SymmetricalEdge second_vertex_different(3, 9, 1);
	SymmetricalEdge weight_different(3, 10, 2);

	EXPECT_EQ(edge, edge);
	EXPECT_EQ(edge, equal_edge);
	EXPECT_NE(edge, first_vertex_different);
	EXPECT_NE(edge, second_vertex_different);
	EXPECT_NE(edge, weight_different);
}