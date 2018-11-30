#include "core/flow_calculators/flow_calculators.hpp"

#include <cmath>
#include <algorithm>
#include <iostream>

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_matrix_graph.hpp"

using namespace graphcpp;

using SymmetricMatrixType = SingleVectorSymmetricMatrix;
using NonOrientedGraphType = NonOrientedMatrixGraph<SingleVectorMatrix>;

namespace
{
	constexpr mcontent flow_to_compute = -1;
	constexpr mcontent hanged_vertex_not_linked = -2;
	//constexpr mcontent hanged_vertex_linked = -3;

	std::unique_ptr<SymmetricMatrixBase> remove_hanged_vertexes(const NonOrientedGraphBase& graph,
		const single_flow_function& single_flow_calculator)
	{
		auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());

		auto hanged_vertexes = graph.get_hanged_vertexes();

		if (hanged_vertexes.empty() || graph.dimension() < 4)
		{
			return flow_calculators::matrix_of_flows(graph, single_flow_calculator);
		}

		for (auto current = hanged_vertexes.cbegin(); !hanged_vertexes.empty() && current != hanged_vertexes.cend(); ++current)
		{
			auto is_standalone_pair = false;
			for (auto suspect = std::next(current); suspect != hanged_vertexes.cend(); ++suspect)
			{
				if (current->first == suspect->second)
				{
					result->set(current->first, current->second, graph.at(current->first, current->second));
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

			result->set(current->first, current->second, graph.at(current->first, current->second));

			for (msize j = 0; j < graph.dimension(); j++)
			{
				if (result->at(current->first, j) == 0 && j != current->first)
				{
					result->set(current->first, j, hanged_vertex_not_linked);
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
			auto subgraph_flows = remove_hanged_vertexes(*graph.extract_subgraph(addition), single_flow_calculator);

			for (auto[i, j] : *subgraph_flows)
			{
				result->set(addition[i], addition[j], subgraph_flows->at(i, j));
			}
		}

		for (const auto&[hanged, support] : hanged_vertexes)
		{
			for (msize i = 0; i < graph.dimension(); i++)
			{
				if (result->at(hanged, i) != 0 && support != i)// && result->at(support, i) != hanged_vertex_not_linked)
				{
					auto flow_from_support_to_i = result->at(i, support);
					assert(flow_from_support_to_i != flow_to_compute);

					auto flow_from_support_to_hanged = graph.at(hanged, support);
						
					result->set(hanged, i, std::min(flow_from_support_to_hanged, flow_from_support_to_i));
				}
			}
		}

		return result;
	}

	msize global_to_chain_number(const std::vector<msize>& chain, msize global_number)
	{
		for (msize i = 0; i < chain.size(); i++)
		{
			if (chain[i] == global_number)
			{
				return i;
			}
		}
		
		abort();
	}

	std::unique_ptr<SymmetricMatrixBase> shrink_chains(NonOrientedGraphBase& graph, std::vector<std::vector<msize>>& chains, const single_flow_function& single_flow_calculator)
	{
		RETURN_IF(chains.empty(), remove_hanged_vertexes(graph, single_flow_calculator));

		auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());

		auto chain = std::move(chains.back());
		chains.pop_back();

		auto capacity = mcontent_undefined;
		auto new_num = msize_undefined;
		for (msize i = 0; i < chain.size() - 1; i++)
		{
			capacity = std::min(capacity, graph.at(chain[i], chain[i + 1]));
			new_num = std::min(new_num, chain[i]);
		}

		auto left_chain_element = chain.front();
		auto right_chain_element = chain.back();

		chain.pop_back();
		chain.erase(chain.begin());

		std::vector<mcontent> left_flows(chain.size());
		auto left_flow = graph.at(left_chain_element, chain.front());		
		for (msize i = 0; i < chain.size() - 1; i++)
		{
			left_flows[i] = left_flow;
			left_flow = std::min(left_flow, graph.at(chain[i], chain[i + 1]));
		}

		std::vector<mcontent> right_flows(chain.size());
		auto right_flow = graph.at(right_chain_element, chain.back());
		for (msize i = chain.size() - 1; i > 0; i--)
		{
			right_flows[i] = right_flow;
			right_flow = std::min(right_flow, graph.at(chain[i], chain[i - 1]));
		}

		auto new_nums = graph.delete_vertexes(chain);
		graph.set(new_nums[left_chain_element], new_nums[right_chain_element], graph.at(new_nums[left_chain_element], new_nums[right_chain_element]) + capacity);

		for (auto& chain : chains)
		{
			for(msize i = 0; i < chain.size(); i++)
			{
				chain[i] = new_nums[chain[i]];
			}
		}

		auto subgraph_flows = shrink_chains(graph, chains, single_flow_calculator);

		for(auto[i, j] : *result)
		{
			if (new_nums[i] != msize_undefined && new_nums[j] != msize_undefined)
			{
				result->set(i, j, subgraph_flows->at(new_nums[i], new_nums[j]));
			}
			else if (new_nums[i] == msize_undefined && new_nums[j] == msize_undefined)
			{
                result->set(i, j, std::fabs(right_flows[global_to_chain_number(chain, i)] - right_flows[global_to_chain_number(chain, j)]));
			}
			else if (new_nums[i] != msize_undefined)
			{
				auto flow = std::min(subgraph_flows->at(new_nums[i], new_nums[left_chain_element]), left_flows[global_to_chain_number(chain, j)]) +
					std::min(subgraph_flows->at(new_nums[i], new_nums[right_chain_element]), right_flows[global_to_chain_number(chain, j)]);

				result->set(i, j, flow);
			}
			else if (new_nums[j] != msize_undefined)
			{
				auto flow = std::min(subgraph_flows->at(new_nums[j], new_nums[left_chain_element]), left_flows[global_to_chain_number(chain, i)]) +
					std::min(subgraph_flows->at(new_nums[j], new_nums[right_chain_element]), right_flows[global_to_chain_number(chain, i)]);

				result->set(i, j, flow);
			}
		}

		return result;
	}

	std::unique_ptr<SymmetricMatrixBase> parse_chains(NonOrientedGraphBase& graph, const single_flow_function& single_flow_calculator)
	{
		auto chains = graph.get_chains();
		return shrink_chains(graph, chains, single_flow_calculator);
	}
}

namespace
{
    
    std::unique_ptr<SymmetricMatrixBase> flow_in_tree(const NonOrientedGraphBase& graph, single_flow_function flow_calc)
    {
        assert(graph.is_tree());
        return flow_calculators::matrix_of_flows(graph, flow_calc);
    }
    
    std::vector<msize> process_subtree(NonOrientedGraphBase& graph, SymmetricMatrixType& result, std::vector<msize>& tree, msize vertex)
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
    
    std::unique_ptr<SymmetricMatrixBase> reduce_connected_trees(NonOrientedGraphBase& graph,
                                                                std::list<std::vector<msize>>& trees,
                                                                const single_flow_function& flow_calc)
    {
        RETURN_IF(trees.empty(), remove_hanged_vertexes(graph, flow_calc))
        auto treeeees = graph.get_connected_trees();
        
        auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());
        
        auto tree = std::move(trees.back());
        trees.pop_back();
        
        const auto root = tree.front();
        tree.erase(tree.cbegin());
        std::sort(tree.begin(), tree.end());
        
        for (auto& other_tree : trees)
        {
            other_tree = reduce_vertexes_numbers(other_tree, tree);
        }
            
        process_subtree(graph, *result, tree, root);
        
        auto addition = find_addition(tree, graph.dimension());
        
        auto subgraph_flows = reduce_connected_trees(*graph.extract_subgraph(addition), trees, flow_calc);
        for (auto[i, j] : *subgraph_flows)
        {
            result->set(addition[i], addition[j], subgraph_flows->at(i, j));
        }
            
        addition.erase(std::find(addition.cbegin(), addition.cend(), root));
        
        for (auto rest_vertex : addition)
        {
            const auto flow_to_root = result->at(rest_vertex, root);
            for (auto tree_vertex : tree)
            {
                result->set(tree_vertex, rest_vertex, std::min(flow_to_root, result->at(root, tree_vertex)));
            }
        }

        return result;
    }
    
    std::unique_ptr<SymmetricMatrixBase> reduce_connected_trees(NonOrientedGraphBase& graph, const single_flow_function& flow_calc)
    {
        auto connected_trees = graph.get_connected_trees();
        decltype(connected_trees) filtered_trees;
        
        for (auto& tree : connected_trees)
        {
            if (tree.size() > 3)
            {
                filtered_trees.emplace_back(std::move(tree));
            }
        }
        
        connected_trees.clear();
        
        return reduce_connected_trees(graph, filtered_trees, flow_calc);
    }
}

std::unique_ptr<SymmetricMatrixBase> flow_calculators::reduction_use_algorithm(const NonOrientedGraphBase& graph, const single_flow_function& single_flow_calculator)
{
	auto result = std::make_unique<SymmetricMatrixType>(graph.dimension());

	auto components = graph.get_connected_components();
	for (const auto& component : components)
	{
		if (component.size() == 1)
		{
			continue;
		}

        std::unique_ptr<SymmetricMatrixBase> subgraph_flows;
        
        if (auto subgraph = graph.extract_subgraph(component); subgraph->is_tree())
        {
            subgraph_flows = flow_in_tree(*subgraph, single_flow_calculator);
        }
        else
        {
            subgraph_flows = reduce_connected_trees(*subgraph, single_flow_calculator);
            assert(subgraph_flows->dimension() == component.size());
        }
        
		for (msize i = 1; i < component.size(); i++)
		{
			for (msize j = 0; j < i; j++)
			{
				result->set(component[i], component[j], subgraph_flows->at(i, j));
			}
		}
	}

	return result;
}
