#include <memory>

#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/macroses.hpp"
#include "unit_tests/implementations.hpp"

using namespace graphcpp;

namespace //TODO: move it to test_data
{
	const std::vector<std::vector<mcontent>> test_array = 
	{{ 0, 0, 0, 4, 8, 0, 0, 0, 0},
	 { 0, 0, 0, 7, 0, 0, 10, 0, 0},
	 { 0, 0, 0, 0, 5, 0, 9, 40, 30},
	 { 4, 7, 0, 0, 1, 0, 0, 0, 0},
	 { 8, 0, 5, 1, 0, 0, 0, 0, 0},
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0},
	 { 0, 10, 9, 0, 0, 0, 0, 0, 1},
	 { 0, 0, 40, 0, 0, 0, 0, 0, 0},
	 { 0, 0, 30, 0, 0, 0, 1, 0, 0} };

	const auto test_dimension = test_array.size();

	const std::vector<msize> test_permutation = { 3,6,7,0,4,1,2,8,5 };

	const std::vector<std::vector<mcontent>> rearranged_test_array =
	{{ 0, 0, 0, 4, 1, 0, 7, 0, 0 },
	 { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 0, 0, 0, 1, 10, 9, 0 },
	 { 4, 0, 0, 0, 8, 0, 0, 0, 0 },
	 { 1, 0, 0, 8, 0, 0, 0, 5, 0 },
	 { 0, 0, 1, 0, 0, 0, 0, 30, 0 },
	 { 7, 0, 10, 0, 0, 0, 0, 0, 0 },
	 { 0, 0, 9, 0, 5, 30, 0, 0, 40},
	 { 0, 0, 0, 0, 0, 0, 0, 40, 0 } };

	template<class T>
	std::unique_ptr<SymmetricMatrixBase> GetMatrix(const std::vector<std::vector<mcontent>>& array);

	template<>
	std::unique_ptr<SymmetricMatrixBase> GetMatrix<FullSymmetricMatrix>(const std::vector<std::vector<mcontent>>& array) 
	{
		return std::make_unique<FullSymmetricMatrix>(array);
	}

	template<>
	std::unique_ptr<SymmetricMatrixBase> GetMatrix<HalfSymmetricMatrix>(const std::vector<std::vector<mcontent>>& array) 
	{
		return std::make_unique<HalfSymmetricMatrix>(array);
	}
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
}; 

TYPED_TEST_CASE(SymmetricMatrixTests, SymmetricMatrixImplementations);

TYPED_TEST(SymmetricMatrixTests, GetterTest)
{
	msize x_first_test_index = 0, y_first_test_index = 1;
	auto first_indexed_value = test_array[0][1];
	msize x_second_test_index = 4, y_second_test_index = 0;
	auto second_indexed_value = test_array[4][0];

	EXPECT_EQ(this->test_matrix->at(x_first_test_index, y_first_test_index), first_indexed_value);
	EXPECT_EQ(this->test_matrix->at(x_second_test_index, y_second_test_index), second_indexed_value);
}

TYPED_TEST(SymmetricMatrixTests, DimensionTest)
{
	msize test_dimension = test_array.size();

	EXPECT_EQ(this->test_matrix->dimension(), test_dimension);
}

TYPED_TEST(SymmetricMatrixTests, EqualityTest)
{
	std::vector<std::vector<mcontent>> dimensional_non_equal_array = { { 1,0,0 },
																	   { 0,1,0 },
																	   { 0,0,1 } };
	std::vector<std::vector<mcontent>> content_non_equal_array(test_array);
	content_non_equal_array[5][2]++;
	content_non_equal_array[2][5]++;

	auto equal_to_test_matrix = GetMatrix<TypeParam>(test_array);
	auto dimensional_non_equal_matrix = GetMatrix<TypeParam>(dimensional_non_equal_array);
	auto content_non_equal_matrix = GetMatrix<TypeParam>(content_non_equal_array);

	EXPECT_EQ(*this->test_matrix, *this->test_matrix);
	EXPECT_EQ(*this->test_matrix, *equal_to_test_matrix);
	EXPECT_NE(*this->test_matrix, *dimensional_non_equal_matrix);
	EXPECT_NE(*this->test_matrix, *content_non_equal_matrix);
}

