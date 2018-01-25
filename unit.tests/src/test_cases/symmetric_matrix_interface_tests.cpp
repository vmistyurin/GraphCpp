#include "core/MatrixImplementation/full_symmetric_matrix.h"
#include "core/MatrixImplementation/half_symmetric_matrix.h"
#include "gtest/gtest.h"
#include <memory>

using namespace graphcpp;

const std::vector<std::vector<mcontent>> test_array  
{ { 0, 8, 0, 4, 0 },
  { 8, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0 },
  { 4, 1, 0, 0, 1 },
  { 0, 0, 0, 1, 0 } };

template<class T> std::unique_ptr<SymmetricMatrixBase> GetMatrix(const std::vector<std::vector<mcontent>>& array);

template<> std::unique_ptr<SymmetricMatrixBase> GetMatrix<FullSymmetricMatrix>(const std::vector<std::vector<mcontent>>& array)
{
	return std::make_unique<FullSymmetricMatrix>(array);
}

template<> std::unique_ptr<SymmetricMatrixBase> GetMatrix<HalfSymmetricMatrix>(const std::vector<std::vector<mcontent>>& array)
{
	return nullptr;
}

template<class TestMatrixType>
class SymmetricMatrixTests: public testing::Test
{
public:
	SymmetricMatrixTests() : 
		test_matrix(GetMatrix<TestMatrixType>(test_array))	
	{
	};
	std::unique_ptr<SymmetricMatrixBase> test_matrix;
	const std::unique_ptr<SymmetricMatrixBase> equal_to_test_matrix            = GetMatrix<TestMatrixType>(test_array);
	const std::unique_ptr<SymmetricMatrixBase> dimensional_non_equal_matrix    = GetMatrix<TestMatrixType>(dimensional_non_equal_array);
	const std::unique_ptr<SymmetricMatrixBase> content_non_equal_matrix        = GetMatrix<TestMatrixType>(content_non_equal_array);
	const std::unique_ptr<SymmetricMatrixBase> expected_after_swap_matrix      = GetMatrix<TestMatrixType>(expected_after_swap_array);
	const std::unique_ptr<SymmetricMatrixBase> expected_after_set_matrix       = GetMatrix<TestMatrixType>(expected_after_set_array);
	const std::unique_ptr<SymmetricMatrixBase> expected_after_rearrange_matrix = GetMatrix<TestMatrixType>(expected_after_rearrange_array);
	const std::unique_ptr<SymmetricMatrixBase> expected_after_delete_matrix    = GetMatrix<TestMatrixType>(expected_after_delete_array);
}; 

using Implementations = testing::Types<FullSymmetricMatrix>;
TYPED_TEST_CASE(SymmetricMatrixTests, Implementations);


const msize x_first_test_index = 0, y_first_test_index = 1;
const mcontent first_indexed_value = 8;
const msize x_second_test_index = 4, y_second_test_index = 1;
const mcontent second_indexed_value = 0;
TYPED_TEST(SymmetricMatrixTests, IndexatorTest)
{
	EXPECT_EQ(test_matrix->at(x_first_test_index, y_first_test_index), first_indexed_value);
	EXPECT_EQ(test_matrix->at(x_second_test_index, y_second_test_index), second_indexed_value);
}


const msize test_dimension = test_array.size();
TYPED_TEST(SymmetricMatrixTests, DimensionTest)
{
	EXPECT_EQ(test_matrix->dimension(), test_dimension);
}


const msize test_string = 1;
const std::vector<mcontent> first_string = test_array[test_string];
TYPED_TEST(SymmetricMatrixTests, GetStringTest)
{
	EXPECT_EQ(test_matrix->get_string(test_string), first_string);
}


const std::vector<std::vector<mcontent>> dimensional_non_equal_array
{ { 1,0,0 },
  { 0,1,0 },
  { 0,0,1 } };
const std::vector<std::vector<mcontent>> content_non_equal_array
{ { 0, 2, 0, 4, 1 },
  { 2, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0 },
  { 4, 1, 0, 0, 1 },
  { 1, 0, 0, 1, 0 } };
TYPED_TEST(SymmetricMatrixTests, EqualityTest)
{
	EXPECT_EQ(*test_matrix, *test_matrix);
	EXPECT_EQ(*equal_to_test_matrix, *test_matrix);
	EXPECT_NE(*dimensional_non_equal_matrix, *test_matrix);
	EXPECT_NE(*content_non_equal_matrix, *test_matrix);
}


const msize first_swapped_string = 0;
const msize second_swapped_string = 3;
const std::vector<std::vector<mcontent>> expected_after_swap_array
{ { 0, 1, 0, 4, 1 },
  { 1, 0, 0, 8, 0 },
  { 0, 0, 0, 0, 0 },
  { 4, 8, 0, 0, 0 },
  { 1, 0, 0, 0, 0 } };
TYPED_TEST(SymmetricMatrixTests, SwapTest)
{
	test_matrix->swap(first_swapped_string, second_swapped_string);

	EXPECT_EQ(*test_matrix, *expected_after_swap_matrix);
}


const msize first_setted_index = 1, second_setted_index = 2;
const mcontent setted_value = 10;
const std::vector<std::vector<mcontent>> expected_after_set_array
{ { 0, 8, 0, 4, 0 },
  { 8, 0, setted_value, 1, 0 },
  { 0, setted_value, 0, 0, 0 },
  { 4, 1, 0, 0, 1 },
  { 0, 0, 0, 1, 0 } };
TYPED_TEST(SymmetricMatrixTests, SetterTest)
{
	test_matrix->set(first_setted_index, second_setted_index, setted_value);

	EXPECT_EQ(*test_matrix, *expected_after_set_matrix);
}


const std::vector<msize> test_permutation{ 2,0,1,3,4 };
const std::vector<std::vector<mcontent>> expected_after_rearrange_array
{ { 0, 0, 8, 1, 0 },
  { 0, 0, 0, 0, 0 },
  { 8, 0, 0, 4, 0 },
  { 1, 0, 4, 0, 1 },
  { 0, 0, 0, 1, 0 } };
TYPED_TEST(SymmetricMatrixTests, RearrangeTest)
{
	test_matrix->rearrange(test_permutation);

	EXPECT_EQ(*test_matrix, *expected_after_rearrange_matrix);
}


const msize number_of_strings_to_delete = 2;
const std::vector<std::vector<mcontent>> expected_after_delete_array
{ { 0, 8, 0 },
  { 8, 0, 0 },
  { 0, 0, 0 } };
TYPED_TEST(SymmetricMatrixTests, DeleteLastStringsTest)
{
	test_matrix->delete_last_strings(number_of_strings_to_delete);

	EXPECT_EQ(*test_matrix, *expected_after_delete_matrix);
}