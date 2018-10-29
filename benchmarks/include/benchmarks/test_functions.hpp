#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#include "core/all.hpp"

namespace graphcpp_bench
{
	namespace
	{
		template<class T> 
		T read_graph_from_stream(std::ifstream&& stream)
		{
			unsigned int V, E;
			stream >> V >> E;

			std::vector<graphcpp::SymmetricEdge> edges;
			edges.reserve(V);
			for (size_t i = 0; i < E; i++)
			{
				unsigned int v1, v2, weight;
				stream >> v1 >> v2 >> weight;
				edges.emplace_back(graphcpp::SymmetricEdge(v1, v2, weight));
			}

			return T(edges, V);
		}
	}

	template<class T> 
	std::function<std::string(std::ifstream&&)> Edmonds_Karp_algorithm()
	{
		static_assert(std::is_base_of_v<graphcpp::GraphBase, T>, "T must be descendant of GraphBase");

		return [&](std::ifstream&& input) 
		{
			auto graph = read_graph_from_stream<T>(std::move(input));
			
			return graphcpp::flow_calculators::matrix_of_flows(graph, graphcpp::flow_calculators::Edmonds_Karp_algorithm)->to_string();
		};
	}

	template<class T>
	std::function<std::string(std::ifstream&&)> Dinic_algorithm()
	{
		static_assert(std::is_base_of_v<graphcpp::GraphBase, T>, "T must be descendant of GraphBase");

		return [&](std::ifstream&& input)
		{
			auto graph = read_graph_from_stream<T>(std::move(input));

			return graphcpp::flow_calculators::matrix_of_flows(graph, graphcpp::flow_calculators::Dinic_algorithm)->to_string();
		};
	}

	template<class T>
	std::function<std::string(std::ifstream&&)> preflow_push_algorithm()
	{
		static_assert(std::is_base_of_v<graphcpp::GraphBase, T>, "T must be descendant of GraphBase");

		return [&](std::ifstream&& input)
		{
			auto graph = read_graph_from_stream<T>(std::move(input));

			return graphcpp::flow_calculators::matrix_of_flows(graph, graphcpp::flow_calculators::preflow_push_algorithm)->to_string();
		};
	}

	template<class T>
	std::function<std::string(std::ifstream&&)> reduction_use_algorithm(
		const std::function<graphcpp::mcontent(const graphcpp::NonOrientedGraphBase&, graphcpp::msize, graphcpp::msize)>& base_function)
	{
		static_assert(std::is_base_of_v<graphcpp::GraphBase, T>, "T must be descendant of GraphBase");

		return [&](std::ifstream&& input)
		{
			auto graph = read_graph_from_stream<T>(std::move(input));

			return graphcpp::flow_calculators::reduction_use_algorithm(graph, base_function)->to_string();
		};
	}
    
    template<class T>
    std::function<std::string(std::ifstream&&)> single_threaded_matrix_of_flows(graphcpp::flow_function&& base_function)
    {
        static_assert(std::is_base_of_v<graphcpp::RandomNonOrientedGraphBase, T>, "T must be descendant of RandomNonOrientedGraphBase");
        
        return [&](std::ifstream&& input)
        {
            auto graph = std::make_unique<T>(T::read_from_stream(input));
            
            auto calculator = graphcpp::SingleThreadCalculator(std::move(graph), std::move(base_function));
            
            return calculator.expected_value()->to_string();
        };
    }
    
    template<class T>
    std::function<std::string(std::ifstream&&)> multi_threaded_matrix_of_flows(graphcpp::flow_function&& base_function)
    {
        static_assert(std::is_base_of_v<graphcpp::RandomNonOrientedGraphBase, T>, "T must be descendant of RandomNonOrientedGraphBase");
        
        return [&](std::ifstream&& input)
        {
            auto graph = std::make_unique<T>(T::read_from_stream(input));

            auto calculator = graphcpp::MultiThreadCalculator(std::move(graph), std::move(base_function));
            
            return calculator.expected_value()->to_string();
        };
    }
}
