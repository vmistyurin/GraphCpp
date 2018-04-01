#include "core/matrix_implementation/half_symmetric_matrix.hpp"
#include "core/macroses.hpp"
#include "core/utils.hpp"
#include <assert.h>
#include <algorithm>

using namespace graphcpp;

HalfSymmetricMatrix::HalfSymmetricMatrix::HalfSymmetricMatrix(msize dimension)
{
	assert(dimension != 0);

	_matrix.resize(dimension - 1);
	for (msize i = 0; i < dimension - 1; i++)
	{
		_matrix[i].resize(i + 1);
	}
}

HalfSymmetricMatrix::HalfSymmetricMatrix(const std::vector<std::vector<mcontent>>& matrix) :
	HalfSymmetricMatrix(matrix.size())
{
	assert(check_symmetrical_matrix(matrix));

	for (msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < i; j++)
		{
			_matrix[i - 1][j] = matrix[i][j];
		}
	}
}

HalfSymmetricMatrix::HalfSymmetricMatrix(const SymmetricMatrixBase& matrix) : HalfSymmetricMatrix(matrix.dimension())
{
	for (msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < i; j++)
		{
			_matrix[i - 1][j] = matrix.at(i, j);
		}
	}
}

bool HalfSymmetricMatrix::operator==(const SymmetricMatrixBase& rhs) const
{
	RETURN_IF(this == &rhs, true);
	RETURN_IF(rhs.dimension() != dimension(), false);
	for (msize i = 1; i < dimension(); i++)
	{
		for (msize j = 0; j < i; j++)
		{
			RETURN_IF(_matrix[i - 1][j] != rhs.at(i, j), false);
		}
	}
	return true;
}

bool HalfSymmetricMatrix::operator!=(const SymmetricMatrixBase& rhs) const
{
	return !(*this == rhs);
}

msize HalfSymmetricMatrix::dimension() const
{
	return _matrix.size() + 1;
}

mcontent HalfSymmetricMatrix::at(msize index1, msize index2) const
{
	MINMAX(index1, index2);
	assert(index2 < dimension());

	RETURN_IF(index1 == index2, 0);

	return _matrix[index2 - 1][index1];
}

void HalfSymmetricMatrix::set(msize index1, msize index2, mcontent value)
{
	MINMAX(index1, index2);
	assert(index1 != index2);
	assert(index2 < dimension());

	_matrix[index2 - 1][index1] = value;
}

void HalfSymmetricMatrix::reduce_element(msize index1, msize index2, mcontent difference)
{
	MINMAX(index1, index2);
	assert(index1 != index2);
	assert(index2 < dimension());

	_matrix[index2 - 1][index1] -= difference;
}

std::vector<mcontent> HalfSymmetricMatrix::get_string(msize str) const
{
	assert(str < dimension());

	std::vector<mcontent> result;
	result.reserve(dimension());
	for (msize i = 0; i < dimension(); i++)
	{
		result.push_back(at(i, str));
	}

	return result;
}

void HalfSymmetricMatrix::swap(msize str1, msize str2)
{
	MINMAX(str1, str2);
	assert(str1 != str2);
	assert(str2 < dimension());

	for (msize i = 0; i < str1; i++)
	{
		std::swap(_matrix[str1 - 1][i], _matrix[str2 - 1][i]);
	}

	for (msize i = str1 + 1; i < str2; i++)
	{
		std::swap(_matrix[i - 1][str1], _matrix[str2 - 1][i]);
	}

	for (msize i = str2 + 1; i < dimension(); i++)
	{
		std::swap(_matrix[i - 1][str1], _matrix[i - 1][str2]);
	}
}

void HalfSymmetricMatrix::rearrange_with_permutations(const std::vector<msize>& new_nums)
{
	assert(new_nums.size() == dimension());
	assert(is_permutation(new_nums));

	auto transpositions = to_transpositions(new_nums);
	for (auto[str1, str2] : transpositions)
	{
		swap(str1, str2);
	}
}

void HalfSymmetricMatrix::rearrange_with_allocate(const std::vector<msize>& new_nums)
{
	assert(new_nums.size() == dimension());
	assert(is_permutation(new_nums));

	HalfSymmetricMatrix result(dimension());

	for (msize i = 1; i < new_nums.size(); i++)
	{
		for (msize j = 0; j < i; j++)
		{
			result.set(new_nums[i], new_nums[j], at(i, j));
		}
	}

	_matrix = std::move(result._matrix);
}

void HalfSymmetricMatrix::make_rearranged(const std::vector<msize>& new_nums, std::shared_ptr<SymmetricMatrixBase> result) const
{
	assert(new_nums.size() == dimension());
	assert(is_permutation(new_nums));
	assert(result->dimension() == dimension());

	for (msize i = 1; i < new_nums.size(); i++)
	{
		for (msize j = 0; j < i; j++)
		{
			result->set(new_nums[i], new_nums[j], at(i, j));
		}
	}
}

void HalfSymmetricMatrix::delete_last_strings(msize count)
{
	assert(count <= dimension());

	for (msize i = 0; i < count; i++)
	{
		_matrix.pop_back();
	}
}