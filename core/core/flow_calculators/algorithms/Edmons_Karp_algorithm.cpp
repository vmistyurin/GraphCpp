#include "core/flow_calculators/flow_calculators.hpp"

#include <cassert>
#include <queue>
#include <algorithm>

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/matrices/non_symmetric_matrices/single_vector_matrix.hpp"
#include "core/graphs/non_oriented_graphs/non_oriented_graph_base.hpp"

using namespace graphcpp;

using MatrixType = SingleVectorMatrix;
using SymmetricMatrixType = SingleVectorSymmetricMatrix;

namespace 
{
	std::vector<msize> get_reversed_path_from_bfs_tree(const std::vector<msize>& partial_tree, msize start, msize finish)
	{
		std::vector<msize> result;

		auto current_vertex = finish;
		while (current_vertex != start)
		{
			result.push_back(current_vertex);
			current_vertex = partial_tree[current_vertex];
		}
		result.push_back(start);

		return result;
	}

	std::vector<msize> get_random_path(MatrixBase& matrix, msize start, msize finish)
	{
		assert(std::max(start, finish) < matrix.dimension());

		std::vector<msize> ancestors(matrix.dimension(), msize_undefined);
		ancestors[start] = start;
		std::queue<msize> queue;

		queue.push(start);

		while (!queue.empty())
		{
			const auto current_vertex = queue.front(); queue.pop();
			for (msize i = 0; i < matrix.dimension(); i++)
			{
				if (matrix.at(current_vertex, i) > 0 && (ancestors[i] == msize_undefined))
				{
					ancestors[i] = current_vertex;
					if (finish == i)
					{
						return get_reversed_path_from_bfs_tree(ancestors, start, finish);
					}
					queue.push(i);
				}
			}
		}
		return {};
	}
}

mcontent flow_calculators::Edmonds_Karp_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink)
{
	assert(source != sink);
	assert(std::max(source, sink) < graph.dimension());

	MatrixType current_flows(*graph.get_matrix());
	mcontent flow = 0;

	auto path = get_random_path(current_flows, source, sink);
	while (!path.empty())
	{
		auto min_flow = std::numeric_limits<mcontent>::max();
		for (msize i = 0; i < path.size() - 1; i++)
		{
			min_flow = std::min(min_flow, current_flows.at(path[i + 1], path[i]));
		}

		for (msize i = 0; i < path.size() - 1; i++)
		{
			current_flows.reduce_element(path[i + 1], path[i], min_flow);
			current_flows.reduce_element(path[i], path[i + 1], -min_flow);
		}

		flow += min_flow;
		path = get_random_path(current_flows, source, sink);
	}

	return flow;
}
