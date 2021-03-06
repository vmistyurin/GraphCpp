#include "gtest/gtest.h"

#include "unit_tests/utils/comparators.hpp"
#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

namespace graphcpp::testing
{
	template<class NorGraphType>
	class NonOrientedGraphBaseTests : public ::testing::Test
	{
	protected:
		NonOrientedGraphBaseTests() :
			test_dimension(non_oriented_test_graph::dimension()),
			test_graph(non_oriented_test_graph::get_graph<NorGraphType>())
		{
		}
		
		msize test_dimension;
		std::unique_ptr<NorGraphType> test_graph;
	};

	TYPED_TEST_CASE(NonOrientedGraphBaseTests, NonOrientedGraphImplementations,);

	TYPED_TEST(NonOrientedGraphBaseTests, DimensionTest)
	{
		EXPECT_EQ(this->test_graph->dimension(), this->test_dimension);
	}

	TYPED_TEST(NonOrientedGraphBaseTests, GetterTest)
	{
		EXPECT_EQ(this->test_graph->at(non_oriented_test_graph::get_edges()[0].v1(), non_oriented_test_graph::get_edges()[0].v2()), non_oriented_test_graph::get_edges()[0].weight);
		EXPECT_EQ(this->test_graph->at(non_oriented_test_graph::get_edges()[0].v2(), non_oriented_test_graph::get_edges()[0].v1()), non_oriented_test_graph::get_edges()[0].weight);
	}

	TYPED_TEST(NonOrientedGraphBaseTests, SetterTest)
	{
		msize v1 = 0, v2 = 5;
		mcontent value = 10;

		this->test_graph->set(v1, v2, value);

		EXPECT_EQ(this->test_graph->at(v1, v2), value);
	}

