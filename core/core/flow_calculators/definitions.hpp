#pragma once

#include <functional>

#include "core/macroses.hpp"

namespace graphcpp
{
    class NonOrientedGraphBase;
    class SymmetricMatrixBase;
}

namespace graphcpp::flow_calculators
{
	class ReductionStats;
}

namespace graphcpp
{
    template<class MatrixType, class GraphType>
    using flow_func_t = std::function<MatrixType(const GraphType&)>;

	template<class GraphType>
	using single_flow_function_t = std::function<mcontent(const GraphType&, msize, msize)>;

	template<class RandomGraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	using reductor_t = std::function<SymMatrixType(RandomGraphType, flow_calculators::ReductionStats*)>;
}
