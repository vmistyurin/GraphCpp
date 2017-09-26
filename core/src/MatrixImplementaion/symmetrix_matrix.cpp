#include "core/symmetric_matrix.h"
#include <assert.h>
#include <limits>

using namespace graphcpp;

SymmetricMatrix::SymmetricMatrix(ushort dimension)
{
	_matrix.resize(dimension);
	for (unsigned short i = 0; i < dimension; i++)
	{
		_matrix[i].resize(i);
	}	
}
SymmetricMatrix::SymmetricMatrix(const std::vector<std::vector<bool>>& matrix) : SymmetricMatrix(matrix.size())
{
	for (ushort i = 0; i < matrix.size(); i++)
	{
		for (ushort j = 0; j < i; j++)
		{
			_matrix[i][j] = matrix[i][j];
		}
	}
}

bool SymmetricMatrix::at(ushort index1, ushort index2)
{
	if (index1 == index2)
	{
		return true;
	}
	return (index1 > index2) ? _matrix[index1][index2] : _matrix[index2][index1];
}

ushort SymmetricMatrix::dimension() const
{
	assert(!_matrix.empty());
	assert(_matrix.size() < std::numeric_limits<unsigned short>::max());
	return _matrix.size();
}


