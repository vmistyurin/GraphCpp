#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <set>

#include "core/macroses.hpp"
#include "core/utils/numeric.hpp"

namespace graphcpp 
{
    template<class ImplType>
	class MatrixBase
	{
	public:
        template<class RhsImplType>
        bool operator==(const MatrixBase<RhsImplType>& rhs) const;
        template<class RhsImplType>
		bool operator!=(const MatrixBase<RhsImplType>& rhs) const;

        template<class RhsImplType>
		void make_rearranged(const std::vector<msize>& new_nums, MatrixBase<RhsImplType>& memory) const;

		void delete_strings(const std::vector<msize>& strings);

		std::string to_string() const;
        
        CRTP_CLASS_OPERATIONS(MatrixBase);
        
    protected:
        ~MatrixBase() = default;
        
    private:
        ImplType* self();
        const ImplType* cself() const;
	};
    
    template<class ImplType>
    template<class RhsImplType>
    bool MatrixBase<ImplType>::operator==(const MatrixBase<RhsImplType>& rhs) const
    {
        RETURN_IF(self()->dimension() != rhs.dimension(), false);
        
        for (msize i = 0; i < cself()->dimension(); i++)
        {
            for (msize j = 0; j < cself()->dimension(); j++)
            {
                RETURN_IF(cself()->at(i, j) != rhs.at(i, j), false);
            }
        }
        return true;
    }
    
    template<class ImplType>
    template<class RhsImplType>
    bool MatrixBase<ImplType>::operator!=(const MatrixBase<RhsImplType>& rhs) const
    {
        return !(*this == rhs);
    }
    
    template<class ImplType>
    template<class RhsImplType>
    void MatrixBase<ImplType>::make_rearranged(const std::vector<msize>& new_nums, MatrixBase<RhsImplType>& memory) const
    {
        assert(new_nums.size() == cself()->dimension());
        assert(is_permutation(new_nums));
        assert(memory.dimension() == cself()->dimension());
        
        for(msize i = 0; i < cself()->dimension(); i++)
        {
            for (msize j = 0; j < cself()->dimension(); j++)
            {
                memory.set(new_nums[i], new_nums[j], cself()->at(i, j));
            }
        }
    }
    
    template<class ImplType>
    void MatrixBase<ImplType>::delete_strings(const std::vector<msize>& strings)
    {
        std::set<msize, std::greater<msize>> to_delete(strings.cbegin(), strings.cend());
        
        auto current_position = self()->dimension() - 1;
        
        for (auto it = to_delete.cbegin(); it != to_delete.cend(); ++it)
        {
            while (to_delete.count(current_position) == 1)
            {
                ++it;
                current_position--;
            }
            
            for (auto i = *it; i < current_position; i++)
            {
                self()->swap(i, i + 1);
            }
            
            current_position--;
        }
        self()->delete_last_strings(strings.size());
    }
    
    template<class ImplType>
    std::string MatrixBase<ImplType>::to_string() const
    {
        unsigned int max_len = 0;
        for (msize i = 0; i < cself()->dimension(); i++)
        {
            for (msize j = 0; j < cself()->dimension(); j++)
            {
                max_len = std::max(max_len, static_cast<unsigned int>(get_len(self()->at(i, j))));
            }
        }
        
        std::string result;
        for (msize i = 0; i < cself()->dimension(); i++)
        {
            std::string current_string;
            for (msize j = 0; j < cself()->dimension(); j++)
            {
                current_string += get_aligned_string(self()->at(i, j), max_len);
                current_string += ",";
            }
            current_string.pop_back();
            
            result += current_string;
            result += '\n';
        }
        
        return result;
    }
    
    template<class ImplType>
    ImplType* MatrixBase<ImplType>::self()
    {
        return static_cast<ImplType*>(this);
    }
    
    template<class ImplType>
    const ImplType* MatrixBase<ImplType>::cself() const
    {
        return static_cast<ImplType*>(this);
    }

    template<class ImplType>
    std::ostream& operator<<(std::ostream& stream, const MatrixBase<ImplType>& matrix)
    {
        return stream << matrix.to_string();
    }
}
