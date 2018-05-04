#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit.tests/test_data/reliable_test_graph.hpp"
#include "unit.tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class EdmondsKarpAlgorithmTests : public ::testing::Test
{
protected:
	EdmondsKarpAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<GraphType>())
	{
	}
	std::unique_ptr<GraphType> test_graph;
};

TYPED_TEST_CASE(EdmondsKarpAlgorithmTests, NonOrientedGraphImplementations);

TYPED_TEST(EdmondsKarpAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::Edmonds_Karp_algorithm(*this->test_graph, 3, 6), reliable_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::Edmonds_Karp_algorithm(*this->test_graph, 1, 5), reliable_test_graph::get_flows()[1][5]);
}

TYPED_TEST(EdmondsKarpAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::Edmonds_Karp_algorithm(*this->test_graph), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}