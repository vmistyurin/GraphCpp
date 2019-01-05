#pragma once

#include <atomic>
#include <functional>

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_graph_base.hpp"

namespace graphcpp
{
    template<class SymMatrixType, class NonOrientedGraphType>
    using flow_function = std::function<std::unique_ptr<SymMatrixType>(const NonOrientedGraphType&)>;
    
	template<class NonOrientedGraphType>
    using single_flow_function = std::function<mcontent(const NonOrientedGraphType&, msize, msize)>;
    
    struct ReductionStatistic final
    {
        
    };
}
