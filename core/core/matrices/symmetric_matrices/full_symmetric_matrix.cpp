#include "core/matrices/symmetric_matrices/full_symmetric_matrix.hpp"

#include <cassert>
#include <algorithm>

#include "core/utils/numeric.hpp"

using namespace graphcpp;

namespace
{
	void fill_diagonal(std::vector<std::vector<mcontent>>& matrix, mcontent value)
	{
		for (msize i = 0; i < matrix.size(); i++)
		{
			matrix[i][i] = value;
		}
	}
}

FullSymmetricMatrix::FullSymmetricMatrix(msize dimension)
{
	_matrix.resize(dimension);
	for (auto& str : _matrix)
	{
		str.resize(dimension);
	}
}

FullSymmetricMatrix::FullSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix) : 
	FullSymmetricMatrix(matrix.size())
{
	assert(check_symmetrical_matrix(matrix));

	for (msize i = 0; i < matrix.size(); i++)
	{
		for (msize j = 0; j < matrix.size(); j++)
		{
			_matrix[i][j] = matrix[i][j];
		}
	}
	fill_diagonal(_matrix, 0);
}

FullSymmetricMatrix::FullSymmetricMatrix(const SymmetricMatrixBase& matrix) :
	FullSymmetricMatrix(matrix.dimension())
{
	for (auto[i, j] : matrix)
	{
		set(i, j, matrix.at(i, j));
	}
}

msize FullSymmetricMatrix::dimension() const
{
	return _matrix.size();
}

mcontent FullSymmetricMatrix::at(msize index1, msize index2) const
{
	assert(std::max(index1, index2) < dimension());

	return _matrix[index1][index2];
}

void FullSymmetricMatrix::set(msize index1, msize index2, mcontent value) 
{
	assert(index1 != index2);
	assert(std::max(index1, index2) < dimension());

	_matrix[index1][index2] = value;
	_matrix[index2][index1] = value;
}

void FullSymmetricMatrix::reduce_element(msize index1, msize index2, mcontent difference)
{
	assert(index1 != index2);
	assert(std::max(index1, index2) < dimension());

	_matrix[index1][index2] -= difference;
	_matrix[index2][index1] -= difference;
}

void FullSymmetricMatrix::swap(msize str1, msize str2) //Todo: optimize
{
	assert(str1 != str2);
	assert(std::max(str1, str2) < dimension());

	const mcontent previous_value = _matrix[str1][str2];

	std::swap(_matrix[str1], _matrix[str2]);

	for (msize i = 0; i < dimension(); i++)
	{
		std::swap(_matrix[i][str1], _matrix[i][str2]);
	}

	_matrix[str1][str2] = previous_value;
	_matrix[str2][str1] = previous_value;
}

void FullSymmetricMatrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
	assert(new_nums.size() == dimension());
	assert(is_permutation(new_nums));

	FullSymmetricMatrix result(dimension());
	for(auto[i, j] : *this)
	{
		result.set(new_nums[i], new_nums[j], _matrix[i][j]);
	}

	_matrix = std::move(result._matrix);
}

void FullSymmetricMatrix::delete_last_strings(msize count)
{
	assert(count < dimension());

	for (msize i = 0; i < count; i++)
	{
		_matrix.pop_back();
	}
	for (msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < count; j++)
		{
			_matrix[i].pop_back();
		}
	}
}