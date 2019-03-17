#pragma once

#include "core/macroses.hpp"

namespace graphcpp
{
    class NonOrientedGraphBase;
}

namespace graphcpp::flow_calculators
{
	mcontent Edmonds_Karp_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent Dinic_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);

	mcontent preflow_push_algorithm(const NonOrientedGraphBase& graph, msize source, msize sink);
}
