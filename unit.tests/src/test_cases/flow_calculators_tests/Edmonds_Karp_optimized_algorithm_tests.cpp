#include "unit.tests/test_data/reliable_test_graph.hpp"
#include "core/all.hpp"
#include "gtest/gtest.h"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class TestGraphType>
class EdmondsKarpOptimizedAlgorithmTests : public ::testing::Test
{
protected:
	EdmondsKarpOptimizedAlgorithmTests() :
		test_graph(reliable_test_graph::get_graph<TestGraphType>())
	{
	}
	std::unique_ptr<GraphBase> test_graph;
};

using GraphImplementations = testing::Types<MatrixGraph<FullSymmetricMatrix>, MatrixGraph<HalfSymmetricMatrix>>;
TYPED_TEST_CASE(EdmondsKarpOptimizedAlgorithmTests, GraphImplementations);

TYPED_TEST(EdmondsKarpOptimizedAlgorithmTests, FlowsMatrixTests)
{
	EXPECT_EQ(*flow_calculators::Edmonds_Karp_optimized_algorithm(*this->test_graph), FullSymmetricMatrix(reliable_test_graph::get_flows()));
}