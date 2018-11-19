#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/test_data/non_oriented_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class DinicAlgorithmTests : public ::testing::Test
{
protected:
	DinicAlgorithmTests() :
		test_graph(non_oriented_test_graph::get_graph<GraphType>())
	{
	}
    
	std::unique_ptr<NonOrientedGraphBase> test_graph;
};

TYPED_TEST_CASE(DinicAlgorithmTests, NonOrientedGraphImplementations,);

TYPED_TEST(DinicAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::Dinic_algorithm(*this->test_graph, 3, 6), non_oriented_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::Dinic_algorithm(*this->test_graph, 1, 5), non_oriented_test_graph::get_flows()[1][5]);
}

TYPED_TEST(DinicAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::matrix_of_flows(*this->test_graph, flow_calculators::Dinic_algorithm), FullSymmetricMatrix(non_oriented_test_graph::get_flows()));
}
