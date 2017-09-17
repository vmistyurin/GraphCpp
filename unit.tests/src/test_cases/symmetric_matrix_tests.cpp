#include "core/symmetric_matrix.h"
#include "gtest/gtest.h"
#include <array>
#include <memory>

using namespace graphcpp;

class SymmetricMatrixTests : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		std::array<std::array<bool, 5>, 5> arr{ std::array<bool,5> { 1, 0, 0, 0, 0 },
																   { 1, 1, 0, 0, 0 },
																   { 0, 0, 1, 0, 0 },
																   { 1, 1, 0, 1, 0 },
																   { 0, 0, 0, 1, 1 } };
		matrix = std::make_shared<SymmetricMatrix>(arr);
	}

	virtual void TearDown() {}

	std::shared_ptr<SymmetricMatrix> matrix;
};

TEST_F(SymmetricMatrixTests, IndexatorTests)
{
	ASSERT_EQ(matrix->at(0, 0), true);
	ASSERT_EQ(matrix->at(4, 0), false);
	ASSERT_EQ(matrix->at(1, 4), false);
}

TEST_F(SymmetricMatrixTests, DimensionTest)
{
	ASSERT_EQ(matrix->dimension(), 5);
}
