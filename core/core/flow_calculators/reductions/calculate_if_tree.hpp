#pragma once

#include "core/macroses.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/flow_helpers.hpp"

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType calculate_if_tree(
        NorGraphType graph,
        std::shared_ptr<ReductionStatistic> stats,
        std::function<SymMatrixType(NorGraphType, std::shared_ptr<ReductionStatistic>)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        if (graph.is_tree())
        {
            return calculate_flows_in_tree<SymMatrixType>(graph);
        }
        else 
        {
            return next_reductor(std::move(graph), stats);
        }
    }
}