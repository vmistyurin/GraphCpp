#pragma once

#include <functional>

#include "core/edges/symmetric_random_edge.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_graph_base.hpp"
#include "core/random_graphs/random_graph_base.hpp"

namespace graphcpp
{
    class RandomNonOrientedGraphBase: public RandomGraphBase
    {
	public:
		using factorize_function = std::function<void(std::unique_ptr<NonOrientedGraphBase>&&, double)>;

	private:
		void factorize_from(SymmetricMatrixIterator iter, const factorize_function& func, double probability);

    public:
        std::vector<SymmetricRandomEdge> get_edges() const;
		virtual std::unique_ptr<NonOrientedGraphBase> release_graph() = 0;

		virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const = 0;
		virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_edge(msize i, msize j) const = 0;

		void factorize(const factorize_function& func, double probability = 1);

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(RandomNonOrientedGraphBase)
    };
}
