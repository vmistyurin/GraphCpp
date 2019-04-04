#pragma once

#include <iostream>
#include <fstream>
#include <functional>

#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/computations/single_threaded/single_thread_calculator.hpp"
#include "core/computations/multi_threaded/multi_thread_calculator.hpp"

namespace graphcpp::bench
{
    template<class MatrixType, class GraphType, class RandomGraphType = RandomNonOrientedGraph<GraphType, MatrixType>>
    std::function<std::string(std::ifstream&&)> single_threaded_matrix_of_flows(flow_func_t<MatrixType, GraphType> base_function)
    {
        IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);
        IS_NOR_GRAPH_IMPL(GraphType);
        IS_SYM_MATRIX_IMPL(MatrixType);
        
        return [base_function = std::move(base_function)](std::ifstream&& input)
        {
            auto graph = std::make_unique<RandomGraphType>(RandomGraphType::read_from_stream(input));
            
            auto calculator = graphcpp::SingleThreadCalculator(std::move(graph), base_function);
            
            return calculator.expected_value()->to_string();
        };
    }
    
    template<class RandomGraphType, class GraphType = NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, class MatrixType = SingleVectorSymmetricMatrix>
    std::function<std::string(std::ifstream&&)> single_threaded_matrix_of_flows(graphcpp::single_flow_function base_function)
    {
        IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);
        IS_NOR_GRAPH_IMPL(GraphType);
        IS_SYM_MATRIX_IMPL(MatrixType);

        return single_threaded_matrix_of_flows<RandomGraphType>([base_function = std::move(base_function)](const GraphType& graph)
        {
            return graphcpp::flow_calculators::matrix_of_flows<MatrixType, GraphType>(graph, base_function);
        });
    }

    template<class RandomGraphType, class GraphType = NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>, class MatrixType = SingleVectorSymmetricMatrix>
    std::function<std::string(std::ifstream&&)> multi_threaded_matrix_of_flows(graphcpp::single_flow_function base_function)
    {
        IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);
        IS_NOR_GRAPH_IMPL(GraphType);
        IS_SYM_MATRIX_IMPL(MatrixType);

        return multi_threaded_matrix_of_flows<MatrixType, GraphType, RandomGraphType>([base_function = std::move(base_function)](const GraphType& graph)
        {
            return graphcpp::flow_calculators::matrix_of_flows<MatrixType, GraphType>(graph, base_function);
        });
    }

    template<class MatrixType, class GraphType, class RandomGraphType = RandomNonOrientedGraph<GraphType, MatrixType>>
    std::function<std::string(std::ifstream&&)> multi_threaded_matrix_of_flows(std::function<MatrixType(GraphType, flow_calculators::ReductionStats*)> base_function)
    {
        IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);
        IS_NOR_GRAPH_IMPL(GraphType);
        IS_SYM_MATRIX_IMPL(MatrixType);
        
        return [base_function = std::move(base_function)](std::ifstream&& input)
        {
            auto graph = std::make_unique<RandomGraphType>(RandomGraphType::read_from_stream(input));

            auto calculator = graphcpp::MultiThreadCalculator<MatrixType, GraphType>(std::move(graph), base_function);
            
            const auto result = calculator.expected_value()->to_string();

            std::cout << *calculator.get_stats();

            return result; 
        };
    }
}

