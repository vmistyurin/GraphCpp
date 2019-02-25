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
    template<class MatrixType = SingleVectorSymmetricMatrix, class GraphType = NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>>
    class MultiThreadCalculator final
    {
    private:
        std::unique_ptr<RandomNonOrientedGraphBase> _graph;
        MultiThreadSummator<SingleVectorSymmetricMatrix> _summator;
        const flow_func_t<MatrixType, GraphType> _flow_function;
        ThreadPool _thread_pool;
        
        static inline std::once_flag _print_number_of_cores_flag;
        
    public:
        MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, flow_func_t<MatrixType, GraphType> flow_function);
        
        std::unique_ptr<MatrixType> expected_value();
    };

    template<class MatrixType, class GraphType>
    MultiThreadCalculator<MatrixType, GraphType>::MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, flow_func_t<MatrixType, GraphType> flow_function) :
        _graph(std::move(graph)),
        _summator(SingleVectorSymmetricMatrix(_graph->dimension())),
        _flow_function(std::move(flow_function)),
        _thread_pool(std::thread::hardware_concurrency())
    {
        std::call_once(_print_number_of_cores_flag, []
        {
            std::cout << "Number of threads: " << std::thread::hardware_concurrency() << std::endl;
        });
    }

    template<class MatrixType, class GraphType>
    std::unique_ptr<MatrixType> MultiThreadCalculator<MatrixType, GraphType>::MultiThreadCalculator::expected_value()
    {    
        _graph->factorize<GraphType>([&](std::unique_ptr<GraphType> graph, double probability)
        {
            _thread_pool.add_task([graph_raw = graph.release(), probability, this]
            {
                std::unique_ptr<GraphType> graph(graph_raw); //MSVC has some problems with moving lambdas
                auto flows = _flow_function(*graph);
                _summator.add(flows, probability);
            });
        });
        
        auto future = _summator.start_compute();
        assert(future.valid());
        
        return std::make_unique<MatrixType>(future.get());
    }

}
