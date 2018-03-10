#include "unit.tests/utils/comparators.h"
#include "unit.tests/macroses.h"
#include "core/GraphImplementation/graph_base.h"
#include "core/GraphImplementation/matrix_graph.h"
#include "core/MatrixImplementation/full_symmetric_matrix.h"
#include "core/MatrixImplementation/half_symmetric_matrix.h"
#include "gtest/gtest.h"
#include <memory>

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	const std::vector<Edge> test_edges =
	{ 
		Edge(3, 6, 1),
		Edge(4, 6, 2),
		Edge(1, 5, 7),
		Edge(3, 4, 10),
		Edge(2, 4, 4),
		Edge(6, 0, 2),
		Edge(6, 7, 10)
	};
	const msize test_dimension = 8;

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

TYPED_TEST(GraphBaseTests, DimensionTest)
{
	EXPECT_EQ(this->test_graph->dimension(), test_dimension);
}

TYPED_TEST(GraphBaseTests, LinkedVertexesTest)
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

TYPED_TEST(GraphBaseTests, EdgesTest)
{
    EXPECT_TRUE(compare_vectors_without_order(test_edges, this->test_graph->get_edges()));
}

TYPED_TEST(GraphBaseTests, VertexesDegreeTest)
{
    EXPECT_EQ(this->test_graph->get_degrees(), degrees);
}

TYPED_TEST(GraphBaseTests, VertexDegreeTests)
{
	const msize first_test_vertex = 0;
	const msize second_test_vertex = 6;

    EXPECT_EQ(this->test_graph->get_degree(first_test_vertex), degrees[first_test_vertex]);
    EXPECT_EQ(this->test_graph->get_degree(second_test_vertex), degrees[second_test_vertex]);
}

TYPED_TEST(GraphBaseTests, DeleteVertexesTest1)
{
	const std::vector<msize> deleted_vertexes = { 3,4 };
	const msize expected_dimension = test_dimension - deleted_vertexes.size();
	const std::vector<Edge> expected_edges 
    {
		Edge(0, 1, 2),
		Edge(1, 2, 10),
		Edge(3, 4, 7)
	};
	TypeParam expected_graph(expected_edges, expected_dimension);

	this->test_graph->delete_vertexes(deleted_vertexes);

    EXPECT_TRUE(this->test_graph->equal(expected_graph));
}

TYPED_TEST(GraphBaseTests, ConnectedComponentTest)
{
	const std::vector<msize> first_expected_component = { 0, 2, 3, 4, 6, 7 };
	const std::vector<msize> second_expected_component = { 1,5 };

	const auto first_component = this->test_graph->get_connected_component(3);
	const auto second_component = this->test_graph->get_connected_component(1);

	EXPECT_EQ(first_component, first_expected_component);
	EXPECT_EQ(second_component, second_expected_component);
}

TYPED_TEST(GraphBaseTests, ConnectedComponentsTest)
{
	const std::vector<std::vector<msize>> expected_components = { { 0, 2, 3, 4, 6, 7 }, {1, 5} };

	const auto components = this->test_graph->get_connected_components();

	EXPECT_EQ(components, expected_components);
}

TYPED_TEST(GraphBaseTests, HangedVertexesTest)
{
	const std::list<std::pair<msize, msize>> expected_hanged = { {0, 6}, {7, 6}, {5, 1}, {1, 5}, {2, 4} };

	const auto hanged = this->test_graph->get_hanged_vertexes();

	EXPECT_TRUE(compare_lists_without_order(hanged, expected_hanged));
}

TYPED_TEST(GraphBaseTests, FlowTest)
{
	const auto first_expected_flow = 3;
	const auto second_expected_flow = 7;

	auto first_flow = this->test_graph->get_flow(3, 6);
	auto second_flow = this->test_graph->get_flow(1, 5);

	EXPECT_EQ(first_flow, first_expected_flow);
	EXPECT_EQ(second_flow, second_expected_flow);
}

TYPED_TEST(GraphBaseTests, MatrixOfFlowsTest)
{
	const std::vector<std::vector<mcontent>> flows = { {0, 0, 2, 2,  2,  0, 2, 2},
													   {0, 0, 0, 0,  0,  7, 0, 0},
													   {2, 0, 0, 4,  4,  0, 3, 3},
													   {2, 0, 4, 0,  11, 0, 3, 3},
													   {2, 0, 4, 11, 0,  0, 3, 3},
													   {0, 7, 0, 0,  0,  0, 0, 0},
													   {2, 0, 3, 3,  3,  0, 0, 10},
													   {2, 0, 3, 3,  3,  0, 10, 0}};
	const auto ptr_to_matrix = std::make_shared<FullSymmetricMatrix>(flows);

	const auto matrix_of_flows = this->test_graph->get_matrix_of_flows();

	EXPECT_EQ(*matrix_of_flows, *ptr_to_matrix);
}


TYPED_TEST(GraphBaseTests, OptimizedMatrixOfFlowsTest)
{
	const std::vector<std::vector<mcontent>> flows = { { 0, 0, 2, 2,  2,  0, 2, 2 },
	{ 0, 0, 0, 0,  0,  7, 0, 0 },
	{ 2, 0, 0, 4,  4,  0, 3, 3 },
	{ 2, 0, 4, 0,  11, 0, 3, 3 },
	{ 2, 0, 4, 11, 0,  0, 3, 3 },
	{ 0, 7, 0, 0,  0,  0, 0, 0 },
	{ 2, 0, 3, 3,  3,  0, 0, 10 },
	{ 2, 0, 3, 3,  3,  0, 10, 0 } };
	const auto ptr_to_matrix = std::make_shared<FullSymmetricMatrix>(flows);

	const auto matrix_of_flows = this->test_graph->optimized_get_matrix_of_flows();

	EXPECT_EQ(*matrix_of_flows, *ptr_to_matrix);
}

#ifdef USE_SLOW_TESTS
	TYPED_TEST(GraphBaseTests, EqualityTest)
	{
		TypeParam same_edges_graph(test_edges, test_dimension);


		std::vector<Edge> shuffled_edges = test_edges;
		std::swap(shuffled_edges[0], shuffled_edges[4]);
		std::swap(shuffled_edges[1], shuffled_edges[3]);
		TypeParam shuffled_edges_graph(shuffled_edges, test_dimension);


		std::vector<Edge> equal_edges
		{
			Edge(3, 6,7),
			Edge(1, 5, 10),
			Edge(1, 4, 2),
			Edge(1, 2, 1),
			Edge(0, 2, 10),
			Edge(0, 1, 2),
			Edge(0, 7, 4)
		};
		TypeParam equal_graph(equal_edges, test_dimension);


		TypeParam dimensional_non_equal_graph(test_edges, test_dimension + 1);


		std::vector<Edge> different_degrees_edges
		{
			Edge(1, 5, 2),
			Edge(4, 5, 3),
			Edge(1, 4, 10),
			Edge(2, 5, 1),
			Edge(3, 5, 7),
			Edge(7, 1, 10)
		};
		TypeParam different_degrees_graph(different_degrees_edges, test_dimension);


		std::vector<Edge> different_edges
		{
			Edge(0, 1, 1),
			Edge(0, 2, 1),
			Edge(0, 3, 1),
			Edge(0, 4, 1),
			Edge(4, 5, 1),
			Edge(5, 7, 1),
			Edge(5, 6, 1)
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
#endif // USE_SLOW_TESTS

