#include "unit_tests/test_data/tested_matrix.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	const std::vector<std::vector<mcontent>> test_matrix = { {0, 10, 0, 0, 0, 6},
															 {22, 0, 0, 0, 0, 0},
															 {5, 0, 0, 0, 8, 0},
															 {0, 0, 0, 0, 0, 0},
															 {0, 0, 0, 6, 0, 5},
															 {7, 0, 0, 0, 0, 0} };
	constexpr msize test_dimension = 6;
}

msize tested_matrix::dimension()
{
	return test_dimension;
}

template<>
std::unique_ptr<Matrix> tested_matrix::matrix<Matrix>()
{
	return std::make_unique<Matrix>(test_matrix);
}

std::vector<std::vector<mcontent>> tested_matrix::matrix_as_vector()
{
	return test_matrix;
}

std::vector<msize> tested_matrix::test_permutation()
{
	return { 1,2,5,0,4,3 };
}

std::vector<std::vector<mcontent>> tested_matrix::expected_after_rearrange_matrix()
{
	return { {0, 0, 0, 0, 0, 0},
			 {0, 0, 10, 6, 0, 0},
			 {0, 22, 0, 0, 0, 0},
			 {0, 7, 0, 0, 0, 0},
			 {6, 0, 0, 5, 0, 0},
			 {0, 5, 0, 0, 8, 0} };
}

std::pair<msize, msize> tested_matrix::swapped_strings()
{
	return { 0, 2 };
}
std::vector<std::vector<mcontent>> tested_matrix::expected_after_swap_matrix()
{
	return { {0, 0, 5, 0, 8, 0},
			 {0 ,0, 22, 0, 0, 0},
			 {0, 10, 0, 0, 0, 6},
			 {0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 6, 0, 5},
			 {0, 0, 7, 0, 0, 0} };
}