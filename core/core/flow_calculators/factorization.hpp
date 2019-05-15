#pragma once

#include "core/macroses.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/computations/single_threaded/single_thread_calculator.hpp"
#include "core/flow_calculators/computations/multi_threaded/multi_thread_calculator.hpp"

namespace graphcpp::flow_calculators::internal
{
    template<class RandomGraphType, class CalculatorType>
    void factorize_from(RandomGraphType random_graph, double probability, CalculatorType& calc)
    {
        for(auto iter = random_graph.probabilities().begin(); iter != random_graph.probabilities().end(); ++iter)
        {
            const auto[i, j] = *iter;
            
            const auto vertex_probability = random_graph.probability_at(i, j);
            if (!(are_doubles_equal(vertex_probability, 0) || are_doubles_equal(vertex_probability, 1)))
            {
                auto deleted_branch = random_graph.with_deleted_edge(i, j);
                factorize_from(std::move(deleted_branch), probability * (1.0 - vertex_probability), calc);

                probability *= vertex_probability;
                random_graph.set_probability(i, j, 1);
            }
        }

        calc.calculate(random_graph.graph(), probability);
    }

	template<class NorGraphType, class SymMatrixType>
	std::unique_ptr<CalculatorBase<NorGraphType, SymMatrixType>> make_calculator(bool parallel, flow_func_t<SymMatrixType, NorGraphType> calc, msize dimension)
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

namespace graphcpp::flow_calculators
{
    template<class RandomGraphType, class NorGraphType = typename RandomGraphType::GraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	SymMatrixType factorize(RandomGraphType random_graph, flow_func_t<SymMatrixType, NorGraphType> calc, bool parallel)
    {
		auto calculator = internal::make_calculator<NorGraphType, SymMatrixType>(parallel, std::move(calc), random_graph.dimension());
		internal::factorize_from(std::move(random_graph), 1, *calculator);
		return calculator->get_result();
    } 

	template<class RandomGraphType, class NorGraphType = typename RandomGraphType::GraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	typename RandomGraphType::MatrixType factorize(RandomGraphType random_graph, single_flow_function_t<NorGraphType> calc, bool parallel)
	{
		flow_func_t<SymMatrixType, NorGraphType> matrix_of_flow = std::bind(matrix_of_flows<SymMatrixType, NorGraphType>, std::placeholders::_1, std::move(calc));

		return factorize(
			std::move(random_graph),
			std::move(matrix_of_flow),
			parallel
		);
	}
}
