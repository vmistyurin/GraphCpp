#pragma once

#include "core/matrices/symmetric_matrices/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class HalfSymmetricMatrix final: public SymmetricMatrixBase
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		HalfSymmetricMatrix() = default;
		explicit HalfSymmetricMatrix(msize dimension);
		explicit HalfSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
		explicit HalfSymmetricMatrix(const SymmetricMatrixBase& matrix);
        
        HalfSymmetricMatrix& operator+(const HalfSymmetricMatrix& rhs);
        HalfSymmetricMatrix& operator*(double rhs);

		msize dimension() const override;
		mcontent at(msize index1, msize index2) const override;
		void set(msize index1, msize index2, mcontent value) override;
		void reduce_element(msize index1, msize index2, mcontent difference) override;
		void add_string() override;

		void rearrange_with_allocate(const std::vector<msize>& new_nums) override;

		void swap(msize str1, msize str2) override;
		void delete_last_strings(msize count) override;

		HalfSymmetricMatrix extract_matrix(const std::vector<msize>& rows) const;
	};
}
