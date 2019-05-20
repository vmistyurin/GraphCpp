#pragma once

#include "core/matrices/symmetric_matrices/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class FullSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		FullSymmetricMatrix() = default;
		explicit FullSymmetricMatrix(msize dimension);
		explicit FullSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
		explicit FullSymmetricMatrix(const SymmetricMatrixBase& matrix);
		
        FullSymmetricMatrix& operator+(const FullSymmetricMatrix& rhs);
        FullSymmetricMatrix& operator*(double rhs);

		msize dimension() const override;
		mcontent at(msize index1, msize index2) const override;
		void set(msize index1, msize index2, mcontent value) override;
		void reduce_element(msize index1, msize index2, mcontent difference) override;
		void add_string() override;

		void rearrange_with_allocate(const std::vector<msize>& new_nums) override;

		void swap(msize str1, msize str2) override;
		void delete_last_strings(msize count) override;

		FullSymmetricMatrix extract_matrix(const std::vector<msize>& rows) const;
	};
}
