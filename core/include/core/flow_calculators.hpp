#ifndef GRAPH_CORE_FLOW_CALCULATORS_HPP
#define GRAPH_CORE_FLOW_CALUCLATORS_HPP

#include "core/graph_implementations/graph_base.hpp"

namespace graphcpp::flow_calculators
{
	template<class GraphType>
	mcontent Edmonds_Karp_algorithm(const GraphType& graph, msize source, msize sink);

	template<class GraphType>
	std::shared_ptr<SymmetricMatrixBase> Edmonds_Karp_algorithm(const GraphType& graph);

	template<class GraphType>
	std::shared_ptr<SymmetricMatrixBase> Edmonds_Karp_optimized_algorithm(const GraphType& graph);

	template<class GraphType>
	mcontent Dinic_algorithm(const GraphType& graph, msize source, msize sink);

	template<class GraphType>
    std::shared_ptr<SymmetricMatrixBase> Dinic_algorithm(const GraphType& graph);
}
#endif