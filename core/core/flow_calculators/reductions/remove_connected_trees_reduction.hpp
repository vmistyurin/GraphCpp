#pragma once

#include <list>

#include "core/macroses.hpp"
#include "core/utils/numeric.hpp"
#include "core/flow_calculators/definitions.hpp"

namespace graphcpp::flow_calculators::reductors::internal 
{
    template<class SymMatrixType, class NorGraphType>
    std::vector<msize> process_subtree(NorGraphType& graph, SymMatrixType& result, std::vector<msize>& tree, msize vertex)
    {
        std::vector<msize> childs;
        std::vector<std::vector<msize>> subtrees;

        for (msize i = 0; i < graph.dimension(); i++)
        {
            if (std::binary_search(tree.cbegin(), tree.cend(), i) && graph.at(vertex, i) > 0 && result.at(vertex, i) == 0)
            {
                result.set(vertex, i, graph.at(vertex, i));
                childs.push_back(i);

                if (auto next_childs = process_subtree(graph, result, tree, i); !next_childs.empty())
                {
                    for (auto child : next_childs)
                    {
                        result.set(vertex, child, std::min(result.at(vertex, i), result.at(i, child)));
                    }

                    childs.insert(childs.cend(), next_childs.cbegin(), next_childs.cend());

                    subtrees.emplace_back(std::move(next_childs));
                }
                else
                {
                    subtrees.emplace_back();
                }

                subtrees.back().push_back(i);
            }
        }

        for (typename decltype(subtrees)::size_type i = 0; i < subtrees.size(); i++)
        {
            for (decltype(i) j = i + 1; j < subtrees.size(); j++)
            {
                for (auto first_vertex : subtrees[i])
                {
                    for (auto second_vertex : subtrees[j])
                    {
                        result.set(first_vertex, second_vertex, std::min(result.at(first_vertex, vertex), result.at(second_vertex, vertex)));
                    }
                }
            }
        }

        return childs;
    }

    template<class SymMatrixType, class NorGraphType>
    SymMatrixType apply_remove_connected_trees(
        NorGraphType graph, 
        std::list<std::vector<msize>>& trees,
        std::shared_ptr<ReductionStatistic> stats,
        std::function<SymMatrixType(NorGraphType, std::shared_ptr<ReductionStatistic>)> calculator
    )
    {
        RETURN_IF(trees.empty(), calculator(graph, stats));
        
        auto result = SymMatrixType(graph.dimension());
        
        auto tree = std::move(trees.back());
        trees.pop_back();
        
        const auto root = tree.front();
        tree.erase(tree.cbegin());
        std::sort(tree.begin(), tree.end());
        
        for (auto& other_tree : trees)
        {
            other_tree = reduce_vertexes_numbers(other_tree, tree);
        }
        
        process_subtree(graph, result, tree, root);
        
        auto addition = find_addition(tree, graph.dimension());
        auto addition_subgraph = graph.template extract_subgraph<NorGraphType>(addition);

        auto subgraph_flows = apply_remove_connected_trees<SymMatrixType, NorGraphType>(std::move(addition_subgraph), trees, stats, calculator);
        for (auto[i, j] : subgraph_flows)
        {
            result.set(addition[i], addition[j], subgraph_flows.at(i, j));
        }
        
        addition.erase(std::find(addition.cbegin(), addition.cend(), root));
        
        for (auto rest_vertex : addition)
        {
            const auto flow_to_root = result.at(rest_vertex, root);
            for (auto tree_vertex : tree)
            {
                result.set(tree_vertex, rest_vertex, std::min(flow_to_root, result.at(root, tree_vertex)));
            }
        }
            
        return result;
    }
}

namespace graphcpp::flow_calculators::reductors
{
    template<class SymMatrixType, class NorGraphType>
    SymMatrixType remove_connected_trees(
        NorGraphType graph,
        std::shared_ptr<ReductionStatistic> stats,
        std::function<SymMatrixType(NorGraphType, std::shared_ptr<ReductionStatistic>)> next_reductor
    )
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        auto trees = graph.get_connected_trees();
        return internal::apply_remove_connected_trees(std::move(graph), trees, stats, next_reductor);
    }
}