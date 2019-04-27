#pragma once

#include <functional>

#include "core/macroses.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

namespace graphcpp::flow_calculators::reductions
{
    template<class RandomGraphType, class SymMatrixType>
    SymMatrixType split_to_components(
        RandomGraphType random_graph,
        ReductionStats* stats,
        std::function<SymMatrixType(RandomGraphType, ReductionStats*)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);

        auto result = SymMatrixType(random_graph.graph().dimension());
        
        const auto components = random_graph.graph().get_connected_components();
        for (const auto& component : components)
        {
            if (component.size() == 1) 
            {
                continue;
            }   

            SymMatrixType subgraph_flows;

            subgraph_flows = next_reductor(random_graph.graph().extract_subgraph(component), stats);
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