#pragma once

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

		void make_rearranged(const std::vector<msize>& new_nums, SymmetricMatrixBase& memory) const;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		virtual ~SymmetricMatrixBase() = default;
		SymmetricMatrixBase() = default;
		SymmetricMatrixBase(const SymmetricMatrixBase&) = default;
		SymmetricMatrixBase& operator=(const SymmetricMatrixBase&) = default;
		SymmetricMatrixBase(SymmetricMatrixBase&&) = default;
		SymmetricMatrixBase& operator=(SymmetricMatrixBase&&) = default;
	}; 
}