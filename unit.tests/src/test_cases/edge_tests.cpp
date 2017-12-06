#include "core/edge.h"
#include "gtest/gtest.h"

using namespace graphcpp;

class EdgeTests : public ::testing::Test 
{
protected:
	static void SetUpTestCase() 
	{
	}
};

TEST_F(EdgeTests, CreatingBadEdge)
{
	ASSERT_DEATH({Edge edge(2, 2, 1);}, "");
}

TEST_F(EdgeTests, GettersTest)
{
	Edge edge(1, 10, 3);

	EXPECT_EQ(1, edge.v1());
	EXPECT_EQ(10, edge.v2());
	EXPECT_EQ(3, edge.weight());
}
TEST_F(EdgeTests, InvertEdge)
{
	Edge edge(10, 3, 1);

	EXPECT_EQ(edge.v1(), 3);
	EXPECT_EQ(edge.v2(), 10);
}

TEST_F(EdgeTests, EqualityEdges)
{
	Edge e1(3, 10, 1);
	Edge e2(3, 10, 1);
	Edge e3(3, 9, 1);
	Edge e4(4, 10, 1);
	Edge e5(3, 10, 2);

	EXPECT_EQ(e1, e2);
	EXPECT_NE(e1, e3);
	EXPECT_NE(e1, e4);
	EXPECT_NE(e1, e5);
}