#pragma once

#include <cassert>
#include <set>
#include <queue>
#include <algorithm>
#include <numeric>

#include "core/utils/numeric.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/edges/symmetric_edge.hpp"

namespace graphcpp
{
	template<class SymmetricalMatrixType>
	class NonOrientedMatrixGraph : public NonOrientedGraphBase
	{
	protected:
		SymmetricalMatrixType _matrix;

	public:
		NonOrientedMatrixGraph();
		NonOrientedMatrixGraph(const std::vector<SymmetricEdge>& edges, msize dimension);
		explicit NonOrientedMatrixGraph(const NonOrientedGraphBase& other);
		explicit NonOrientedMatrixGraph(const SymmetricMatrixBase& rhs);

		template<class SymmetricMatrixTypeForwarded>
		explicit NonOrientedMatrixGraph(SymmetricMatrixTypeForwarded&& matrix);

		msize dimension() const override;
		mcontent at(msize v1, msize v2) const override;
		void set(msize v1, msize v2, mcontent value) override;

		std::vector<SymmetricEdge> get_edges() const override;
		std::unique_ptr<SymmetricMatrixBase> get_matrix() const override;
		std::unique_ptr<NonOrientedGraphBase> extract_subgraph(const std::vector<msize>& vertexes) const override;

		bool equal(const GraphBase& rhs) const override;

		std::vector<msize> get_linked_vertexes(msize vertex) const override;
		std::vector<msize> get_degrees() const override;
		msize get_degree(msize vertex) const override;

		std::list<std::pair<msize, msize>> get_hanged_vertexes() const override;
		std::vector<msize> get_connected_component(msize vertex) const override;
		std::vector<std::vector<msize>> get_connected_components() const override;

		std::vector<msize> delete_vertexes(const std::vector<msize>& vertexes) override;
		std::unique_ptr<NonOrientedGraphBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const override;
		std::unique_ptr<NonOrientedGraphBase> with_deleted_edge(msize i, msize j) const override;

		void rearrange(const std::vector<msize>& new_nums) override;
	};

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph() : 
		_matrix(0)
	{
	}

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(const std::vector<SymmetricEdge>& edges, msize dimension) :
		_matrix(dimension)
	{
		for (auto edge : edges)
		{
			assert(std::max(edge.v1(), edge.v2()) < dimension);
			set(edge.v1(), edge.v2(), edge.weight);
		}
	}

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(const NonOrientedGraphBase& other) :
		_matrix(other.get_matrix())
	{
	}

	template<class T>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(const SymmetricMatrixBase& rhs) :
		_matrix(rhs)
	{	
	}

	template<class T> template<class SymmetricMatrixTypeForwarded>
	NonOrientedMatrixGraph<T>::NonOrientedMatrixGraph(SymmetricMatrixTypeForwarded&& matrix) :
		_matrix(std::forward<SymmetricMatrixTypeForwarded>(matrix))
	{
	}

	template<class T>
	msize NonOrientedMatrixGraph<T>::dimension() const
	{
		return _matrix.dimension();
	}

	template<class T>
	mcontent NonOrientedMatrixGraph<T>::at(msize v1, msize v2) const
	{
		assert(std::max(v1, v2) < dimension());

		return _matrix.at(v1, v2);
	}

	template<class T>
	void NonOrientedMatrixGraph<T>::set(msize v1, msize v2, mcontent value)
	{
		assert(std::max(v1, v2) < dimension());

		_matrix.set(v1, v2, value);
	}

