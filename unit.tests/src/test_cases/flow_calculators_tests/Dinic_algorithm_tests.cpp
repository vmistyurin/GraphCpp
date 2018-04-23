#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit.tests/test_data/reliable_test_graph.hpp"


using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class DinicAlgorithmTests : public ::testing::Test
{
protected:
	DinicAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<GraphType>())
	{
	}
	std::unique_ptr<GraphType> test_graph;
};

using GraphImplementations = testing::Types<MatrixGraph<FullSymmetricMatrix>, MatrixGraph<HalfSymmetricMatrix>>;
TYPED_TEST_CASE(DinicAlgorithmTests, GraphImplementations);

TYPED_TEST(DinicAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::Dinic_algorithm(*this->test_graph, 3, 6), reliable_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::Dinic_algorithm(*this->test_graph, 1, 5), reliable_test_graph::get_flows()[1][5]);
}

TYPED_TEST(DinicAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::Dinic_algorithm(*this->test_graph), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}