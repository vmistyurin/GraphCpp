#pragma once

#include "core/macroses.hpp"

namespace graphcpp
{
	template<class NorGraphType, class SymMatrixType>
	class CalculatorBase
	{
	public:
		IS_SYM_MATRIX_IMPL(SymMatrixType);
		IS_NOR_GRAPH_IMPL(NorGraphType);

		virtual void calculate(NorGraphType graph, double probability) = 0;
		virtual SymMatrixType get_result() = 0;

		ABSTRACT_CLASS_OPERATIONS(CalculatorBase);
	};
}