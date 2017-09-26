#ifndef GRAPH_CORE_MACROSES
#define GRAPH_CORE_MACROSES

#define THROW_IF(condition, exception) if(condition) throw exception;

using ushort = unsigned short;

#ifdef _M_AMD64
using word = unsigned long long;
#else
using word = unsigned int;
#endif  

#endif