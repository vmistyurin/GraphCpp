#include "core/matrix_implementations/non-symmetric_matrixes/single_vector_matrix.hpp"

#include "core/utils/numeric.hpp"

using namespace graphcpp;

SingleVectorMatrix::SingleVectorMatrix(msize dimension) :
    _dimension(dimension), _internal_dimension(dimension), _matrix(dimension * dimension)
{
    assert(dimension != 0);
}

SingleVectorMatrix::SingleVectorMatrix(const std::vector<std::vector<mcontent>>& matrix) :
    SingleVectorMatrix(matrix.size())
{
    for(auto[i, j] : *this)
    {
        set(i, j, matrix[i][j]);
    }
}



SingleVectorMatrix::SingleVectorMatrix(const SingleVectorMatrix& rhs) :
    _dimension(rhs.dimension()), _internal_dimension(rhs.dimension()), _matrix(_dimension * _dimension)
{
    for (auto[i, j] : *this)
    {
        set(i, j, rhs.at(i, j));
    }
}

SingleVectorMatrix& SingleVectorMatrix::operator=(const SingleVectorMatrix& rhs)
{
    _dimension = rhs.dimension();
    _internal_dimension = rhs.dimension();
    _matrix = std::vector<mcontent>(); _matrix.resize(_dimension * _dimension);
    
    for(auto[i, j] : *this)
    {
        set(i, j, rhs.at(i, j));
    }
    
    return *this;
}

msize SingleVectorMatrix::dimension() const
{
    return _dimension;
}

mcontent SingleVectorMatrix::at(msize index1, msize index2) const
{
    assert(std::max(index1, index2) < dimension());
    
    return _matrix[index1 * _internal_dimension + index2];
}

void SingleVectorMatrix::set(msize index1, msize index2, mcontent value)
{
    _matrix[index1 * _internal_dimension + index2] = value;
}

void SingleVectorMatrix::reduce_element(msize index1, msize index2, mcontent difference)
{
    _matrix[index1 * _internal_dimension + index2] = _matrix[index1 * _internal_dimension + index2] - difference;
}


void SingleVectorMatrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
    SingleVectorMatrix result(dimension());
    
    for (auto[i, j] : *this)
    {
        result.set(new_nums[i], new_nums[j], at(i, j));
    }
    
    _matrix = std::move(result._matrix);
}

void SingleVectorMatrix::swap(msize str1, msize str2)
{
    assert(str1 != str2);
    assert(std::max(str1, str2) < dimension());
    
    const mcontent first_previous_value = at(str1, str2);
    const mcontent second_previous_value = at(str2, str1);
    
    for (msize i = 0; i < dimension(); i++)
    {
        auto prev = at(i, str1);
        set(i, str1, at(i, str2));
        set(i, str2, prev);
        
        prev = at(str1, i);
        set(str1, i, at(str2, i));
        set(str2, i, prev);
    }
    
    set(str1, str2, second_previous_value);
    set(str2, str1, first_previous_value);
    
    set(str1, str1, 0);
    set(str2, str2, 0);
}

void SingleVectorMatrix::delete_last_strings(msize count)
{
    assert(count < dimension());
    
    _dimension -= count;
    
    for (msize i = 0; i < _dimension; i++)
    {
        set(i, i, 0);
    }
}
