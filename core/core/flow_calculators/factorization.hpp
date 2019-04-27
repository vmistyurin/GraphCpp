#pragma once

#include "core/macroses.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/computations/multi_threaded/multi_thread_calculator.hpp"

namespace graphcpp::flow_calculators::internal
{
    template<class RandomGraphType, class NorGraphType, class SymMatrixType>
    void factorize_from(RandomGraphType random_graph, double probability, MultiThreadCalculator<NorGraphType, SymMatrixType>& calc)
    {
        for(auto iter = random_graph.probabilities().begin(); iter != random_graph.probabilities().end(); ++iter)
        {
            const auto[i, j] = *iter;
            
            const auto vertex_probability = random_graph.probability_at(i, j);
            if (!(are_doubles_equal(vertex_probability, 0) || are_doubles_equal(vertex_probability, 1)))
            {
                auto deleted_branch = random_graph.with_deleted_edge(i, j);
                factorize_from<RandomGraphType, NorGraphType, SymMatrixType>(std::move(deleted_branch), probability * (1.0 - vertex_probability), calc);

                probability *= vertex_probability;
                random_graph.set_probability(i, j, 1);
            }
        }

        calc.calculate(random_graph.graph(), probability);
    } 
}

namespace graphcpp::flow_calculators
{
    template<class RandomGraphType, class NorGraphType, class SymMatrixType>
    SymMatrixType factorize(RandomGraphType random_graph, flow_func_t<SymMatrixType, NorGraphType> calc)
    {
        auto calculator = MultiThreadCalculator<NorGraphType, SymMatrixType>(std::move(calc));

        internal::factorize_from(std::move(random_graph), 1, calculator);

        return calculator.get_result().get();
    } 
}
