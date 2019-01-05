#pragma once

#include <vector>
#include <functional>

#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/random_graph_implementations/random_graph_base.hpp"
#include "core/edges/symmetric_random_edge.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

namespace graphcpp
{
    class RandomNonOrientedGraphBase: public RandomGraphBase
    {
	public:
		template<class NonOrientedGraphType>
		using factorize_function = std::function<void(std::unique_ptr<NonOrientedGraphType>&&, double)>;

	private:
		template<class NonOrientedGraphType>
		void factorize_from(SymmetricMatrixIterator iter, const factorize_function<NonOrientedGraphType>& func, double probability);

    public:
        std::vector<SymmetricRandomEdge> get_edges() const;
		virtual std::unique_ptr<NonOrientedGraphBase> release_graph() = 0;

		//virtual std::unique_ptr<RandomNonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const = 0;

		//template<class RandomNonOrientedGraphType>
		//std::unique_ptr<RandomNonOrientedGraphType> with_deleted_edge(msize i, msize j) const = 0;

		template<class NonOrientedGraphType>
		void factorize(const factorize_function< NonOrientedGraphType>& func, double probability = 1);

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(RandomNonOrientedGraphBase)
    };

	template<class NonOrientedGraphType>
	void RandomNonOrientedGraphBase::factorize(const factorize_function<NonOrientedGraphType>& func, double probability)
	{
		factorize_from(begin(), func, probability);
	}

	template<class NonOrientedGraphType>
	void RandomNonOrientedGraphBase::factorize_from(SymmetricMatrixIterator iter, const factorize_function<NonOrientedGraphType>& func, double probability)
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

		func(release_graph(), probability);
	}
}
