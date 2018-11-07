#include "core/computations/multi_threaded/multi_thread_calculator.hpp"

#include <future>

#include "core/utils.hpp"

using namespace graphcpp;

MultiThreadCalculator::MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function&& flow_func) :
    _graph(std::move(graph)),
    _summator(FullSymmetricMatrix(_graph->dimension())),
    _flow_func(std::move(flow_func)),
    _thread_pool(std::thread::hardware_concurrency())
{
}

std::unique_ptr<SymmetricMatrixBase> MultiThreadCalculator::expected_value()
{    
    _graph->factorize([&](std::unique_ptr<NonOrientedGraphBase> graph, double probability)
    {
        _thread_pool.add_task([graph_raw = graph.release(), probability, this]
        {
			std::unique_ptr<NonOrientedGraphBase> graph(graph_raw); //MSVC has some problems with moving lambdas
            const auto flows = _flow_func(*graph);
            _summator.add(*flows, probability);
        });
    });
    
    auto future = _summator.start_compute();
    assert(future.valid());
    
    return std::make_unique<FullSymmetricMatrix>(future.get());
}
