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

//
//std::ostream& graphcpp::operator<<(std::ostream& stream, const MatrixBase& matrix)
//{
//    return stream << matrix.to_string();
//}
