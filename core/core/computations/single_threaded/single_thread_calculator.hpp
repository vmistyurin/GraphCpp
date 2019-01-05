#pragma once

#include <memory>

#include "core/matrix_implementations/symmetric_matrixes/full_symmetric_matrix.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/computations/single_threaded/single_thread_summator.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

namespace graphcpp
{
	template<class SymMatrixType, class NonOrientedGraphType, class RandomNonOrientedGraphType>
	class SingleThreadCalculator final
	{
	private:
		RandomNonOrientedGraphType _graph;
		SingleThreadSummator<SymMatrixType> _summator;
        flow_function<SymMatrixType, NonOrientedGraphType> _flow_func;

	public:
        SingleThreadCalculator(RandomNonOrientedGraphType graph, flow_function<SymMatrixType, NonOrientedGraphType> flow_func);
		
		SymMatrixType expected_value();
	};

	template<class SymMatrixType, class NonOrientedGraphType, class RandomNonOrientedGraphType>
	SingleThreadCalculator<SymMatrixType, NonOrientedGraphType, RandomNonOrientedGraphType>::SingleThreadCalculator(
		RandomNonOrientedGraphType graph,
		flow_function<SymMatrixType, NonOrientedGraphType> flow_func
	) :
		_graph(std::move(graph)),
		_summator(SymMatrixType(_graph.dimension())),
		_flow_func(std::move(flow_func))
	{
	}

	template<class SymMatrixType, class NonOrientedGraphType, class RandomNonOrientedGraphType>
	SymMatrixType SingleThreadCalculator<SymMatrixType, NonOrientedGraphType, RandomNonOrientedGraphType>::expected_value()
	{
		_graph.factorize([&](std::unique_ptr<NonOrientedGraphType> graph, double probability)
		{
			const auto flows = _flow_func(*graph);
			_summator.add(*flows, probability);
		});

		assert(are_doubles_equal(_summator.current_probability(), 1));
		return _summator.current_sum();
	}
}
