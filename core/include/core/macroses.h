#ifndef GRAPH_CORE_MACROSES_H
#define GRAPH_CORE_MACROSES_H

#include <cstddef>

#define RETURN_IF(condition, value) if(condition) return value;
#define MINMAX(value1, value2) if(value1 > value2) std::swap(value1,value2)
using msize = size_t;
using mcontent = unsigned int; //TODO: Template it

#endif
