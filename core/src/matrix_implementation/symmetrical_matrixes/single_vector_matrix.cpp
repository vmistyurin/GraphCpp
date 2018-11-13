#include "core/matrix_implementations/symmetric_matrixes/single_vector_matrix.hpp"

#include <cassert>

#include "gsl/span"

#include "core/utils.hpp"

using namespace graphcpp;

SingleVectorMatrix::SingleVectorMatrix(msize dimension) :
    _dimension(dimension), _matrix(dimension * dimension)
{
    assert(dimension != 0);
}

SingleVectorMatrix::SingleVectorMatrix(const std::vector<std::vector<mcontent>>& matrix) :
    SingleVectorMatrix(matrix.size())
{
    assert(check_symmetrical_matrix(matrix));
    
    for (auto[i, j] : *this)
    {
        set(i, j, matrix[i][j]);
    }
}

msize SingleVectorMatrix::dimension() const
{
    return _dimension;
}

mcontent SingleVectorMatrix::at(msize index1, msize index2) const
{
    assert(std::max(index1, index2) < dimension());
    
    return _matrix[index1 * dimension() + index2];
}

void SingleVectorMatrix::set(msize index1, msize index2, mcontent value)
{
    assert(std::max(index1, index2) < dimension());
    
    _matrix[index1 * dimension() + index2] = value;
    _matrix[index2 * dimension() + index1] = value;
}

void SingleVectorMatrix::reduce_element(msize index1, msize index2, mcontent difference)
{
    assert(std::max(index1, index2) < dimension());
    
    _matrix[index1 * dimension() + index2] =  _matrix[index1 * dimension() + index2] - difference;
}

void SingleVectorMatrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
    assert(new_nums.size() == dimension());
    
    SingleVectorMatrix new_matrix(_dimension);
    
    for (auto[i,j] : *this)
    {
        new_matrix.set(i, j, at(new_nums[i], new_nums[j]));
    }
    
    _matrix = std::move(new_matrix._matrix);
}

void SingleVectorMatrix::swap(msize str1, msize str2)
{
    assert(str1 != str2);
    assert(std::max(str1, str2) < dimension());
    
    const mcontent previous_value = at(str1, str2);

    std::swap(_matrix[str1], _matrix[str2]);

    for (msize i = 0; i < dimension(); i++)
    {
        auto prev = at(i, str1);
        set(i, str1, at(i, str2));
        set(i, str2, prev);
        
        prev = at(str1, i);
        set(str1, i, at(i, str2));
        set(str2, i, prev);
    }

    set(str1, str2, previous_value);
    set(str2, str1, previous_value);
}

void SingleVectorMatrix::delete_last_strings(msize count)
{
    assert(count < dimension());
    
    _dimension -= count;
}

std::unique_ptr<SymmetricMatrixBase> SingleVectorMatrix::with_deleted_vertexes(const std::vector<msize>& vertexes) const
{
    assert(!vertexes.empty());
    assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) { return vertex < dimension(); }));
    
    auto result = std::make_unique<SingleVectorMatrix>(dimension() - vertexes.size());
    
    auto new_nums = std::vector<msize>(); new_nums.reserve(dimension() - vertexes.size());
    msize position_in_deleted = 0;
    for (msize i = 0; i < dimension(); i++)
    {
        if (vertexes[position_in_deleted] == i)
        {
            position_in_deleted++;
            continue;
        }
        new_nums.push_back(i);
    }
    
    for (msize i = 0; i < new_nums.size(); i++)
    {
        for (msize j = i + 1; j < new_nums.size(); j++)
        {
            result->set(i, j, at(new_nums[i], new_nums[j]));
        }
    }
    
    return result;
}

std::unique_ptr<SymmetricMatrixBase> SingleVectorMatrix::with_deleted_element(msize i, msize j) const
{
    assert(std::max(i, j) < dimension());
    
    auto result = std::make_unique<SingleVectorMatrix>(*this);
    result->set(i, j, 0);
    return result;
}
