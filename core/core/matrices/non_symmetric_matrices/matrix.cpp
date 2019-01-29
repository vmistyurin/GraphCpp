#include "core/matrices/non_symmetric_matrices/matrix.hpp"

#include <cassert>
#include <algorithm>

#include "core/utils/numeric.hpp"

using namespace graphcpp;

Matrix::Matrix(msize dimension) :
	_matrix(dimension)
{
	for (auto& str : _matrix)
	{
		str.resize(dimension);
	}
}

Matrix::Matrix(std::vector<std::vector<mcontent>> matrix) :
	_matrix(std::move(matrix))
{
}

Matrix::Matrix(const MatrixBase& rhs) :
	Matrix(rhs.dimension())
{
	for (const auto&[i, j] : *this)
	{
		_matrix[i][j] = rhs.at(i, j);	
	}
}

msize Matrix::dimension() const
{
	return _matrix.size();
}

mcontent Matrix::at(msize index1, msize index2) const
{
	assert(std::max(index1, index2) < dimension());

	return _matrix[index1][index2];
}

void Matrix::set(msize index1, msize index2, mcontent value)
{
	assert(std::max(index1, index2) < dimension());

	_matrix[index1][index2] = value;
}

void Matrix::reduce_element(msize index1, msize index2, mcontent difference)
{
	assert(std::max(index1, index2) < dimension());

	_matrix[index1][index2] -= difference;
}

void Matrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
	Matrix result(dimension());
	
	for (auto[i, j] : *this)
	{
		result.set(new_nums[i], new_nums[j], at(i, j));
	}

	_matrix = std::move(result._matrix);
}

void Matrix::swap(msize str1, msize str2)
{
	assert(std::max(str1, str2) < dimension());
	assert(str1 != str2);

	std::swap(_matrix[str1], _matrix[str2]);

	for (msize i = 0; i < dimension(); i++)
	{
		std::swap(_matrix[i][str1], _matrix[i][str2]);
	}
}

void Matrix::delete_last_strings(msize count)
{
	assert(count < dimension());

	for (msize i = 0; i < count; i++)
	{
		_matrix.pop_back();
	}

	for (msize i = 0; i < _matrix.size(); i++)
	{
		for (msize j = 0; j < count; j++)
		{
			_matrix[i].pop_back();
		}
	}
}
