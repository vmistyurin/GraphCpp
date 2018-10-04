#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/utils/comparators.hpp"
#include "unit_tests/macroses.hpp"
#include "unit_tests/test_data/random_test_graph.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

template<class RandomGraphType>
class RandomGraphBaseTests : public ::testing::Test
{
protected:
	RandomGraphBaseTests() :
		test_graph(graphcpp_testing::random_test_graph::get_graph<RandomGraphType>())
	{
	}
	std::unique_ptr<RandomGraphBase> test_graph;
};

TYPED_TEST_CASE(RandomGraphBaseTests, RandomGraphImplementations);

TYPED_TEST(RandomGraphBaseTests, DimensionTest)
{
	EXPECT_EQ(this->test_graph->dimension(), random_test_graph::dimension());
}

TYPED_TEST(RandomGraphBaseTests, ProbabilitiesTest)
{
	EXPECT_EQ(this->test_graph->probabilities(), random_test_graph::probabilities());
}

TYPED_TEST(RandomGraphBaseTests, GetterTest)
{
	for(auto[index, weight] : random_test_graph::getter_test())
	{
		EXPECT_EQ(this->test_graph->at(index.first, index.second), weight);
	}
}