#include "unit_tests/test_data/non_oriented_test_graph.hpp"

using namespace graphcpp;
using namespace graphcpp::testing;

namespace
{
	const std::vector<SymmetricEdge> test_edges = {
		SymmetricEdge(3, 6, 1),
		SymmetricEdge(4, 6, 2),
		SymmetricEdge(1, 5, 7),
		SymmetricEdge(3, 4, 10),
		SymmetricEdge(2, 4, 4),
		SymmetricEdge(6, 0, 2),
		SymmetricEdge(6, 7, 10)
	};
	constexpr msize test_dimension = 8;

	const std::vector<std::vector<mcontent>> flows = {
        { 0, 0, 2, 2,  2,  0, 2, 2 },
        { 0, 0, 0, 0,  0,  7, 0, 0 },
        { 2, 0, 0, 4,  4,  0, 3, 3 },
        { 2, 0, 4, 0,  11, 0, 3, 3 },
        { 2, 0, 4, 11, 0,  0, 3, 3 },
        { 0, 7, 0, 0,  0,  0, 0, 0 },
        { 2, 0, 3, 3,  3,  0, 0, 10 },
        { 2, 0, 3, 3,  3,  0, 10, 0 }
    };
}

msize non_oriented_test_graph::dimension()
{
	return test_dimension;
}

std::vector<SymmetricEdge> non_oriented_test_graph::get_edges()
{
	return test_edges;
}

std::vector<msize> non_oriented_test_graph::get_degrees()
{
	std::vector<msize> degrees(test_dimension);

	for (const auto& edge : test_edges)
	{
		degrees[edge.v1()]++;
		degrees[edge.v2()]++;
	}

	return degrees;
}

std::vector<std::vector<mcontent>> non_oriented_test_graph::get_flows()
{
	return flows;
}
