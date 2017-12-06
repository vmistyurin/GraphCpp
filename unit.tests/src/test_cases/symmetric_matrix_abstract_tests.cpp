#include "core/MatrixImplementation/matrix.h"
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
	std::shared_ptr<SymmetricMatrixBase> matrix;
	std::vector<std::vector<mcontent>> array;
};

TEST_F(MatrixTests, IndexatorTest)
{
	EXPECT_EQ(matrix->at(0, 1), (unsigned int)1);
	EXPECT_EQ(matrix->at(4, 0), (unsigned int)0);
}

TEST_F(MatrixTests, DimensionTest)
{
	EXPECT_EQ(matrix->dimension(), 5);
}

TEST_F(MatrixTests, GetStringTest)
{
	auto expected_vector = std::vector<mcontent>{ 1, 0, 0, 1, 0 };
	EXPECT_EQ(matrix->get_string(1), expected_vector );
}

TEST_F(MatrixTests, EqualityTest)
{
	auto equal_matrix = Matrix((*matrix));
	auto non_equal_matrix = Matrix({ {1,0,0}, {0,1,0},{0,0,1} });

	EXPECT_EQ(equal_matrix, *matrix);
	EXPECT_EQ(*matrix, *matrix);
	EXPECT_NE(non_equal_matrix, *matrix);
}

TEST_F(MatrixTests, SwapTest)
{
	std::vector<std::vector<mcontent>> expected_array{ { 1, 0, 0, 0, 0 },
												   { 0, 1, 1, 1, 0 },
												   { 0, 1, 1, 1, 0 },
	                                               { 0, 1, 1, 1, 1 },
												   { 0, 0, 0, 1, 1 } };

	Matrix expected_matrix(expected_array);
	matrix->swap(0, 2);

	EXPECT_EQ(*matrix, expected_matrix);		
}

TEST_F(MatrixTests, SetterTest)
{
	std::vector<std::vector<mcontent>> expected_array{ { 1, 1, 0, 1, 0 },
												   { 1, 1, 1, 1, 0 },
												   { 0, 1, 1, 0, 0 },
												   { 1, 1, 0, 1, 1 },
												   { 0, 0, 0, 1, 1 } };
	Matrix expected_matrix(expected_array);
	matrix->set(1, 2, true);

	EXPECT_EQ(*matrix, expected_matrix);
	//EXPECT_DEATH(matrix->set(1, 1, true), "");
}

TEST_F(MatrixTests, RearrangeTest)
{
	std::vector<msize> permutation {2,0,1,3,4};
	std::vector<std::vector<mcontent>> expected_array{ { 1, 0, 1, 1, 0 },
													   { 0, 1, 0, 0, 0 },
													   { 1, 0, 1, 1, 0 },
													   { 1, 0, 1, 1, 1 },
													   { 0, 0, 0, 1, 1 } };
	Matrix expected_matrix(expected_array);

	matrix->rearrange(permutation);

	EXPECT_EQ(*matrix, expected_matrix);
}