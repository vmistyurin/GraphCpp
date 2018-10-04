#include "gtest/gtest.h"

#include "core/all.hpp"

using namespace graphcpp;

class SymmetricalEdgeTests : public ::testing::Test 
{
protected:
	std::unique_ptr<SymmetricalEdge> edge;

	void SetUp() override
	{
		edge = std::make_unique<SymmetricalEdge>(1, 10, 3);
	}
};

TEST_F(SymmetricalEdgeTests, GettersTest)
{
	EXPECT_EQ(edge->v1(), 1);
	EXPECT_EQ(edge->v2(), 10);
	EXPECT_EQ(edge->weight, 3);
}

TEST_F(SymmetricalEdgeTests, InvertEdge)
{
	SymmetricalEdge edge(10, 1, 3);

	EXPECT_EQ(edge.v1(), 1);
	EXPECT_EQ(edge.v2(), 10);
	EXPECT_EQ(edge.weight, 3);
}

TEST_F(SymmetricalEdgeTests, EqualityEdges)
{
	SymmetricalEdge equal_edge(1, 10, 3);
	SymmetricalEdge first_vertex_different(4, 10, 3);
	SymmetricalEdge second_vertex_different(1, 9, 3);
	SymmetricalEdge weight_different(1, 10, 5);

	EXPECT_EQ(*edge, *edge);
	EXPECT_EQ(*edge, equal_edge);
	EXPECT_NE(*edge, first_vertex_different);
	EXPECT_NE(*edge, second_vertex_different);
	EXPECT_NE(*edge, weight_different);
}