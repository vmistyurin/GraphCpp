#pragma once

#include <memory>
#include <cassert>
#include <algorithm>

#include "core/matrices/matrix_base.hpp"
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

		template<class MatrixType>
		MatrixType with_deleted_vertexes(const std::vector<msize>& vertexes) const;

		template<class MatrixType>
		MatrixType with_deleted_element(msize i, msize j) const;

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

		ABSTRACT_CLASS_OPERATIONS(SymmetricMatrixBase)
	};

	template<class MatrixType>
	MatrixType SymmetricMatrixBase::with_deleted_vertexes(const std::vector<msize>& vertexes) const
	{
		assert(!vertexes.empty());
		assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) { return vertex < dimension(); }));

		auto result = MatrixType(dimension() - vertexes.size());

		auto new_nums = std::vector<msize>(); new_nums.reserve(dimension() - vertexes.size());
		msize position_in_deleted = 0;
		for (msize i = 0; i < dimension(); i++)
		{
			if (vertexes[position_in_deleted] == i)
			{
				position_in_deleted++;
				continue;
			}
			new_nums.push_back(i);
		}

		for (msize i = 0; i < new_nums.size(); i++)
		{
			for (msize j = i + 1; j < new_nums.size(); j++)
			{
				result.set(i, j, at(new_nums[i], new_nums[j]));
			}
		}

		return result;	
	}

	template<class MatrixType>
	MatrixType SymmetricMatrixBase::with_deleted_element(msize i, msize j) const
	{
		assert(std::max(i, j) < dimension());

		auto result = MatrixType(*this);
		result.set(i, j, 0);
		return result;
	}
}
