#include "gtest/gtest.h"

#include "core/flow_calculators/flow_calculators.hpp"
#include "core/flow_calculators/flow_helpers.hpp"

#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class ReductionUseAlgorithmTests : public ::testing::Test
{
protected:
	ReductionUseAlgorithmTests() :
		test_graph(*non_oriented_test_graph::get_graph<GraphType>()),
		expected_flows(non_oriented_test_graph::get_flows())
	{
	}
    
	GraphType test_graph;
	FullSymmetricMatrix expected_flows;
};

TYPED_TEST_CASE(ReductionUseAlgorithmTests, NonOrientedGraphImplementations,);

TYPED_TEST(ReductionUseAlgorithmTests, WithEdmondsKarpAlgorithm)
{
	const auto actual_flows = flow_calculators::reduction_use_algorithm_de<TypeParam, SingleVectorSymmetricMatrix>(
		this->test_graph,
		flow_calculators::Edmonds_Karp_algorithm
	);
	
	EXPECT_EQ(this->expected_flows, actual_flows);
}

TYPED_TEST(ReductionUseAlgorithmTests, WithDinicAlgorithm)
{
	const auto actual_flows = flow_calculators::reduction_use_algorithm_de<TypeParam, FullSymmetricMatrix>(
		this->test_graph, 
		flow_calculators::Dinic_algorithm
	);

	EXPECT_EQ(this->expected_flows, actual_flows);
}

TYPED_TEST(ReductionUseAlgorithmTests, WithPreflowPushAlgorithm)
{
	const auto actual_flows = flow_calculators::reduction_use_algorithm_de<TypeParam, HalfSymmetricMatrix>(
		this->test_graph, 
		flow_calculators::preflow_push_algorithm
	);
	
	EXPECT_EQ(this->expected_flows, actual_flows);
}
