#pragma once

#include <memory>

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/computations/single_threaded/single_thread_summator.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

namespace graphcpp
{
	class RandomNonOrientedGraphBase;	
}

namespace graphcpp
{
	template<class MatrixType = SingleVectorSymmetricMatrix, class GraphType = NonOrientedMatrixGraph<SingleVectorSymmetricMatrix>> 
	class SingleThreadCalculator final
	{
	private:
		std::unique_ptr<RandomNonOrientedGraphBase> _graph;
		SingleThreadSummator<SingleVectorSymmetricMatrix> _summator;
        const flow_func_t<MatrixType, GraphType> _flow_func;

	public:
        SingleThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, flow_func_t<MatrixType, GraphType> flow_func);
		
		std::unique_ptr<SymmetricMatrixBase> expected_value();
	};


	template<class MatrixType, class GraphType> 
	SingleThreadCalculator<MatrixType, GraphType>::SingleThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase> graph, flow_func_t<MatrixType, GraphType> flow_func) :
		_graph(std::move(graph)), 
		_summator(SingleVectorSymmetricMatrix(_graph->dimension())), 
		_flow_func(std::move(flow_func))
	{
	}

	template<class MatrixType, class GraphType> 
	std::unique_ptr<SymmetricMatrixBase> SingleThreadCalculator<MatrixType, GraphType>::SingleThreadCalculator::expected_value()
	{
		_graph->factorize<GraphType>([&](std::unique_ptr<GraphType> graph, double probability)
		{
			auto flows = _flow_func(*graph);
			_summator.add(flows, probability);
		});

		assert(are_doubles_equal(_summator.current_probability(), 1));
		return std::make_unique<SingleVectorSymmetricMatrix>(_summator.current_sum());
}
}
