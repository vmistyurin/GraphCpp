#ifndef BENCHMARKS_TEST_FUNCTIONS_H
#define BENCHMARKS_TEST_FUNCTIONS_H

#include "core/edge.hpp"
#include "core/graph_implementation/graph_base.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

namespace graphcpp_bench
{
	namespace
	{
		template<class T> T read_graph_from_stream(std::ifstream&& stream)
		{
			unsigned int V, E;
			stream >> V >> E;

			std::vector<graphcpp::Edge> edges;
			edges.reserve(V);
			for (size_t i = 0; i < E; i++)
			{
				unsigned int v1, v2, weight;
				stream >> v1 >> v2 >> weight;
				edges.emplace_back(graphcpp::Edge(v1, v2, weight));
			}

			return T(edges, V);
		}
	}

	template<class T> std::function<std::string(std::ifstream&&)> get_test_function_matrix_of_flows()
	{
		static_assert(std::is_base_of_v<graphcpp::GraphBase, T>, "T must be descendant of GraphBase");

		return [&](std::ifstream&& input) 
		{
			auto graph = read_graph_from_stream<T>(std::move(input));
			
			return graph.get_matrix_of_flows()->to_string();
		};
	}
	
	template<class T> std::function<std::string(std::ifstream&&)> get_test_function_optimized_matrix_of_flows()
	{
		static_assert(std::is_base_of_v<graphcpp::GraphBase, T>, "T must be descendant of GraphBase");

		return [&](std::ifstream&& input)
		{
			auto graph = read_graph_from_stream<T>(std::move(input));

			return graph.optimized_get_matrix_of_flows()->to_string();
		};
	}
}

#endif