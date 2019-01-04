#pragma once

#include <memory>

#include "core/macroses.hpp"
#include "core/utils/numeric.hpp"
#include "core/matrix_implementations/matrix_base.hpp"
#include "core/iterators/symmetric_matrix_iterator.hpp"

namespace graphcpp
{
    template<class ImplType>
	class SymmetricMatrixBase : public MatrixBase<ImplType>
	{
	public:
        template<class RhsImplType>
		bool operator==(const RhsImplType& rhs) const;
        
        template<class RhsImplType>
        bool operator!=(const RhsImplType& rhs) const;

        template<class RhsImplType>
		void make_rearranged(const std::vector<msize>& new_nums, RhsImplType& memory) const;
        
        void rearrange_with_permutations(const std::vector<msize>& new_nums);

		SymmetricMatrixIterator begin() const;
		SymmetricMatrixIterator end() const;

        CRTP_CLASS_OPERATIONS(SymmetricMatrixBase)
        
    protected:
        ~SymmetricMatrixBase() = default;
        
    private:
        ImplType* self();
        const ImplType* cself() const;
	};
    
    template<class ImplType>
    template<class RhsImplType>
    bool SymmetricMatrixBase<ImplType>::operator==(const RhsImplType& rhs) const
    {
		if constexpr (std::is_same_v<ImplType, RhsImplType>) 
		{
			RETURN_IF(this == &rhs, true);
		}

        RETURN_IF(rhs.dimension() != cself()->dimension(), false);
        
        for (auto[i, j] : *this)
        {
            RETURN_IF(cself()->at(i, j) != rhs.at(i, j), false);
        }
        return true;
    }
    
    template<class ImplType>
    template<class RhsImplType>
    bool SymmetricMatrixBase<ImplType>::operator!=(const RhsImplType& rhs) const
    {
        return !(*this == rhs);
    }
    
    template<class ImplType>
    template<class RhsImplType>
    void SymmetricMatrixBase<ImplType>::make_rearranged(const std::vector<msize>& new_nums, RhsImplType& memory) const
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
    void SymmetricMatrixBase<ImplType>::rearrange_with_permutations(const std::vector<msize>& new_nums)
    {
        assert(new_nums.size() == self()->dimension());
        assert(is_permutation(new_nums));
        
        auto transpositions = to_transpositions(new_nums);
        for (auto[str1, str2] : transpositions)
        {
            self()->swap(str1, str2);
        }
    }
    
    template<class ImplType>
    SymmetricMatrixIterator SymmetricMatrixBase<ImplType>::begin() const
    {
        return SymmetricMatrixIterator(cself()->dimension());
    }
    
    template<class ImplType>
    SymmetricMatrixIterator SymmetricMatrixBase<ImplType>::end() const
    {
        return SymmetricMatrixIterator();
    }
    
    template<class ImplType>
    ImplType* SymmetricMatrixBase<ImplType>::self()
    {
        return static_cast<ImplType*>(this);
    }
    
    template<class ImplType>
    const ImplType* SymmetricMatrixBase<ImplType>::cself() const
    {
        return static_cast<const ImplType*>(this);
    }
}
