#pragma once

#include <functional>
#include <memory>

#include "core/flow_calculators/definitions.hpp"

namespace graphcpp
{
    class SymmetricMatrixBase;
    class NonOrientedGraphBase;
}

namespace graphcpp::flow_calculators
{
    namespace internal
    {
        template<class MatrixType, class GraphType>
        std::vector<msize> process_subtree(const GraphType& graph, MatrixType& result, msize vertex)
        {
            std::vector<msize> childs;
            std::vector<std::vector<msize>> subtrees;
            
            for (msize i = 0; i < graph.dimension(); i++)
            {
                if (graph.at(vertex, i) > 0 && result.at(vertex, i) == 0)
                {
                    result.set(vertex, i, graph.at(vertex, i));
                    childs.push_back(i);
                    
                    if (auto next_childs = process_subtree(graph, result, i); !next_childs.empty())
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
            
            for (decltype(subtrees)::size_type i = 0; i < subtrees.size(); i++)
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
    }

    template<class MatrixType, class GraphType>
    MatrixType calculate_flows_in_tree(const GraphType& graph)
    {
        IS_SYM_MATRIX_IMPL(MatrixType);
        assert(graph.is_tree());
        
        auto result = MatrixType(graph.dimension());
        
        internal::process_subtree(graph, result, 0);
        
        return result;
    }

    template<class MatrixType, class GraphType>
	MatrixType matrix_of_flows(
        const GraphType& graph,
		const single_flow_function& single_flow_calculator
    )
    {
        IS_SYM_MATRIX_IMPL(MatrixType);

        MatrixType result(graph.dimension());

        for (auto[i, j] : graph)
        {
            result.set(i, j, single_flow_calculator(graph, i, j));
        }

        return result;
    }
}

