#pragma once

#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/internal/reduction_use_algorithm_impl.hpp"

namespace graphcpp::flow_calculators
{
	mcontent Edmonds_Karp_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent Dinic_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent preflow_push_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);
    
    template<class NorGraphType, class SymMatrixType>
    SymMatrixType reduction_use_algorithm_de(const NorGraphType& graph, single_flow_function flow_calc)
    {		
        IS_NOR_GRAPH_IMPL(NorGraphType);
        IS_SYM_MATRIX_IMPL(SymMatrixType);

        return graphcpp::internal::ReductionUseAlgorithmImpl<NorGraphType, SymMatrixType>(graph, std::move(flow_calc)).get_flow().first;
    }
}
