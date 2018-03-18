#include "core/MatrixImplementation/symmetric_matrix_base.h"
#include <string>
#include <algorithm>
#include <assert.h>

using namespace graphcpp;

namespace {
	unsigned int get_len(mcontent number)
	{
		return std::to_string(number).length();
	}

	std::string get_aligned_string(mcontent number, mcontent len)
	{
		assert(get_len(number) <= len);
		return std::to_string(number) + std::string(len - get_len(number) + 1, ' ');
	}
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