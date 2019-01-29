#pragma once

#include <atomic>
#include <functional>

#include "core/macroses.hpp"
#include "core/matrices/symmetric_matrices/symmetric_matrix_base.hpp"

namespace graphcpp
{
    class NonOrientedGraphBase;
    class SymmetricMatrixBase;
}

namespace graphcpp
{
    using flow_function = std::function<std::unique_ptr<SymmetricMatrixBase>(const NonOrientedGraphBase&)>;
    using single_flow_function = std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>;
    
    struct ReductionStatistic final
    {
        
    };
}
