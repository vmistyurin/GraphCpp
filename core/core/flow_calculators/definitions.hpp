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
    template<class MatrixType, class GraphType>
    using flow_func_t = std::function<MatrixType(const GraphType&)>;

    using single_flow_function = std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>;
    
    struct ReductionStatistic final
    {
        //std::atomic<unsigned int> hanged_vertexes;
    };
}
