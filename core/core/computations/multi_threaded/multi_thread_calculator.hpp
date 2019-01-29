#pragma once

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/utils/thread_pool.hpp"

namespace graphcpp
{
    class RandomNonOrientedGraphBase;
}

namespace graphcpp
{
    class MultiThreadCalculator final
    {
    private:
        std::unique_ptr<RandomNonOrientedGraphBase> _graph;
        MultiThreadSummator<SingleVectorSymmetricMatrix> _summator;
        const flow_function _flow_func;
        ThreadPool _thread_pool;
        
        static inline std::once_flag _print_number_of_cores_flag;
        
    public:
        MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function flow_func);
        
        std::unique_ptr<SymmetricMatrixBase> expected_value();
    };
}
