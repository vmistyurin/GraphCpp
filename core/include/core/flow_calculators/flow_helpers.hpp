#pragma once

#include <functional>

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"
#include "core/graph_implementations/graph_base.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

namespace graphcpp::flow_calculators
{
    std::unique_ptr<SymmetricMatrixBase> calculate_flows_in_tree(const NonOrientedGraphBase& graph);
}

