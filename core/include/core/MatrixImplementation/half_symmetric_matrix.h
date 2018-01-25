#ifndef GRAPH_CORE_HALF_SYMMETRIC_MATRIX_H
#define GRAPH_CORE_HALF_SYMMETRIC_MATRIX_H

#include "core/MatrixImplementation/symmetric_matrix_base.h"

namespace graphcpp
{
	class HalfSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		int a;
	public:
		bool operator==(const SymmetricMatrixBase&) const override
		{
			return false;
		}
		 bool operator!=(const SymmetricMatrixBase&) const override
		{
			return false;
		}

		msize dimension() const override
		{
			return 0;
		}
		mcontent at(msize index1, msize index2) const override
		{
			return 0;
		}
		void set(msize index1, msize index2, mcontent value) override
		{
			
		}
		const std::vector<mcontent>& get_string(msize str) const override
		{
			return std::vector<mcontent>();
		}
		void swap(msize str1, msize str2) override
		{

		}
		void rearrange(const std::vector<msize>& new_nums) override
		{

		}
		void delete_last_strings(msize count) = 0;

		std::vector<std::vector<mcontent>>::const_iterator begin() const override
		{
			return std::vector<std::vector<mcontent>>::const_iterator();
		}
		std::vector<std::vector<mcontent>>::const_iterator end() const override
		{
			return std::vector<std::vector<mcontent>>::const_iterator();
		}
	};
}
#endif