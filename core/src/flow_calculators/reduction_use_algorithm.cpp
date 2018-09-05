#include "core/flow_calculators.hpp"

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/graph_implementations/non-oriented_graphs/non_oriented_matrix_graph.hpp"

using namespace graphcpp;
using MatrixType = FullSymmetricMatrix;
using GraphType = NonOrientedMatrixGraph<HalfSymmetricMatrix>;

using flow_func = const std::function<mcontent(const NonOrientedGraphBase&, msize, msize)>&;

namespace
{
	constexpr mcontent flow_to_compute = -1;
	constexpr mcontent hanged_vertex_not_linked = -2;
	constexpr mcontent hanged_vertex_linked = -3;


	std::shared_ptr<SymmetricMatrixBase> remove_hanged_vertexes(const NonOrientedGraphBase& graph,
		flow_func single_flow_calculator)
	{
		auto result = std::make_shared<MatrixType>(graph.dimension());

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
		for(msize i = 0; i < chain.size(); i++)
		{
			if(chain[i] == global_number)
			{
				return i;
			}
		}
		
		abort();
	}

	std::shared_ptr<SymmetricMatrixBase> shrink_chains(NonOrientedGraphBase& graph, std::vector<std::vector<msize>>& chains, flow_func single_flow_calculator)
	{
		RETURN_IF(chains.empty(), remove_hanged_vertexes(graph, single_flow_calculator));

		auto result = std::make_shared<MatrixType>(graph.dimension());

		auto chain = std::move(chains.back());
		chains.pop_back();

		auto capacity = mcontent_undefined;
		auto new_num = msize_undefined;
		for(msize i = 0; i < chain.size() - 1; i++)
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
		for(msize i = 0; i < chain.size() - 1; i++)
		{
			left_flows[i] = left_flow;
			left_flow = std::min(left_flow, graph.at(chain[i], chain[i + 1]));
		}

		std::vector<mcontent> right_flows(chain.size());
		auto right_flow = graph.at(right_chain_element, chain.back());
		for(msize i = chain.size() - 1; i > 0; i++)
		{
			right_flows[i] = right_flow;
			right_flow = std::min(right_flow, graph.at(chain[i], chain[i - 1]));
		}

		auto new_nums = graph.delete_vertexes(chain);
		graph.set(new_nums[left_chain_element], new_nums[right_chain_element], graph.at(new_nums[left_chain_element], new_nums[right_chain_element]) + capacity);

		for(auto& chain : chains)
		{
			for(msize i = 0; i < chain.size(); i++)
			{
				chain[i] = new_nums[chain[i]];
			}
		}

		auto subgraph_flows = shrink_chains(graph, chains, single_flow_calculator);

		for(auto[i,j] : *result)
		{
			if (new_nums[i] != msize_undefined && new_nums[j] != msize_undefined)
			{
				result->set(i, j, subgraph_flows->at(new_nums[i], new_nums[j]));
			}
			else if(new_nums[i] == msize_undefined && new_nums[j] == msize_undefined)
			{
				result->set(i, j, abs(right_flows[global_to_chain_number(chain, i)] - right_flows[global_to_chain_number(chain, j)]));
			}
			else if(new_nums[i] != msize_undefined)
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

	std::shared_ptr<SymmetricMatrixBase> parse_chains(NonOrientedGraphBase& graph, flow_func single_flow_calculator)
	{
		auto chains = graph.get_chains();
		return shrink_chains(graph, chains, single_flow_calculator);
	}
}

std::shared_ptr<SymmetricMatrixBase> flow_calculators::reduction_use_algorithm(const NonOrientedGraphBase& graph, flow_func single_flow_calculator)
{
	auto result = std::make_shared<MatrixType>(graph.dimension());

	auto components = graph.get_connected_components();
	for (const auto& component : components)
	{
		if (component.size() == 1)
		{
			continue;
		}

		auto subgraph_flows = remove_hanged_vertexes(*graph.extract_subgraph(component), single_flow_calculator);
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