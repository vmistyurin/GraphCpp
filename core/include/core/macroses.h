#ifndef GRAPH_CORE_MACROSES
#define GRAPH_CORE_MACROSES

#define RETURN_IF(condition, value) if(condition) return value;
using ushort = unsigned short;
using msize = ushort;
using mcontent = unsigned int; //TODO: Template it

#ifdef _M_AMD64
using word = unsigned long long;
#else
using word = unsigned int;
#endif  

#endif