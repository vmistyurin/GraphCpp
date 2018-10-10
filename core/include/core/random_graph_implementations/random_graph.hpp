#pragma once

#include "core/edges/random_edge.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/matrix.hpp"
#include "core/graph_implementations/graph_implementations.hpp"
#include "core/random_graph_implementations/random_graph_base.hpp"

namespace graphcpp
{
	template<class GraphType>
	class RandomGraph final: public RandomGraphBase
	{
	private:
		GraphType _graph;
		Matrix _probabilities;

	public:
//		template<class InitGraphType, class VectorType>
//		RandomGraph(InitGraphType&& graph, VectorType&& probabilities);

		explicit RandomGraph(const std::vector<RandomEdge>& edges, msize dimension);

		msize dimension() const;
		mcontent at(msize index1, msize index2) const;
		void set(msize index1, msize index2, mcontent value);
		void reduce_element(msize index1, msize index2, mcontent difference);

		void rearrange_with_permutations(const std::vector<msize>& new_nums);
		void rearrange_with_allocate(const std::vector<msize>& new_nums);
	};

//	template<class T> template<class GraphType, class VectorType>
//	RandomGraph<T>::RandomGraph(GraphType&& graph, VectorType&& probabilities) :
//		_graph(std::forward<GraphType>(graph)), _probabilities(std::forward<VectorType>(probabilities))
//	{
//	}

    template <class T>
    RandomGraph<T>::RandomGraph(const std::vector<RandomEdge>& edges, msize dimension) :
        _graph(dimension), _probabilities(dimension)
    {
        for (const auto& edge : edges) {
            assert(std::max(edge.v1(), edge.v2()) < dimension);
            _graph.set(edge.v1(), edge.v2(), edge.weight());
            _probabilities.set(edge.v1(), edge.v2(), edge.probability());
        }
    }

	template<class T>
	msize RandomGraph<T>::dimension() const
	{
		return _graph.dimension();
	}

	template<class T>
	mcontent RandomGraph<T>::at(msize index1, msize index2) const
	{
		assert(std::max(index1, index2) < dimension());
		return _graph.at(index1, index2);
	}

	template<class T>
	void RandomGraph<T>::set(msize index1, msize index2, mcontent value)
	{
		assert(std::max(index1, index2) < dimension());
		_graph.set(index1, index2, value);
	}

	template<class T>
	void RandomGraph<T>::reduce_element(msize index1, msize index2, mcontent difference)
	{
		assert(std::max(index1, index2) < dimension());
		_graph.set(index1, index2, _graph.at(index1, index2) - difference);
	}

//	template<class T>
//	const std::vector<double>& RandomGraph<T>::probabilities() const
//	{
//		return _probabilities;
//	}

	template<class T>
	void RandomGraph<T>::rearrange_with_permutations(const std::vector<msize>& new_nums)
	{
		assert(is_permutation(new_nums));
		apply_permutation_with_transpositions(_probabilities, new_nums);
		_graph.rearrange(new_nums);
	}

	template<class T>
	void RandomGraph<T>::rearrange_with_allocate(const std::vector<msize>& new_nums)
	{
		assert(is_permutation(new_nums));
		apply_permutation_alloc(_probabilities, new_nums);
		_graph.rearrange(new_nums);
	}
}
