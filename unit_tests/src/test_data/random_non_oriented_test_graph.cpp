#include "unit_tests/test_data/random_non_oriented_test_graph.hpp"

#include <type_traits>

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	const std::vector<SymmetricRandomEdge> edges = { SymmetricRandomEdge(SymmetricEdge(0, 2, 10), 0.5),
                                                     SymmetricRandomEdge(SymmetricEdge(0, 3, 20), 0.7),
                                                     SymmetricRandomEdge(SymmetricEdge(2, 3, 5), 0.1),
                                                     SymmetricRandomEdge(SymmetricEdge(1, 2, 6), 0.2),
                                                     SymmetricRandomEdge(SymmetricEdge(2, 4, 100), 1)};

	const auto not_existed_edge = std::pair(0, 1);

	const auto dimension = 5;
}

msize random_non_oriented_test_graph::dimension()
{
	return ::dimension;
}

std::vector<SymmetricRandomEdge> random_non_oriented_test_graph::edges()
{
	return ::edges;
}

std::pair<msize, msize> random_non_oriented_test_graph::not_existed_edge()
{
	return ::not_existed_edge;
}

std::vector<msize> random_non_oriented_test_graph::vertexes_to_delete()
{
	return { 1, 4 };
}

std::vector<SymmetricRandomEdge> random_non_oriented_test_graph::edges_after_delete()
{
	return {
		SymmetricRandomEdge(SymmetricEdge(0, 1, 10), 0.5),
		SymmetricRandomEdge(SymmetricEdge(0, 2, 20), 0.7),
		SymmetricRandomEdge(SymmetricEdge(1, 2, 5), 0.1)
	};
}