#include "core/flow_calculators.hpp"

#include <cassert>
#include <functional>

#include "boost/preprocessor.hpp"

#include "core/matrix_implementations/matrix_implementations.hpp"
#include "core/matrix_implementations/non-symmetric_matrixes/matrix.hpp"
#include "core/graph_implementations/graph_implementations.hpp"
#include "core/graph_implementations/oriented_graphs/oriented_matrix_graph.hpp"

using namespace graphcpp;
using MatrixType = HalfSymmetricMatrix;

namespace
{
	msize get_excess_vertex(const std::vector<mcontent>& excesses, msize sink)
	{
		for(msize i = 0; i < excesses.size(); i++)
		{
			if(excesses[i] > 0 && i != sink)
			{
				return i;
			}
		}

		return sink;
	}
}

template<class GraphType>
mcontent flow_calculators::preflow_push_algorithm(const GraphType& _graph, msize source, msize sink)
{
	assert(source != sink);
	assert(std::max(source, sink) < _graph.dimension());

	OrientedMatrixGraph<Matrix> graph(_graph);

	std::vector<msize> heights(graph.dimension());
	heights[source] = graph.dimension();

	std::vector<mcontent> excesses(graph.dimension());
	for (msize i = 0; i < graph.dimension(); i++)
	{
		excesses[i] = graph.at(source, i);
	}

	OrientedMatrixGraph<Matrix> flows(graph.dimension());

	for(msize i = 0; i < flows.dimension(); i++)
	{
		flows.set(source, i, graph.at(source, i));
		flows.set(i, source, - graph.at(source, i));
	}
	
	//auto excessed_vertex = get_excess_vertex(excesses, sink);

	while(true)
	{
		auto moved = false;
		for(msize i = 0; i < graph.dimension(); i++)
		{
			if(excesses[i] > 0 && i != sink && i != source)
			{
				auto pushed = false;
				for (msize j = 0; j < graph.dimension(); j++)
				{
					if (graph.at(i, j) - flows.at(i, j) > 0 && heights[i] == heights[j] + 1)
					{ //push
						const auto flow_to_push = std::min(excesses[i], graph.at(i, j) - flows.at(i, j));
						flows.set(i, j, flows.at(i, j) + flow_to_push);
						flows.set(j, i, -flows.at(i, j));

						excesses[i] -= flow_to_push;
						excesses[j] += flow_to_push;

						pushed = true;
						moved = true;
						break;
					}
				}

				if(pushed)
				{
					break;
				}

				msize new_height = msize_undefined;
				auto can_lift = true;
				for(msize j = 0; j < graph.dimension(); j++)
				{
					if(graph.at(i, j) - flows.at(i, j) > 0)
					{ 
						if(heights[i] <= heights[j])
						{
							new_height = std::min(new_height, heights[j]);
						}
						else
						{
							can_lift = false;
							break;
						}
					}
				}

				if(can_lift)
				{
					heights[i] = new_height + 1;
					moved = true;
				}

				break;
			}
		}

		if(!moved)
		{
			break;
		}
	}
	/*while (excessed_vertex != sink)
	{
		msize vertex_to_push;	
		for (vertex_to_push = 0; vertex_to_push < graph.dimension(); vertex_to_push++)
		{
			if (graph.at(excessed_vertex, vertex_to_push) - flows.at(excessed_vertex, vertex_to_push) > 0 &&
				heights[excessed_vertex] == heights[vertex_to_push] + 1)
			{
				break;
			}
		}

		if (vertex_to_push == graph.dimension())
		{//lift
			auto new_height = msize_undefined;
			for (msize i = 0; i < graph.dimension(); i++)
			{
				if (graph.at(excessed_vertex, i) - flows.at(excessed_vertex, i) > 0)
				{
					new_height = std::min(new_height, heights[i]);
				}
			}

			assert(new_height != msize_undefined);
			heights[excessed_vertex] = new_height + 1;
		}
		else
		{//push
			const auto flow_to_push = std::min(excesses[excessed_vertex], 
				graph.at(excessed_vertex, vertex_to_push) - flows.at(excessed_vertex, vertex_to_push));
			flows.set(excessed_vertex, vertex_to_push, flows.at(excessed_vertex, vertex_to_push) + flow_to_push);
			flows.set(vertex_to_push, excessed_vertex, - flows.at(excessed_vertex, vertex_to_push));

			excesses[excessed_vertex] -= flow_to_push;
			excesses[vertex_to_push] += flow_to_push;
		}

		excessed_vertex = get_excess_vertex(excesses, sink);
	}*/

	mcontent flow = 0;
	for (msize i = 0; i < graph.dimension(); i++)
	{
		flow += flows.at(source, i);
	}

	return flow;
}

#define PREFLOW_PUSH_SINGLE_MACRO(r, data, graph_type) template mcontent flow_calculators::preflow_push_algorithm<graph_type>(const graph_type&, msize, msize);
BOOST_PP_SEQ_FOR_EACH(PREFLOW_PUSH_SINGLE_MACRO, 0, NON_ORIENTED_GRAPH_IMPLEMENTATIONS_SEQ);

template<class GraphType>
std::shared_ptr<SymmetricMatrixBase> flow_calculators::preflow_push_algorithm(const GraphType& graph)
{
	auto result = std::make_shared<MatrixType>(graph.dimension());

	for (auto[i, j] : graph)
	{
		result->set(i, j, preflow_push_algorithm<GraphType>(graph, i, j));
	}

	return result;
}

#define PREFLOW_PUSH_MATRIX_MACRO(r, data, graph_type) template std::shared_ptr<SymmetricMatrixBase> flow_calculators::preflow_push_algorithm<graph_type>(const graph_type&);
BOOST_PP_SEQ_FOR_EACH(PREFLOW_PUSH_MATRIX_MACRO, 0, NON_ORIENTED_GRAPH_IMPLEMENTATIONS_SEQ);