#include "gtest/gtest.h"

#include "core/flow_calculators/flow_calculators.hpp"
#include "core/flow_calculators/flow_helpers.hpp"

#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

using SymMatrixType = FullSymmetricMatrix;

template<class GraphType>
class PreflowPushAlgorithmTests : public ::testing::Test
{
protected:
	PreflowPushAlgorithmTests() :
		test_graph(non_oriented_test_graph::get_graph<GraphType>())
	{
	}
    
	std::unique_ptr<GraphType> test_graph;
};

TYPED_TEST_CASE(PreflowPushAlgorithmTests, NonOrientedGraphImplementations,);

TYPED_TEST(PreflowPushAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::preflow_push_algorithm(*this->test_graph, 3, 6), non_oriented_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::preflow_push_algorithm(*this->test_graph, 1, 5), non_oriented_test_graph::get_flows()[1][5]);
}

TYPED_TEST(PreflowPushAlgorithmTests, FlowsMatrixTests)
{
	const auto actual_flows = flow_calculators::matrix_of_flows<SymMatrixType, TypeParam>(*this->test_graph, flow_calculators::preflow_push_algorithm); 
	const auto expected_flows = SymMatrixType(non_oriented_test_graph::get_flows());
 
	EXPECT_EQ(actual_flows, expected_flows);
}