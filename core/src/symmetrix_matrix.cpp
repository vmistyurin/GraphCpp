#include "core/symmetric_matrix.h"
#include <assert.h>

using namespace graphcpp;

SymmetricMatrix::SymmetricMatrix(unsigned int dimension)
{
	_matrix.resize(dimension);
	for (unsigned int i = 0; i < dimension; i++)
	{
		_matrix[i].resize(i);
	}
}

bool SymmetricMatrix::at(unsigned int index1, unsigned int index2)
{
	if (index1 == index2)
	{
		return true;
	}
	return (index1 > index2) ? _matrix[index1][index2] : _matrix[index2][index1];
}

unsigned int SymmetricMatrix::dimension() const
{
	assert(!_matrix.empty());
	return _matrix.size();
}