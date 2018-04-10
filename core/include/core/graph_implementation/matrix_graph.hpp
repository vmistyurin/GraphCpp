#ifndef GRAPH_CORE_MATRIX_GRAPH_HPP
#define GRAPH_CORE_MATRIX_GRAPH_HPP

#include "core/matrix_implementation/symmetric_matrix_base.hpp"
#include "core/graph_implementation/graph_base.hpp"
#include "core/macroses.hpp"
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>
#include <assert.h>

namespace graphcpp
{
	template<class SymmetricMatrixType> class MatrixGraph final : public GraphBase
	{
	private:
		SymmetricMatrixType _matrix;

	public:
		MatrixGraph();
		MatrixGraph(const std::vector<Edge>& edges, msize dimension);
		explicit MatrixGraph(const GraphBase& other);

		template<class V>
		explicit MatrixGraph(V&& matrix);

		msize dimension() const override;
		mcontent at(msize v1, msize v2) const;
		void set(msize v1, msize v2, mcontent value);

		bool equal(const GraphBase& other) const override;
		std::shared_ptr<SymmetricMatrixBase> get_matrix() const override;
		std::vector<Edge> get_edges() const override;

		std::vector<msize> get_linked_vertexes(msize vertex) const override;
		std::list<std::pair<msize, msize>> get_hanged_vertexes() const override;
		std::vector<msize> get_degrees() const override;
		msize get_degree(msize vertex) const override;
		std::shared_ptr<GraphBase> extract_subgraph(const std::vector<msize>& vertexes) const override;

		std::vector<msize> get_connected_component(msize vertex) const override;
		std::vector<std::vector<msize>> get_connected_components() const override;

		void delete_vertexes(const std::vector<msize>& vertexes) override;
		void rearrange(const std::vector<msize>& new_nums) override;
	};

	namespace
	{
		bool is_matrix_from_graph(const SymmetricMatrixBase& first, const GraphBase& second)
		{
			for (auto[i, j] : second)
			{
				RETURN_IF(first.at(i, j) != second.at(i, j), false);
			}
			return true;
		}
	}

	template<class T> inline
	MatrixGraph<T>::MatrixGraph() :
		_matrix(0)
	{
	}

	template<class T> inline
	MatrixGraph<T>::MatrixGraph(const std::vector<Edge>& edges, msize dimension) :
		_matrix(dimension)
	{
		for (const auto& edge : edges)
		{
			assert(std::max(edge.v1(), edge.v2()) < dimension);
			_matrix.set(edge.v1(), edge.v2(), edge.weight);
		}
	}

	template<class T> inline
	MatrixGraph<T>::MatrixGraph(const GraphBase& other) :
		_matrix(other.get_matrix())
	{
	}

	template<class T> template<class V>  inline
	MatrixGraph<T>::MatrixGraph(V&& matrix) :
		_matrix(std::forward<V>(matrix))
	{

	}

	template<class T> inline
	msize MatrixGraph<T>::dimension() const
	{
		return _matrix.dimension();
	}

	template<class T> inline
	mcontent MatrixGraph<T>::at(msize v1, msize v2) const
	{
		assert(std::max(v1, v2) < dimension());

		return _matrix.at(v1, v2);
	}

	template<class T> inline
	void MatrixGraph<T>::set(msize v1, msize v2, mcontent value)
	{
		assert(std::max(v1, v2) < dimension());

		_matrix.set(v1, v2, value);
	}

	template<class T> inline
	bool MatrixGraph<T>::equal(const GraphBase& other) const //TODO: Optimize, maybe add weight check
	{
		RETURN_IF(this == &other, true);
		RETURN_IF(dimension() != other.dimension(), false);

		auto this_degrees = get_degrees();
		auto other_degrees = other.get_degrees();
		RETURN_IF(!std::is_permutation(this_degrees.cbegin(), this_degrees.cend(), other_degrees.cbegin()), false);

		std::vector<msize> permutation(dimension());
		std::iota(permutation.begin(), permutation.end(), 0);

		std::shared_ptr<T> this_copy = std::make_shared<T>(_matrix);
		do
		{
			_matrix.make_rearranged(permutation, this_copy);
			RETURN_IF(is_matrix_from_graph(*this_copy, other), true);
		} while (std::next_permutation(permutation.begin(), permutation.end()));

		return false;
	}

	template<class T> inline
	std::shared_ptr<SymmetricMatrixBase> MatrixGraph<T>::get_matrix() const
	{
		return std::make_shared<T>(_matrix);
	}

	template<class T> inline
	std::vector<Edge> MatrixGraph<T>::get_edges() const
	{
		std::vector<Edge> result;
		for (msize i = 1; i < dimension(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				if (_matrix.at(i, j) != 0)
				{
					result.emplace_back(i, j, _matrix.at(i, j));
				}
			}
		}
		return result;
	}

	template<class T> inline
	std::vector<msize> MatrixGraph<T>::get_linked_vertexes(msize vertex) const
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

	template<class T> inline
	std::list<std::pair<msize, msize>> MatrixGraph<T>::get_hanged_vertexes() const
	{
		std::list<std::pair<msize, msize>> result;

		for (msize i = 0; i < dimension(); i++)
		{
			auto linked_with = get_linked_vertexes(i);
			if (linked_with.size() == 1)
			{
				result.emplace_front(i, linked_with[0]);
			}
		}

		return result;
	}

	template<class T> inline
	std::vector<msize> MatrixGraph<T>::get_degrees() const
	{
		std::vector<msize> result; result.reserve(dimension());
		for (msize i = 0; i < dimension(); i++)
		{
			msize current_degree = 0;
			for (msize j = 0; j < dimension(); j++)
			{
				if (_matrix.at(i, j) > 0)
				{
					current_degree++;
				}
			}
			result.push_back(current_degree);
		}
		return result;
	}

	template<class T> inline
	msize MatrixGraph<T>::get_degree(msize vertex) const
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

	template<class T> inline
	std::shared_ptr<GraphBase> MatrixGraph<T>::extract_subgraph(const std::vector<msize>& vertexes) const
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) {return vertex < dimension(); }));

		T result(vertexes.size());
		for (msize i = 0; i < vertexes.size(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				result.set(i, j, _matrix.at(vertexes[i], vertexes[j]));
			}
		}

		return std::make_shared<MatrixGraph<T>>(std::move(result));
	}

	template<class T> inline
	void MatrixGraph<T>::delete_vertexes(const std::vector<msize>& vertexes)
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](msize vertex) {return vertex < dimension(); }));

		std::set<msize> to_delete(vertexes.cbegin(), vertexes.cend());
		msize current_position = dimension() - 1;
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

	template<class T> inline
	void MatrixGraph<T>::rearrange(const std::vector<msize>& new_nums)
	{
		_matrix.rearrange_with_allocate(new_nums);
	}

	template<class T> inline
	std::vector<msize> MatrixGraph<T>::get_connected_component(msize vertex) const
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
						(void)it; //to prevent compiler warning
						queue.push(i);
					}
				}
			}
		}

		return std::vector<msize>(result.cbegin(), result.cend());
	}

	template<class T> inline
	std::vector<std::vector<msize>> MatrixGraph<T>::get_connected_components() const
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
#endif