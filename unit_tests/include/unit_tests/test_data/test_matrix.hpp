#ifndef UNIT_TESTS_TEST_MATRIX_HPP
#define UNIT_TESTS_TEST_MATRIX_HPP

#include "core/all.hpp"

namespace graphcpp_testing::test_matrix
{
	using namespace graphcpp;

	msize dimension();

	template<class MatrixType>
	std::unique_ptr<MatrixType> matrix();

	std::vector<std::vector<mcontent>> matrix_as_vector();

	std::vector<msize> test_permutation();
	std::vector<std::vector<mcontent>> expected_after_rearrange_matrix();

	std::pair<msize, msize> swapped_strings();
	std::vector<std::vector<mcontent>> expected_after_swap_matrix();
}
#endif