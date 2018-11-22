#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>

#include "core/all.hpp"

namespace graphcpp_bench
{
    template<class RandomGraphType>
    std::function<std::string(std::ifstream&&)> single_threaded_matrix_of_flows(graphcpp::flow_function&& base_function)
    {
        static_assert(std::is_base_of_v<graphcpp::RandomNonOrientedGraphBase, RandomGraphType>, "T must be descendant of RandomNonOrientedGraphBase");
        
        return [base_function = std::move(base_function)](std::ifstream&& input)
        {
            auto function = std::move(base_function);

            auto graph = std::make_unique<RandomGraphType>(RandomGraphType::read_from_stream(input));
            
            auto calculator = graphcpp::SingleThreadCalculator(std::move(graph), std::move(function));
            
            return calculator.expected_value()->to_string();
        };
    }
    
    template<class RandomGraphType>
    std::function<std::string(std::ifstream&&)> single_threaded_matrix_of_flows(graphcpp::single_flow_function&& base_function)
    {
        return single_threaded_matrix_of_flows<RandomGraphType>([base_function = std::move(base_function)](const graphcpp::NonOrientedGraphBase& graph)
        {
            return graphcpp::flow_calculators::matrix_of_flows(graph, base_function);
        });
    }
    
    template<class RandomGraphType>
    std::function<std::string(std::ifstream&&)> multi_threaded_matrix_of_flows(graphcpp::flow_function&& base_function)
    {
        static_assert(std::is_base_of_v<graphcpp::RandomNonOrientedGraphBase, RandomGraphType>, "T must be descendant of RandomNonOrientedGraphBase");
        
        return [base_function = std::move(base_function)](std::ifstream&& input)
        {
            auto function = std::move(base_function);
            
            auto graph = std::make_unique<RandomGraphType>(RandomGraphType::read_from_stream(input));

            auto calculator = graphcpp::MultiThreadCalculator(std::move(graph), std::move(function));
            
            return calculator.expected_value()->to_string();
        };
    }
    
    template<class RandomGraphType>
    std::function<std::string(std::ifstream&&)> multi_threaded_matrix_of_flows(graphcpp::single_flow_function&& base_function)
    {
        return multi_threaded_matrix_of_flows<RandomGraphType>([base_function = std::move(base_function)](const graphcpp::NonOrientedGraphBase& graph)
        {
            return graphcpp::flow_calculators::matrix_of_flows(graph, base_function);
        });
    }
}
