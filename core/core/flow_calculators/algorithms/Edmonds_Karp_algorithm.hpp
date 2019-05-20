#pragma once

#include <cassert>
#include <queue>
#include <algorithm>

#include "core/macroses.hpp"
#include "core/utils/defer.hpp"
#include "core/matrices/non_symmetric_matrices/single_vector_matrix.hpp"
#include "core/graphs/oriented_graphs/oriented_matrix_graph.hpp"

namespace graphcpp::flow_calculators
{
	template<class NorGraphType>
	mcontent Edmonds_Karp_algorithm(NorGraphType copy, msize source, msize sink)
	{
		IS_NOR_GRAPH_IMPL(NorGraphType);

		assert(source != sink);
		assert(std::max(source, sink) < copy.dimension());

		mcontent flow = 0;

		auto graph = OrientedMatrixGraph<SingleVectorMatrix>(copy);

		auto wrapped_path = get_random_path(graph, source, sink);
		while (wrapped_path)
		{
			Defer defer([&] { wrapped_path = get_random_path(graph, source, sink); });
            const auto path = wrapped_path.value_or(std::vector<msize>({}));
			// wrapped_path.value();

			auto min_flow = std::numeric_limits<mcontent>::max();
			for (msize i = 0; i < path.size() - 1; i++)
			{
				min_flow = std::min(min_flow, graph.at(path[i + 1], path[i]));
			}

			for (msize i = 0; i < path.size() - 1; i++)
			{
				graph.reduce_edge(path[i + 1], path[i], min_flow);
				graph.reduce_edge(path[i], path[i + 1], -min_flow);
			}

			flow += min_flow;
		}

		return flow;
	}
}
