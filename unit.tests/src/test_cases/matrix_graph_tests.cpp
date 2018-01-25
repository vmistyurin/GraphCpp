#include "unit.tests/utils/comparators.h"
#include "core/GraphImplementation/matrix_graph.h"
#include "core/MatrixImplementation/full_symmetric_matrix.h"
#include "gtest/gtest.h"
#include <memory>

using namespace graphcpp_testing;

class MatrixGraphTests : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		edges = std::vector<Edge>
		{ Edge(0,6,2),
			Edge(3,6,1),
			Edge(4,6,2),
			Edge(1,5,7),
			Edge(3,4,10) };

		tested_graph = MatrixGraph<FullSymmetricMatrix>(edges, 7);
		linked_with_third = { 4,6 };
		degrees = { 1,1,0,2,2,1,3 };
    }
	MatrixGraph<FullSymmetricMatrix> tested_graph;
    std::vector<Edge> edges;
    std::vector<msize> linked_with_third;
    std::vector<msize> degrees;

};

TEST_F(MatrixGraphTests, GetLinkedVertexesTest)
{
    EXPECT_EQ(linked_with_third, tested_graph.get_linked_vertexes(3));
}

TEST_F(MatrixGraphTests, GetEdgesTest)
{
    EXPECT_TRUE(AreVectorsOfEdgesEqual(edges, tested_graph.get_edges()));
}

TEST_F(MatrixGraphTests, GetVertexesDegreeTest)
{
    EXPECT_EQ(degrees, tested_graph.get_degrees());
}

TEST_F(MatrixGraphTests, GetVertexDegreeTest)
{
    EXPECT_EQ(degrees[0], tested_graph.get_degree(0));
    EXPECT_EQ(degrees[5], tested_graph.get_degree(5));
}

TEST_F(MatrixGraphTests, EqualityTest)
{
	std::vector<Edge> same_edges
	{ 
		Edge(0,6,2),
		Edge(3,6,1),
		Edge(4,6,2),
		Edge(1,5,7),
		Edge(3,4,10) 
	};
	MatrixGraph<> same_edges_graph(same_edges, 7);

    std::vector<Edge> equal_edges
    {
        Edge(1,5,2),
        Edge(4,5,2),
        Edge(2,4,10),
        Edge(2,5,1),
        Edge(3,6,7)
    };
    MatrixGraph<> equal_graph(equal_edges, 7);

    std::vector<Edge> dimensional_non_equal_edges
    {
            Edge(1,5,2),
            Edge(4,5,2),
            Edge(2,4,10),
            Edge(2,5,1),
            Edge(3,6,7)
    };
    MatrixGraph<> dimensional_non_equal_graph(dimensional_non_equal_edges, 8);

    std::vector<Edge> different_degrees_non_equal_edges
    {
            Edge(1,5,2),
            Edge(4,5,3),
            Edge(1,4,10),
            Edge(2,5,1),
            Edge(3,5,7)
    };
    MatrixGraph<> different_degrees_non_equal_graph(different_degrees_non_equal_edges, 7);

	std::vector<Edge> different_edges_non_equal_edges
	{
		Edge(1,5,2),
		Edge(2,6,3),
		Edge(3,4,10),
		Edge(3,5,1),
		Edge(2,5,7)
	};
	MatrixGraph<> different_edges_non_equal_graph(different_edges_non_equal_edges, 7);

    EXPECT_TRUE(tested_graph.equal(tested_graph));
	EXPECT_TRUE(tested_graph.equal(same_edges_graph));
    EXPECT_TRUE(tested_graph.equal(equal_graph));
    EXPECT_FALSE(tested_graph.equal(dimensional_non_equal_graph));
	EXPECT_FALSE(tested_graph.equal(different_degrees_non_equal_graph));
    EXPECT_FALSE(tested_graph.equal(different_edges_non_equal_graph));
}

TEST_F(MatrixGraphTests, DeleteVertexesTest1)
{
    std::vector<Edge> expected_edges = std::vector<Edge>
    { Edge(0,1,2),
      Edge(2,3,7) };
    msize expected_dimension = 5;
	MatrixGraph<FullSymmetricMatrix> expected_graph(expected_edges, expected_dimension);

    std::vector<msize> deleted_vertexes{3,4};
    tested_graph.delete_vertexes(deleted_vertexes);

    EXPECT_TRUE(expected_graph.equal(tested_graph));
}

TEST_F(MatrixGraphTests, DeleteVertexesTest2)
{
	std::vector<Edge> expected_edges = std::vector<Edge>
	{ Edge(1,2,10) };
	msize expected_dimension = 4;
	MatrixGraph<FullSymmetricMatrix> expected_graph(expected_edges, expected_dimension);

	std::vector<msize> deleted_vertexes{1,5,6};
	tested_graph.delete_vertexes(deleted_vertexes);

	EXPECT_TRUE(expected_graph.equal(tested_graph));
}