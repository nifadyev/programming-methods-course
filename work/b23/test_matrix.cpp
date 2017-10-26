#include "utmatrix.h"

#include <gtest/gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
	TMatrix<int> matrix(5);

	ASSERT_NO_THROW(matrix);
}

TEST(TMatrix, cant_create_too_large_matrix)
{
	ASSERT_THROW(TMatrix<int> matrix(MAX_MATRIX_SIZE + 1), range_error);
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_THROW(TMatrix<int> matrix(-1), length_error);
}

TEST(TMatrix, can_create_copied_matrix)
{
	TMatrix<int> sourceMatrix(5);

	ASSERT_NO_THROW(TMatrix<int> copiedMatrix(sourceMatrix));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> sourceMatrix(5), copiedMatrix(5);
	sourceMatrix[0][3] = 1;
	sourceMatrix[2][2] = 4;
	sourceMatrix[1][1] = 7;

	EXPECT_EQ(copiedMatrix = sourceMatrix, sourceMatrix);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> sourceMatrix(5), copiedMatrix(5);
	sourceMatrix[0][2] = 3;
	copiedMatrix = sourceMatrix;

	EXPECT_NE(&copiedMatrix[0][2], &sourceMatrix[0][2]);
}

TEST(TMatrix, can_get_size)
{
	TMatrix<int> matrix(5);

	EXPECT_EQ(matrix.GetSize(), 5);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int> matrix(5);

	ASSERT_NO_THROW(matrix[2][2] = 4);
	EXPECT_EQ(matrix[2][2], 4);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int> matrix(5);

	ASSERT_THROW(matrix[-1][1] = 8, range_error);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int> matrix(5);

	ASSERT_THROW(matrix[10][1] = 1, range_error);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int> matrix(5);
	matrix[0][3] = 1;
	matrix[2][2] = 4;
	matrix[1][1] = 7;

	EXPECT_EQ(matrix = matrix, matrix);
}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int> matrix(5), resultMatrix(5);
	matrix[0][3] = 1;
	matrix[2][2] = 4;
	matrix[1][1] = 7;

	ASSERT_NO_THROW(resultMatrix = matrix);
	EXPECT_EQ(resultMatrix, matrix);
}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int> matrix(7), resultMatrix(5);
	matrix[0][3] = 1;
	matrix[2][2] = 4;
	matrix[1][1] = 7;
	resultMatrix = matrix;

	EXPECT_EQ(resultMatrix.GetSize(), 7);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int> matrix1(7), matrix2(5);
	matrix1[0][3] = 1;
	matrix1[2][2] = 4;
	matrix1[1][1] = 7;

	ASSERT_NO_THROW(matrix2 = matrix1);
	EXPECT_EQ(matrix2, matrix1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int> matrix1(5);
	matrix1[0][3] = 1;
	matrix1[2][2] = 4;
	matrix1[1][1] = 7;

	TMatrix<int> matrix2(matrix1);

	EXPECT_TRUE(matrix1 == matrix2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int> matrix(5);
	matrix[0][3] = 1;
	matrix[2][2] = 4;
	matrix[1][1] = 7;

	EXPECT_TRUE(matrix == matrix);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int> matrix1(5), matrix2(9);

	EXPECT_FALSE(matrix1 == matrix2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int> matrix1(5), matrix2(5), expectedMatrix(5);
	matrix1[0][4] = 1;
	matrix1[2][3] = 4;
	matrix1[3][3] = 6;
	matrix1[4][4] = 7;

	matrix2[0][3] = 2;
	matrix2[1][1] = 5;
	matrix2[2][2] = 4;
	matrix2[4][4] = 1;

	expectedMatrix[0][3] = 2;
	expectedMatrix[0][4] = 1;
	expectedMatrix[1][1] = 5;
	expectedMatrix[2][2] = 4;
	expectedMatrix[2][3] = 4;
	expectedMatrix[3][3] = 6;
	expectedMatrix[4][4] = 8;

	EXPECT_EQ(matrix1 + matrix2, expectedMatrix);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int> matrix1(5), matrix2(7);

	ASSERT_THROW(matrix1 + matrix2, length_error);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int> matrix1(5), matrix2(5), expectedMatrix(5);
	matrix1[0][4] = 1;
	matrix1[2][3] = 4;
	matrix1[3][3] = 6;
	matrix1[4][4] = 7;

	matrix2[0][3] = 1;
	matrix2[1][1] = 5;
	matrix2[2][2] = 4;
	matrix2[4][4] = 1;

	expectedMatrix[0][3] = -1;
	expectedMatrix[0][4] = 1;
	expectedMatrix[1][1] = -5;
	expectedMatrix[2][2] = -4;
	expectedMatrix[2][3] = 4;
	expectedMatrix[3][3] = 6;
	expectedMatrix[4][4] = 6;

	EXPECT_EQ(matrix1 - matrix2, expectedMatrix);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int> matrix1(5), matrix2(7);

	ASSERT_THROW(matrix1 - matrix2, length_error);

}


TEST(TMatrixCustom, can_create_matrix_from_vector)
{
	TVector<TVector<int>> vector(4);

	ASSERT_NO_THROW(TMatrix<int> matrix(vector));
}

TEST(TMatrixCustom, can_set_and_get_large_element)
{
	TMatrix<int> matrix(5);

	ASSERT_NO_THROW(matrix[3][4] = INT32_MAX);
	EXPECT_EQ(matrix[3][4], INT32_MAX);
}

TEST(TMatrixCustom, compare_equal_matrices_return_false)
{
	TMatrix<int> matrix1(5);
	matrix1[0][3] = 1;
	matrix1[2][2] = 4;
	matrix1[1][1] = 7;

	TMatrix<int> matrix2(matrix1);

	EXPECT_FALSE(matrix1 != matrix2);
}

TEST(TMatrixCustom, can_add_three_matrices_with_equal_size)
{
	TMatrix<int> matrix1(5), matrix2(5), matrix3(5), expectedMatrix(5);
	matrix1[0][4] = 1;
	matrix1[2][3] = 4;
	matrix1[3][3] = 6;
	matrix1[4][4] = 7;

	matrix2[0][3] = 2;
	matrix2[1][1] = 5;
	matrix2[2][2] = 4;
	matrix2[4][4] = 1;

	matrix3[0][0] = 2;
	matrix3[1][1] = 2;
	matrix3[2][4] = 9;
	matrix3[4][4] = -4;

	expectedMatrix[0][0] = 2;
	expectedMatrix[0][3] = 2;
	expectedMatrix[0][4] = 1;
	expectedMatrix[1][1] = 7;
	expectedMatrix[2][2] = 4;
	expectedMatrix[2][3] = 4;
	expectedMatrix[2][4] = 9;
	expectedMatrix[3][3] = 6;
	expectedMatrix[4][4] = 4;

	EXPECT_EQ(matrix1 + matrix2 + matrix3, expectedMatrix);
}

TEST(TMatrixCustom, can_substract_three_matrices_with_equal_size)
{
	TMatrix<int> matrix1(5), matrix2(5), matrix3(5), expectedMatrix(5);
	matrix1[0][4] = 1;
	matrix1[2][3] = 4;
	matrix1[3][3] = 6;
	matrix1[4][4] = 7;

	matrix2[0][3] = 2;
	matrix2[1][1] = 5;
	matrix2[2][2] = 4;
	matrix2[4][4] = 1;

	matrix3[0][0] = 2;
	matrix3[1][1] = 2;
	matrix3[2][4] = 9;
	matrix3[4][4] = -4;

	expectedMatrix[0][0] = -2;
	expectedMatrix[0][3] = -2;
	expectedMatrix[0][4] = 1;
	expectedMatrix[1][1] = -7;
	expectedMatrix[2][2] = -4;
	expectedMatrix[2][3] = 4;
	expectedMatrix[2][4] = -9;
	expectedMatrix[3][3] = 6;
	expectedMatrix[4][4] = 10;

	EXPECT_EQ(matrix1 - matrix2 - matrix3, expectedMatrix);
}

