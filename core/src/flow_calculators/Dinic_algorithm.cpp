#include "core/flow_calculators.hpp"

#include <cassert>
#include <queue>

#include "boost/preprocessor.hpp"

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/matrix.hpp"
#include "core/graph_implementations/graph_implementations.hpp"
#include "core/graph_implementations/oriented_graphs/oriented_matrix_graph.hpp"

using namespace graphcpp;
using MatrixType = FullSymmetricMatrix;

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

	void dfs(const GraphBase& graph, msize current, msize finish, std::vector<msize>& ancestors, msize depth = 0)
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
				dfs(graph, i, finish, ancestors, depth + 1);
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

	template<class GraphType>	
	mcontent Single_Dinic_algorithm_typed(GraphType _graph, msize source, msize sink)
	{
		assert(source != sink);
		assert(std::max(source, sink) < _graph.dimension());

		mcontent flow = 0;
			
		OrientedMatrixGraph<Matrix> matrix_graph(_graph);
		auto layers = get_layers(matrix_graph, source);

		while (layers[sink] != msize_undefined)
		{
			auto layered_network = get_layered_network<OrientedMatrixGraph<Matrix>>(matrix_graph, layers, source);

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
}

template<class GraphType>
mcontent flow_calculators::Dinic_algorithm(const GraphType& graph, msize source, msize sink)
{
	return Single_Dinic_algorithm_typed(graph, source, sink);
}

#define DINIC_ALGORITHM_SINGLE_MACRO(r, data, graph_type) template mcontent flow_calculators::Dinic_algorithm<graph_type>(const graph_type&, msize, msize);
BOOST_PP_SEQ_FOR_EACH(DINIC_ALGORITHM_SINGLE_MACRO, 0, NON_ORIENTED_GRAPH_IMPLEMENTATIONS_SEQ)

template<class GraphType>
std::shared_ptr<SymmetricMatrixBase> flow_calculators::Dinic_algorithm(const GraphType& graph)
{
	auto result = std::make_shared<MatrixType>(graph.dimension());

	for (auto[i, j] : graph)
	{
		result->set(i, j, Single_Dinic_algorithm_typed<GraphType>(graph, i, j));
	}

	return result;
}

#define DINIC_ALGORITHM_MATRIX_MACRO(r, data, graph_type) template std::shared_ptr<SymmetricMatrixBase> flow_calculators::Dinic_algorithm<graph_type>(const graph_type&);
BOOST_PP_SEQ_FOR_EACH(DINIC_ALGORITHM_MATRIX_MACRO, 0, NON_ORIENTED_GRAPH_IMPLEMENTATIONS_SEQ)