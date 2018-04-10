#ifndef GRAPH_CORE_FLOW_CALCULATORS_HPP
#define GRAPH_CORE_FLOW_CALUCLATORS_HPP

#include "core/graph_implementation/graph_base.hpp"

namespace graphcpp::flow_calculators
{
	mcontent Edmonds_Karp_algorithm(const GraphBase& graph, msize source, msize sink);
	std::shared_ptr<SymmetricMatrixBase> Edmonds_Karp_algorithm(const GraphBase& graph);

	std::shared_ptr<SymmetricMatrixBase> Edmonds_Karp_optimized_algorithm(const GraphBase& graph);
}
#endif