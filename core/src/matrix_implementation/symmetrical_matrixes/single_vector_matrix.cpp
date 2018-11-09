#include "core/matrix_implementations/symmetric_matrixes/single_vector_matrix.hpp"

using namespace graphcpp;

SingleVectorMatrix::SingleVectorMatrix(msize dimension) :
    _matrix(dimension * dimension), _dimension(dimension)
{
    assert(dimension != 0);
}

msize SingleVectorMatrix::dimension() const
{
    return _dimension;
}

mcontent SingleVectorMatrix::at(msize index1, msize index2) const
{
    return _matrix[index1 * dimension() + index2];
}

void SingleVectorMatrix::set(msize index1, msize index2, mcontent value)
{
    _matrix[index1 * dimension() + index2] = value;
}

void SingleVectorMatrix::reduce_element(msize index1, msize index2, mcontent difference)
{
    _matrix[index1 * dimension() + index2] =  _matrix[index1 * dimension() + index2] - difference;
}

void SingleVectorMatrix::rearrange_with_permutations(const std::vector<msize>& new_nums)
{
    
}

void SingleVectorMatrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
    
}

void SingleVectorMatrix::swap(msize str1, msize str2)
{
    
}

void SingleVectorMatrix::delete_last_strings(msize count)
{
    
}

std::unique_ptr<SymmetricMatrixBase> SingleVectorMatrix::with_deleted_vertexes(const std::vector<msize>& vertexes) const
{
    
}

std::unique_ptr<SymmetricMatrixBase> SingleVectorMatrix::with_deleted_element(msize i, msize j) const
{
    
}
