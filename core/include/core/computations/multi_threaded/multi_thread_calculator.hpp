#pragma once

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"
#include "core/flow_calculators/flow_calculators.hpp"
#include "core/utils/thread_pool.hpp"

namespace graphcpp
{
    class MultiThreadCalculator final
    {
    private:
        std::unique_ptr<RandomNonOrientedGraphBase> _graph;
        MultiThreadSummator<SingleVectorSymmetricMatrix> _summator;
        const flow_function<SingleVectorSymmetricMatrix> _flow_func;
        ThreadPool _thread_pool;
        
        static inline std::once_flag _print_number_of_cores_flag;
        
    public:
        MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function<SingleVectorSymmetricMatrix> flow_func);
        
        std::unique_ptr<SingleVectorMatrix> expected_value();
    };
}
