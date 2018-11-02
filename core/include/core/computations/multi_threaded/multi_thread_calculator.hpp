#pragma once

#include "core/matrix_implementations/symmetric_matrixes/full_symmetric_matrix.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"
#include "core/flow_calculators.hpp"
#include "core/utils/thread_pool.hpp"

namespace graphcpp
{
    class MultiThreadCalculator final
    {
    private:
        std::unique_ptr<RandomNonOrientedGraphBase> _graph;
        MultiThreadSummator<FullSymmetricMatrix> _summator;
        const flow_function _flow_func;
        ThreadPool _thread_pool;
        
    public:
        MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function&& flow_func);
        
        std::unique_ptr<SymmetricMatrixBase> expected_value();
    };
}
