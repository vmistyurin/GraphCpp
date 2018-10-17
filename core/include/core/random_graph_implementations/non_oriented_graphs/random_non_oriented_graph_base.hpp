#pragma once

#include <vector>
#include <functional>

#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/random_graph_implementations/random_graph_base.hpp"
#include "core/edges/symmetric_random_edge.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

namespace graphcpp
{
	using factorize_function = std::function<void(GraphBase&&, double)>;

    class RandomNonOrientedGraphBase: public RandomGraphBase
    {
	private:
		void factorize_from(SymmetricMatrixIterator iter, const factorize_function& func);

    public:
        std::vector<SymmetricRandomEdge> get_edges() const;

		virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const = 0;
		virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_edge(msize i, msize j) const = 0;

		void factorize(const factorize_function& func);

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
