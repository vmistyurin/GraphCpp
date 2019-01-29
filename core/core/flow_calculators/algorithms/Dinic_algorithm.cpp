#include "core/flow_calculators/flow_calculators.hpp"

#include <cassert>
#include <queue>

#include "core/matrices/non_symmetric_matrices/single_vector_matrix.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/graphs/oriented_graphs/oriented_matrix_graph.hpp"

using namespace graphcpp;

using MatrixType = SingleVectorMatrix;
using SymmetricMatrixType = SingleVectorSymmetricMatrix;

using GraphType = OrientedMatrixGraph<MatrixType>;

namespace
{
	std::vector<msize> get_layers(const GraphBase& graph, msize start)
	{
		assert(start < graph.dimension());

		std::vector<msize> layers(graph.dimension(), msize_undefined);
		layers[start] = 0;

		std::queue<msize> queue;
		queue.push(start);

		while (!queue.empty())
		{
			const auto current = queue.front(); queue.pop();

			for (msize i = 0; i < graph.dimension(); i++)
			{
				if (graph.at(current, i) > 0 && layers[i] == msize_undefined)
				{
					layers[i] = layers[current] + 1;
					queue.push(i);
				}
			}
		}

		return layers;
	}

	template<class GraphType>	
	GraphType get_layered_network(const GraphType& graph, const std::vector<msize>& layers, msize start)
	{
		assert(start < graph.dimension());
		assert(layers.size() == graph.dimension());

		GraphType result(graph);
		
		for (auto[i, j] : result)
		{
			if (result.at(i, j) > 0 && layers[i] == layers[j] + 1)
			{
				result.set(i, j, 0);
			}
		}

		return result;
	}

	void dfs(const GraphBase& graph, msize current, msize finish, std::vector<msize>& ancestors)
	{
		assert(current < graph.dimension());
		
		for (msize i = 0; i < graph.dimension(); i++)
		{
			if (graph.at(current, i) > 0 && ancestors[i] == msize_undefined)
			{
				ancestors[i] = current;
				if (i == finish)
				{
					return;
				}
				dfs(graph, i, finish, ancestors);
			}
		}
	}

	template<class GraphType>
	std::vector<msize> get_path(const GraphType& graph, msize start, msize finish)
	{
		assert(start != finish);
		assert(std::max(start, finish) < graph.dimension());

		std::vector<msize> partial_dfs_tree(graph.dimension(), msize_undefined);
		partial_dfs_tree[start] = start;

		dfs(graph, start, finish, partial_dfs_tree);

		RETURN_IF(partial_dfs_tree[finish] == msize_undefined, {});

		std::vector<msize> result;

		auto current = finish;
		while (current != start)
		{
			result.push_back(current);
			current = partial_dfs_tree[current];
		}

		result.push_back(current);

		std::reverse(result.begin(), result.end());
		return result;
	}
}

mcontent flow_calculators::Dinic_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink)
{
	assert(source != sink);
	assert(std::max(source, sink) < graph.dimension());

	mcontent flow = 0;

	GraphType matrix_graph(graph);
	auto layers = get_layers(matrix_graph, source);

	while (layers[sink] != msize_undefined)
	{
		auto layered_network = get_layered_network<GraphType>(matrix_graph, layers, source);

		auto path = get_path(layered_network, source, sink);
		while (!path.empty())
		{
			mcontent min_flow = std::numeric_limits<mcontent>::max();

			for (msize i = 0; i < path.size() - 1; i++)
			{
				min_flow = std::min(min_flow, layered_network.at(path[i], path[i + 1]));
			}

			for (msize i = 0; i < path.size() - 1; i++)
			{
				layered_network.set(path[i], path[i + 1], layered_network.at(path[i], path[i + 1]) - min_flow);
				layered_network.set(path[i + 1], path[i], layered_network.at(path[i + 1], path[i]) + min_flow);


				matrix_graph.set(path[i], path[i + 1], matrix_graph.at(path[i], path[i + 1]) - min_flow);
				matrix_graph.set(path[i + 1], path[i], matrix_graph.at(path[i + 1], path[i]) + min_flow);
			}

			flow += min_flow;
			path = get_path(layered_network, source, sink);
		}
		layers = get_layers(matrix_graph, source);
	}
	return flow;
}
