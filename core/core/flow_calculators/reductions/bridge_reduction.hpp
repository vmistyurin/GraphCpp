#pragma once

#include "core/macroses.hpp"
#include "core/utils/numeric.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/flow_calculators/reductions/calculate_if_small_graph.hpp"

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType bridge_reduction(
        NorGraphType graph,
        ReductionStats* stats,
        std::function<SymMatrixType(NorGraphType, ReductionStats*)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        if (const auto result = calculate_if_small_graph<SymMatrixType>(graph, stats); result)
        {
            return result.value_or(SymMatrixType());
        }
        
        auto[bridges, classes] = graph.get_bridges();

        if (bridges.empty())
        {
            return next_reductor(std::move(graph), stats);
        } 
        
		if (stats != nullptr)
		{
			stats->register_bridges(1);
		}
        
        auto result = SymMatrixType(graph.dimension());
        
        auto[u, v] = bridges.front();
        
        const auto bridge_capacity = graph.at(u, v);
        graph.set(u, v, 0);
        const auto first_component = get_connected_component(graph, 0);
        const auto second_component = find_addition(first_component, graph.dimension());
        
        if (std::binary_search(first_component.cbegin(), first_component.cend(), v))
        {
            std::swap(u, v);
        }
        
        const auto first_graph_result = bridge_reduction(graph.extract_subgraph(first_component), stats, next_reductor);
        const auto second_graph_result = bridge_reduction(graph.extract_subgraph(second_component), stats, std::move(next_reductor));
        
        std::vector<msize> mapping(graph.dimension());
        for (msize i = 0; i < mapping.size(); i++)
        {
            if (const auto it = binary_search(first_component, i); it != first_component.cend())
            {
                mapping[i] = std::distance(first_component.cbegin(), it);
            }
            else
            {
                const auto second_it = binary_search(second_component, i);
                mapping[i] = std::distance(second_component.cbegin(), second_it);
            }
        }
        
        for (const auto[i, j] : result)
        {
            const auto i_it = binary_search(first_component, i);
            const auto j_it = binary_search(first_component, j);
            
            const auto i_is_first_component = (i_it != first_component.cend());
            const auto j_is_first_component = (j_it != first_component.cend());
            
            if (i_is_first_component && j_is_first_component)
            {
                result.set(i, j, first_graph_result.at(mapping[i], mapping[j]));
            }
            else if (!i_is_first_component && !j_is_first_component)
            {
                result.set(i, j, second_graph_result.at(mapping[i], mapping[j]));
            }
            else if ((u == i && v == j) || (u == j && v == i))
            {
                result.set(i, j, bridge_capacity);
            }
            else
            {
                mcontent u_flow, v_flow;
                if (i_it == first_component.cend())
                {
                    if (j == u)
                    {
                        u_flow = std::numeric_limits<mcontent>::max();
                    }
                    else
                    {
                        u_flow = first_graph_result.at(mapping[j], mapping[u]);
                    }
                    
                    if (i == v)
                    {
                        v_flow = std::numeric_limits<mcontent>::max();
                    }
                    else
                    {
                        v_flow = second_graph_result.at(mapping[i], mapping[v]);
                    }
                }
                else
                {
                    if (i == u)
                    {
                        u_flow = std::numeric_limits<mcontent>::max();
                    }
                    else
                    {
                        u_flow = first_graph_result.at(mapping[i], mapping[u]);
                    }
                    
                    if (j == v)
                    {
                        v_flow = std::numeric_limits<mcontent>::max();
                    }
                    else
                    {
                        v_flow = second_graph_result.at(mapping[j], mapping[v]);
                    }
                }
                
                const auto flow = std::min(std::min(u_flow, v_flow), bridge_capacity);
                result.set(i, j, flow);
            }
        }
        
        return result;
    }
}
