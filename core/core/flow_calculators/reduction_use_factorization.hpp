#pragma once

#include <optional>

#include "core/utils/defer.hpp"
#include "core/edges/symmetric_edge.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

#include "core/flow_calculators/computations/single_threaded/single_thread_calculator.hpp"
#include "core/flow_calculators/computations/multi_threaded/multi_thread_calculator.hpp"

namespace graphcpp::flow_calculators::internal
{
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

	template<class RandomGraphType>
	std::optional<std::pair<msize, msize>> edge_to_factorize(const RandomGraphType& random_graph)
	{
		for (auto iter = random_graph.probabilities().begin(); iter != random_graph.probabilities().end(); ++iter)
		{
			const auto [i, j] = *iter;
			const auto edge_probability = random_graph.probability_at(i, j);

			if (!(are_doubles_equal(edge_probability, 0) || edge_probability(vertex_probability, 1)))
			{
				return std::pair(i, j);
			}
		}

		return std::nullopt;
	}

	template<class RandomGraphType, class NorGraphType = typename RandomGraphType::GraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	SymMatrixType calculate_in_deleted_branch(RandomGraphType random_graph)
	{
		const reductor_t<RandomGraphType> factorization = [=](RandomGraphType graph, ReductionStats * stats)
		{
			return factorize<RandomGraphType>(std::move(graph), flow_calc, parallel);
		};


		return random_graph_reductions::split_to_components<RandomGraphType>(random_graph, stats, factorization);
	}
}

namespace graphcpp::flow_calculators
{
	template<class RandomGraphType, class NorGraphType = typename RandomGraphType::GraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	SymMatrixType reduction_use_factorization(RandomGraphType random_graph, flow_func_t<SymMatrixType, NorGraphType> calc, ReductionStats* stats, bool parallel)
	{
		auto calculator = internal::make_calculator<NorGraphType, SymMatrixType>(parallel, std::move(calc), random_graph.dimension());

		const auto factorized_edge = internal::edge_to_factorize(random_graph);
		while (factorized_edge)
		{
			Defer defer([&] { factorized_edge = internal::edge_to_factorize(random_graph); });
			const auto[i, j] = factorized_edge.value();

			auto deleted_branch = random_graph.with_deleted_edge();
			random_graph.set_probability_at(i, j, 1);

		}
	}
}