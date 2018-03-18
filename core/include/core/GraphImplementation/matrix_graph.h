#ifndef GRAPH_CORE_MATRIX_GRAPH_H
#define GRAPH_CORE_MATRIX_GRAPH_H

#include "core/MatrixImplementation/symmetric_matrix_base.h"
#include "core/GraphImplementation/graph_base.h"
#include "core/macroses.h"
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

		msize dimension() const override;
		bool equal(const GraphBase& other) const override;
		const SymmetricMatrixBase& get_matrix() const override;
		std::vector<Edge> get_edges() const override;

		std::vector<msize> get_linked_vertexes(msize vertex) const override;
		std::list<std::pair<msize, msize>> get_hanged_vertexes() const override;
		std::vector<msize> get_degrees() const override;
		msize get_degree(msize vertex) const override;

		std::vector<msize> get_connected_component(msize vertex) const override;
		std::vector<std::vector<msize>> get_connected_components() const override;

		mcontent get_flow(msize source, msize sink) const override;
		std::shared_ptr<SymmetricMatrixBase> get_matrix_of_flows() const override;
		std::shared_ptr<SymmetricMatrixBase> optimized_get_matrix_of_flows() const override;

		void delete_vertexes(const std::vector<msize>& vertexes) override;
		void rearrange(const std::vector<msize>& new_nums) override;
	private:
		bool is_connected(msize vertex1, msize vertex2);
	};

	namespace
	{
		constexpr mcontent flow_to_compute = -1;
		constexpr mcontent hanged_vertex_not_linked = -2;
		constexpr mcontent hanged_vertex_linked = -3;

		std::vector<msize> get_random_path(const SymmetricMatrixBase& matrix, msize start, msize finish)
		{
			assert(std::max(start, finish) < matrix.dimension());

			std::vector<msize> ancestors(matrix.dimension(), msize_undefined);
			ancestors[start] = start;
			std::queue<msize> queue;

			queue.push(start);

			while (!queue.empty())
			{
				auto current_vertex = queue.front(); queue.pop();
				for (msize i = 0; i < matrix.dimension(); i++)
				{
					if (matrix.at(current_vertex, i) > 0)
					{
						if (ancestors[i] == msize_undefined)
						{
							ancestors[i] = current_vertex;
							if (finish == i)
							{
								goto success;
							}
							queue.push(i);
						}
					}
				}
			}
			return {};

		success:
			std::vector<msize> result;

			auto current_vertex = finish;
			while (current_vertex != start)
			{
				result.push_back(current_vertex);
				current_vertex = ancestors[current_vertex];
			}
			result.push_back(start);

			return result;
		}
	}

	template<typename T>
	inline MatrixGraph<T>::MatrixGraph() :
		_matrix(0)
	{
	}

	template<typename T>
	inline MatrixGraph<T>::MatrixGraph(const std::vector<Edge>& edges, msize dimension) :
		_matrix(dimension)
	{
		for (const auto& edge : edges)
		{
			assert(std::max(edge.v1(), edge.v2()) < dimension);
			_matrix.set(edge.v1(), edge.v2(), edge.weight);
		}
	}

	template<typename T> inline 
	MatrixGraph<T>::MatrixGraph(const GraphBase& other) :
		_matrix(other.get_matrix())
	{
	}

	template<typename T> inline 
	msize MatrixGraph<T>::dimension() const
	{
		return _matrix.dimension();
	}

	template<typename T> inline
	bool MatrixGraph<T>::equal(const GraphBase& other) const //TODO: Optimize, maybe add weight check
	{
		RETURN_IF(this == &other, true);
		RETURN_IF(dimension() != other.dimension(), false);

		auto this_degrees = get_degrees();
		auto other_degrees = other.get_degrees();
		RETURN_IF(!std::is_permutation(this_degrees.cbegin(), this_degrees.cend(), other_degrees.cbegin()), false);

		std::vector<msize> permutation(dimension());
		std::iota(permutation.begin(), permutation.end(), 0);

		MatrixGraph other_copy(other);
		do
		{
			other_copy.rearrange(permutation);
			RETURN_IF(_matrix == other_copy.get_matrix(), true);
		} while (std::next_permutation(permutation.begin(), permutation.end()));

		return false;
	}

	template<typename T> inline
	const SymmetricMatrixBase& MatrixGraph<T>::get_matrix() const
	{
		return _matrix;
	}

	template<typename T> inline
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

	template<typename T> inline
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

	template<typename T> inline
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

	template<typename T> inline
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

	template<typename T> inline
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

	template<typename T> inline
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

	template<typename T> inline
	void MatrixGraph<T>::rearrange(const std::vector<msize>& new_nums)
	{
		MatrixGraph<T>::_matrix.rearrange(new_nums);
	}

	template<typename T> inline
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
						auto de_it = *it; //to prevent compiler warning
						queue.push(i);
					}
				}
			}
		}

		return std::vector<msize>(result.cbegin(), result.cend());
	}

	template<typename T> inline
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

	template<typename T> inline
	mcontent MatrixGraph<T>::get_flow(msize source, msize sink) const
	{
		assert(source != sink);
		assert(std::max(source, sink) < dimension());

		auto current_flows = _matrix;
		mcontent flow = 0;
		auto path = get_random_path(current_flows, source, sink);
		while (!path.empty())
		{
			auto min_flow = std::numeric_limits<mcontent>::max();
			for (msize i = 0; i < path.size() - 1; i++)
			{
				min_flow = std::min(min_flow, current_flows.at(path[i], path[i + 1]));
			}

			for (msize i = 0; i < path.size() - 1; i++)
			{
				current_flows.reduce_element(path[i], path[i + 1], min_flow);
			}
			flow += min_flow;
			path = get_random_path(current_flows, source, sink);
		}

		return flow;
	}

	template<typename T> inline
	std::shared_ptr<SymmetricMatrixBase> MatrixGraph<T>::get_matrix_of_flows() const
	{
		auto result = std::make_shared<T>(dimension());

		for (msize i = 1; i < dimension(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				result->set(i, j, get_flow(i, j));
			}
		}

		return result;
	}

	template<typename T> inline
	std::shared_ptr<SymmetricMatrixBase> MatrixGraph<T>::optimized_get_matrix_of_flows() const
	{
		auto result = std::make_shared<T>(dimension());

		auto components = get_connected_components();
		for (const auto& component : components)
		{
			for (msize i = 0; i < component.size(); i++)
			{
				for (msize j = i + 1; j < component.size(); j++)
				{
					result->set(component[i], component[j], flow_to_compute);
				}
			}
		}

		auto hanged_vertexes = get_hanged_vertexes();
		for (auto current = hanged_vertexes.cbegin(); !hanged_vertexes.empty() && current != hanged_vertexes.cend(); ++current)
		{
			auto standalone_pair = false;
			for (auto suspect = std::next(current); suspect != hanged_vertexes.cend(); ++suspect)
			{
				if (current->first == suspect->second)
				{
					result->set(current->first, current->second, _matrix.at(current->first, current->second));
					hanged_vertexes.erase(suspect);
					current = hanged_vertexes.erase(current);
					standalone_pair = true;
					break;
				}
			}
			if (standalone_pair)
			{
				if (current == hanged_vertexes.cend())
				{
					break;
				}
				continue;
			}

			for (msize j = 0; j < dimension(); j++)
			{
				if (result->at(current->first, j) == flow_to_compute)
				{
					result->set(current->first, j, hanged_vertex_not_linked);
				}
			}
			result->set(current->first, current->second, _matrix.at(current->first, current->second));
		}


		for (msize i = 1; i < dimension(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				if (result->at(i, j) == flow_to_compute)
				{
					result->set(i, j, get_flow(i, j));
					continue;
				}
			}
		}

		for (const auto&[hanged, support] : hanged_vertexes)
		{
			for (msize i = 0; i < dimension(); i++)
			{
				if (result->at(hanged, i) != 0 && support != i)// && result->at(support, i) != hanged_vertex_not_linked)
				{
					auto flow_from_support_to_i = result->at(i, support);
					assert(flow_from_support_to_i != flow_to_compute);

					auto flow_from_support_to_hanged = _matrix.at(hanged, support);

					result->set(hanged, i, std::min(flow_from_support_to_hanged, flow_from_support_to_i));
				}
			}
		}

		return result;
	}

	template<typename T> inline
	bool MatrixGraph<T>::is_connected(msize vertex1, msize vertex2)
	{
		std::queue<msize> queue;
		queue.insert(vertex1);

		while (!queue.empty())
		{
			auto current_vertex = queue.front(); queue.pop();
			for (msize i = 0; i < dimension(); i++)
			{
				if (_matrix.at(current_vertex, i) > 0)
				{
					if (auto[it, success] = result.insert(i); success)
					{
						*it; //to prevent compiler warning
						RETURN_IF(vertex2 == i, true)
							queue.push(i);
					}
				}
			}
		}

		return false;
	}
}
#endif