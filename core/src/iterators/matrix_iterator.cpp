#include "core/iterators/matrix_iterator.hpp"

#include <cassert>
#include <algorithm>

using namespace graphcpp;

MatrixIterator::MatrixIterator() 
	: MatrixIterator(msize_undefined)
{
}

MatrixIterator::MatrixIterator(msize dimension) 
	: MatrixIterator(0, 0, dimension)
{
}

MatrixIterator::MatrixIterator(msize i, msize j, msize dimension) 
	: _i(i), _j(j), _dimension(dimension)
{
	assert(std::max(i, j) < dimension);
	assert(dimension > 1);
}

std::pair<msize, msize> MatrixIterator::operator*() const
{
	return std::make_pair(_i, _j);
}

bool MatrixIterator::operator==(const MatrixIterator& rhs) const
{
	RETURN_IF(_dimension == msize_undefined && rhs._dimension == msize_undefined, true);

	return _dimension == rhs._dimension && _i == rhs._i && _j == rhs._j;
}

bool MatrixIterator::operator!=(const MatrixIterator& rhs) const
{
	return !(*this == rhs);
}

MatrixIterator& MatrixIterator::operator++()
{
	assert(_dimension != msize_undefined);
	if (_i == _dimension - 1)
	{
		if (_j == _dimension - 1)
		{
			_dimension = msize_undefined;
		}
		else
		{
			_i = 0;
			_j++;
		}
	}
	else
	{
		_i++;
	}
	return *this;
}

MatrixIterator MatrixIterator::operator++(int)
{
	auto tmp = *this;
	++*this;
	return tmp;
}