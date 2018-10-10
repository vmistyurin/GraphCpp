#pragma once

#include "core/all.hpp"

namespace graphcpp_testing::oriented_test_graph
{
	using namespace graphcpp;

	msize dimension();
	std::vector<Edge> get_edges();
	std::vector<msize> get_degrees();

	template<class OrientedGraphType>
	std::unique_ptr<OrientedGraphType> get_graph();
}