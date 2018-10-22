#include "core/computations/single_threaded/single_thread_calculator.hpp"

using namespace graphcpp;

SingleThreadCalculator::SingleThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph) :
	_graph(std::move(graph)), _summator(FullSymmetricMatrix(_graph->dimension()))
{
}

std::unique_ptr<SymmetricMatrixBase> SingleThreadCalculator::expected_value()
{
	_graph->factorize([&](std::unique_ptr<NonOrientedGraphBase> graph, double probability)
	{

	});

	assert(are_doubles_equal(_summator.current_probability(), 1));
	return std::make_unique<FullSymmetricMatrix>(_summator.current_sum());
}