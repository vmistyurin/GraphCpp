#pragma once

#include <memory>

#include "core/matrix_implementations/symmetric_matrixes/full_symmetric_matrix.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/computations/single_threaded/single_thread_summator.hpp"
#include "core/flow_calculators/flow_calculators.hpp"

namespace graphcpp
{
	class SingleThreadCalculator final
	{
	private:
		std::unique_ptr<RandomNonOrientedGraphBase> _graph;
		SingleThreadSummator<SingleVectorSymmetricMatrix> _summator;
        flow_function<SingleVectorSymmetricMatrix> _flow_func;

	public:
        SingleThreadCalculator(std::unique_ptr<RandomNonOrientedGraphBase>&& graph, flow_function<SingleVectorSymmetricMatrix> flow_func);
		
		std::unique_ptr<SingleVectorSymmetricMatrix> expected_value();
	};
}
