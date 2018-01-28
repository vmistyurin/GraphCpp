#include "core/MatrixImplementation/full_symmetric_matrix.h"
#include "core/MatrixImplementation/half_symmetric_matrix.h"
#include "gtest/gtest.h"
#include <memory>

using namespace graphcpp;

namespace
{
	const std::vector<std::vector<mcontent>> test_array
			{{0, 8, 0, 4, 0},
			 {8, 0, 0, 1, 0},
			 {0, 0, 0, 0, 0},
			 {4, 1, 0, 0, 1},
			 {0, 0, 0, 1, 0}};

	template<class T>
	std::unique_ptr<SymmetricMatrixBase> GetMatrix(const std::vector<std::vector<mcontent>> &array);

	template<>
	std::unique_ptr<SymmetricMatrixBase>
	GetMatrix<FullSymmetricMatrix>(const std::vector<std::vector<mcontent>> &array) {
		return std::make_unique<FullSymmetricMatrix>(array);
	}

	template<>
	std::unique_ptr<SymmetricMatrixBase>
	GetMatrix<HalfSymmetricMatrix>(const std::vector<std::vector<mcontent>> &array) {
		return nullptr;
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

using SymmericMatrixImplementations = testing::Types<FullSymmetricMatrix>;
TYPED_TEST_CASE(SymmetricMatrixTests, SymmericMatrixImplementations);


TYPED_TEST(SymmetricMatrixTests, IndexatorTest)
{
	const msize x_first_test_index = 0, y_first_test_index = 1;
	const mcontent first_indexed_value = 8;
	const msize x_second_test_index = 4, y_second_test_index = 1;
	const mcontent second_indexed_value = 0;

	EXPECT_EQ(this->test_matrix->at(x_first_test_index, y_first_test_index), first_indexed_value);
	EXPECT_EQ(this->test_matrix->at(x_second_test_index, y_second_test_index), second_indexed_value);
}

TYPED_TEST(SymmetricMatrixTests, DimensionTest)
{
	const msize test_dimension = test_array.size();

	EXPECT_EQ(this->test_matrix->dimension(), test_dimension);
}

TYPED_TEST(SymmetricMatrixTests, GetStringTest)
{
	const msize test_string = 1;
	const std::vector<mcontent> first_string = test_array[test_string];

	EXPECT_EQ(this->test_matrix->get_string(test_string), first_string);
}

TYPED_TEST(SymmetricMatrixTests, EqualityTest)
{
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
	const auto equal_to_test_matrix = GetMatrix<TypeParam>(test_array);
	const auto dimensional_non_equal_matrix = GetMatrix<TypeParam>(dimensional_non_equal_array);
	const auto content_non_equal_matrix = GetMatrix<TypeParam>(content_non_equal_array);

	EXPECT_EQ(*this->test_matrix, *this->test_matrix);
	EXPECT_EQ(*this->test_matrix, *equal_to_test_matrix);
	EXPECT_NE(*this->test_matrix, *dimensional_non_equal_matrix);
	EXPECT_NE(*this->test_matrix, *content_non_equal_matrix);
}

TYPED_TEST(SymmetricMatrixTests, SwapTest)
{
	const msize first_swapped_string = 0;
	const msize second_swapped_string = 3;
	const std::vector<std::vector<mcontent>> expected_after_swap_array
			{ { 0, 1, 0, 4, 1 },
			  { 1, 0, 0, 8, 0 },
			  { 0, 0, 0, 0, 0 },
			  { 4, 8, 0, 0, 0 },
			  { 1, 0, 0, 0, 0 } };
	const auto expected_after_swap_matrix = GetMatrix<TypeParam>(expected_after_swap_array);

	this->test_matrix->swap(first_swapped_string, second_swapped_string);

	EXPECT_EQ(*this->test_matrix, *expected_after_swap_matrix);
}

TYPED_TEST(SymmetricMatrixTests, SetterTest)
{
	const msize first_setted_index = 1, second_setted_index = 2;
	const mcontent setted_value = 10;
	const std::vector<std::vector<mcontent>> expected_after_set_array
			{ { 0, 8, 0, 4, 0 },
			  { 8, 0, setted_value, 1, 0 },
			  { 0, setted_value, 0, 0, 0 },
			  { 4, 1, 0, 0, 1 },
			  { 0, 0, 0, 1, 0 } };
	const auto expected_after_set_matrix = GetMatrix<TypeParam>(expected_after_set_array);

	this->test_matrix->set(first_setted_index, second_setted_index, setted_value);

	EXPECT_EQ(*this->test_matrix, *expected_after_set_matrix);
}

TYPED_TEST(SymmetricMatrixTests, RearrangeTest)
{
	const std::vector<msize> test_permutation{ 2,0,1,3,4 };
	const std::vector<std::vector<mcontent>> expected_after_rearrange_array
			{ { 0, 0, 8, 1, 0 },
			  { 0, 0, 0, 0, 0 },
			  { 8, 0, 0, 4, 0 },
			  { 1, 0, 4, 0, 1 },
			  { 0, 0, 0, 1, 0 } };
	const auto expected_after_rearrange_matrix = GetMatrix<TypeParam>(expected_after_rearrange_array);

	this->test_matrix->rearrange(test_permutation);

	EXPECT_EQ(*this->test_matrix, *expected_after_rearrange_matrix);
}

TYPED_TEST(SymmetricMatrixTests, DeleteLastStringsTest)
{
	const msize number_of_strings_to_delete = 2;
	const std::vector<std::vector<mcontent>> expected_after_delete_array
			{ { 0, 8, 0 },
			  { 8, 0, 0 },
			  { 0, 0, 0 } };
	const auto expected_after_delete_matrix = GetMatrix<TypeParam>(expected_after_delete_array);

	this->test_matrix->delete_last_strings(number_of_strings_to_delete);

	EXPECT_EQ(*this->test_matrix, *expected_after_delete_matrix);
}