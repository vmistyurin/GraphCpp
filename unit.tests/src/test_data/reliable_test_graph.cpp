#include "unit.tests/test_data/reliable_test_graph.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	const std::vector<Edge> test_edges =
	{
		Edge(3, 6, 1),
		Edge(4, 6, 2),
		Edge(1, 5, 7),
		Edge(3, 4, 10),
		Edge(2, 4, 4),
		Edge(6, 0, 2),
		Edge(6, 7, 10)
	};
	constexpr msize test_dimension = 8;

	const std::vector<std::vector<mcontent>> flows = { { 0, 0, 2, 2,  2,  0, 2, 2 },
													   { 0, 0, 0, 0,  0,  7, 0, 0 },
													   { 2, 0, 0, 4,  4,  0, 3, 3 },
													   { 2, 0, 4, 0,  11, 0, 3, 3 },
													   { 2, 0, 4, 11, 0,  0, 3, 3 },
													   { 0, 7, 0, 0,  0,  0, 0, 0 },
													   { 2, 0, 3, 3,  3,  0, 0, 10 },
													   { 2, 0, 3, 3,  3,  0, 10, 0 } };
}

msize reliable_test_graph::dimension()
{
	return test_dimension;
}

std::vector<Edge> reliable_test_graph::get_edges()
{
	return test_edges;
}

std::vector<msize> reliable_test_graph::get_degrees()
{
	std::vector<msize> degrees(test_dimension);

	for (const auto& edge : test_edges)
	{
		degrees[edge.v1()]++;
		degrees[edge.v2()]++;
	}

	return degrees;
}

template<>
std::unique_ptr<GraphBase> reliable_test_graph::get_graph<MatrixGraph<FullSymmetricMatrix>>()
{
	return std::make_unique<MatrixGraph<FullSymmetricMatrix>>(test_edges, test_dimension);
}

template<>
std::unique_ptr<GraphBase> reliable_test_graph::get_graph<MatrixGraph<HalfSymmetricMatrix>>()
{
	return std::make_unique<MatrixGraph<HalfSymmetricMatrix>>(test_edges, test_dimension);
}

std::vector<std::vector<mcontent>> reliable_test_graph::get_flows()
{
	return flows;
}