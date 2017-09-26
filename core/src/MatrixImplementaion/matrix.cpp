#include "core/matrix.h"
#include <limits>
#include <assert.h>
using namespace graphcpp;

Matrix::Matrix(ushort dimension)
{
	_matrix.resize(dimension);
	for(auto& str : _matrix)
	{
		str.resize(dimension);
	}
}
Matrix::Matrix(const std::vector<std::vector<bool>>& matrix) : Matrix(matrix.size())
{
	assert(matrix.size() < std::numeric_limits<ushort>::max());
	for(ushort i = 0; i < matrix.size(); i++)
	{
		for(ushort j = 0; j < matrix.size(); j++)
		{
			_matrix[i][j] = matrix[i][j];
		}
	}
}

bool Matrix::operator==(const MatrixBase& right) const
{
	if (this == &right)
	{
		return true;
	}
	if (right.dimension() != right.dimension())
	{
		return false;
	}
	for (ushort i = 0; i < dimension(); i++)
	{
		if (get_string(i) != right.get_string(i))
		{
			return false;
		}
	}
	return true;
}

bool Matrix::operator!=(const MatrixBase& right) const
{
	return !(*this == right);
}
void Matrix::swap(ushort str1, ushort str2)
{
	const bool were_connected = _matrix[str1][str2];

	std::swap(_matrix[str1], _matrix[str2]);

	for(ushort i = 0; i < dimension(); i++)
	{
		std::swap(_matrix[i][str1], _matrix[i][str2]);
	}

	_matrix[str1][str1] = true;
	_matrix[str2][str2] = true;

	_matrix[str1][str2] = were_connected;
	_matrix[str2][str1] = were_connected;
}

const std::vector<bool>& Matrix::get_string(ushort str) const
{
	return _matrix[str];
}
bool Matrix::at(ushort string, ushort column) const
{
	return _matrix[string][column];
}


ushort Matrix::dimension() const
{
	return _matrix.size();
}