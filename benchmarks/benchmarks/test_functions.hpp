#pragma once

#include <iostream>
#include <fstream>
#include <functional>

#include "core/graphs/non_oriented_graphs/non_oriented_matrix_graph.hpp"

#include "core/random_graphs/non_oriented_graphs/random_non_oriented_graph.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/factorization.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

namespace graphcpp::bench
{
	template<class RandomGraphType, class NorGraphType = typename RandomGraphType::GraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	std::function<std::string(std::ifstream&&)> factorization(single_flow_function_t<NorGraphType> flow_calc, bool parallel)
	{
		IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);

		return [flow_calc = std::move(flow_calc), parallel](std::ifstream&& input)
		{
			auto random_graph = RandomGraphType::read_from_stream(input);

			const auto result = flow_calculators::factorize(std::move(random_graph), std::move(flow_calc), parallel);

			return result.to_string();
		};
	}

	template<class RandomGraphType, class NorGraphType = typename RandomGraphType::GraphType, class SymMatrixType = typename RandomGraphType::MatrixType>
	std::function<std::string(std::ifstream&&)> reduction_use_algorithm(single_flow_function_t<NorGraphType> flow_calc, bool parallel)
	{
		IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);

		return [flow_calc = std::move(flow_calc), parallel](std::ifstream&& input)
		{
			auto random_graph = RandomGraphType::read_from_stream(input);

			flow_calculators::ReductionStats stats;
			const auto result = flow_calculators::reduction_use_algorithm_r<RandomGraphType>(std::move(random_graph), flow_calc, &stats, parallel);

			return result.to_string();
		};
	}
}

