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
	ASSERT_DEATH({Edge edge(2, 2);}, "");
}

TEST_F(EdgeTests, InvertEdge)
{
	Edge edge(10, 3);

	EXPECT_EQ(edge.v1(), 3);
	EXPECT_EQ(edge.v2(), 10);
}

TEST_F(EdgeTests, EqualityEdges)
{
	Edge e1(3, 10);
	Edge e2(10, 3);
	Edge e3(3, 9);

	EXPECT_EQ(e1, e2);
	EXPECT_NE(e1, e3);
}