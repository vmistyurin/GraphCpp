#pragma once

#include <functional>

#include "core/macroses.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

#include "core/flow_calculators/random_graph_reductions/calculate_if_small_graph.hpp"

namespace graphcpp::flow_calculators::random_graph_reductions
{
    template<class RandomGraphType>
	typename RandomGraphType::MatrixType split_to_components(
        RandomGraphType random_graph,
        ReductionStats* stats,
        reductor_t<RandomGraphType> next_reductor
    )
    {
        IS_NOR_RANDOM_GRAPH_IMPL(RandomGraphType);

        auto result = typename RandomGraphType::MatrixType(random_graph.graph().dimension());
        
        const auto components = random_graph.graph().get_connected_components();
        for (const auto& component : components)
        {
            if (stats != nullptr)
            {
                stats->register_disconnected_component(component.size());
            }
            
			auto subgraph = random_graph.extract_subgraph(component);
			typename RandomGraphType::MatrixType subgraph_flows;
			if (auto sub_flows = calculate_if_small_graph<typename RandomGraphType::MatrixType>(subgraph, stats); sub_flows)
            {
				subgraph_flows = std::move(sub_flows.value_or(typename RandomGraphType::MatrixType(1)));
                assert(subgraph_flows.dimension() == component.size());
            } 
			else
			{
				subgraph_flows = next_reductor(std::move(subgraph), stats);
                assert(subgraph_flows.dimension() == component.size());
            }

			assert(subgraph_flows.dimension() == component.size());
            
            for (msize i = 1; i < component.size(); i++)
            {
                for (msize j = 0; j < i; j++)
                {
                    result.set(component[i], component[j], subgraph_flows.at(i, j));
                }
            }
        }
        
        return result;
    }
}
