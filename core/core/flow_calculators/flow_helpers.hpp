#pragma once

#include <functional>
#include <memory>

#include "core/flow_calculators/definitions.hpp"

namespace graphcpp
{
    class SymmetricMatrixBase;
    class NonOrientedGraphBase;
}

namespace graphcpp::flow_calculators::internal
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

    template<class NorGraphType>
    mcontent flow_in_4d_graph(const NorGraphType& graph, msize i, msize j)
    {
        IS_NOR_GRAPH_IMPL(NorGraphType);

        assert(graph.dimension() == 4);

        msize k = -1, l = -1;

        for(int it = 0; it < 4; it++) 
        {
            if (it != i && it != j) 
            {
                if (k == -1)
                {
                    k = it;
                } 
                else 
                {
                    l = it;
                }
            }
        }

        return graph.at(i, j) + std::min(graph.at(i, k), graph.at(k, j)) + std::min(graph.at(i, l), graph.at(l, j)) +
            std::min
            ({
                std::max(graph.at(i, k) - std::min(graph.at(i, k), graph.at(k, j)), mcontent(0)), 
                graph.at(k, l), 
                std::max(graph.at(l, j) - std::min(graph.at(i, l), graph.at(l, j)), mcontent(0))
            }) + 
            std::min
            ({
                std::max(graph.at(i, l) - std::min(graph.at(i, l), graph.at(l, j)), mcontent(0)), 
                graph.at(k, l), 
                std::max(graph.at(k, j) - std::min(graph.at(i, k), graph.at(k, j)), mcontent(0))
            });
    }
}

namespace graphcpp::flow_calculators
{
    template<class MatrixType, class GraphType>
    MatrixType calculate_flows_in_tree(const GraphType& graph)
    {
        IS_SYM_MATRIX_IMPL(MatrixType);
        assert(graph.is_tree());
        
        auto result = MatrixType(graph.dimension());
        
        internal::process_subtree(graph, result, 0);
        
        return result;
    }

	template<class SymMatrixType, class GraphType>
	SymMatrixType matrix_of_flows(
		const GraphType& graph,
		const single_flow_function_t<GraphType> single_flow_calculator
	)
	{
		IS_SYM_MATRIX_IMPL(SymMatrixType);

		SymMatrixType result(graph.dimension());

		for (auto [i, j] : graph)
		{
			result.set(i, j, single_flow_calculator(graph, i, j));
		}

		return result;
	}

    template<class SymMatrixType, class NorGraphType>
	SymMatrixType calculate_for_small_graph(const NorGraphType& graph) 
    {
        IS_SYM_MATRIX_IMPL(SymMatrixType);
        IS_NOR_GRAPH_IMPL(NorGraphType);

        assert(graph.dimension() < 5);

        if (graph.dimension() == 1) 
        {
			return SymMatrixType(1);
        }

        if (graph.dimension() == 2)
        {
            return SymMatrixType({
				{ 0, graph.at(0, 1) },
                { graph.at(0, 1), 0 } 
			});
        }

        if (graph.dimension() == 3)
        {
            auto result = SymMatrixType(3);

            result.set(0, 1, graph.at(0, 1) + std::min(graph.at(0, 2), graph.at(1, 2))); 
            result.set(0, 2, graph.at(0, 2) + std::min(graph.at(0, 1), graph.at(1, 2)));
            result.set(1, 2, graph.at(1, 2) + std::min(graph.at(0, 1), graph.at(0, 2))); 

            return result;
        }

        if (graph.dimension() == 4)
        {
            auto result = SymMatrixType(4);

            for (auto[i, j] : result)
            {
                result.set(i, j, internal::flow_in_4d_graph(graph, i, j)); 
            }

			return result;
        }

        abort();
    }
}

