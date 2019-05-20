#pragma once

#include "core/macroses.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/flow_calculators/reductions/calculate_if_small_graph.hpp"

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType calculate_if_tree(
        NorGraphType graph,
        ReductionStats* stats,
        std::function<SymMatrixType(NorGraphType, ReductionStats*)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        if (auto small_graph_result = calculate_if_small_graph<SymMatrixType>(graph, stats); small_graph_result) 
        {
             return small_graph_result.value_or(SymMatrixType(1));
        }

        if (graph.is_tree())
        {
            if (stats != nullptr)
            {
                stats->register_calculated_tree(graph.dimension());
            }

            return calculate_flows_in_tree<SymMatrixType>(graph);
        }
        else 
        {
            return next_reductor(std::move(graph), stats);
        }
    }
}
