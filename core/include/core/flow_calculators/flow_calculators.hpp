#pragma once

#include <functional>

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/graph_implementations/graph_base.hpp"

namespace graphcpp
{
    using flow_function = std::function<std::unique_ptr<SymmetricMatrixBase>(const NonOrientedGraphBase&)>;
    using single_flow_function = std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>;
}

namespace graphcpp::flow_calculators
{
	mcontent Edmonds_Karp_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent Dinic_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent preflow_push_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	std::unique_ptr<SymmetricMatrixBase> reduction_use_algorithm(const NonOrientedGraphBase& graph,
		const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);

	std::unique_ptr<SymmetricMatrixBase> matrix_of_flows(const NonOrientedGraphBase& graph,
		const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);
}
