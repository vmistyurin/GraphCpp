#include "unit.tests/utils/comparators.h"
#include "core/GraphImplementation/graph_base.h"
#include "core/GraphImplementation/matrix_graph.h"
#include "core/MatrixImplementation/full_symmetric_matrix.h"
#include "core/MatrixImplementation/half_symmetric_matrix.h"
#include "gtest/gtest.h"
#include <memory>

using namespace graphcpp_testing;

namespace
{
	const std::vector<Edge> test_edges =
	{ 
		Edge(0,6,2),
		Edge(3,6,1),
		Edge(4,6,2),
		Edge(1,5,7),
		Edge(3,4,10) 
	};
	const msize test_dimension = 7;

	template<class T>
	std::unique_ptr<GraphBase> GetGraph(const std::vector<Edge>& edges, msize dimension);

	template<>
	std::unique_ptr<GraphBase> GetGraph<MatrixGraph<FullSymmetricMatrix>>(const std::vector<Edge>& edges, msize dimension)
	{
		return std::make_unique<MatrixGraph<FullSymmetricMatrix>>(edges, dimension);
	}

	template<>
	std::unique_ptr<GraphBase> GetGraph<MatrixGraph<HalfSymmetricMatrix>>(const std::vector<Edge>& edges, msize dimension)
	{
		return std::make_unique<MatrixGraph<HalfSymmetricMatrix>>(edges, dimension);
	}
}

template<class TestGraphType>
class GraphBaseTests : public ::testing::Test
{
protected:
	GraphBaseTests() :
		test_graph(GetGraph<TestGraphType>(test_edges, test_dimension))
	{
		degrees.resize(test_dimension);
		for (const auto& edge : test_edges)
		{
			degrees[edge.v1()]++;
			degrees[edge.v2()]++;
		}
	}
	std::unique_ptr<GraphBase> test_graph;
	std::vector<msize> degrees;

};

using GraphImplementations = testing::Types<MatrixGraph<FullSymmetricMatrix>, MatrixGraph<HalfSymmetricMatrix>>;
TYPED_TEST_CASE(GraphBaseTests, GraphImplementations);

TYPED_TEST(GraphBaseTests, GetDimensionTest)
{
	EXPECT_EQ(this->test_graph->dimension(), test_dimension);
}

TYPED_TEST(GraphBaseTests, GetLinkedVertexesTest)
{
	const msize test_vertex = 3;
	std::vector<msize> linked_with_test_vertex;
	for (const auto& edge : test_edges)
	{
		if (edge.v1() == test_vertex)
		{
			linked_with_test_vertex.push_back(edge.v2());
		}
		else if (edge.v2() == test_vertex)
		{
			linked_with_test_vertex.push_back(edge.v1());
		}
	}
	std::sort(linked_with_test_vertex.begin(), linked_with_test_vertex.end());

    EXPECT_EQ(this->test_graph->get_linked_vertexes(test_vertex), linked_with_test_vertex);
}

TYPED_TEST(GraphBaseTests, GetEdgesTest)
{
    EXPECT_TRUE(AreVectorsOfEdgesEqual(test_edges, this->test_graph->get_edges()));
}

TYPED_TEST(GraphBaseTests, GetVertexesDegreeTest)
{
    EXPECT_EQ(this->test_graph->get_degrees(), degrees);
}

TYPED_TEST(GraphBaseTests, GetVertexDegreeTests)
{
	const msize first_test_vertex = 0;
	const msize second_test_vertex = 5;

    EXPECT_EQ(this->test_graph->get_degree(first_test_vertex), degrees[first_test_vertex]);
    EXPECT_EQ(this->test_graph->get_degree(second_test_vertex), degrees[second_test_vertex]);
}

