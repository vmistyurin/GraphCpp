#pragma once

#include <memory>

#include "core/matrices/symmetric_matrices/full_symmetric_matrix.hpp"
#include "core/computations/single_threaded/single_thread_summator.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

namespace graphcpp
{
	class RandomNonOrientedGraphBase;	
}

namespace graphcpp
{
	class SingleThreadCalculator final
	{
	private:
		std::unique_ptr<RandomNonOrientedGraphBase> _graph;
		SingleThreadSummator<FullSymmetricMatrix> _summator;
        flow_function _flow_func;

	public:
        SingleThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function flow_func);
		
		std::unique_ptr<SymmetricMatrixBase> expected_value();
	};
}
