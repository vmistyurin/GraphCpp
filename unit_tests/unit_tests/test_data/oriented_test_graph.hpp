#pragma once

#include <vector>
#include <memory>

#include "core/edges/edge.hpp"

namespace graphcpp
{
	class OrientedGraphBase;
}

namespace graphcpp::testing::oriented_test_graph
{
	using namespace graphcpp;

	msize dimension();
	std::vector<Edge> get_edges();
	std::vector<msize> get_degrees();

	template<class OrientedGraphType>
	std::unique_ptr<OrientedGraphType> get_graph()
    {
        return std::make_unique<OrientedGraphType>(get_edges(), dimension());
    }
}
