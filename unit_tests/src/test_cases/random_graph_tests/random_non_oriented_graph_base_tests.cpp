#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/utils/comparators.hpp"
#include "unit_tests/macroses.hpp"
#include "unit_tests/test_data/random_non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"
#include "unit_tests/utils/first_n_range.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class RandomGraphType>
class RandomNonOrientedGraphBaseTests : public ::testing::Test
{
protected:
	RandomNonOrientedGraphBaseTests() :
		test_graph(random_non_oriented_test_graph::get_graph<RandomGraphType>())
	{
	}
	std::unique_ptr<RandomNonOrientedGraphBase> test_graph;
};

TYPED_TEST_CASE(RandomNonOrientedGraphBaseTests, RandomNonOrientedGraphImplementations);

TYPED_TEST(RandomNonOrientedGraphBaseTests, DimensionTest)
{
    EXPECT_EQ(this->test_graph->dimension(), random_non_oriented_test_graph::dimension());
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, GetWeightTest)
{
    auto edges = random_non_oriented_test_graph::edges();
	for(const auto& edge : FirstNRange(edges.begin(), 3))
	{
        EXPECT_EQ(this->test_graph->at(edge.v1(), edge.v2()), edge.weight());
	}

	const auto[index1, index2] = random_non_oriented_test_graph::not_existed_edge();
	EXPECT_EQ(this->test_graph->at(index1, index2), 0);
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, SetWeightTest)
{
	this->test_graph->set(1, 2, 100);
	EXPECT_EQ(this->test_graph->at(1, 2), 100);
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, GetProbabilityTest)
{
	for(const auto& edge : random_non_oriented_test_graph::edges())
	{
		EXPECT_EQ(this->test_graph->probability_at(edge.v1(), edge.v2()), edge.probability());
	}
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, SetProbabilityTest)
{
	this->test_graph->set_probability(1, 2, 0.3);
	EXPECT_EQ(this->test_graph->probability_at(1, 2), 0.3);
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, GetEdgesTest)
{
	const auto edges = this->test_graph->edges();

	EXPECT_TRUE(compare_vectors_without_order(edges, random_non_oriented_test_graph::edges()));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, DeleteVertexesTest)
{
	this->test_graph->delete_vertexes(random_non_oriented_test_graph::vertexes_to_delete());

	const auto edges = this->test_graph->edges();

	EXPECT_TRUE(compare_vectors_without_order(edges, random_non_oriented_test_graph::edges_after_delete()));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, WithDeletedVertexesTest)
{
	auto graph = this->test_graph->with_deleted_vertexes(random_non_oriented_test_graph::vertexes_to_delete());

	const auto edges = graph->edges();

	EXPECT_TRUE(compare_vectors_without_order(edges, random_non_oriented_test_graph::edges_after_delete()));
}
