#pragma once

#include "core/macroses.hpp"
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

        auto [bridges, classes] = graph.get_bridges();

		if (stats != nullptr)
		{
			stats->register_bridges(bridges.size());
		}

		return next_reductor(std::move(graph), stats);
    }
}