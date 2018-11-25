#include "core/matrix_implementations/matrix_base.hpp"

#include <cassert>
#include <algorithm>
#include <set>

#include "core/utils/numeric.hpp"

using namespace graphcpp;

namespace
{
	auto get_len(mcontent number)
	{
		return std::to_string(number).length();
	}

	std::string get_aligned_string(mcontent number, unsigned int len)
	{
		assert(get_len(number) <= len);
		return std::to_string(number) + std::string(len - get_len(number) + 1, ' ');
	}
}

bool MatrixBase::operator==(const MatrixBase& rhs) const
{
	RETURN_IF(dimension() != rhs.dimension(), false);

	for (msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < dimension(); j++)
		{
			RETURN_IF(at(i, j) != rhs.at(i, j), false);
		}
	}
	return true;
}

bool MatrixBase::operator!=(const MatrixBase& rhs) const
{
	return !(*this == rhs);
}

void MatrixBase::make_rearranged(const std::vector<msize>& new_nums, MatrixBase& memory) const
{
	assert(new_nums.size() == dimension());
	assert(is_permutation(new_nums));
	assert(memory.dimension() == dimension());

	for(msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < dimension(); j++)
		{
			memory.set(new_nums[i], new_nums[j], at(i, j));
		}
	}
}

void MatrixBase::delete_strings(const std::vector<msize>& strings)
{
	std::set<msize, std::greater<msize>> to_delete(strings.cbegin(), strings.cend());

	auto current_position = dimension() - 1;

	for (auto it = to_delete.cbegin(); it != to_delete.cend(); ++it)
	{
		while (to_delete.count(current_position) == 1)
		{
			++it;
			current_position--;
		}

		for (auto i = *it; i < current_position; i++)
		{
			swap(i, i + 1);
		}

		current_position--;
	}
	delete_last_strings(strings.size());
}

std::string MatrixBase::to_string() const
{
	unsigned int max_len = 0;
	for (msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < dimension(); j++)
		{
			max_len = std::max(max_len, static_cast<unsigned int>(get_len(at(i, j))));
		}
	}

	std::string result;
	for (msize i = 0; i < dimension(); i++)
	{
		std::string current_string;
		for (msize j = 0; j < dimension(); j++)
		{
			current_string += get_aligned_string(at(i, j), max_len);
			current_string += ",";
		}
		current_string.pop_back();

		result += current_string;
		result += '\n';
	}

	return result;
}

std::ostream& graphcpp::operator<<(std::ostream& stream, const MatrixBase& matrix)
{
	return stream << matrix.to_string();
}
