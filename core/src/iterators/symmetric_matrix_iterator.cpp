#include "core/iterators/symmetric_matrix_iterator.hpp"

#include <assert.h>

using namespace graphcpp;

SymmetricMatrixIterator::SymmetricMatrixIterator() : SymmetricMatrixIterator(msize_undefined)
{
}

SymmetricMatrixIterator::SymmetricMatrixIterator(msize dimension) : SymmetricMatrixIterator(0, 1, dimension)
{
}

SymmetricMatrixIterator::SymmetricMatrixIterator(msize i, msize j, msize dimension) :
	_i(i), _j(j), _dimension(dimension)
{
	assert(i < j);
	assert(j < dimension);
	assert(dimension > 1);
}

std::pair<msize, msize> SymmetricMatrixIterator::operator*() const
{
	return std::make_pair(_i, _j);
}

bool SymmetricMatrixIterator::operator==(const SymmetricMatrixIterator& rhs) const
{
	RETURN_IF(_dimension == msize_undefined && rhs._dimension == msize_undefined, true);

	return _dimension == rhs._dimension && _i == rhs._i && _j == rhs._j;
}

bool SymmetricMatrixIterator::operator!=(const SymmetricMatrixIterator& rhs) const
{
	return !(*this == rhs);
}

SymmetricMatrixIterator& SymmetricMatrixIterator::operator++()
{
	assert(_dimension != msize_undefined);
	if (_i == _j - 1)
	{
		if (_j == _dimension - 1)
		{
			_dimension = msize_undefined;
		}
		else
		{
			++_j;
			_i = 0;
		}
	}
	else
	{
		_i++;
	}
	return *this;
}

SymmetricMatrixIterator SymmetricMatrixIterator::operator++(int)
{
	auto tmp = *this;
	++*this;
	return tmp;
}