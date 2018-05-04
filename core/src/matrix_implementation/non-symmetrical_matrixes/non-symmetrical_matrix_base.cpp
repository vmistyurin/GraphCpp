#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"

using namespace graphcpp;

MatrixIterator NonSymmetricMatrixBase::begin() const
{
	return MatrixIterator(dimension());
}

MatrixIterator NonSymmetricMatrixBase::end() const
{
	return MatrixIterator();
}