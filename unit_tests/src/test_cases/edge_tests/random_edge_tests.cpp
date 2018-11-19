#include "gtest/gtest.h"

#include "core/all.hpp"

using namespace graphcpp;

class RandomEdgeTests : public ::testing::Test
{
protected:
    RandomEdgeTests() :
        edge(std::make_unique<RandomEdge>(Edge(1, 10, 3), 0.75))
    {
    }
    
    std::unique_ptr<RandomEdge> edge;
};

TEST_F(RandomEdgeTests, GettersTest)
{
    EXPECT_EQ(edge->v1(), 1);
    EXPECT_EQ(edge->v2(), 10);
    EXPECT_EQ(edge->weight(), 3);
    EXPECT_TRUE(are_doubles_equal(edge->probability(), 0.75));
}

TEST_F(RandomEdgeTests, EqualityEdges)
{
    RandomEdge equal_edge(Edge(1, 10, 3), 0.75);
    RandomEdge first_vertex_different(Edge(4, 10, 1), 0.75);
    RandomEdge second_vertex_different(Edge(3, 9, 1), 0.75);
    RandomEdge weight_different(Edge(3, 10, 2), 0.75);
    RandomEdge probability_different(Edge(3, 10, 1), 0.5);

    EXPECT_EQ(*edge, *edge);
    EXPECT_EQ(*edge, equal_edge);
    EXPECT_NE(*edge, first_vertex_different);
    EXPECT_NE(*edge, second_vertex_different);
    EXPECT_NE(*edge, weight_different);
    EXPECT_NE(*edge, probability_different);
}
