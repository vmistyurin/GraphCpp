#pragma once

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/random_graph_implementations/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"
#include "core/flow_calculators/flow_calculators.hpp"
#include "core/utils/thread_pool.hpp"

namespace graphcpp
{
	template<class SymMatrixType, class NonOrientedGraphType, class RandomNonOrientedGraphType>
    class MultiThreadCalculator final
    {
    private:
		RandomNonOrientedGraphType _graph;
        MultiThreadSummator<SymMatrixType> _summator;
        const flow_function<SymMatrixType, NonOrientedGraphType> _flow_func;
        ThreadPool _thread_pool;
        
        static inline std::once_flag _print_number_of_cores_flag;
        
    public:
        MultiThreadCalculator(RandomNonOrientedGraphType graph, flow_function<SymMatrixType, NonOrientedGraphType> flow_func);
        
		SymMatrixType expected_value();
    };
	
	template<class SymMatrixType, class NonOrientedGraphType, class RandomNonOrientedGraphType>
	MultiThreadCalculator<SymMatrixType, NonOrientedGraphType, RandomNonOrientedGraphType>::MultiThreadCalculator(
		RandomNonOrientedGraphType graph,
		flow_function<SymMatrixType, NonOrientedGraphType> flow_func
	) :
		_graph(std::move(graph)),
		_summator(SymMatrixType(_graph->dimension())),
		_flow_func(std::move(flow_func)),
		_thread_pool(std::thread::hardware_concurrency())
	{
		std::call_once(_print_number_of_cores_flag, []
		{
			std::cout << "Number of threads: " << std::thread::hardware_concurrency() << std::endl;
		});
	}

	template<class SymMatrixType, class NonOrientedGraphType, class RandomNonOrientedGraphType>
	SymMatrixType MultiThreadCalculator<SymMatrixType, NonOrientedGraphType, RandomNonOrientedGraphType>::expected_value()
	{
		_graph.factorize([&](std::unique_ptr<NonOrientedGraphType> graph, double probability)
		{
			_thread_pool.add_task([graph_raw = graph.release(), probability, this]
				{
					std::unique_ptr<NonOrientedGraphType> graph(graph_raw); //MSVC has some problems with moving lambdas
					const auto flows = _flow_func(*graph);
					_summator.add(*flows, probability);
				});
		});

		auto future = _summator.start_compute();
		assert(future.valid());

		return future.get();
	}
}
