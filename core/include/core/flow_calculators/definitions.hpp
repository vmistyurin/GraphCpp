#pragma once

#include <atomic>

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"

namespace graphcpp
{
    using flow_function = std::function<std::unique_ptr<SymmetricMatrixBase>(const NonOrientedGraphBase&)>;
    using single_flow_function = std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>;
    
    struct ReductionStatistic final
    {
        
    };
}
