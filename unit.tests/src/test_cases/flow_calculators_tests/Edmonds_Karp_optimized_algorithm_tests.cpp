#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit.tests/test_data/reliable_test_graph.hpp"
#include "unit.tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class GraphType>
class EdmondsKarpOptimizedAlgorithmTests : public ::testing::Test
{
protected:
	EdmondsKarpOptimizedAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<GraphType>())
	{
	}
	std::unique_ptr<GraphType> test_graph;
};

TYPED_TEST_CASE(EdmondsKarpOptimizedAlgorithmTests, NonOrientedGraphImplementations);

TYPED_TEST(EdmondsKarpOptimizedAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::Edmonds_Karp_optimized_algorithm(*this->test_graph), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}