#pragma once

#include "core/utils/numeric.hpp"
#include "core/iterators/matrix_iterator.hpp"
#include "core/matrix_implementations/matrix_base.hpp"

namespace graphcpp
{
    template<class ImplType>
	class NonSymmetricMatrixBase : public MatrixBase<ImplType>
	{
	public:
        void rearrange_with_permutations(const std::vector<msize>& new_nums);
        
        template<class MemoryImplType>
        void make_rearranged(const std::vector<msize>& new_nums, MemoryImplType& memory) const;
        
		MatrixIterator begin() const;
		MatrixIterator end() const;
        
		CRTP_CLASS_OPERATIONS(NonSymmetricMatrixBase);
        
    protected:
        ~NonSymmetricMatrixBase() = default;
    
    private:
        ImplType* self();
        const ImplType* cself() const;
	};
    
    template<class ImplType>
    void NonSymmetricMatrixBase<ImplType>::rearrange_with_permutations(const std::vector<msize>& new_nums)
    {
        assert(new_nums.size() == self()->dimension());
        assert(is_permutation(new_nums));
        
        for (auto[i, j] : to_transpositions(new_nums))
        {
            self()->swap(i, j);
        }
    }
    
    template<class ImplType>
    template<class MemoryImplType>
    void NonSymmetricMatrixBase<ImplType>::make_rearranged(const std::vector<msize>& new_nums, MemoryImplType& memory) const
    {
        assert(new_nums.size() == cself()->dimension());
        assert(is_permutation(new_nums));
        assert(memory.dimension() == cself()->dimension());
        
        for (auto[i, j] : *this)
        {
            memory.set(new_nums[i], new_nums[j], cself()->at(i, j));
        }
    }
    
    template<class ImplType>
    MatrixIterator NonSymmetricMatrixBase<ImplType>::begin() const
    {
        return MatrixIterator(cself()->dimension());
    }
    
    template<class ImplType>
    MatrixIterator NonSymmetricMatrixBase<ImplType>::end() const
    {
        return MatrixIterator();
    }

    template<class ImplType>
    ImplType* NonSymmetricMatrixBase<ImplType>::self()
    {
        return static_cast<ImplType*>(this);
    }
    
    template<class ImplType>
    const ImplType* NonSymmetricMatrixBase<ImplType>::cself() const
    {
        return static_cast<const ImplType*>(this);
    }
}
