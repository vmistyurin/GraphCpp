#include "gtest/gtest.h"

#include "core/flow_calculators/algorithms.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

namespace graphcpp::testing
{
	template<class NorGraphType>
	class ReductionUseAlgorithmTests : public ::testing::Test
	{
	protected:
		ReductionUseAlgorithmTests() :
			test_graph(*non_oriented_test_graph::get_graph<NorGraphType>()),
			expected_flows(non_oriented_test_graph::get_flows())
		{
		}
		
		NorGraphType test_graph;
		FullSymmetricMatrix expected_flows;
	};

	TYPED_TEST_CASE(ReductionUseAlgorithmTests, NonOrientedGraphImplementations,);

	TYPED_TEST(ReductionUseAlgorithmTests, WithEdmondsKarpAlgorithm)
	{
		const auto actual_flows = flow_calculators::reduction_use_algorithm_d<TypeParam, SingleVectorSymmetricMatrix>(
			this->test_graph,
			flow_calculators::Edmonds_Karp_algorithm
		);
		
		EXPECT_EQ(this->expected_flows, actual_flows);
	}

	TYPED_TEST(ReductionUseAlgorithmTests, WithDinicAlgorithm)
	{
		const auto actual_flows = flow_calculators::reduction_use_algorithm_d<TypeParam, FullSymmetricMatrix>(
			this->test_graph, 
			flow_calculators::Dinic_algorithm
		);

		EXPECT_EQ(this->expected_flows, actual_flows);
	}

	TYPED_TEST(ReductionUseAlgorithmTests, WithPreflowPushAlgorithm)
	{
		const auto actual_flows = flow_calculators::reduction_use_algorithm_d<TypeParam, HalfSymmetricMatrix>(
			this->test_graph, 
			flow_calculators::preflow_push_algorithm
		);
		
		EXPECT_EQ(this->expected_flows, actual_flows);
	}
}
