#pragma once

#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/computations/calculator_base.hpp"
#include "core/flow_calculators/computations/single_threaded/single_thread_summator.hpp"

namespace graphcpp
{
	template<class NorGraphType, class SymMatrixType>
    class SingleThreadCalculator final: public CalculatorBase<NorGraphType, SymMatrixType>
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

    private:
        flow_func_t<SymMatrixType, NorGraphType> _flow_function;
        SingleThreadSummator<SymMatrixType> _summator;

    public:
        SingleThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function, msize dimension);

        void calculate(NorGraphType graph, double probability) override;
		SymMatrixType get_result() override;
    };

    template<class NorGraphType, class SymMatrixType>
    SingleThreadCalculator<NorGraphType, SymMatrixType>::SingleThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function, msize dimension) :
        _flow_function(std::move(flow_function)), _summator(SingleThreadSummator(SymMatrixType(dimension)))
    {
        assert(_flow_function);
    }

    template<class NorGraphType, class SymMatrixType>
    void SingleThreadCalculator<NorGraphType, SymMatrixType>::calculate(NorGraphType graph, double probability)
    {
		auto flows = _flow_function(graph);
		_summator.add(std::move(flows), probability);
    }

    template<class NorGraphType, class SymMatrixType>
    SymMatrixType SingleThreadCalculator<NorGraphType, SymMatrixType>::get_result()
    {
		assert(are_doubles_equal(_summator.current_probability(), 1));

		return _summator.current_sum();
    }
}
