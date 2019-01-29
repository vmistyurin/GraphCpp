#include "core/flow_calculators/flow_helpers.hpp"

#include <cassert>
#include <algorithm>

#include "core/graphs/non_oriented_graphs/non_oriented_graph_base.hpp"
#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"

using namespace graphcpp;

using SymmetricMatrixType = SingleVectorSymmetricMatrix;

namespace
{
    std::vector<msize> process_subtree(const NonOrientedGraphBase& graph, SymmetricMatrixType& result, msize vertex)
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

std::unique_ptr<SymmetricMatrixBase> flow_calculators::calculate_flows_in_tree(const NonOrientedGraphBase& graph)
{
    assert(graph.is_tree());
    
    auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());
    
    process_subtree(graph, *result, 0);
    
    return result;
}
