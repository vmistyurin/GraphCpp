#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/test_data/reliable_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class ReductionUseAlgorithmTests : public ::testing::Test
{
protected:
	ReductionUseAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<GraphType>())
	{
	}
	std::unique_ptr<GraphType> test_graph;
};

TYPED_TEST_CASE(ReductionUseAlgorithmTests, NonOrientedGraphImplementations);

TYPED_TEST(ReductionUseAlgorithmTests, WithEdmondsKarpAlgorithm)
{
	EXPECT_EQ(*flow_calculators::reduction_use_algorithm(*this->test_graph, flow_calculators::Edmonds_Karp_algorithm), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}

TYPED_TEST(ReductionUseAlgorithmTests, WithDinicAlgorithm)
{
	EXPECT_EQ(*flow_calculators::reduction_use_algorithm(*this->test_graph, flow_calculators::Dinic_algorithm), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}

TYPED_TEST(ReductionUseAlgorithmTests, WithPreflowPushAlgorithm)
{
	EXPECT_EQ(*flow_calculators::reduction_use_algorithm(*this->test_graph, flow_calculators::preflow_push_algorithm), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}