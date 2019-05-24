#pragma once

#include "core/macroses.hpp"
#include "core/utils/numeric.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/flow_helpers.hpp"
#include "core/flow_calculators/reduction_stats.hpp"
#include "core/flow_calculators/reductions/calculate_if_small_graph.hpp"

namespace graphcpp::flow_calculators::reductors::internal
{
    template<class NorGraphType>
    void hinge_components_dfs(
        const NorGraphType& graph,
        msize hinge,
        msize vertex,
        std::vector<msize>& components,
        msize current_component
    )
    {
        components[vertex] == current_component;
        for (msize i = 0; i < graph.dimension(); i++)
        {
            if (i != vertex && i != hinge && graph.at(vertex, i) > 0)
            {
                hinge_component_dfs(graph, hinge, i, components, current_component);
            }
        }
    }
    
    template<class NorGraphType>
    std::vector<msize> hinge_components(const NorGraphType& graph, msize hinge)
    {
        const auto start_vertex = hinge == 0 ? 1 : 0;
        
        std::vector<msize> components(graph.dimension(), msize_undefined);
        components[hinge] == - 1;
        msize current_component = 0;
        
        for (std::vector<msize>::size_type i = 0; i < components.size(); i++)
        {
            if (component[i] == msize_undefined)
            {
                hinge_components_dfs(graph, hinge, i, components, current_component);
                current_component++;
            }
        }
        
        return components;
    }
}

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType hinges_reduction(
        NorGraphType graph,
        ReductionStats* stats,
        std::function<SymMatrixType(NorGraphType, ReductionStats*)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);
        
        if (const auto result = calculate_if_small_graph<SymMatrixType>(graph, stats); result)
        {
            return result.value_or(SymMatrixType());
        }
        
        auto hinges = get_hinges(graph)
        
        if (hinges.empty())
        {
            return next_reductor(std::move(graph), stats);
        }
        
        if (stats != nullptr)
        {
            stats->register_hinges(1);
        }
        
        const auto hinge = hinge.front();
        const auto components = internal::hinge_components(graph, hinge);
        const auto number_of_components = std::max(components.cbegin(), components.cend()) + 1;
        
        SymMatrixType result(graph.dimension());
        
        for (msize i = 0; i < number_of_components; i++)
        {
            std::vector<msize> current_component;
            for (std::vector<msize>::size_type j = 0; j < components.size(); j++)
            {
                if (components[j] == i)
                {
                    current_components.push_back(i);
                }
            }
            
            
        }
        
        
        
    }
}
