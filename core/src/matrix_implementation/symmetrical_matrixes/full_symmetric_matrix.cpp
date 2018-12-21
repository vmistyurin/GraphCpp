#include "core/matrix_implementations/symmetric_matrixes/full_symmetric_matrix.hpp"

#include <cassert>
#include <algorithm>

#include "core/utils/numeric.hpp"
#include "core/iterators/matrix_iterator.hpp"

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

std::unique_ptr<FullSymmetricMatrix> FullSymmetricMatrix::with_deleted_vertexes(const std::vector<msize>& vertexes) const
{
	assert(!vertexes.empty());
	assert(std::all_of(vertexes.cbegin(), vertexes.cend(), [&](auto vertex) { return vertex < dimension(); }));

	auto result = std::make_unique<FullSymmetricMatrix>(dimension() - vertexes.size());

	auto new_nums = std::vector<msize>(); new_nums.reserve(dimension() - vertexes.size());
	msize position_in_deleted = 0;
	for (msize i = 0; i < dimension(); i++)
	{
		if (vertexes[position_in_deleted] == i)
		{
			position_in_deleted++;
			continue;
		}
		new_nums.push_back(i);
	}

	for (msize i = 0; i < new_nums.size(); i++)
	{
		for (msize j = i + 1; j < new_nums.size(); j++)
		{
			result->set(i, j, at(new_nums[i], new_nums[j]));
		}
	}

	return result;
}

std::unique_ptr<FullSymmetricMatrix> FullSymmetricMatrix::with_deleted_element(msize i, msize j) const
{
	assert(std::max(i, j) < dimension());

	auto result = std::make_unique<FullSymmetricMatrix>(*this);
	result->set(i, j, 0);
	return result;
}
