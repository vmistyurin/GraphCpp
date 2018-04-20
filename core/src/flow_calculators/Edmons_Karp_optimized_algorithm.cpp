#include "core/flow_calculators.hpp"
#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/graph_implementations/graph_implementations.hpp"

#include "boost/preprocessor.hpp"

#include <algorithm>
#include <assert.h>

using namespace graphcpp;
using MatrixType = HalfSymmetricMatrix;

namespace
{
	constexpr mcontent flow_to_compute = -1;
	constexpr mcontent hanged_vertex_not_linked = -2;
	constexpr mcontent hanged_vertex_linked = -3;

	template<class GraphType>
	std::shared_ptr<SymmetricMatrixBase> EK_optimized_algorithm_splited(const GraphType& graph)
	{
		auto result = std::make_shared<MatrixType>(graph.dimension());

		auto hanged_vertexes = graph.get_hanged_vertexes();
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

			for (msize j = 0; j < graph.dimension(); j++)
			{
				if (result->at(current->first, j) == flow_to_compute)
				{
					result->set(current->first, j, hanged_vertex_not_linked);
				}
			}
			result->set(current->first, current->second, graph.at(current->first, current->second));
		}

		for (auto[i, j] : graph)
		{
			if (result->at(i, j) == 0)
			{
				result->set(i, j, flow_calculators::Edmonds_Karp_algorithm(graph, i, j));
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

	template<class GraphType>
	std::shared_ptr<SymmetricMatrixBase> EK_optimized_algorithm_not_splited(const GraphType& graph)
	{
		auto result = std::make_shared<MatrixType>(graph.dimension());

		auto components = graph.get_connected_components();
		for (const auto& component : components)
		{
			if (component.size() == 1)
			{
				continue;
			}

			auto subgraph = std::static_pointer_cast<GraphType>(graph.extract_subgraph(component));
			auto subgraph_flows = EK_optimized_algorithm_splited(*subgraph);
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
}

template<class GraphType>
std::shared_ptr<SymmetricMatrixBase> flow_calculators::Edmonds_Karp_optimized_algorithm(const GraphType& graph)
{
	return EK_optimized_algorithm_not_splited(graph);
}

#define EDMONDS_KARP_OPTIMIZED_ALGORITHM_MACRO(r, data, graph_type) template std::shared_ptr<SymmetricMatrixBase> flow_calculators::Edmonds_Karp_optimized_algorithm<graph_type>(const graph_type&);
BOOST_PP_SEQ_FOR_EACH(EDMONDS_KARP_OPTIMIZED_ALGORITHM_MACRO, 0, GRAPH_IMPLEMENTATIONS_SEQ);