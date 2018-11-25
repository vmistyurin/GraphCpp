#pragma once

#include <memory>

#include "core/macroses.hpp"
#include "core/matrix_implementations/matrix_base.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

namespace graphcpp
{
	class SymmetricMatrixBase : public MatrixBase
	{
	public:
		bool operator==(const SymmetricMatrixBase& rhs) const;
		bool operator!=(const SymmetricMatrixBase& rhs) const;
        SymmetricMatrixBase& operator+=(const SymmetricMatrixBase& rhs);
        SymmetricMatrixBase& operator*=(double rhs);

		void make_rearranged(const std::vector<msize>& new_nums, SymmetricMatrixBase& memory) const;
        void rearrange_with_permutations(const std::vector<msize>& new_nums) override;

		virtual std::unique_ptr<SymmetricMatrixBase> with_deleted_vertexes(const std::vector<msize>& vertexes) const = 0;
		virtual std::unique_ptr<SymmetricMatrixBase> with_deleted_element(msize i, msize j) const = 0;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(SymmetricMatrixBase);
	}; 
}
