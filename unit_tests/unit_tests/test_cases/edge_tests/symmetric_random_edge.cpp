#include "gtest/gtest.h"

#include "core/all.hpp"

using namespace graphcpp;

class SymmetricRandomEdgeTests : public ::testing::Test
{
protected:
    SymmetricRandomEdgeTests() :
        edge(std::make_unique<SymmetricRandomEdge>(SymmetricEdge(1, 10, 3), 0.75))
    {
    }
    
    std::unique_ptr<SymmetricRandomEdge> edge;
};

TEST_F(SymmetricRandomEdgeTests, InvertTest)
{
    auto edge = SymmetricRandomEdge(SymmetricEdge(10, 1, 5), 0.75);

    EXPECT_EQ(edge.v1(), 1);
    EXPECT_EQ(edge.v2(), 10);
}

TEST_F(SymmetricRandomEdgeTests, GettersTest)
{
    EXPECT_EQ(edge->v1(), 1);
    EXPECT_EQ(edge->v2(), 10);
    EXPECT_EQ(edge->weight(), 3);
    EXPECT_TRUE(are_doubles_equal(edge->probability(), 0.75));
}

TEST_F(SymmetricRandomEdgeTests, EqualityEdges)
{
    SymmetricRandomEdge equal_edge(SymmetricEdge(1, 10, 3), 0.75);
    SymmetricRandomEdge first_vertex_different(SymmetricEdge(4, 10, 1), 0.75);
    SymmetricRandomEdge second_vertex_different(SymmetricEdge(3, 9, 1), 0.75);
    SymmetricRandomEdge weight_different(SymmetricEdge(3, 10, 2), 0.75);
    SymmetricRandomEdge probability_different(SymmetricEdge(3, 10, 1), 0.5);

    EXPECT_EQ(*edge, *edge);
    EXPECT_EQ(*edge, equal_edge);
    EXPECT_NE(*edge, first_vertex_different);
    EXPECT_NE(*edge, second_vertex_different);
    EXPECT_NE(*edge, weight_different);
    EXPECT_NE(*edge, probability_different);
}
