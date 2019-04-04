#pragma once

#include "core/macroses.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType split_to_components(
        NorGraphType graph,
        ReductionStats* stats,
        std::function<SymMatrixType(NorGraphType, ReductionStats*)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        auto result = SymMatrixType(graph.dimension());
        
        auto components = graph.get_connected_components();
        for (const auto& component : components)
        {
            if (auto small_graph_result = calculate_if_small_graph<SymMatrixType>(graph, stats); small_graph_result) 
            {
                return small_graph_result.value();
            }
            
            SymMatrixType subgraph_flows;

            subgraph_flows = next_reductor(graph.template extract_subgraph<NorGraphType>(component), stats);
            assert(subgraph_flows.dimension() == component.size());
            
            for (msize i = 1; i < component.size(); i++)
            {
                for (msize j = 0; j < i; j++)
                {
                    result.set(component[i], component[j], subgraph_flows.at(i, j));
                }
            }
        }
        
        return result;
    }
}