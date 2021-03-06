#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "core/macroses.hpp"

namespace graphcpp 
{
	class MatrixBase
	{
	public:
		bool operator==(const MatrixBase& rhs) const;
		bool operator!=(const MatrixBase& rhs) const;

		virtual msize dimension() const = 0;
		virtual mcontent at(msize index1, msize index2) const = 0;
		virtual void set(msize index1, msize index2, mcontent value) = 0;
		virtual void reduce_element(msize index1, msize index2, mcontent difference) = 0;
		virtual void add_string() = 0;

		virtual void rearrange_with_permutations(const std::vector<msize>& new_nums) = 0;
		virtual void rearrange_with_allocate(const std::vector<msize>& new_nums) = 0;
		void make_rearranged(const std::vector<msize>& new_nums, MatrixBase& memory) const;

		virtual void swap(msize str1, msize str2) = 0;
		virtual void delete_last_strings(msize count) = 0;
		void delete_strings(const std::vector<msize>& strings);

        mcontent average() const;
		std::string to_string() const;

		ABSTRACT_CLASS_OPERATIONS(MatrixBase)
	}; 

    std::ostream& operator<<(std::ostream& stream, const MatrixBase& matrix);
    
}
