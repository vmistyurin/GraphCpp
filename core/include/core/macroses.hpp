#ifndef GRAPH_CORE_MACROSES_HPP
#define GRAPH_CORE_MACROSES_HPP

#include <cstddef>
#include <limits>

#define RETURN_IF(condition, value) if(condition) return value;
#define MINMAX(value1, value2) if(value1 > value2) std::swap(value1, value2)

namespace graphcpp
{
	using msize = size_t;
	using mcontent = int; //TODO: Template it

	constexpr static auto msize_undefined = std::numeric_limits<msize>::max();
	constexpr static auto mcontent_undefined = std::numeric_limits<mcontent>::max();
}
#endif
