#ifndef GRAPH_CORE_SYMMETRIC_MATRIX
#define GRAPH_CORE_SYMMETRIC_MATRIX 

#include "macroses.h"
#include <vector>

namespace graphcpp
{
	class SymmetricMatrix 
	{
	private:
		std::vector<std::vector<bool>> _matrix;
	public:
		explicit SymmetricMatrix(ushort dimension);
		explicit SymmetricMatrix(const std::vector<std::vector<bool>>& matrix);

		void swap(ushort str1, ushort str2);
		bool at(ushort index1, ushort index2);
		ushort dimension() const;
	};
}
#endif