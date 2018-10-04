#pragma once

#include "core/all.hpp"

namespace graphcpp_testing::random_test_graph
{
	using namespace graphcpp;

	msize dimension();
	std::vector<Edge> get_edges();
	std::vector<double> probabilities();
	std::vector<std::pair<std::pair<msize, msize>, mcontent>> getter_test();

	template<class RandomGraphType>
	std::unique_ptr<RandomGraphBase> get_graph();
}