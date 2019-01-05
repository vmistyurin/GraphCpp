#pragma once

#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

namespace graphcpp
{
	class HalfSymmetricMatrix final: public SymmetricMatrixBase<HalfSymmetricMatrix>
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		HalfSymmetricMatrix() = default;
		explicit HalfSymmetricMatrix(msize dimension);
		explicit HalfSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix);
        
        template<class SymMatrixImpl>
		explicit HalfSymmetricMatrix(const SymmetricMatrixBase<SymMatrixImpl>& matrix);

		HalfSymmetricMatrix& operator+=(const HalfSymmetricMatrix& rhs);

		msize dimension() const;
		mcontent at(msize index1, msize index2) const;
		void set(msize index1, msize index2, mcontent value);
		void reduce_element(msize index1, msize index2, mcontent difference);

		void rearrange_with_allocate(const std::vector<msize>& new_nums);

		void swap(msize str1, msize str2);
		void delete_last_strings(msize count);
	};
    
    
    template <class SymMatrixImpl>
    HalfSymmetricMatrix::HalfSymmetricMatrix(const SymmetricMatrixBase<SymMatrixImpl>& matrix) :
        HalfSymmetricMatrix(matrix.dimension())
    {
        for (auto[i, j] : *this)
        {
            set(i, j, matrix.at(i, j));
        }
    }
}
