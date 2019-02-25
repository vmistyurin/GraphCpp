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
		template<class GraphType>
		using factorize_function = std::function<void(std::unique_ptr<GraphType>, double)>;

	private:
		template<class GraphType>
		void factorize_from(SymmetricMatrixIterator iter, const factorize_function<GraphType>& func, double probability);

    public:
        std::vector<SymmetricRandomEdge> get_edges() const;
		virtual std::unique_ptr<NonOrientedGraphBase> release_graph() = 0;

		virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const = 0;
		virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_edge(msize i, msize j) const = 0;

		template<class GraphType>
		void factorize(const factorize_function<GraphType>& func, double probability = 1);

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(RandomNonOrientedGraphBase)
    };

	template<class GraphType>
	void RandomNonOrientedGraphBase::factorize(const factorize_function<GraphType>& func, double probability)
	{
		factorize_from(begin(), func, probability);
	}

	template<class GraphType>
	void RandomNonOrientedGraphBase::factorize_from(SymmetricMatrixIterator iter, const factorize_function<GraphType>& func, double probability)
	{
		for (; iter != end(); ++iter)
		{
			const auto[i, j] = *iter;
			
			const auto vertex_probability = probability_at(i, j);
			if (!(are_doubles_equal(vertex_probability, 0) || are_doubles_equal(vertex_probability, 1)))
			{
				auto deleted_branch = with_deleted_edge(i, j);
				deleted_branch->factorize(func, probability * (1.0 - vertex_probability));

				probability *= vertex_probability;
				set_probability(i, j, 1);
			}
		}

		func(std::make_unique<GraphType>(std::move(*release_graph())), probability);
	}
}
