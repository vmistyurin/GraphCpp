#include "core/computations/single_threaded/single_thread_calculator.hpp"

using namespace graphcpp;

SingleThreadCalculator::SingleThreadCalculator(
    std::unique_ptr<RandomNonOrientedGraphBase>&& graph,
    flow_function<SingleVectorSymmetricMatrix> flow_func
) :
    _graph(std::move(graph)),
    _summator(SingleVectorSymmetricMatrix(_graph->dimension())),
    _flow_func(std::move(flow_func))
{
}

std::unique_ptr<SingleVectorSymmetricMatrix> SingleThreadCalculator::expected_value()
{
	_graph->factorize([&](std::unique_ptr<NonOrientedGraphBase> graph, double probability)
	{
        const auto flows = _flow_func(*graph);
        _summator.add(*flows, probability);
	});

	assert(are_doubles_equal(_summator.current_probability(), 1));
	return std::make_unique<SingleVectorSymmetricMatrix>(_summator.current_sum());
}
