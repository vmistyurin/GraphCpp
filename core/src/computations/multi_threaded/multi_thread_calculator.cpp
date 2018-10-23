#include "core/computations/multi_threaded/multi_thread_calculator.hpp"

#include <future>

#include "core/utils.hpp"

using namespace graphcpp;

MultiThreadCalculator::MultiThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function&& flow_func) :
    _graph(std::move(graph)), _summator(FullSymmetricMatrix(graph->dimension()))
{
}

std::unique_ptr<SymmetricMatrixBase> MultiThreadCalculator::expected_value()
{
    _graph->factorize([&](std::unique_ptr<NonOrientedGraphBase> graph, double probability)
    {
        //const auto result = std::async(std::launch::async, _flow_func, *_graph));
    });
    
    assert(are_doubles_equal(_summator.current_probability(), 1));
    return std::make_unique<FullSymmetricMatrix>(_summator.wait_for_result());
}
