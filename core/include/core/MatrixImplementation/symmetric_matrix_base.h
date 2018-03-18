#ifndef GRAPH_CORE_MATRIX_BASE_H
#define GRAPH_CORE_MATRIX_BASE_H

#include "core/macroses.h"
#include <vector>
#include <ostream>

namespace graphcpp
{
	class SymmetricMatrixBase
	{
	public:
		virtual ~SymmetricMatrixBase() = default;
		virtual bool operator==(const SymmetricMatrixBase&) const = 0;
		virtual bool operator!=(const SymmetricMatrixBase&) const = 0;

		virtual msize dimension() const = 0;
		virtual mcontent at(msize index1, msize index2) const = 0;
		virtual void set(msize index1, msize index2, mcontent value) = 0;
		virtual void reduce_element(msize index1, msize index2, mcontent difference) = 0;
		virtual std::vector<mcontent> get_string(msize str) const = 0;
		virtual void swap(msize str1, msize str2) = 0;
		virtual void rearrange(const std::vector<msize>& new_nums) = 0;
		virtual void delete_last_strings(msize count) = 0;

		std::string to_string() const;
	}; 

	std::ostream& operator<< (std::ostream& stream, const SymmetricMatrixBase& matrix);
}
#endif