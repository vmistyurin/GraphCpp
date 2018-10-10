#pragma once


#include <vector>
#include <string>

#include "core/macroses.hpp"
#include "core/random_graph_implementations/random_graph_base.hpp"
#include "core/edges/symmetric_random_edge.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

namespace graphcpp
{
    class RandomNonOrientedGraphBase: public RandomGraphBase
    {
    public:
        std::vector<SymmetricRandomEdge> edges() const;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

        virtual ~RandomNonOrientedGraphBase() = default;
        RandomNonOrientedGraphBase() = default;
        RandomNonOrientedGraphBase(const RandomNonOrientedGraphBase&) = default;
        RandomNonOrientedGraphBase& operator=(const RandomNonOrientedGraphBase&) = default;
        RandomNonOrientedGraphBase(RandomNonOrientedGraphBase&&) = default;
        RandomNonOrientedGraphBase& operator=(RandomNonOrientedGraphBase&&) = default;
    };
}
