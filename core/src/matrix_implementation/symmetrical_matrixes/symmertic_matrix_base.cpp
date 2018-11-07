#include "core/matrix_implementations/symmetric_matrixes/symmetric_matrix_base.hpp"

#include <cassert>
#include <string>
#include <algorithm>

#include "core/utils.hpp"

using namespace graphcpp;

bool SymmetricMatrixBase::operator==(const SymmetricMatrixBase& rhs) const
{
	RETURN_IF(this == &rhs, true);
	RETURN_IF(rhs.dimension() != dimension(), false);

	for (auto[i, j] : *this)
	{
		RETURN_IF(at(i, j) != rhs.at(i, j), false);
	}
	return true;
}

bool SymmetricMatrixBase::operator!=(const SymmetricMatrixBase& rhs) const
{
	return !(*this == rhs);
}

SymmetricMatrixBase& SymmetricMatrixBase::operator+=(const SymmetricMatrixBase& rhs)
{
    assert(dimension() == rhs.dimension());
    
    for (const auto[i, j] : *this)
    {
        set(i, j, at(i, j) + rhs.at(i, j));
    }
    
    return *this;
}

SymmetricMatrixBase& SymmetricMatrixBase::operator*=(double rhs)
{
    for (const auto[i, j] : *this)
    {
        set(i, j, rhs * at(i, j));
    }
    
    return *this;
}

void SymmetricMatrixBase::make_rearranged(const std::vector<msize>& new_nums, SymmetricMatrixBase& memory) const
{
	assert(new_nums.size() == dimension());
	assert(is_permutation(new_nums));
	assert(memory.dimension() == dimension());

	for (auto[i, j] : *this)
	{
		memory.set(new_nums[i], new_nums[j], at(i, j));
	}
}

SymmetricMatrixIterator SymmetricMatrixBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator SymmetricMatrixBase::end() const
{
	return SymmetricMatrixIterator();
}
