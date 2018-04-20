#include "core/matrix_implementations/symmetric_matrix_base.hpp"
#include <string>
#include <algorithm>
#include <assert.h>

using namespace graphcpp;

namespace 
{
	auto get_len(mcontent number)
	{
		return std::to_string(number).length();
	}

	std::string get_aligned_string(mcontent number, mcontent len)
	{
		assert(get_len(number) <= len);
		return std::to_string(number) + std::string(len - get_len(number) + 1, ' ');
	}
}

SymmetricMatrixIterator SymmetricMatrixBase::begin() const
{
	return SymmetricMatrixIterator(dimension());
}

SymmetricMatrixIterator SymmetricMatrixBase::end() const
{
	return SymmetricMatrixIterator();
}

std::string SymmetricMatrixBase::to_string() const
{
	mcontent max_len = 0;
	for (msize i = 0; i < dimension(); i++)
	{
		for (msize j = 0; j < dimension(); j++)
		{
			max_len = std::max(max_len, static_cast<mcontent>(get_len(at(i, j))));
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

std::ostream& graphcpp::operator<< (std::ostream& stream, const SymmetricMatrixBase& matrix)
{
	stream << matrix.to_string();
	return stream;
}