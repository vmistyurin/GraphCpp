#ifndef GRAPH_CORE_ORIENTED_MATRIX_GRAPH_HPP
#define GRAPH_CORE_ORIENTED_MATRIX_GRAPH_HPP

#include <cassert>
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>

#include "core/utils.hpp"
#include "core/edge.hpp"
#include "core/graph_implementations/oriented_graphs/oriented_graph_base.hpp"

namespace graphcpp
{
	template<class MatrixType>
	class OrientedMatrixGraph : public OrientedGraphBase
	{
	protected:
		MatrixType _matrix;

	public:
		OrientedMatrixGraph();
		OrientedMatrixGraph(const std::vector<Edge>& edges, msize dimension);
		explicit OrientedMatrixGraph(const OrientedGraphBase& other);

		template<class SymmetricalMatrixTypeForwarded>
		explicit OrientedMatrixGraph(SymmetricalMatrixTypeForwarded&& matrix);

		std::vector<Edge> get_edges() const override;
		std::shared_ptr<MatrixBase> get_matrix() const override;
		std::shared_ptr<OrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const override;

		msize dimension() const override;
		mcontent at(msize v1, msize v2) const override;
		void set(msize v1, msize v2, mcontent value) override;

		bool equal(const GraphBase& rhs) const override;

		std::vector<msize> get_linked_vertexes(msize vertex) const override;
		std::vector<msize> get_degrees() const override;
		msize get_degree(msize vertex) const override;

		void delete_vertexes(const std::vector<msize>& vertexes) override;
		void rearrange(const std::vector<msize>& new_nums) override;
	};

	template<class T>
	OrientedMatrixGraph<T>::OrientedMatrixGraph() :
		_matrix(0)
	{
	}

	template<class T>
	OrientedMatrixGraph<T>::OrientedMatrixGraph(const std::vector<Edge>& edges, msize dimension) :
		_matrix(dimension)
	{
		for (auto edge : edges)
		{
			assert(std::max(edge.v1(), edge.v2()) < dimension);
			set(edge.v1(), edge.v2(), edge.weight);
		}
	}

	template<class T>
	OrientedMatrixGraph<T>::OrientedMatrixGraph(const OrientedGraphBase& other) :
		_matrix(other)
	{
	}


	template<class T> template<class SymmetricalMatrixTypeForwarded>
	OrientedMatrixGraph<T>::OrientedMatrixGraph(SymmetricalMatrixTypeForwarded&& matrix) :
		_matrix(std::forward<SymmetricalMatrixTypeForwarded>(matrix))
	{
	}

	template<class T>
	msize OrientedMatrixGraph<T>::dimension() const
	{
		return _matrix.dimension();
	}

	template<class T>
	mcontent OrientedMatrixGraph<T>::at(msize v1, msize v2) const
	{
		assert(std::max(v1, v2) < dimension());

		return _matrix.at(v1, v2);
	}

	template<class T>
	void OrientedMatrixGraph<T>::set(msize v1, msize v2, mcontent value)
	{
		assert(std::max(v1, v2) < dimension());

		_matrix.set(v1, v2, value);
	}

	template<class T>
	bool OrientedMatrixGraph<T>::equal(const GraphBase& rhs) const //TODO: Optimize, maybe add weight check
	{
		RETURN_IF(this == &rhs, true);
		RETURN_IF(dimension() != rhs.dimension(), false);

		auto this_degrees = get_degrees();
		auto other_degrees = rhs.get_degrees();
		RETURN_IF(!std::is_permutation(this_degrees.cbegin(), this_degrees.cend(), other_degrees.cbegin()), false);

		std::vector<msize> permutation(dimension());
		std::iota(permutation.begin(), permutation.end(), 0);

		T this_copy = _matrix;
		do
		{
			_matrix.make_rearranged(permutation, this_copy);
			RETURN_IF(is_matrix_from_graph(this_copy, rhs), true);
		} while (std::next_permutation(permutation.begin(), permutation.end()));

		return false;
	}

	template<class T>
	std::vector<Edge> OrientedMatrixGraph<T>::get_edges() const
	{
		std::vector<Edge> result;
		for (auto[i, j] : *this)
		{
			if (at(i, j) != 0)
			{
				result.emplace_back(i, j, at(i, j));
			}
		}

		return result;
	}

	template<class T>
	std::shared_ptr<MatrixBase> OrientedMatrixGraph<T>::get_matrix() const
	{
		return std::make_shared<T>(_matrix);
	}

	template<class T>
	std::vector<msize> OrientedMatrixGraph<T>::get_linked_vertexes(msize vertex) const
	{
		assert(vertex < dimension());

		std::vector<msize> result;
		for (msize i = 0; i < dimension(); i++)
		{
			if (_matrix.at(vertex, i) > 0)
			{
				result.push_back(i);
			}
		}
		return result;
	}

	template<class T>
	std::vector<msize> OrientedMatrixGraph<T>::get_degrees() const
	{
		std::vector<msize> result(dimension());

		for (msize i = 0; i < dimension(); i++)
		{
			result[i] = get_degree(i);
		}

		return result;
	}

	template<class T>
	msize OrientedMatrixGraph<T>::get_degree(msize vertex) const
	{
		assert(vertex < dimension());

		msize result = 0;
		for (msize i = 0; i < dimension(); i++)
		{
			if (_matrix.at(vertex, i) > 0)
			{
				result++;
			}
		}
		return result;
	}

	template<class T>
	std::shared_ptr<OrientedGraphBase> OrientedMatrixGraph<T>::extract_subgraph(const std::vector<msize>& vertexes) const
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) {return vertex < dimension(); }));

		T result(vertexes.size());
		for (msize i = 0; i < vertexes.size(); i++)
		{
			for (msize j = 0; j < vertexes.size(); j++)
			{
				result.set(i, j, _matrix.at(vertexes[i], vertexes[j]));
			}
		}

		return std::make_shared<OrientedMatrixGraph<T>>(std::move(result));
	}

	template<class T>
	void OrientedMatrixGraph<T>::delete_vertexes(const std::vector<msize>& vertexes)
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](msize vertex) {return vertex < dimension(); }));

		std::set<msize> to_delete(vertexes.cbegin(), vertexes.cend());
		auto current_position = dimension() - 1;
		for (auto current_deleted : to_delete)
		{
			while (to_delete.count(current_position) == 1)
			{
				to_delete.erase(current_position);
				current_position--;
			}
			_matrix.swap(current_position, current_deleted);
			current_position--;
		}
		_matrix.delete_last_strings(vertexes.size());
	}

	template<class T>
	void OrientedMatrixGraph<T>::rearrange(const std::vector<msize>& new_nums)
	{
		_matrix.rearrange_with_allocate(new_nums);
	}
}
#endif