#pragma once

#include "core/utils/system_info.hpp"
#include "core/utils/thread_pool.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"

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
        const std::function<MatrixType(GraphType, flow_calculators::ReductionStats*)> _flow_function;
        ThreadPool _thread_pool;
        std::shared_ptr<flow_calculators::ReductionStats> _stats;
        
    public:
        MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, flow_func_t<MatrixType, GraphType> flow_function);
        MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, std::function<MatrixType(GraphType, flow_calculators::ReductionStats*)> flow_function);
        
        std::unique_ptr<MatrixType> expected_value();
        std::shared_ptr<flow_calculators::ReductionStats> get_stats();
    };

    template<class MatrixType, class GraphType>
    MultiThreadCalculator<MatrixType, GraphType>::MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, flow_func_t<MatrixType, GraphType> flow_function) :
        _graph(std::move(graph)),
        _summator(SingleVectorSymmetricMatrix(_graph->dimension())),
        _flow_function([flow_function = std::move(flow_function)](const GraphType& graph, auto stats) { return flow_function(graph); }),
        _thread_pool(number_of_threads()),
        _stats(nullptr)
    {
    }

    template<class MatrixType, class GraphType>
    MultiThreadCalculator<MatrixType, GraphType>::MultiThreadCalculator(
        std::unique_ptr<RandomNonOrientedGraphBase> graph, 
        std::function<MatrixType(GraphType, flow_calculators::ReductionStats*)> flow_function
    ) :
        _graph(std::move(graph)),
        _summator(SingleVectorSymmetricMatrix(_graph->dimension())),
        _flow_function(std::move(flow_function)),
        _thread_pool(number_of_threads()),
        _stats(std::make_shared<flow_calculators::ReductionStats>())
    {
    }

    template<class MatrixType, class GraphType>
    std::unique_ptr<MatrixType> MultiThreadCalculator<MatrixType, GraphType>::MultiThreadCalculator::expected_value()
    {        
        _graph->factorize<GraphType>([&](std::unique_ptr<GraphType> graph, double probability)
        {
            _thread_pool.add_task([graph_raw = graph.release(), probability, this]
            {
                std::unique_ptr<GraphType> graph(graph_raw); //MSVC has some problems with move-only lambdas
                auto flows = _flow_function(*graph, _stats.get());
                _summator.add(flows, probability);
            });
        });
        
        auto future = _summator.start_compute();
        assert(future.valid());
        
        return std::make_unique<MatrixType>(future.get());
    }

    template<class MatrixType, class GraphType>
    std::shared_ptr<flow_calculators::ReductionStats> MultiThreadCalculator<MatrixType, GraphType>::get_stats()
    {
        return _stats;
    }
}
