#include "core/flow_calculators.hpp"

#include <cassert>

#include "boost/preprocessor.hpp"

#include "core/graph_implementations/graph_implementations.hpp"
#include "core/matrix_implementations/matrix_implementations.hpp"

using namespace graphcpp;
using MatrixType = HalfSymmetricMatrix;

template<class GraphType>
mcontent flow_calculators::preflow_push_algorithm(const GraphType& graph, msize source, msize sink)
{
	assert(source != sink);
	assert(std::max(source, sink) < graph.dimension());

	std::vector<msize> heights(graph.dimension());
	heights[source] = graph.dimension();

	std::vector<mcontent> excesses(graph.dimension());
	for (msize i = 0; i < graph.dimension(); i++)
	{
		excesses[i] = graph.at(i, source);
	}

	GraphType flows(graph.dimension());

	auto excessed_vertex_it = std::find(excesses.cbegin(), excesses.cend(), 0);
	while (excessed_vertex_it != excesses.cend())
	{
		auto excessed_vertex = std::distance(excesses.cbegin(), excessed_vertex_it);

		msize vertex_to_push;
		for (vertex_to_push = 0; vertex_to_push < graph.dimension(); vertex_to_push++)
		{
			if (graph.at(excessed_vertex, vertex_to_push) - flows.at(excessed_vertex, vertex_to_push) > 0 &&
				std::fabs(heights[excessed_vertex] - heights[vertex_to_push]) == 1)
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
			auto flow_to_push = std::max(excesses[excessed_vertex], graph.at(excessed_vertex, vertex_to_push) - flows.at(excessed_vertex, vertex_to_push));
			flows.set(excessed_vertex, vertex_to_push, flows.at(excessed_vertex, vertex_to_push) + flow_to_push);

			excesses[excessed_vertex] -= flow_to_push;
			excesses[vertex_to_push] += flow_to_push;
		}

		excessed_vertex_it = std::find(excesses.cbegin(), excesses.cend(), 0);
	}

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