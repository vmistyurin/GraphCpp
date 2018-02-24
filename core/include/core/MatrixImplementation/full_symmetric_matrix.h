#ifndef GRAPH_CORE_FULL_SYMMETRIC_MATRIX_H
#define GRAPH_CORE_FULL_SYMMETRIC_MATRIX_H

#include "symmetric_matrix_base.h"

namespace graphcpp
{
	class FullSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit FullSymmetricMatrix(msize dimension);
		explicit FullSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
		explicit FullSymmetricMatrix(const SymmetricMatrixBase& matrix);
		
		bool operator==(const SymmetricMatrixBase& rhs) const override;
		bool operator!=(const SymmetricMatrixBase& rhs) const override;

		msize dimension() const override;
		mcontent at(msize index1, msize index2) const override;
		void set(msize index1, msize index2, mcontent value) override;
		std::vector<mcontent> get_string(msize str) const override;
		void swap(msize str1, msize str2) override;
		void rearrange(const std::vector<msize>& new_nums) override;
		void delete_last_strings(msize count) override;
		
		std::vector<std::vector<mcontent>>::const_iterator begin() const override;
		std::vector<std::vector<mcontent>>::const_iterator end() const override;
	private:
		void fill_diagonal(mcontent value = 0);
	};
}
#endif