TYPED_TEST(SymmetricMatrixTests, SwapTest)
{
	msize first_swapped_string = 2;
	msize second_swapped_string = 6;
	std::vector<std::vector<mcontent>> expected_after_swap_array
	{ { 0, 0, 0, 4, 8, 0, 0, 0, 0 },
	  { 0, 0, 10, 7, 0, 0, 0, 0, 0 },
	  { 0, 10, 0, 0, 0, 0, 9, 0, 1 },
	  { 4, 7, 0, 0, 1, 0, 0, 0, 0 },
	  { 8, 0, 0, 1, 0, 0, 5, 0, 0 },
	  { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	  { 0, 0, 9, 0, 5, 0, 0, 40, 30 },
	  { 0, 0, 0, 0, 0, 0, 40, 0, 0 },
	  { 0, 0, 1, 0, 0, 0, 30, 0, 0 } };
	auto expected_after_swap_matrix = GetMatrix<TypeParam>(expected_after_swap_array);

	this->test_matrix->swap(first_swapped_string, second_swapped_string);

	EXPECT_EQ(*this->test_matrix, *expected_after_swap_matrix);
}

TYPED_TEST(SymmetricMatrixTests, SetUpperDiagonalTest)
{
	msize x_test_index = 0, y_test_index = 1;
	mcontent setted_value = test_array[x_test_index][y_test_index] + 10;

	auto expected_after_set_array = test_array;
	expected_after_set_array[x_test_index][y_test_index] = setted_value;
	expected_after_set_array[y_test_index][x_test_index] = setted_value;

	auto expected_after_set_matrix = GetMatrix<TypeParam>(expected_after_set_array);

	this->test_matrix->set(x_test_index, y_test_index, setted_value);

	EXPECT_EQ(*this->test_matrix, *expected_after_set_matrix);
}

TYPED_TEST(SymmetricMatrixTests, SetUnderDiagonalTest)
{
	msize x_test_index = 4, y_test_index = 0;
	mcontent setted_value = test_array[x_test_index][y_test_index] + 100;

	auto expected_after_set_array = test_array;
	expected_after_set_array[x_test_index][y_test_index] = setted_value;
	expected_after_set_array[y_test_index][x_test_index] = setted_value;

	auto expected_after_set_matrix = GetMatrix<TypeParam>(expected_after_set_array);

	this->test_matrix->set(x_test_index, y_test_index, setted_value);

	EXPECT_EQ(*this->test_matrix, *expected_after_set_matrix);
}

TYPED_TEST(SymmetricMatrixTests, RearrangeWithSwapTest)
{
	auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(rearranged_test_array);

	this->test_matrix->rearrange_with_permutations(test_permutation);

	EXPECT_EQ(*this->test_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(SymmetricMatrixTests, RearrangeWithAllocTest)
{	
	auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(rearranged_test_array);

	this->test_matrix->rearrange_with_allocate(test_permutation);

	EXPECT_EQ(*this->test_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(SymmetricMatrixTests, MakeRearrangedTest)
{
	auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(rearranged_test_array);
	TypeParam rearranged_matrix(test_dimension);

	this->test_matrix->make_rearranged(test_permutation, rearranged_matrix);

	EXPECT_EQ(rearranged_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(SymmetricMatrixTests, DeleteLastStringsTest)
{
	msize number_of_strings_to_delete = 2;
	std::vector<std::vector<mcontent>> expected_after_delete_array(test_array);
	for (msize i = 0; i < number_of_strings_to_delete; i++)
	{
		expected_after_delete_array.pop_back();
	}
	for (msize i = 0; i < test_dimension - number_of_strings_to_delete; i++)
	{
		for (msize j = 0; j < number_of_strings_to_delete; j++)
		{
			expected_after_delete_array[i].pop_back();
		}
	}

	auto expected_after_delete_matrix = GetMatrix<TypeParam>(expected_after_delete_array);

	this->test_matrix->delete_last_strings(number_of_strings_to_delete);

	EXPECT_EQ(*this->test_matrix, *expected_after_delete_matrix);
}

TYPED_TEST(SymmetricMatrixTests, ReduceElementTest)
{
	msize x_test_index = 0;
	msize y_test_index = 4;
	mcontent difference = 5;

	auto expected_after_set_array = test_array;
	expected_after_set_array[x_test_index][y_test_index] -= difference;
	expected_after_set_array[y_test_index][x_test_index] -= difference;

	auto expected_after_set_matrix = GetMatrix<TypeParam>(expected_after_set_array);

	this->test_matrix->reduce_element(x_test_index, y_test_index, difference);

	EXPECT_EQ(*this->test_matrix, *expected_after_set_matrix);
}

TYPED_TEST(SymmetricMatrixTests, WithDeletedVertexesTest)
{
	const std::vector<msize> deleted_vertexes = { 0, 3, 5, 8 };
	const std::vector<std::vector<mcontent>> expected_array =
	{ {  0, 0, 0, 10, 0 },
	  {  0, 0, 5, 9,  40 },
	  {  0, 5, 0, 0,  0 },
	  { 10, 9, 0, 0,  0 },
	  { 0, 40, 0, 0,  0 } };
	const auto expected_matrix = GetMatrix<TypeParam>(expected_array);

	auto matrix_afted_delete = this->test_matrix->with_deleted_vertexes(deleted_vertexes);

	EXPECT_EQ(*matrix_afted_delete, *expected_matrix);
}

TYPED_TEST(SymmetricMatrixTests, WithDeletedElementTest)
{
	const msize x = 0;
	const msize y = 5;

	const auto with_deleted_element = this->test_matrix->with_deleted_element(x, y);

	this->test_matrix->set(x, y, 0);

	EXPECT_EQ(*with_deleted_element, *this->test_matrix);
}