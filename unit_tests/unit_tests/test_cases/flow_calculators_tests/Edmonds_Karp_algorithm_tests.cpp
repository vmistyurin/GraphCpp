#include "gtest/gtest.h"

#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/flow_helpers.hpp"

#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

namespace graphcpp::testing
{
	template<class NorGraphType>
	class EdmondsKarpAlgorithmTests : public ::testing::Test
	{
	protected:
		EdmondsKarpAlgorithmTests() :
			test_graph(non_oriented_test_graph::get_graph<NorGraphType>())
		{
		}
		
		std::unique_ptr<NorGraphType> test_graph;
	};

	TYPED_TEST_CASE(EdmondsKarpAlgorithmTests, NonOrientedGraphImplementations,);

	TYPED_TEST(EdmondsKarpAlgorithmTests, SingleFlowTests)
	{
		EXPECT_EQ(flow_calculators::Edmonds_Karp_algorithm(*this->test_graph, 3, 6), non_oriented_test_graph::get_flows()[3][6]);
		EXPECT_EQ(flow_calculators::Edmonds_Karp_algorithm(*this->test_graph, 1, 5), non_oriented_test_graph::get_flows()[1][5]);
	}

	TYPED_TEST(EdmondsKarpAlgorithmTests, FlowsMatrixTests)
	{
		const auto actual_flows = flow_calculators::matrix_of_flows<FullSymmetricMatrix, TypeParam>(*this->test_graph, flow_calculators::Edmonds_Karp_algorithm<TypeParam>); 
		const auto expected_flows = FullSymmetricMatrix(non_oriented_test_graph::get_flows());
	
		EXPECT_EQ(actual_flows, expected_flows);
	}
}

