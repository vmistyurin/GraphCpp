#pragma once

#include <functional>

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/graph_implementations/graph_base.hpp"

namespace graphcpp::flow_calculators
{
    template<class SymMatrixType>
    std::unique_ptr<SymMatrixType> calculate_flows_in_tree(const NonOrientedGraphBase& graph);

	template<class SymMatrixType>
	std::unique_ptr<SymMatrixType> matrix_of_flows(const NonOrientedGraphBase& graph,
		const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>& single_flow_calculator);
}

