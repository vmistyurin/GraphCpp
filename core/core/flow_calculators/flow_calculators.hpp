#pragma once

#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/internal/reduction_use_algorithm_impl.hpp"

namespace graphcpp::flow_calculators
{
	mcontent Edmonds_Karp_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent Dinic_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent preflow_push_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	std::unique_ptr<SymmetricMatrixBase> reduction_use_algorithm(const NonOrientedGraphBase& graph,
		const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);
    
    template<class GraphType, class MatrixType>
    std::unique_ptr<SymmetricMatrixBase> reduction_use_algorithm_de(const NonOrientedGraphBase& graph, single_flow_function flow_calc)
    {
        return internal::ReductionUseAlgorithmImpl<GraphType, MatrixType>(graph, std::move(flow_calc)).get_flow().first;
    }

	std::unique_ptr<SymmetricMatrixBase> matrix_of_flows(const NonOrientedGraphBase& graph,
		const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);
}
