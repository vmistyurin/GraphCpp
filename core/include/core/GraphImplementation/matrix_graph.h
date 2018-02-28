#ifndef GRAPH_CORE_MATRIX_GRAPH_H
#define GRAPH_CORE_MATRIX_GRAPH_H

#include "core/MatrixImplementation/symmetric_matrix_base.h"
#include "core/GraphImplementation/graph_base.h"
#include "core/macroses.h"
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>
#include <type_traits>
#include <assert.h>

namespace graphcpp
{
	namespace
	{
		std::vector<msize> get_random_path(const SymmetricMatrixBase& matrix, msize start, msize finish)
		{
			assert(std::max(start, finish) < matrix.dimension());

			std::vector<msize> ancestors(matrix.dimension());
			std::queue<msize> queue;

			queue.push(start);

			while (!queue.empty())
			{
				auto current_vertex = queue.front(); queue.pop();
				for (msize i = 0; i < matrix.dimension(); i++)
				{
					if (matrix.at(current_vertex, i) > 0)
					{
						if (ancestors[i] == 0)
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

	template<class SymmetricMatrixType> class MatrixGraph final : public GraphBase
	{
	private:
		SymmetricMatrixType _matrix;

	public:
		MatrixGraph() :
			_matrix(0)
		{}

		explicit MatrixGraph(const std::vector<Edge>& edges, msize dimension) :
			_matrix(dimension)
		{
			for (const auto& edge : edges)
			{
				assert(std::max(edge.v1(), edge.v2()) < dimension);
				_matrix.set(edge.v1(), edge.v2(), edge.weight);
			}
		}

		explicit MatrixGraph(const GraphBase& other) :
			_matrix(other.get_matrix())
		{}

		msize dimension() const override
		{
			return _matrix.dimension();
		}

		bool equal(const GraphBase& other) const override //TODO: Optimize, maybe add weight check
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

		const SymmetricMatrixBase& get_matrix() const override
		{
			return _matrix;
		}

		std::vector<Edge> get_edges() const override
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

		std::vector<msize> get_linked_vertexes(msize vertex) const override
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

		std::vector<std::pair<msize, msize>> get_hanged_vertexes() const
		{			
			std::vector<msize> hanged_vertexes;
			auto degrees = get_degrees();
			for (msize i = 0; i < degrees.size(); i++)
			{
				if (degrees[i] == 1)
				{
					hanged_vertexes.push_back(i);
				}
			}

			std::vector<std::pair<msize, msize>> result; result.reserve(hanged_vertexes.size());
			for (auto vertex : hanged_vertexes)
			{
				result.emplace_back(vertex, get_linked_vertexes(vertex)[0]);
			}

			return result;
		}

        std::vector<msize> get_degrees() const override
        {
			std::vector<msize> result; result.reserve(dimension());
			for (msize i = 0; i < dimension(); i++)
            {
                msize current_degree = 0;
                for(msize j = 0; j < dimension(); j++)
                {
                    if(_matrix.at(i,j) > 0)
                    {
                        current_degree++;
                    }
                }
                result.push_back(current_degree);
            }
            return result;
        }

		msize get_degree(msize vertex) const override
		{
			assert(vertex < dimension());

			msize result = 0;
			for(msize i = 0; i < dimension(); i++)
			{
				if(_matrix.at(vertex, i) > 0)
				{
					result++;
				}
			}
			return result;
		}

		void delete_vertexes(const std::vector<msize>& vertexes) override
		{
			assert(!vertexes.empty());
			assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](msize vertex){return vertex < dimension();}));

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

		void rearrange(const std::vector<msize>& new_nums) override
		{
			_matrix.rearrange(new_nums);
		}

		std::vector<msize> get_connected_component(msize vertex) const override
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
							*it; //to prevent compiler warning
							queue.push(i);
						}
					}
				}
			}

			return std::vector<msize>(result.cbegin(), result.cend());
		}

		std::vector<std::vector<msize>> get_connected_components() const override
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


		mcontent get_flow(msize source, msize sink) const override
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

		std::shared_ptr<SymmetricMatrixBase> get_matrix_of_flows() const override
		{
			SymmetricMatrixType matrix(dimension());

			for (msize i = 1; i < dimension(); i++)
			{
				for (msize j = 0; j < i; j++)
				{
					matrix.set(i, j, get_flow(i, j));
				}
			}

			return std::make_shared<SymmetricMatrixType>(matrix);
		}

	private:
		bool is_connected(msize vertex1, msize vertex2) 
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
	};
}
#endif