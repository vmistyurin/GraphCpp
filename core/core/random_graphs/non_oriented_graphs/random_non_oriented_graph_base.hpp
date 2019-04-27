#pragma once

#include <functional>

#include "core/utils/numeric.hpp"
#include "core/edges/symmetric_random_edge.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_graph_base.hpp"
#include "core/random_graphs/random_graph_base.hpp"

namespace graphcpp
{
    class RandomNonOrientedGraphBase: public RandomGraphBase
    {
    public:
        std::vector<SymmetricRandomEdge> get_edges() const;
		virtual std::unique_ptr<NonOrientedGraphBase> release_graph() = 0;
		
		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(RandomNonOrientedGraphBase)
    };
}
