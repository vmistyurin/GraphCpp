#include "unit_tests/test_data/random_test_graph.hpp"

#include <type_traits>

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	namespace oriented_graph
	{

		const std::vector<Edge> matrix = { Edge(3, 4, 10), 
										   Edge(3, 5, 6), 
										   Edge(4, 3, 10), 
										   Edge(2, 0, 1), 
										   Edge(2, 1, 40),
										   Edge(0, 1, 7),
										   Edge(0, 3, 5),
										   Edge(3, 0, 5),
										   Edge(1, 2, 30)
										  };
	}

	namespace non_oriented_graph
	{
		const std::vector<SymmetricalEdge> matrix = { SymmetricalEdge(3, 4, 10),
													  SymmetricalEdge(3, 5, 6),
													  SymmetricalEdge(4, 3, 10),
													  SymmetricalEdge(2, 0, 1),
													  SymmetricalEdge(2, 1, 40),
													  SymmetricalEdge(0, 1, 7),
													  SymmetricalEdge(0, 3, 5),
													  SymmetricalEdge(3, 0, 5),
													  SymmetricalEdge(1, 2, 30)
													};
	}

	const std::vector<double> probabilities = { 0.5, 0.3, 0.6, 0.33, 1, 0.1 };
	const auto dimension = probabilities.size();
}

msize random_test_graph::dimension() 
{
	return ::dimension;
}

std::vector<Edge> random_test_graph::get_edges()
{
	return oriented_graph::matrix;
}

std::vector<double> random_test_graph::probabilities()
{
	return ::probabilities;
}

std::vector<std::pair<std::pair<msize, msize>, mcontent>> random_test_graph::getter_test()
{
	decltype(getter_test()) result; result.reserve(3);

	for(msize i = 0; i < result.size(); i++)
	{
		auto edge = oriented_graph::matrix[i];
		result.push_back(std::pair(std::pair(edge.v1(), edge.v2()), edge.weight));
	}

	return result;
}

template<>
std::unique_ptr<RandomGraphBase> random_test_graph::get_graph<RandomGraph<NonOrientedMatrixGraph<FullSymmetricMatrix>>>()
{
    return std::make_unique<RandomGraph<NonOrientedMatrixGraph<FullSymmetricMatrix>>>(NonOrientedMatrixGraph<FullSymmetricMatrix>(non_oriented_graph::matrix, dimension()), probabilities());
}

template<>
std::unique_ptr<RandomGraphBase> random_test_graph::get_graph<RandomGraph<OrientedMatrixGraph<Matrix>>>()
{
    return std::make_unique<RandomGraph<OrientedMatrixGraph<Matrix>>>(OrientedMatrixGraph<Matrix>(oriented_graph::matrix, dimension()), probabilities());
}