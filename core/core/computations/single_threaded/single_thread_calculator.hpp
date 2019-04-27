#pragma once

#include <future>
#include <memory>

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/computations/single_threaded/single_thread_summator.hpp"

namespace graphcpp
{
	class RandomNonOrientedGraphBase;	
}

namespace graphcpp
{
	template<class NorGraphType, class SymMatrixType>
    class SingleThreadCalculator final
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

    private:
        flow_func_t<SymMatrixType, NorGraphType> _flow_function;
        SingleThreadSummator<SymMatrixType> _summator = SingleThreadSummator<SymMatrixType>();

    public:
        SingleThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function);

        void calculate(NorGraphType graph, double probability);
        std::future<SymMatrixType> get_result();
    };

    template<class NorGraphType, class SymMatrixType>
    SingleThreadCalculator<NorGraphType, SymMatrixType>::SingleThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function) :
        _flow_function(std::move(flow_function))
    {
        assert(!flow_function.is_empty());
    }

    template<class NorGraphType, class SymMatrixType>
    void SingleThreadCalculator<NorGraphType, SymMatrixType>::calculate(NorGraphType graph, double probability)
    {
		auto flows = _flow_function(graph);
		this->_summator.add(std::move(flows, probability));
    }

    template<class NorGraphType, class SymMatrixType>
    std::future<SymMatrixType> SingleThreadCalculator<NorGraphType, SymMatrixType>::get_result()
    {
		assert(are_doubles_equal(_summator.current_probability, 1));
        return std::future<SymMatrixType>(_summator.current_sum());
    }
}
