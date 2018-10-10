#pragma once

#include "core/all.hpp"

namespace graphcpp_testing::reliable_test_graph
{
	using namespace graphcpp;

	msize dimension();
	std::vector<SymmetricEdge> get_edges();
	std::vector<msize> get_degrees();

	template<class GraphType>
	std::unique_ptr<GraphType> get_graph();

	std::vector<std::vector<mcontent>> get_flows();
}