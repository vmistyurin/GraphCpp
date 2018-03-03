#ifndef GRAPH_CORE_MACROSES_H
#define GRAPH_CORE_MACROSES_H

#include <cstddef>
#include <type_traits>

#define RETURN_IF(condition, value) if(condition) return value;
#define MINMAX(value1, value2) if(value1 > value2) std::swap(value1, value2)
#define CONTAINS(container, value) (std::find(container.cbegin(), container.cend(), value) != container.cend())

namespace graphcpp
{
	using msize = size_t;
	using mcontent = int; //TODO: Template it
}
#endif
