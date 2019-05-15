#pragma once

#include "core/matrices/non_symmetric_matrices/single_vector_matrix.hpp"
#include "core/graphs/oriented_graphs/oriented_matrix_graph.hpp"

namespace graphcpp::flow_calculators::internal
{
	template<class NorGraphType>
	std::pair<std::vector<msize>, std::vector<msize>> minimal_cut(const NorGraphType& graph, msize u, msize v)
	{
		auto graph = OrientedMatrixGraph<SingleVectorMatrix>(copy);

		auto wrapped_path = get_random_path(graph, u, v);
		while (wrapped_path)
		{
			Defer defer([&] { wrapped_path = get_random_path(graph, source, sink); });
			const auto path = wrapped_path.value();

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
		}

		auto component = get_connected_component(graph, u);

		return std::pair(
			component,
			find_addition(component, graph.dimension())
		)
	}

	std::optional<std::pair<msize, msize>> pick_vertexes(std::vector<std::vector<msize>>& vertexes)
	{
		for (msize i = 0; i < vertexes.size(); i++)
		{
			auto& component = vertexes[i];
			if (component.size() > 1)
			{
				const auto u = component[0];
				const auto v = component[1];

				component.erase(std::find(component.cbegin(), component.cend(), u));
				component.erase(std::find(component.cbegin(), component.cend(), v));

				vertexes.emplace_back(std::vector<msize>({ u }));
				vertexes.emplace_back(std::vector<msize>({ v }));
			}
		}

		return std::nullopt;
	}
}

namespace graphcpp::flow_calculators
{
	template<class NorGraphType, class SymMatrixType>
	SymMatrixType Gomory_Hu_algorithm(const NorGraphType& graph)
	{
		NorGraphType result_tree();

		std::vector<msize> all_vertexes(graph.dimension());
		std::iota(all_vertexes.begin(), all_vertexes.end(), 0);

		std::vector<std::vector<msize>> vertexes = { std::move(all_vertexes) };

		auto wrapped_pair = internal::pick_vertexes(vertexes);
		while (wrapped_pair)
		{
			Defer defer([&] { wrapped_pair = internal::pick_vertexes(vertexes); });
			const auto[u, v] = wrapped_pair.value();

			const auto [first_cut, second_cut] = internal::minimal_cut(graph, u, v);

			NorGraphType.add_vertex();

		}

	}
}