	TYPED_TEST(NonOrientedGraphBaseTests, LinkedVertexesTest)
	{
		msize test_vertex = 3;
		std::vector<msize> linked_with_test_vertex;
		for (const auto& edge : non_oriented_test_graph::get_edges())
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

	TYPED_TEST(NonOrientedGraphBaseTests, EdgesTest)
	{
		EXPECT_TRUE(compare_without_order(non_oriented_test_graph::get_edges(), this->test_graph->get_edges()));
	}

	TYPED_TEST(NonOrientedGraphBaseTests, NumberOfEdgesTest)
	{
		EXPECT_EQ(non_oriented_test_graph::get_edges().size(), this->test_graph->get_number_of_edges());
	}

	TYPED_TEST(NonOrientedGraphBaseTests, VertexesDegreeTest)
	{
		EXPECT_EQ(this->test_graph->get_degrees(), non_oriented_test_graph::get_degrees());
	}

	TYPED_TEST(NonOrientedGraphBaseTests, VertexDegreeTests)
	{
		msize first_test_vertex = 0;
		msize second_test_vertex = 6;

		EXPECT_EQ(this->test_graph->get_degree(first_test_vertex), non_oriented_test_graph::get_degrees()[first_test_vertex]);
		EXPECT_EQ(this->test_graph->get_degree(second_test_vertex), non_oriented_test_graph::get_degrees()[second_test_vertex]);
	}

	TYPED_TEST(NonOrientedGraphBaseTests, DeleteVertexesTest)
	{
		std::vector<msize> deleted_vertexes = { 3, 4 };
		auto expected_dimension = this->test_dimension - deleted_vertexes.size();

		std::vector<msize> expected_new_nums = { 0, 1, 2, msize_undefined, msize_undefined, 3, 4, 5, 6 };
		std::vector<SymmetricEdge> expected_edges = {
			SymmetricEdge(0, 4, 2),
			SymmetricEdge(4, 5, 10),
			SymmetricEdge(1, 3, 7)
		};
		TypeParam expected_graph(expected_edges, expected_dimension);

		auto new_nums = this->test_graph->delete_vertexes(deleted_vertexes);

		auto edges = this->test_graph->get_edges();
		
		EXPECT_TRUE(this->test_graph->equal(expected_graph));
	}

	TYPED_TEST(NonOrientedGraphBaseTests, ConnectedComponentTest)
	{
		std::vector<msize> first_expected_component = { 0, 2, 3, 4, 6, 7 };
		std::vector<msize> second_expected_component = { 1, 5 };

		auto first_component = this->test_graph->get_connected_component(3);
		auto second_component = this->test_graph->get_connected_component(1);

		EXPECT_EQ(first_component, first_expected_component);
		EXPECT_EQ(second_component, second_expected_component);
	}

	TYPED_TEST(NonOrientedGraphBaseTests, ConnectedComponentsTest)
	{
		std::vector<std::vector<msize>> expected_components = { { 0, 2, 3, 4, 6, 7 }, { 1, 5 } };

		auto components = this->test_graph->get_connected_components();

		EXPECT_EQ(components, expected_components);
	}

	TYPED_TEST(NonOrientedGraphBaseTests, HangedVertexesTest)
	{
		std::list<std::pair<msize, msize>> expected_hanged = { { 0, 6 }, { 7, 6 }, { 5, 1 }, { 1, 5 }, { 2, 4 } };

		auto hanged = this->test_graph->get_hanged_vertexes();

		EXPECT_TRUE(compare_without_order(hanged, expected_hanged));
	}

	TYPED_TEST(NonOrientedGraphBaseTests, BridgesTest)
	{
		std::vector<SymmetricEdge> edges = {
			SymmetricEdge(0, 1, 1),
			SymmetricEdge(0, 2, 1),
			SymmetricEdge(1, 2, 1),
			SymmetricEdge(2, 3, 1),
			SymmetricEdge(3, 5, 1),
			SymmetricEdge(5, 7, 1),
			SymmetricEdge(3, 7, 1),
			SymmetricEdge(2, 4, 1),
			SymmetricEdge(4, 6, 1),
			SymmetricEdge(4, 8, 1),
			SymmetricEdge(6, 8, 1)
		};

		TypeParam graph(edges, 9);

		std::list<std::pair<msize, msize>> expected_bridges = { { 2, 3 }, { 2, 4 } };
		std::vector<msize> expected_classes = { 0, 0, 0, 1, 2, 1, 2, 1, 2 };

		auto[bridges, classes] = graph.get_bridges();

		ASSERT_TRUE(compare_without_order(bridges, expected_bridges));

		for (msize i = 0; i < expected_classes.size(); i++)
		{
			for (msize j = 0; j < expected_classes.size(); j++)
			{
				EXPECT_EQ(classes[i] == classes[j], expected_classes[i] == expected_classes[j]);
			}
		}
	}

	TYPED_TEST(NonOrientedGraphBaseTests, ChainsTest)
	{
		std::vector<SymmetricEdge> edges = {
			SymmetricEdge(0, 1, 4),
			SymmetricEdge(1, 4, 1),
			SymmetricEdge(1, 3, 1),
			SymmetricEdge(0, 4, 1),
			SymmetricEdge(4, 8, 1),
			SymmetricEdge(5, 8, 1),
			SymmetricEdge(5, 9, 1),
			SymmetricEdge(2, 7, 1),
			SymmetricEdge(2, 9, 1),
			SymmetricEdge(6, 9, 1),
			SymmetricEdge(3, 6, 1)
		};

		TypeParam graph(edges, 10);

		std::vector<std::vector<msize>> expected_chains = { { 4, 8, 5, 9 }, { 1, 3, 6, 9 }, { 7, 2, 9 }, { 1, 0, 4 } };
		
		std::vector<std::vector<msize>> reversed_expected_chains;  
		reversed_expected_chains.reserve(expected_chains.size());
		for(const auto& chain : expected_chains)
		{
			reversed_expected_chains.emplace_back(chain.crbegin(), chain.crend());
		}

		auto chains = graph.get_chains();

		ASSERT_EQ(chains.size(), expected_chains.size());
		for(msize i = 0; i < chains.size(); i++)
		{
			auto finded = false;
			for (msize j = 0; j < expected_chains.size(); j++)
			{
				finded = chains[i] == expected_chains[j] || chains[i] == reversed_expected_chains[j];
				if (finded)
				{
					break;
				}
			}

			EXPECT_TRUE(finded);
		}
	}

	TYPED_TEST(NonOrientedGraphBaseTests, ConnectedTreesTest)
	{
		std::vector<SymmetricEdge> edges = {
			SymmetricEdge(0, 7, 1),
			SymmetricEdge(0, 2, 1),
			SymmetricEdge(0, 1, 1),
			SymmetricEdge(1, 2, 1),
			SymmetricEdge(1, 8, 1),
			SymmetricEdge(4, 8, 1),
			SymmetricEdge(6, 8, 1),
			SymmetricEdge(3, 6, 1),
			SymmetricEdge(5, 6, 1),
		};
		TypeParam graph(edges, 9);
		
		std::list<std::vector<msize>> expected_trees = { { 0, 7 }, { 1, 8, 4, 6, 3, 5 } }; //TODO : start ignore vertexes order
		
		const auto trees = graph.get_connected_trees();
		
		EXPECT_TRUE(compare_without_order(trees, expected_trees));
	}

	TYPED_TEST(NonOrientedGraphBaseTests, WithDeletedVertexesTest)
	{
		const std::vector<msize> vertexes_to_delete = { 2, 5, 7 };

		const std::vector<SymmetricEdge> expected_edges = {
			SymmetricEdge(0, 4, 2),
			SymmetricEdge(2, 4, 1),
			SymmetricEdge(3, 4, 2),
			SymmetricEdge(2, 3, 10)
		};

		const auto edges_after_delete = this->test_graph->template with_deleted_vertexes<TypeParam, FullSymmetricMatrix>(vertexes_to_delete).get_edges();

		EXPECT_TRUE(compare_without_order(edges_after_delete, expected_edges));
	}

	TYPED_TEST(NonOrientedGraphBaseTests, WithDeletedEdgeTest)
	{
		const msize first = 2;
		const msize second = 5;

		const auto with_deleted_edge = this->test_graph->template with_deleted_edge<TypeParam, FullSymmetricMatrix>(first, second);

		this->test_graph->set(first, second, 0);

		EXPECT_TRUE(compare_without_order(with_deleted_edge.get_edges(), this->test_graph->get_edges()));
	}

	TYPED_TEST(NonOrientedGraphBaseTests, IsTreeTest)
	{
		const std::vector<SymmetricEdge> tree_edges = {
			SymmetricEdge(0, 1, 2),
			SymmetricEdge(1, 5, 1),
			SymmetricEdge(1, 3, 2),
			SymmetricEdge(2, 3, 10),
			SymmetricEdge(3, 4, 1)
		};
		TypeParam tree(tree_edges, 6);
		
		const std::vector<SymmetricEdge> not_tree_edges = {
			SymmetricEdge(0, 1, 2),
			SymmetricEdge(1, 5, 1),
			SymmetricEdge(1, 3, 2),
			SymmetricEdge(2, 3, 10),
			SymmetricEdge(3, 4, 1),
			SymmetricEdge(2, 4, 5)
		};
		TypeParam not_tree(not_tree_edges, 6);
		
		const std::vector<SymmetricEdge> disconnected_edges = {
			SymmetricEdge(1, 5, 1),
			SymmetricEdge(1, 3, 2),
			SymmetricEdge(2, 3, 10),
			SymmetricEdge(3, 4, 1),
			SymmetricEdge(2, 4, 5)
		};
		TypeParam disconnected_graph(disconnected_edges, 6);

		EXPECT_TRUE(tree.is_tree());
		EXPECT_FALSE(not_tree.is_tree());
		EXPECT_FALSE(disconnected_graph.is_tree());
	}

	TYPED_TEST(NonOrientedGraphBaseTests, AddVertexTest)
	{
		TypeParam increased_copy = *this->test_graph;
		increased_copy.add_vertex();

		ASSERT_EQ(increased_copy.dimension(), this->test_graph->dimension() + 1);
		for (const auto[i, j] : *this->test_graph)
		{
			EXPECT_EQ(this->test_graph->at(i, j), increased_copy.at(i, j));
		}
	}

	#ifdef USE_SLOW_TESTS
		TYPED_TEST(NonOrientedGraphBaseTests, EqualityTest)
		{
			TypeParam same_edges_graph(non_oriented_test_graph::get_edges(), this->test_dimension);

			std::vector<SymmetricEdge> shuffled_edges = non_oriented_test_graph::get_edges();
			std::swap(shuffled_edges[0], shuffled_edges[4]);
			std::swap(shuffled_edges[1], shuffled_edges[3]);
			TypeParam shuffled_edges_graph(shuffled_edges, this->test_dimension);

			std::vector<SymmetricEdge> equal_edges = {
				SymmetricEdge(3, 6,7),
				SymmetricEdge(1, 5, 10),
				SymmetricEdge(1, 4, 2),
				SymmetricEdge(1, 2, 1),
				SymmetricEdge(0, 2, 10),
				SymmetricEdge(0, 1, 2),
				SymmetricEdge(0, 7, 4)
			};
			TypeParam equal_graph(equal_edges, this->test_dimension);

			TypeParam dimensional_non_equal_graph(non_oriented_test_graph::get_edges(), this->test_dimension + 1);

			std::vector<SymmetricEdge> different_degrees_edges = {
				SymmetricEdge(1, 5, 2),
				SymmetricEdge(4, 5, 3),
				SymmetricEdge(1, 4, 10),
				SymmetricEdge(2, 5, 1),
				SymmetricEdge(3, 5, 7),
				SymmetricEdge(7, 1, 10)
			};
			TypeParam different_degrees_graph(different_degrees_edges, this->test_dimension);

			std::vector<SymmetricEdge> different_edges = {
				SymmetricEdge(0, 1, 1),
				SymmetricEdge(0, 2, 1),
				SymmetricEdge(0, 3, 1),
				SymmetricEdge(0, 4, 1),
				SymmetricEdge(4, 5, 1),
				SymmetricEdge(5, 7, 1),
				SymmetricEdge(5, 6, 1)
			};
			TypeParam different_edges_graph(different_edges, this->test_dimension);

			std::vector<SymmetricEdge> different_weight_edges = non_oriented_test_graph::get_edges();
			different_weight_edges[0].weight++;
			different_weight_edges[4].weight++;
			TypeParam different_weight_graph(different_weight_edges, this->test_dimension);

			EXPECT_TRUE(this->test_graph->equal(*(this->test_graph)));
			EXPECT_TRUE(this->test_graph->equal(same_edges_graph));
			EXPECT_TRUE(this->test_graph->equal(shuffled_edges_graph));
			EXPECT_TRUE(this->test_graph->equal(equal_graph));
			EXPECT_FALSE(this->test_graph->equal(dimensional_non_equal_graph));
			EXPECT_FALSE(this->test_graph->equal(different_degrees_graph));
			EXPECT_FALSE(this->test_graph->equal(different_edges_graph));
			EXPECT_FALSE(this->test_graph->equal(different_weight_graph));
		}
	#endif // USE_SLOW_TESTS
}