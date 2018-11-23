#include "core/matrix_implementations/non-symmetric_matrixes/non-symmetric_matrix_base.hpp"

#include "core/utils/numeric.hpp"

using namespace graphcpp;

void NonSymmetricMatrixBase::make_rearranged(const std::vector<msize>& new_nums, NonSymmetricMatrixBase& memory) const
{
    assert(new_nums.size() == dimension());
    assert(is_permutation(new_nums));
    assert(memory.dimension() == dimension());
    
    for (auto[i, j] : *this)
    {
        memory.set(new_nums[i], new_nums[j], at(i, j));
    }
}

void NonSymmetricMatrixBase::rearrange_with_permutations(const std::vector<msize>& new_nums)
{
    assert(new_nums.size() == dimension());
    assert(is_permutation(new_nums));
    
    for (auto[i, j] : to_transpositions(new_nums))
    {
        swap(i, j);
    }
}

MatrixIterator NonSymmetricMatrixBase::begin() const
{
	return MatrixIterator(dimension());
}

MatrixIterator NonSymmetricMatrixBase::end() const
{
	return MatrixIterator();
}
