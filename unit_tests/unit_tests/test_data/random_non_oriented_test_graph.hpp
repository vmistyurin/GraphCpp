#pragma once

#include "core/all.hpp"

namespace graphcpp_testing::random_non_oriented_test_graph
{
	using namespace graphcpp;

	msize dimension();
	std::vector<SymmetricRandomEdge> edges();
    std::pair<msize, msize> not_existed_edge();

	template<class RandomGraphType>
	std::unique_ptr<RandomNonOrientedGraphBase> get_graph()
    {
	    return std::make_unique<RandomGraphType>(edges(), dimension());
    }

	std::vector<msize> vertexes_to_delete();
	std::vector<SymmetricRandomEdge> edges_after_delete();
}