#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit.tests/test_data/reliable_test_graph.hpp"
#include "unit.tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class DISABLED_PreflowPushAlgorithmTests : public ::testing::Test
{
protected:
	DISABLED_PreflowPushAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<GraphType>())
	{
	}
	std::unique_ptr<GraphType> test_graph;
};

TYPED_TEST_CASE(DISABLED_PreflowPushAlgorithmTests, NonOrientedGraphImplementations);

TYPED_TEST(DISABLED_PreflowPushAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::preflow_push_algorithm(*this->test_graph, 3, 6), reliable_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::preflow_push_algorithm(*this->test_graph, 1, 5), reliable_test_graph::get_flows()[1][5]);
}

TYPED_TEST(DISABLED_PreflowPushAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::preflow_push_algorithm(*this->test_graph), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}