#include "gtest/gtest.h"

#include <cmath>

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
    std::unique_ptr<RandomNonOrientedGraphBase> test_graph;

	RandomNonOrientedGraphBaseTests() :
		test_graph(random_non_oriented_test_graph::get_graph<RandomGraphType>())
	{
	}
};

TYPED_TEST_CASE(RandomNonOrientedGraphBaseTests, RandomNonOrientedGraphImplementations);

TYPED_TEST(RandomNonOrientedGraphBaseTests, DimensionTest)
{
    EXPECT_EQ(this->test_graph->dimension(), random_non_oriented_test_graph::dimension());
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, GetWeightTest)
{
    const auto edges = random_non_oriented_test_graph::edges();
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
    const auto edges = random_non_oriented_test_graph::edges();
	for(const auto& edge : FirstNRange(edges.begin(), 3))
	{
		EXPECT_TRUE(are_doubles_equal(this->test_graph->probability_at(edge.v1(), edge.v2()), edge.probability()));
	}
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, SetProbabilityTest)
{
    const auto test_probability = 0.3;
	this->test_graph->set_probability(1, 2, test_probability);
	EXPECT_TRUE(are_doubles_equal(this->test_graph->probability_at(1, 2), test_probability));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, GetEdgesTest)
{
	const auto edges = this->test_graph->get_edges();

	EXPECT_TRUE(compare_vectors_without_order(edges, random_non_oriented_test_graph::edges()));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, DeleteVertexesTest)
{
	this->test_graph->delete_vertexes(random_non_oriented_test_graph::vertexes_to_delete());

	const auto edges = this->test_graph->get_edges();

	EXPECT_TRUE(compare_vectors_without_order(edges, random_non_oriented_test_graph::edges_after_delete()));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, WithDeletedVertexesTest)
{
	auto graph = this->test_graph->with_deleted_vertexes(random_non_oriented_test_graph::vertexes_to_delete());

	const auto edges = graph->get_edges();

	EXPECT_TRUE(compare_vectors_without_order(edges, random_non_oriented_test_graph::edges_after_delete()));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, WithDeletedEdgeTest)
{
	const msize i = 2;
	const msize j = 3;

	const auto with_deleted_vertexes = this->test_graph->with_deleted_edge(i, j);

	this->test_graph->set(i, j, 0);
	this->test_graph->set_probability(i, j, 0);

	EXPECT_TRUE(compare_vectors_without_order(with_deleted_vertexes->get_edges(), this->test_graph->get_edges()));
}

TYPED_TEST(RandomNonOrientedGraphBaseTests, FactorizeTest)
{
	std::vector<SymmetricRandomEdge> edges = { SymmetricRandomEdge(SymmetricEdge(0, 1, 5), 0.3),
											   SymmetricRandomEdge(SymmetricEdge(0, 3, 6), 0.5),
											   SymmetricRandomEdge(SymmetricEdge(1, 3, 10), 1),
											   SymmetricRandomEdge(SymmetricEdge(2, 3, 8), 0.2) };
	auto graph = TypeParam(edges, 4);

	std::vector<std::pair<std::vector<SymmetricEdge>, double>> expected_graphs = {
		{ { SymmetricEdge(1, 3, 10) }, 0.28 },

		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(2, 3, 8) }, 0.07 },

		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(0, 3, 6) }, 0.28 },
		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(0, 3, 6), SymmetricEdge(2, 3, 8) }, 0.07 },

		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(0, 1, 5) }, 0.12 },
		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(0, 1, 5), SymmetricEdge(2, 3, 8) }, 0.03 },
		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(0, 1, 5), SymmetricEdge(0, 3, 6) }, 0.12 },
		{ { SymmetricEdge(1, 3, 10), SymmetricEdge(0, 1, 5), SymmetricEdge(0, 3, 6), SymmetricEdge(2, 3, 8) }, 0.03 },
	};

	graph.factorize([&](std::unique_ptr<NonOrientedGraphBase> graph, double probability)
	{
		auto edges = graph->get_edges();

		auto find_result = std::find_if(expected_graphs.cbegin(), expected_graphs.cend(), [&](std::pair<std::vector<SymmetricEdge>, double> result)
		{
			const auto[expected_edges, expected_probability] = result;
			return are_doubles_equal(probability, expected_probability) && compare_vectors_without_order(edges, expected_edges);
		});

		if (find_result != expected_graphs.cend())
		{
			expected_graphs.erase(find_result);
		}
		else
		{
			FAIL();
		}
	});

	EXPECT_TRUE(expected_graphs.empty());
}
