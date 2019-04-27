#pragma once

#include "core/utils/system_info.hpp"
#include "core/utils/thread_pool.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/computations/multi_threaded/multi_thread_summator.hpp"

namespace graphcpp
{
    template<class NorGraphType, class SymMatrixType>
    class MultiThreadCalculator final
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

    private:
        flow_func_t<SymMatrixType, NorGraphType> _flow_function;
        MultiThreadSummator<SymMatrixType> _summator = MultiThreadSummator<SymMatrixType>();

    public:
        MultiThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function);

        void calculate(NorGraphType graph, double probability);
        std::future<SymMatrixType> get_result();
    };

    template<class NorGraphType, class SymMatrixType>
    MultiThreadCalculator<NorGraphType, SymMatrixType>::MultiThreadCalculator(flow_func_t<SymMatrixType, NorGraphType> flow_function) :
        _flow_function(std::move(flow_function))
    {
        assert(_flow_function);
    }

    template<class NorGraphType, class SymMatrixType>
    void MultiThreadCalculator<NorGraphType, SymMatrixType>::calculate(NorGraphType graph, double probability)
    {
        ThreadPool::shared().add_task([graph = std::move(graph), probability, this]()
        {
            auto flows = _flow_function(graph);
            this->_summator.add(std::move(flows), probability);
        });
    }

    template<class NorGraphType, class SymMatrixType>
    std::future<SymMatrixType> MultiThreadCalculator<NorGraphType, SymMatrixType>::get_result()
    {
        return _summator.start_compute();
    }
}
