#include "gtest/gtest.h"

#include "core/edges/edge.hpp"

namespace graphcpp::testing 
{
	class EdgeTests : public ::testing::Test
	{
	protected:
		EdgeTests() :
			edge(std::make_unique<Edge>(1, 10, 3))
		{
		}
		
		std::unique_ptr<Edge> edge;
	};

	TEST_F(EdgeTests, GettersTest)
	{
		EXPECT_EQ(edge->v1(), 1);
		EXPECT_EQ(edge->v2(), 10);
		EXPECT_EQ(edge->weight, 3);
	}

	TEST_F(EdgeTests, EqualityEdges)
	{
		Edge equal_edge(1, 10, 3);
		Edge first_vertex_different(4, 10, 3);
		Edge second_vertex_different(1, 9, 3);
		Edge weight_different(1, 10, 2);

		EXPECT_EQ(*edge, *edge);
		EXPECT_EQ(*edge, equal_edge);
		EXPECT_NE(*edge, first_vertex_different);
		EXPECT_NE(*edge, second_vertex_different);
		EXPECT_NE(*edge, weight_different);
	}
}