	template<class T>
	bool NonOrientedMatrixGraph<T>::equal(const GraphBase& rhs) const //TODO: Optimize, maybe add weight check
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
	std::vector<SymmetricEdge> NonOrientedMatrixGraph<T>::get_edges() const
	{
		std::vector<SymmetricEdge> result;
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
	std::unique_ptr<SymmetricMatrixBase> NonOrientedMatrixGraph<T>::get_matrix() const
	{
		return std::make_unique<T>(_matrix);
	}

	template<class T>
	std::vector<msize> NonOrientedMatrixGraph<T>::get_linked_vertexes(msize vertex) const
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
	std::list<std::pair<msize, msize>> NonOrientedMatrixGraph<T>::get_hanged_vertexes() const
	{
		std::list<std::pair<msize, msize>> result;

		for (msize i = 0; i < dimension(); i++)
		{
			auto linked_with = get_linked_vertexes(i);
			if (linked_with.size() == 1)
			{
				result.emplace_back(i, linked_with[0]);
			}
		}

		return result;
	}

	template<class T>
	std::vector<msize> NonOrientedMatrixGraph<T>::get_degrees() const
	{
		std::vector<msize> result(dimension());

		for (msize i = 0; i < dimension(); i++)
		{
			result[i] = get_degree(i);
		}

		return result;
	}

	template<class T>
	msize NonOrientedMatrixGraph<T>::get_degree(msize vertex) const
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
	std::unique_ptr<NonOrientedGraphBase> NonOrientedMatrixGraph<T>::extract_subgraph(const std::vector<msize>& vertexes) const
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) { return vertex < dimension(); }));

		T result(vertexes.size());
		for (msize i = 0; i < vertexes.size(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				result.set(i, j, _matrix.at(vertexes[i], vertexes[j]));
			}
		}

		return std::make_unique<NonOrientedMatrixGraph<T>>(std::move(result));
	}

	template<class T>
	std::vector<msize> NonOrientedMatrixGraph<T>::delete_vertexes(const std::vector<msize>& vertexes)
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](msize vertex) { return vertex < dimension(); }));

		_matrix.delete_strings(vertexes);
		
		std::vector<msize> new_nums(dimension() + vertexes.size());
		msize current = 0;
		for (msize i = 0; i < new_nums.size(); i++)
		{
			if (contains(vertexes, i))
			{
				new_nums[i] = msize_undefined;
			}
			else
			{
				new_nums[i] = current++;
			}
		}

		return new_nums;
	}

	template<class T>
	std::unique_ptr<NonOrientedGraphBase> NonOrientedMatrixGraph<T>::with_deleted_vertexes(const std::vector<msize>& vertexes) const
	{
		return std::make_unique<NonOrientedMatrixGraph<T>>(*_matrix.with_deleted_vertexes(vertexes));
	}

	template<class T>
	std::unique_ptr<NonOrientedGraphBase> NonOrientedMatrixGraph<T>::with_deleted_edge(msize i, msize j) const
	{
		return std::make_unique<NonOrientedMatrixGraph<T>>(*_matrix.with_deleted_element(i, j));
	}

	template<class T>
	void NonOrientedMatrixGraph<T>::rearrange(const std::vector<msize>& new_nums)
	{
		_matrix.rearrange_with_allocate(new_nums);
	}

	template<class T>
	std::vector<msize> NonOrientedMatrixGraph<T>::get_connected_component(msize vertex) const
	{
		assert(vertex < dimension());

		std::set<msize> result;
		std::queue<msize> queue;

		result.insert(vertex);
		queue.push(vertex);

		while (!queue.empty())
		{
			auto current_vertex = queue.front(); queue.pop();
			for (msize i = 0; i < dimension(); i++)
			{
				if (_matrix.at(current_vertex, i) > 0)
				{
					if (auto[it, success] = result.insert(i); success)
					{
						(void)it;
						queue.push(i);
					}
				}
			}
		}

		return std::vector<msize>(result.cbegin(), result.cend());
	}

	template<class T> inline
	std::vector<std::vector<msize>> NonOrientedMatrixGraph<T>::get_connected_components() const
	{
		std::vector<std::vector<msize>> result;

		std::vector<bool> used(dimension());
		msize current_vertex = 0;
		while (current_vertex != dimension())
		{
			if (used[current_vertex])
			{
				current_vertex++;
				continue;
			}
			auto current_connected_component = get_connected_component(current_vertex);
			for (auto vertex : current_connected_component)
			{
				used[vertex] = true;
			}
			result.push_back(current_connected_component);
		}

		return result;
	}
}
