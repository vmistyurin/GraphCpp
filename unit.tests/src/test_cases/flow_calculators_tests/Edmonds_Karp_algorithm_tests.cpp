#include "unit.tests/test_data/reliable_test_graph.hpp"
#include "core/all.hpp"
#include "gtest/gtest.h"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class TestGraphType>
class EdmondsKarpAlgorithmTests : public ::testing::Test
{
protected:
	EdmondsKarpAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<TestGraphType>())
	{
	}
	std::unique_ptr<GraphBase> test_graph;
};

using GraphImplementations = testing::Types<MatrixGraph<FullSymmetricMatrix>, MatrixGraph<HalfSymmetricMatrix>>;
TYPED_TEST_CASE(EdmondsKarpAlgorithmTests, GraphImplementations);

TYPED_TEST(EdmondsKarpAlgorithmTests, SingleFlowTests)
{
	EXPECT_EQ(flow_calculators::Edmonds_Karp_algorithm(*this->test_graph, 3, 6), reliable_test_graph::get_flows()[3][6]);
	EXPECT_EQ(flow_calculators::Edmonds_Karp_algorithm(*this->test_graph, 1, 5), reliable_test_graph::get_flows()[1][5]);
}

TYPED_TEST(EdmondsKarpAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::Edmonds_Karp_algorithm(*this->test_graph), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}