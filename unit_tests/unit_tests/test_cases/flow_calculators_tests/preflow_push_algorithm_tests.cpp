#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class PreflowPushAlgorithmTests : public ::testing::Test
{
protected:
	PreflowPushAlgorithmTests() :
		test_graph(non_oriented_test_graph::get_graph<GraphType>())
	{
	}
    
	std::unique_ptr<NonOrientedGraphBase> test_graph;
};

TYPED_TEST_CASE(PreflowPushAlgorithmTests, NonOrientedGraphImplementations,);

TYPED_TEST(PreflowPushAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::preflow_push_algorithm(*this->test_graph, 3, 6), non_oriented_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::preflow_push_algorithm(*this->test_graph, 1, 5), non_oriented_test_graph::get_flows()[1][5]);
}

TYPED_TEST(PreflowPushAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::matrix_of_flows(*this->test_graph, flow_calculators::preflow_push_algorithm), FullSymmetricMatrix(non_oriented_test_graph::get_flows()));
}
