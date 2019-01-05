#pragma once

#include "core/all.hpp"

namespace graphcpp_testing::non_oriented_test_graph
{
	using namespace graphcpp;

	msize dimension();
	std::vector<SymmetricEdge> get_edges();
	std::vector<msize> get_degrees();

	template<class GraphType>
	std::unique_ptr<NonOrientedGraphBase> get_graph()
    {
        return std::make_unique<GraphType>(get_edges(), dimension());
    }

	std::vector<std::vector<mcontent>> get_flows();
}
