#pragma once

#include "core/iterators/matrix_iterator.hpp"
#include "core/matrices/matrix_base.hpp"

namespace graphcpp
{ 
	class NonSymmetricMatrixBase : public MatrixBase
	{
	public:
        void make_rearranged(const std::vector<msize>& new_nums, NonSymmetricMatrixBase& memory) const;
        void rearrange_with_permutations(const std::vector<msize>& new_nums);
        
		MatrixIterator begin() const;
		MatrixIterator end() const;
        
		ABSTRACT_CLASS_OPERATIONS(NonSymmetricMatrixBase)
	};
}
