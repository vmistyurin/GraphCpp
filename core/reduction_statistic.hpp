#ifndef GRAPH_CORE_REDUCTION_STATISTIC_HPP
#define GRAPH_CORE_REDUCTION_STATISTIC_HPP

#include <cstddef>
#include <vector>

#include "core/macroses.hpp"

namespace graphcpp
{
	struct ReductionStatistic final
	{
		size_t hanged_vertexes;
		size_t components;
		std::vector<msize> chains;
	};
}
#endif