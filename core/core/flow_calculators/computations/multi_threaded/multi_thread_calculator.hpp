#pragma once

#include <future>

#include "core/utils/thread_pool.hpp"
#include "core/utils/numeric.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/computations/calculator_base.hpp"
#include "core/flow_calculators/computations/multi_threaded/multi_thread_summator.hpp"

namespace graphcpp
{
    template<class NorGraphType, class SymMatrixType>
    class MultiThreadCalculator final: public CalculatorBase<NorGraphType, SymMatrixType>
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

    private:
        flow_func_t<SymMatrixType, NorGraphType> _flow_function;
		MultiThreadSummator<SymMatrixType> _summator;
		ThreadPool _thread_pool = ThreadPool();

    public:
        MultiThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function, msize dimension);

        void calculate(NorGraphType graph, double probability) override;
		SymMatrixType get_result() override;
    };

    template<class NorGraphType, class SymMatrixType>
    MultiThreadCalculator<NorGraphType, SymMatrixType>::MultiThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function, msize dimension) :
		_flow_function(std::move(flow_function)), _summator(MultiThreadSummator(SymMatrixType(dimension)))
    {
        assert(_flow_function);
    }

    template<class NorGraphType, class SymMatrixType>
    void MultiThreadCalculator<NorGraphType, SymMatrixType>::calculate(NorGraphType graph, double probability)
    {
		_thread_pool.add_task([graph = std::move(graph), probability, this]
        {
            auto flows = _flow_function(graph);
            _summator.add(std::move(flows), probability);
        });
    }

    template<class NorGraphType, class SymMatrixType>
    SymMatrixType MultiThreadCalculator<NorGraphType, SymMatrixType>::get_result()
    {
		_thread_pool.wait_for_stop().get();
		
		assert(are_doubles_equal(_summator.current_probability(), 1));

		return _summator.current_sum();
    }
}
