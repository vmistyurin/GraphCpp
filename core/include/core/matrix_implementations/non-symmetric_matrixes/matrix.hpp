#pragma once

#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"

namespace graphcpp
{
	class Matrix final: public NonSymmetricMatrixBase<Matrix>
	{
	private:
		std::vector<std::vector<mcontent>> _matrix;

	public:
		explicit Matrix(msize dimension);
	 	explicit Matrix(std::vector<std::vector<mcontent>> matrix);
        
        template<class MatrixImpl>
		explicit Matrix(const MatrixBase<MatrixImpl>& rhs);

		msize dimension() const;
		mcontent at(msize index1, msize index2) const;
		void set(msize index1, msize index2, mcontent value);
		void reduce_element(msize index1, msize index2, mcontent difference);

		void rearrange_with_allocate(const std::vector<msize>& new_nums);

		void swap(msize str1, msize str2);
		void delete_last_strings(msize count);
	};
    
    template<class MatrixImpl>
    Matrix::Matrix(const MatrixBase<MatrixImpl>& rhs) :
        Matrix(rhs.dimension())
    {
        for (auto[i, j] : *this)
        {
            _matrix[i][j] = rhs.at(i, j);
        }
    }
}
