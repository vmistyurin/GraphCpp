#pragma once

#include <cassert>
#include <optional>

#include "core/utils/boost_future.hpp"
#include "core/utils/defer.hpp"
#include "core/edges/symmetric_edge.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/flow_calculators/reduction_use_algorithm.hpp"
#include "core/flow_calculators/computations/calculator_maker.hpp"

#include "core/flow_calculators/random_graph_reductions/split_to_components.hpp"

namespace graphcpp::flow_calculators::internal
{
	template<class RandomGraphType>
	std::optional<std::pair<msize, msize>> edge_to_factorize(const RandomGraphType& random_graph)
	{
		for (auto iter = random_graph.probabilities().begin(); iter != random_graph.probabilities().end(); ++iter)
		{
			const auto [i, j] = *iter;
			const auto edge_probability = random_graph.probability_at(i, j);

			if (!(are_doubles_equal(edge_probability, 0) || are_doubles_equal(edge_probability, 1)))
			{
				return std::pair(i, j);
			}
		}

		return std::nullopt;
	}

    template<
        class RandomGraphType,
        class NorGraphType = typename RandomGraphType::GraphType,
        class SymMatrixType = typename RandomGraphType::MatrixType
    >
    boost::future<SymMatrixType> reduction_use_factorization(
        RandomGraphType random_graph,
        flow_func_t<SymMatrixType, NorGraphType> flow_func,
        ReductionStats* stats
    );
    
	template<class RandomGraphType,
        class NorGraphType = typename RandomGraphType::GraphType,
        class SymMatrixType = typename RandomGraphType::MatrixType
    >
	boost::future<SymMatrixType> calculate_in_deleted_branch(
        RandomGraphType random_graph,
        flow_func_t<SymMatrixType, NorGraphType> flow_func,
        ReductionStats* stats
    )
	{
        //return reduction_use_factorization<RandomGraphType>(std::move(random_graph), std::move(flow_func), stats);

        const reductor_t<RandomGraphType> factorization = [=](RandomGraphType graph, ReductionStats* stats)
        {
            return reduction_use_factorization<RandomGraphType>(std::move(graph), std::move(flow_func), stats).get();
        };

		using namespace random_graph_reductions;
		return boost::async([&stats, factorization](RandomGraphType graph, flow_func_t<SymMatrixType, NorGraphType> flow_func) {
			return split_to_components<RandomGraphType>(graph, stats, factorization);
		}, std::move(random_graph), std::move(flow_func));
	}
    
    template<
        class RandomGraphType,
        class NorGraphType = typename RandomGraphType::GraphType,
        class SymMatrixType = typename RandomGraphType::MatrixType
    >
	boost::future<SymMatrixType> calculate_in_reliable_branch(
        RandomGraphType random_graph,
        flow_func_t<SymMatrixType, NorGraphType> flow_func,
        ReductionStats* stats
    )
    {
        return reduction_use_factorization<RandomGraphType>(std::move(random_graph), std::move(flow_func), stats);
    }
    
    template<
        class RandomGraphType,
        class NorGraphType, // = typename RandomGraphType::GraphType,
        class SymMatrixType // = typename RandomGraphType::MatrixType
    >
	boost::future<SymMatrixType> reduction_use_factorization(
        RandomGraphType random_graph,
        flow_func_t<SymMatrixType, NorGraphType> flow_func,
        ReductionStats* stats
    )
    {
        if (const auto factorized_edge = internal::edge_to_factorize(random_graph); factorized_edge)
        {
            const auto[i, j] = factorized_edge.value_or(std::pair(0, 0));
            
            const auto probability = random_graph.probability_at(i, j);
            assert(!(are_doubles_equal(probability, 0) || are_doubles_equal(probability, 1)));
            
            auto deleted_branch_result = internal::calculate_in_deleted_branch(
                random_graph.with_deleted_edge(i, j),
                flow_func,
                stats
            );
            
            random_graph.set_probability(i, j, 1);
            auto reliable_branch_result = internal::calculate_in_reliable_branch(
                std::move(random_graph),
                std::move(flow_func),
                stats
            );
            
            //return reliable_branch_result * probability + deleted_branch_result * (1 - probability);
            
            return combine_futures<SymMatrixType>(
                std::move(reliable_branch_result),
                std::move(deleted_branch_result),
                [=](auto&& reliable_branch_result, auto&& deleted_branch_result) {
                    return reliable_branch_result * probability + deleted_branch_result * (1 - probability);
                }
            );
        }
        
        auto action = [random_graph, flow_func, stats]() mutable {
            return reduction_use_algorithm<NorGraphType, SymMatrixType>(random_graph.graph(), flow_func, stats);
        };
        return boost::async(std::move(action));
    }
}

namespace graphcpp::flow_calculators
{
	template<
        class RandomGraphType,
        class NorGraphType = typename RandomGraphType::GraphType,
        class SymMatrixType = typename RandomGraphType::MatrixType
    >
	SymMatrixType reduction_use_factorization(
        RandomGraphType random_graph,
        flow_func_t<SymMatrixType, NorGraphType> flow_func,
        ReductionStats* stats,
        bool parallel
    )
	{
        return internal::reduction_use_factorization(std::move(random_graph), std::move(flow_func), stats).get();
	}
    
    template<
        class RandomGraphType,
        class NorGraphType = typename RandomGraphType::GraphType,
        class SymMatrixType = typename RandomGraphType::MatrixType
    >
    SymMatrixType reduction_use_factorization(
        RandomGraphType random_graph,
        single_flow_function_t<NorGraphType> single_flow_func,
        ReductionStats* stats,
        bool parallel
    )
    {
        flow_func_t<SymMatrixType, NorGraphType> matrix_of_flows = std::bind(
            flow_calculators::matrix_of_flows<SymMatrixType, NorGraphType>,
            std::placeholders::_1,
            std::move(single_flow_func)
        );

        return reduction_use_factorization<RandomGraphType, NorGraphType, SymMatrixType>(
            std::move(random_graph),
            std::move(matrix_of_flows),
            stats,
            parallel
        );
    }
}
