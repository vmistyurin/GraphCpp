#include "core/matrix.h"
#include "gtest/gtest.h"
#include <memory>

using namespace graphcpp;

class MatrixTests : public ::testing::Test
{
protected:
	virtual void SetUp() override
	{
		array =	{ { 1, 1, 0, 1, 0 },
				{ 1, 1, 0, 1, 0 },
				{ 0, 0, 1, 0, 0 },
				{ 1, 1, 0, 1, 1 },
				{ 0, 0, 0, 1, 1 } };
		matrix = std::make_shared<Matrix>(array);
	}

	std::vector<bool> first_string;
	std::vector<bool> second_string;
	std::shared_ptr<Matrix> matrix;
	std::vector<std::vector<bool>> array;
};

TEST_F(MatrixTests, IndexatorTest)
{
	EXPECT_EQ(matrix->at(0, 1), true);
	EXPECT_EQ(matrix->at(4, 0), false);
}

TEST_F(MatrixTests, DimensionTest)
{
	EXPECT_EQ(matrix->dimension(), 5);
}

TEST_F(MatrixTests, GetStringTest)
{
	auto expected_vector = std::vector<bool>{ true, true, false, true, false };
	EXPECT_EQ(matrix->get_string(1), expected_vector );
}

TEST_F(MatrixTests, EqualityTest)
{
	auto equal_matrix = Matrix(*matrix);
	auto non_equal_matrix = Matrix({ {1,0,0}, {0,1,0},{0,0,1} });

	EXPECT_EQ(equal_matrix, *matrix);
	EXPECT_EQ(*matrix, *matrix);
	EXPECT_NE(non_equal_matrix, *matrix);
}

TEST_F(MatrixTests, SwapTest)
{
	std::vector<std::vector<bool>> expected_array{ { 1, 0, 0, 0, 0 },
												   { 0, 1, 1, 1, 0 },
												   { 0, 1, 1, 1, 0 },
	                                               { 0, 1, 1, 1, 1 },
												   { 0, 0, 0, 1, 1 } };

	Matrix expected_matrix(expected_array);
	matrix->swap(0, 2);

	EXPECT_EQ(*matrix, expected_matrix);		

}