TYPED_TEST(GraphBaseTests, EqualityTest)
{
	TypeParam same_edges_graph(test_edges, test_dimension);


	std::vector<Edge> shuffled_edges = test_edges;
	std::swap(shuffled_edges[0], shuffled_edges[4]);
	std::swap(shuffled_edges[1], shuffled_edges[3]);
	TypeParam shuffled_edges_graph(shuffled_edges, 7);


    std::vector<Edge> equal_edges
    {
        Edge(1,5,2),
        Edge(4,5,2),
        Edge(2,4,10),
        Edge(2,5,1),
        Edge(3,6,7)
    };
	TypeParam equal_graph(equal_edges, test_dimension);


	TypeParam dimensional_non_equal_graph(test_edges, test_dimension + 1);


    std::vector<Edge> different_degrees_edges
    {
		Edge(1,5,2),
		Edge(4,5,3),
		Edge(1,4,10),
		Edge(2,5,1),
		Edge(3,5,7)
    };
	TypeParam different_degrees_graph(different_degrees_edges, test_dimension);


	std::vector<Edge> different_edges
	{
		Edge(1,5,2),
		Edge(2,6,3),
		Edge(3,4,10),
		Edge(3,5,1),
		Edge(2,5,7)
	};
	TypeParam different_edges_graph(different_edges, test_dimension);

	std::vector<Edge> different_weight_edges = test_edges;
	different_weight_edges[0].weight++;
	different_weight_edges[4].weight++;
	TypeParam different_weight_graph(different_weight_edges, test_dimension);

	EXPECT_TRUE(this->test_graph->equal(*test_graph));
	EXPECT_TRUE(this->test_graph->equal(same_edges_graph));
	EXPECT_TRUE(this->test_graph->equal(shuffled_edges_graph));
    EXPECT_TRUE(this->test_graph->equal(equal_graph));
    EXPECT_FALSE(this->test_graph->equal(dimensional_non_equal_graph));
	EXPECT_FALSE(this->test_graph->equal(different_degrees_graph));
    EXPECT_FALSE(this->test_graph->equal(different_edges_graph));
	EXPECT_FALSE(this->test_graph->equal(different_weight_graph));
}

TYPED_TEST(GraphBaseTests, DeleteVertexesTest1)
{
	const std::vector<msize> deleted_vertexes{ 3,4 };
	const msize expected_dimension = test_dimension - deleted_vertexes.size();
	const std::vector<Edge> expected_edges 
    {
		Edge(0,1,2),
		Edge(2,3,7) 
	};
	TypeParam expected_graph(expected_edges, expected_dimension);

	this->test_graph->delete_vertexes(deleted_vertexes);

    EXPECT_TRUE(this->test_graph->equal(expected_graph));
}

TYPED_TEST(GraphBaseTests, DeleteVertexesTest2)
{
	const std::vector<msize> deleted_vertexes{ 1,5,6 };
	const msize expected_dimension = test_dimension - deleted_vertexes.size();
	const std::vector<Edge> expected_edges
	{ 
		Edge(1,2,10) 
	};
	TypeParam expected_graph(expected_edges, expected_dimension);

	this->test_graph->delete_vertexes(deleted_vertexes);

	EXPECT_TRUE(this->test_graph->equal(expected_graph));
}

TYPED_TEST(GraphBaseTests, GetConnectedComponentTest)
{
	const std::vector<msize> first_expected_component = { 0,3,4,6 };
	const std::vector<msize> second_expected_component = { 1,5 };

	auto first_component = this->test_graph->get_connected_component(3);
	auto second_component = this->test_graph->get_connected_component(1);

	std::sort(first_component.begin(), first_component.end());
	std::sort(second_component.begin(), second_component.end());

	EXPECT_EQ(first_component, first_expected_component);
	EXPECT_EQ(second_component, second_expected_component);
}

TYPED_TEST(GraphBaseTests, FlowTest)
{
	const auto first_expected_flow = 7;
	const auto second_expected_flow = 3;

	auto first_flow = this->test_graph->get_flow(1, 5);
	auto second_flow = this->test_graph->get_flow(6, 4);

	EXPECT_EQ(first_flow, first_expected_flow);
	EXPECT_EQ(second_flow, second_expected_flow);
}