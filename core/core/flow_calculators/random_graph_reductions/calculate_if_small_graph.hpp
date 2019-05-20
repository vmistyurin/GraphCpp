#pragma once

#include <optional>

#include "core/macroses.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

namespace graphcpp::flow_calculators::random_graph_reductions::internal
{
	template<class RandomGraphType>
	mcontent calculate_in_3d_graph(const RandomGraphType& graph, msize i, msize j)
	{
		msize k = 3 - i - j;

		#define p(i, j) graph.probabilities().at(i, j)
		#define c(i, j) graph.graph().at(i, j)

		//return p(i, j)* ((1 - p(i, k)) * c(i, j) + p(i, k) * ((1 - p(k, j)) * c(i, j) + p(1, 2) * (c(0, 2) + std::min(c(0, 1), c(1, 2)) +
		//	(1 - p(0, 2) * (p(1, 3) * p(1, 2) * std::min(c(0, 1), c(1, 2)));

		return p(i, j) * ((1 - p(i, k)) * c(i, j) + p(i, k) * ((1 - p(k, j)) * c(i, j) + p(k, j) * (c(i, j) + std::min(c(i, k), c(k, j))))) +
			(1 - p(i, j)) * (p(i, k) * p(k, j) * std::min(c(i, k), c(k, j)));
		
		#undef p
		#undef c
	}
}

namespace graphcpp::flow_calculators::random_graph_reductions
{
	template<class SymMatrixType, class RandomGraphType>
	std::optional<SymMatrixType> calculate_if_small_graph(const RandomGraphType& graph, ReductionStats* stats)
	{
		RETURN_IF(graph.dimension() > 3, std::nullopt);

        if (stats != nullptr)
		{
			stats->register_small_random_graph(graph.dimension());
		}

		if (graph.dimension() == 1)
		{
			return SymMatrixType(1);
		}

		if (graph.dimension() == 2)
		{
			const auto flow = graph.graph().at(0, 1) * graph.probabilities().at(0, 1);
			return SymMatrixType({
				{ 0, flow },
				{ flow, 0 }
			});
		}

		if (graph.dimension() == 3)
		{
			auto result = SymMatrixType(3);

			result.set(0, 1, internal::calculate_in_3d_graph(graph, 0, 1));
			result.set(0, 2, internal::calculate_in_3d_graph(graph, 0, 2));
			result.set(1, 2, internal::calculate_in_3d_graph(graph, 1, 2));
			
			return result;
		}

		abort();
	}
}
