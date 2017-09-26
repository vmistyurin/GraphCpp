#ifndef GRAPH_CORE_MATRIX_BASE
#define GRAPH_CORE_MATRIX_BASE

#include "core/macroses.h"
#include <vector>

namespace graphcpp
{
	class MatrixBase
	{
	public:
		virtual bool operator==(const MatrixBase&) const = 0;
		virtual bool operator!=(const MatrixBase&) const = 0;

		virtual void swap(ushort str1, ushort str2) = 0;
		virtual const std::vector<bool>& get_string(ushort str) const = 0;
		virtual bool at(ushort index1, ushort index2) const = 0; 
		virtual ushort dimension() const = 0;
	};
}
#endif