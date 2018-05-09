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


	std::shared_ptr<SymmetricMatrixBase> splited_algorithm(const NonOrientedGraphBase& graph,
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
			auto standalone_pair = false;
			for (auto suspect = std::next(current); suspect != hanged_vertexes.cend(); ++suspect)
			{
				if (current->first == suspect->second)
				{
					result->set(current->first, current->second, graph.at(current->first, current->second));
					hanged_vertexes.erase(suspect);
					current = hanged_vertexes.erase(current);
					standalone_pair = true;
					break;
				}
			}
			if (standalone_pair)
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

		auto current_position = hanged_vertexes.cbegin();
		std::vector<msize> addition; 
		addition.reserve(graph.dimension() - hanged_vertexes.size());

		for(msize i = 0; i < graph.dimension(); i++)
		{
			if(current_position != hanged_vertexes.cend() && current_position->first == i)
			{
				++current_position;
			}
			else
			{
				addition.push_back(i);
			}
		}
		auto subgraph_flows = splited_algorithm(*graph.extract_subgraph(addition), single_flow_calculator);

		for (auto[i, j] : *subgraph_flows)
		{
			result->set(addition[i], addition[j], subgraph_flows->at(i, j));
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
}

std::shared_ptr<SymmetricMatrixBase> flow_calculators::reduction_use_algorithm(const NonOrientedGraphBase& graph,
	flow_func single_flow_calculator)
{
	auto result = std::make_shared<MatrixType>(graph.dimension());

	auto components = graph.get_connected_components();
	for (const auto& component : components)
	{
		if (component.size() == 1)
		{
			continue;
		}

		auto subgraph_flows = splited_algorithm(*graph.extract_subgraph(component), single_flow_calculator);
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