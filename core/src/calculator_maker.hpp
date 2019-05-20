#pragma once

#include <memory>

#include "core/flow_calculators/computations/single_threaded/single_thread_calculator.hpp"
#include "core/flow_calculators/computations/multi_threaded/multi_thread_calculator.hpp"

namespace graphcpp::flow_calculators
{
    template<class NorGraphType, class SymMatrixType>
    auto make_calculator(bool parallel, flow_func_t<SymMatrixType, NorGraphType> calc, msize dimension)
    {
        if (parallel)
        {
            return std::make_unique<MultiThreadCalculator<NorGraphType, SymMatrixType>>(std::move(calc), dimension);
        }
        else
        {
            return std::make_unique<SingleThreadCalculator<NorGraphType, SymMatrixType>>(std::move(calc), dimension);
        }
    }
}
