#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/utils/comparators.hpp"
#include "unit_tests/macroses.hpp"
#include "unit_tests/test_data/oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class TestGraphType>
class OrientedGraphBaseTests : public ::testing::Test
{
protected:
	OrientedGraphBaseTests() :
		test_graph(oriented_test_graph::get_graph<TestGraphType>())
	{
	}
    
	std::unique_ptr<OrientedGraphBase> test_graph;
};

TYPED_TEST_CASE(OrientedGraphBaseTests, OrientedGraphImplementations,);

TYPED_TEST(OrientedGraphBaseTests, DimensionTest)
{
	EXPECT_EQ(this->test_graph->dimension(), oriented_test_graph::dimension());
}

TYPED_TEST(OrientedGraphBaseTests, GetterTest)
{
	EXPECT_EQ(this->test_graph->at(oriented_test_graph::get_edges()[0].v1(), oriented_test_graph::get_edges()[0].v2()), oriented_test_graph::get_edges()[0].weight);
}

TYPED_TEST(OrientedGraphBaseTests, SetterTest)
{
	msize v1 = 0, v2 = 5;
	auto value = 10;

	this->test_graph->set(v1, v2, value);

	EXPECT_EQ(this->test_graph->at(v1, v2), value);
}

TYPED_TEST(OrientedGraphBaseTests, LinkedVertexesTest)
{
	msize test_vertex = 3;
	std::vector<msize> linked_with_test_vertex;
	for (const auto& edge : oriented_test_graph::get_edges())
	{
		if(edge.v1() == test_vertex)
		{
			linked_with_test_vertex.push_back(edge.v2());
		}
	}

	EXPECT_EQ(this->test_graph->get_linked_vertexes(test_vertex), linked_with_test_vertex);
}

TYPED_TEST(OrientedGraphBaseTests, EdgesTest)
{
	EXPECT_TRUE(compare_vectors_without_order(oriented_test_graph::get_edges(), this->test_graph->get_edges()));
}

TYPED_TEST(OrientedGraphBaseTests, VertexesDegreeTest)
{
	EXPECT_EQ(this->test_graph->get_degrees(), oriented_test_graph::get_degrees());
}

TYPED_TEST(OrientedGraphBaseTests, VertexDegreeTests)
{
	const msize first_test_vertex = 0;
	const msize second_test_vertex = 4;

	EXPECT_EQ(this->test_graph->get_degree(first_test_vertex), oriented_test_graph::get_degrees()[first_test_vertex]);
	EXPECT_EQ(this->test_graph->get_degree(second_test_vertex), oriented_test_graph::get_degrees()[second_test_vertex]);
}

TYPED_TEST(OrientedGraphBaseTests, DeleteVertexesTest)
{
	std::vector<msize> deleted_vertexes = { 3, 5 };
	std::vector<std::vector<mcontent>> expected_matrix = {
        { 0, 10, 0, 0 },
        { 22, 0, 0, 0 },
		{ 5, 0, 0, 8 },
		{ 0, 0, 0, 0 }
    };
	TypeParam expected_graph(expected_matrix);

	this->test_graph->delete_vertexes(deleted_vertexes);

	EXPECT_TRUE(this->test_graph->equal(expected_graph));
}

TYPED_TEST(OrientedGraphBaseTests, ExtractSubgraph)
{
	std::vector<msize> vertexes = { 0, 4, 5 };
	std::vector<std::vector<mcontent>> expected_matrix = {
        { 0, 0, 6 },
		{ 0, 0, 5 },
        { 7, 0, 0 }
    };
	TypeParam expected_subgraph(expected_matrix);

	auto extracted_graph = this->test_graph->extract_subgraph(vertexes);

	EXPECT_TRUE(extracted_graph->equal(expected_subgraph));
}

#ifdef USE_SLOW_TESTS
TYPED_TEST(OrientedGraphBaseTests, EqualityTest)
{
	TypeParam same_edges_graph(oriented_test_graph::get_edges(), oriented_test_graph::dimension());

	auto shuffled_edges = oriented_test_graph::get_edges();
	std::swap(shuffled_edges[0], shuffled_edges[4]);
	std::swap(shuffled_edges[1], shuffled_edges[3]);
	TypeParam shuffled_edges_graph(shuffled_edges, oriented_test_graph::dimension());

	std::vector<msize> permutation = { 1, 2, 5, 0, 4, 3 };
	auto equal_graph = oriented_test_graph::get_graph<TypeParam>();
	equal_graph->rearrange(permutation);
    
	TypeParam dimensional_non_equal_graph(oriented_test_graph::get_edges(), oriented_test_graph::dimension() + 1);

	std::vector<Edge> different_degrees_edges = {
		Edge(0, 3, 1),
		Edge(1, 4, 1),
		Edge(2, 5, 1),
	};
	TypeParam different_degrees_graph(different_degrees_edges, oriented_test_graph::dimension());

	std::vector<Edge> different_edges = {
		Edge(0, 3, 1),
		Edge(1, 4, 1),
		Edge(2, 5, 1),
	};
	TypeParam different_edges_graph(different_edges, oriented_test_graph::dimension());

	auto different_weight_edges = oriented_test_graph::get_edges();
	different_weight_edges[0].weight++;
	different_weight_edges[4].weight++;
	TypeParam different_weight_graph(different_weight_edges, oriented_test_graph::dimension());

	EXPECT_TRUE(this->test_graph->equal(*(this->test_graph)));
	EXPECT_TRUE(this->test_graph->equal(same_edges_graph));
	EXPECT_TRUE(this->test_graph->equal(shuffled_edges_graph));
	EXPECT_TRUE(this->test_graph->equal(*equal_graph));
	EXPECT_FALSE(this->test_graph->equal(dimensional_non_equal_graph));
	EXPECT_FALSE(this->test_graph->equal(different_degrees_graph));
	EXPECT_FALSE(this->test_graph->equal(different_edges_graph));
	EXPECT_FALSE(this->test_graph->equal(different_weight_graph));
}
#endif // USE_SLOW_TESTS

