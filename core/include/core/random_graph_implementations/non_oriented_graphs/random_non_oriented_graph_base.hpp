#pragma once

#include <vector>
#include <functional>

#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/random_graph_implementations/random_graph_base.hpp"
#include "core/edges/symmetric_random_edge.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

namespace graphcpp
{
	using factorize_function = std::function<void(GraphBase&&)>;

    class RandomNonOrientedGraphBase: public RandomGraphBase
    {
	private:
		void factorize_from(msize i, msize j, const factorize_function& func);

    public:
        std::vector<SymmetricRandomEdge> edges() const;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		void factorize(const factorize_function& func);

        virtual ~RandomNonOrientedGraphBase() = default;
        RandomNonOrientedGraphBase() = default;
        RandomNonOrientedGraphBase(const RandomNonOrientedGraphBase&) = default;
        RandomNonOrientedGraphBase& operator=(const RandomNonOrientedGraphBase&) = default;
        RandomNonOrientedGraphBase(RandomNonOrientedGraphBase&&) = default;
        RandomNonOrientedGraphBase& operator=(RandomNonOrientedGraphBase&&) = default;
    };
}
