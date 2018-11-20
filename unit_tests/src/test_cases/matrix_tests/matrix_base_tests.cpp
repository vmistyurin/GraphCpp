#include "gtest/gtest.h"

#include "core/all.hpp"
#include "unit_tests/macroses.hpp"
#include "unit_tests/implementations.hpp"
#include "unit_tests/test_data/test_matrix.hpp"

using namespace graphcpp;
using namespace graphcpp_testing;

namespace
{
	template<class GraphType>
	std::unique_ptr<MatrixBase> GetMatrix(const std::vector<std::vector<mcontent>>& array)
    {
        return std::make_unique<GraphType>(array);
    }
}

template<class TestMatrixType>
class MatrixBaseTests : public testing::Test
{
public:
	MatrixBaseTests() :
		test_matrix(GetMatrix<TestMatrixType>(test_matrix::matrix_as_vector()))
	{
	};
    
	std::unique_ptr<MatrixBase> test_matrix;
};

TYPED_TEST_CASE(MatrixBaseTests, MatrixImplementations,);

TYPED_TEST(MatrixBaseTests, IndexatorTest)
{
	msize x_first_test_index = 0, y_first_test_index = 4;
	mcontent first_indexed_value = test_matrix::matrix_as_vector()[x_first_test_index][y_first_test_index];

	msize x_second_test_index = 5, y_second_test_index = 2;
	mcontent second_indexed_value = test_matrix::matrix_as_vector()[x_second_test_index][y_second_test_index];

	EXPECT_EQ(this->test_matrix->at(x_first_test_index, y_first_test_index), first_indexed_value);
	EXPECT_EQ(this->test_matrix->at(x_second_test_index, y_second_test_index), second_indexed_value);
}

TYPED_TEST(MatrixBaseTests, DimensionTest)
{
	msize test_dimension = test_matrix::dimension();

	EXPECT_EQ(this->test_matrix->dimension(), test_dimension);
}

TYPED_TEST(MatrixBaseTests, EqualityTest)
{
	std::vector<std::vector<mcontent>> dimensional_non_equal_array = {
        { 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
    };

	std::vector<std::vector<mcontent>> content_non_equal_array(test_matrix::matrix_as_vector());
	content_non_equal_array[5][2]++;
	content_non_equal_array[2][5]++;

	auto equal_to_test_matrix = GetMatrix<TypeParam>(test_matrix::matrix_as_vector());
	auto dimensional_non_equal_matrix = GetMatrix<TypeParam>(dimensional_non_equal_array);
	auto content_non_equal_matrix = GetMatrix<TypeParam>(content_non_equal_array);

	EXPECT_EQ(*this->test_matrix, *this->test_matrix);
	EXPECT_EQ(*this->test_matrix, *equal_to_test_matrix);
	EXPECT_NE(*this->test_matrix, *dimensional_non_equal_matrix);
	EXPECT_NE(*this->test_matrix, *content_non_equal_matrix);
}

TYPED_TEST(MatrixBaseTests, SwapTest)
{
	auto expected_after_swap_matrix = GetMatrix<TypeParam>(test_matrix::expected_after_swap_matrix());
	auto[first_string, second_string] = test_matrix::swapped_strings();

    std::cout << *this->test_matrix << std::endl;

	this->test_matrix->swap(first_string, second_string);
    
    std::cout << *expected_after_swap_matrix << std::endl;
    std::cout << *this->test_matrix << std::endl;
    
	EXPECT_EQ(*this->test_matrix, *expected_after_swap_matrix);
}

TYPED_TEST(MatrixBaseTests, SetTest)
{
	msize x_test_index = 4, y_test_index = 0;
	mcontent setted_value = test_matrix::matrix_as_vector()[x_test_index][y_test_index] + 100;

	auto expected_after_set_array = test_matrix::matrix_as_vector();
	expected_after_set_array[x_test_index][y_test_index] = setted_value;

	auto expected_after_set_matrix = GetMatrix<TypeParam>(expected_after_set_array);

	this->test_matrix->set(x_test_index, y_test_index, setted_value);

	EXPECT_EQ(*this->test_matrix, *expected_after_set_matrix);
}

TYPED_TEST(MatrixBaseTests, RearrangeWithSwapTest)
{
	auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(test_matrix::expected_after_rearrange_matrix());

	this->test_matrix->rearrange_with_permutations(test_matrix::test_permutation());

	EXPECT_EQ(*this->test_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(MatrixBaseTests, RearrangeWithAllocTest)
{
	auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(test_matrix::expected_after_rearrange_matrix());

	this->test_matrix->rearrange_with_allocate(test_matrix::test_permutation());

	EXPECT_EQ(*this->test_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(MatrixBaseTests, MakeRearrangedTest)
{
	auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(test_matrix::expected_after_rearrange_matrix());
	TypeParam rearranged_matrix(test_matrix::dimension());

	this->test_matrix->make_rearranged(test_matrix::test_permutation(), rearranged_matrix);

	EXPECT_EQ(rearranged_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(MatrixBaseTests, DeleteLastStringsTest)
{
	msize number_of_strings_to_delete = 2;
	auto expected_after_delete_array = test_matrix::matrix_as_vector();
	for (msize i = 0; i < number_of_strings_to_delete; i++)
	{
		expected_after_delete_array.pop_back();
	}
	for (msize i = 0; i < test_matrix::dimension() - number_of_strings_to_delete; i++)
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

TYPED_TEST(MatrixBaseTests, ReduceElementTest)
{
	msize x_test_index = 0;
	msize y_test_index = 4;
	mcontent difference = 5;

	auto expected_after_set_array = test_matrix::matrix_as_vector();
	expected_after_set_array[x_test_index][y_test_index] -= difference;

	auto expected_after_set_matrix = GetMatrix<TypeParam>(expected_after_set_array);

	this->test_matrix->reduce_element(x_test_index, y_test_index, difference);

	EXPECT_EQ(*this->test_matrix, *expected_after_set_matrix);
}
