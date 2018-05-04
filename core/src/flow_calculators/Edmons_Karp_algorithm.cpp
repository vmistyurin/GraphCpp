#include "core/flow_calculators.hpp"

#include <assert.h>
#include <queue>
#include <utility>

#include "boost/preprocessor.hpp"

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/graph_implementations/graph_implementations.hpp"

using namespace graphcpp;
using MatrixType = HalfSymmetricMatrix;

namespace 
{
	std::vector<msize> get_path_from_bfs_tree(const std::vector<msize>& partial_tree, msize start, msize finish)
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

	std::vector<msize> get_random_path(SymmetricMatrixBase& matrix, msize start, msize finish)
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
							return get_path_from_bfs_tree(ancestors, start, finish);
						}
						queue.push(i);
					}
				}
			}
		}
		return {};
	}
}

template<class GraphType>
mcontent flow_calculators::Edmonds_Karp_algorithm(const GraphType& graph, msize source, msize sink)
{
	assert(source != sink);
	assert(std::max(source, sink) < graph.dimension());

	auto current_flows = graph.get_matrix();
	mcontent flow = 0;

	auto path = get_random_path(*current_flows, source, sink);
	while (!path.empty())
	{
		auto min_flow = std::numeric_limits<mcontent>::max();
		for (msize i = 0; i < path.size() - 1; i++)
		{
			min_flow = std::min(min_flow, current_flows->at(path[i], path[i + 1]));
		}

		for (msize i = 0; i < path.size() - 1; i++)
		{
			current_flows->reduce_element(path[i], path[i + 1], min_flow);
		}

		flow += min_flow;
		path = get_random_path(*current_flows, source, sink);
	}

	return flow;
}

#define EDMONDS_KARP_ALGORITHM_SINGLE_MACRO(r, data, graph_type) template mcontent flow_calculators::Edmonds_Karp_algorithm<graph_type>(const graph_type&, msize, msize);
BOOST_PP_SEQ_FOR_EACH(EDMONDS_KARP_ALGORITHM_SINGLE_MACRO, 0, GRAPH_IMPLEMENTATIONS_SEQ);

template<class GraphType>
std::shared_ptr<SymmetricMatrixBase> flow_calculators::Edmonds_Karp_algorithm(const GraphType& graph)
{
	auto result = std::make_shared<MatrixType>(graph.dimension());

	for (auto[i, j] : graph)
	{
		result->set(i, j, flow_calculators::Edmonds_Karp_algorithm(graph, i, j));
	}

	return result;
}

#define EDMONDS_KARP_ALGORITHM_MATRIX_MACRO(r, data, graph_type) template std::shared_ptr<SymmetricMatrixBase> flow_calculators::Edmonds_Karp_algorithm<graph_type>(const graph_type&);
BOOST_PP_SEQ_FOR_EACH(EDMONDS_KARP_ALGORITHM_MATRIX_MACRO, 0, GRAPH_IMPLEMENTATIONS_SEQ);
