#pragma once

#include <optional>

#include "core/macroses.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    std::optional<SymMatrixType> calculate_if_small_graph(const NorGraphType& graph, ReductionStats* stats)
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);
        
        RETURN_IF(graph.dimension() > 4, std::nullopt);

        if (stats != nullptr)
        {
            stats->register_small_graph(graph.dimension());
        }

        return calculate_for_small_graph<SymMatrixType>(graph);
    } 
}
