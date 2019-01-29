#include "core/flow_calculators/flow_calculators.hpp"

#include <cassert>

#include "core/matrices/symmetric_matrices/single_vector_symmetric_matrix.hpp"
#include "core/matrices/non_symmetric_matrices/single_vector_matrix.hpp"
#include "core/graphs/oriented_graphs/oriented_matrix_graph.hpp"

using namespace graphcpp;

using MatrixType = SingleVectorMatrix;
using SymmetricMatrixType = SingleVectorSymmetricMatrix;

using GraphType = OrientedMatrixGraph<MatrixType>;

mcontent flow_calculators::preflow_push_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink)
{
	assert(source != sink);
	assert(std::max(source, sink) < graph.dimension());

	std::vector<msize> heights(graph.dimension());
	heights[source] = graph.dimension();

	std::vector<mcontent> excesses(graph.dimension());
	for (msize i = 0; i < graph.dimension(); i++)
	{
		excesses[i] = graph.at(source, i);
	}

	GraphType flows(graph.dimension());

	for (msize i = 0; i < flows.dimension(); i++)
	{
		flows.set(source, i, graph.at(source, i));
		flows.set(i, source, - graph.at(source, i));
	}
	
	while (true)
	{
		auto moved = false;
		for (msize i = 0; i < graph.dimension(); i++)
		{
			if (excesses[i] > 0 && i != sink && i != source)
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

				if (pushed)
				{
					break;
				}

				msize new_height = msize_undefined;
				auto can_lift = true;
				for(msize j = 0; j < graph.dimension(); j++)
				{
					if (graph.at(i, j) - flows.at(i, j) > 0)
					{ 
						if (heights[i] <= heights[j])
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

				if (can_lift)
				{
					heights[i] = new_height + 1;
					moved = true;
				}

				break;
			}
		}

		if (!moved)
		{
			break;
		}
	}

	mcontent flow = 0;
	for (msize i = 0; i < graph.dimension(); i++)
	{
		flow += flows.at(source, i);
	}

	return flow;
}
