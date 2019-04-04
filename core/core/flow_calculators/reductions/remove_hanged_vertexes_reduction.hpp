#pragma once

#include "core/macroses.hpp"
#include "core/flow_calculators/definitions.hpp"
#include "core/flow_calculators/reduction_stats.hpp"

namespace graphcpp::flow_calculators::reductors::internal 
{
    constexpr mcontent flow_to_compute = -1;
    constexpr mcontent hanged_vertex_not_linked = -2;

    template<class SymMatrixType, class NorGraphType>
    SymMatrixType remove_hanged_vertexes(
        NorGraphType graph,
        ReductionStats* stats,
        std::function<SymMatrixType(NorGraphType, ReductionStats*)> calculator
    )
    {
        auto result = SymMatrixType(graph.dimension());

        auto hanged_vertexes = graph.get_hanged_vertexes();

        if (hanged_vertexes.empty() || graph.dimension() < 4)
        {
            return calculator(std::move(graph), stats);
        }

        for (auto current = hanged_vertexes.cbegin(); !hanged_vertexes.empty() && current != hanged_vertexes.cend(); ++current)
        {
            auto is_standalone_pair = false;
            for (auto suspect = std::next(current); suspect != hanged_vertexes.cend(); ++suspect)
            {
                if (current->first == suspect->second)
                {
                    result.set(current->first, current->second, graph.at(current->first, current->second));
                    hanged_vertexes.erase(suspect);
                    current = hanged_vertexes.erase(current);
                    is_standalone_pair = true;
                    break;
                }
            }
            if (is_standalone_pair)
            {
                if (current == hanged_vertexes.cend())
                {
                    break;
                }
                continue;
            }

            if (stats != nullptr)
            {
                stats->increase_hanged_vertexes_counter(hanged_vertexes.size());
            }

            result.set(current->first, current->second, graph.at(current->first, current->second));

            for (msize j = 0; j < graph.dimension(); j++)
            {
                if (result.at(current->first, j) == 0 && j != current->first)
                {
                    result.set(current->first, j, hanged_vertex_not_linked);
                }
            }
        }

        if (graph.dimension() != hanged_vertexes.size() + 1)
        {
            auto current_position = hanged_vertexes.cbegin();
            std::vector<msize> addition;
            addition.reserve(graph.dimension() - hanged_vertexes.size());

            for (msize i = 0; i < graph.dimension(); i++)
            {
                if (current_position != hanged_vertexes.cend() && current_position->first == i)
                {
                    ++current_position;
                }
                else
                {
                    addition.push_back(i);
                }
            }
            auto subgraph_flows = remove_hanged_vertexes(graph.template extract_subgraph<NorGraphType>(addition), stats, std::move(calculator));

            for (auto[i, j] : subgraph_flows)
            {
                result.set(addition[i], addition[j], subgraph_flows.at(i, j));
            }
        }

        for (auto[hanged, support] : hanged_vertexes)
        {
            for (msize i = 0; i < graph.dimension(); i++)
            {
                if (result.at(hanged, i) != 0 && support != i)
                {
                    auto flow_from_support_to_i = result.at(i, support);
                    assert(flow_from_support_to_i != flow_to_compute);

                    auto flow_from_support_to_hanged = graph.at(hanged, support);

                    result.set(hanged, i, std::min(flow_from_support_to_hanged, flow_from_support_to_i));
                }
            }
        }

        return result;
    }
}

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType remove_hanged_vertexes(
        NorGraphType graph,
        ReductionStats* stats,
        std::function<SymMatrixType(NorGraphType, ReductionStats*)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        return internal::remove_hanged_vertexes(std::move(graph), stats, std::move(next_reductor));
    }
}