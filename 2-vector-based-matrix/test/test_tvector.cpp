#include "utmatrix.h"
#include <gtest/gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
	TVector<int> vector(5);

	ASSERT_NO_THROW(vector);
}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_THROW(TVector<int> vector(MAX_VECTOR_SIZE + 1), length_error);
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_THROW(TVector<int> vector(-6), length_error);
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_THROW(TVector<int> vector(5, -2), invalid_argument);
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> vector(10);
	TVector<int> vector1(vector);

	ASSERT_NO_THROW(vector1);
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> sourceVector(10);
	sourceVector[2] = 5;
	sourceVector[4] = 2;
	sourceVector[9] = 7;

	TVector<int> copiedVector(sourceVector);

	EXPECT_EQ(sourceVector, copiedVector);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	TVector<int> sourceVector(10);
	sourceVector[2] = 5;
	sourceVector[4] = 2;
	sourceVector[9] = 7;

	TVector<int> copiedVector(sourceVector);

	EXPECT_NE(&copiedVector[2], &sourceVector[2]);
}

TEST(TVector, can_get_size)
{
	TVector<int> vector(4);

	EXPECT_EQ(4, vector.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> vector(4, 2);

	EXPECT_EQ(2, vector.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> vector(4);

	ASSERT_NO_THROW(vector[2] = 4);
	EXPECT_EQ(4, vector[2]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> vector(5);

	ASSERT_THROW(vector[-1] = 6, range_error);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> vector(5);

	ASSERT_THROW(vector[7] = 1, range_error);
}

TEST(TVector, can_assign_vector_to_itself)
{
	TVector<int> vector(5);
	EXPECT_EQ(vector = vector, vector);
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	TVector<int> vector1(10), vector2(10), expectedVector(10);
	vector2[2] = 5;
	vector2[4] = 2;
	vector2[9] = 7;

	expectedVector[2] = 5;
	expectedVector[4] = 2;
	expectedVector[9] = 7;

	EXPECT_EQ(vector1 = vector2, expectedVector);
}

TEST(TVector, assign_operator_change_vector_size)
{
	TVector<int> vector1(10), vector2(20, 2);
	vector2[2] = 5;
	vector2[4] = 2;
	vector2[8] = 7;

	vector1 = vector2;

	EXPECT_EQ(vector1.GetSize(), 20);
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	TVector<int> vector1(10), vector2(20, 2), expectedVector(20, 2);
	vector2[2] = 5;
	vector2[4] = 2;
	vector2[8] = 7;

	expectedVector[2] = 5;
	expectedVector[4] = 2;
	expectedVector[8] = 7;

	EXPECT_EQ(vector1 = vector2, expectedVector);
}

TEST(TVector, compare_equal_vectors_return_true)
{
	TVector<int> vector1(10, 3), vector2(10, 3);
	vector1[4] = 5;
	vector1[7] = 2;
	vector1[9] = 7;

	vector2[4] = 5;
	vector2[7] = 2;
	vector2[9] = 7;

	EXPECT_TRUE(vector1 == vector2);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> vector1(10, 3);
	vector1[4] = 5;
	vector1[7] = 2;
	vector1[9] = 7;

	EXPECT_TRUE(vector1 == vector1);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> vector1(10, 3), vector2(8, 3);

	EXPECT_NE(vector1, vector2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	TVector<int> vector1(5), expectedVector(5);
	vector1[0] = 5;
	vector1[2] = 2;
	vector1[4] = 7;

	expectedVector[0] = 8;
	expectedVector[1] = 3;
	expectedVector[2] = 5;
	expectedVector[3] = 3;
	expectedVector[4] = 10;

	EXPECT_EQ(expectedVector, vector1 + 3);
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	TVector<int> vector1(5), expectedVector(5);
	vector1[0] = 5;
	vector1[2] = 2;
	vector1[4] = 7;

	expectedVector[0] = 2;
	expectedVector[1] = -3;
	expectedVector[2] = -1;
	expectedVector[3] = -3;
	expectedVector[4] = 4;

	EXPECT_EQ(expectedVector, vector1 - 3);
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	TVector<int> vector1(5), expectedVector(5);
	vector1[0] = 5;
	vector1[2] = 2;
	vector1[4] = 7;

	expectedVector[0] = 15;
	expectedVector[1] = 0;
	expectedVector[2] = 6;
	expectedVector[3] = 0;
	expectedVector[4] = 21;

	EXPECT_EQ(expectedVector, vector1 * 3);
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	TVector<int> vector1(5), vector2(5), expectedVector(5);
	vector1[0] = 5;
	vector1[1] = 2;
	vector1[3] = 7;

	vector2[1] = 3;
	vector2[2] = 9;
	vector2[3] = 1;

	expectedVector[0] = 5;
	expectedVector[1] = 5;
	expectedVector[2] = 9;
	expectedVector[3] = 8;
	expectedVector[4] = 0;

	EXPECT_EQ(expectedVector, vector1 + vector2);
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	TVector<int> vector1(10), vector2(17);

	ASSERT_THROW(vector1 + vector2, length_error);
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	TVector<int> vector1(5), vector2(5), expectedVector(5);
	vector1[0] = 5;
	vector1[1] = 2;
	vector1[3] = 7;

	vector2[1] = 3;
	vector2[2] = 9;
	vector2[3] = 1;

	expectedVector[0] = 5;
	expectedVector[1] = -1;
	expectedVector[2] = -9;
	expectedVector[3] = 6;
	expectedVector[4] = 0;

	EXPECT_EQ(expectedVector, vector1 - vector2);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	TVector<int> vector1(10), vector2(17);

	ASSERT_THROW(vector1 - vector2, length_error);
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	TVector<int> vector1(10), vector2(10);
	vector1[4] = 5;
	vector1[7] = 2;
	vector1[9] = 7;

	vector2[4] = 3;
	vector2[5] = 9;
	vector2[9] = 1;

	EXPECT_EQ(vector1 * vector2, 22);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	TVector<int> vector1(10), vector2(17);

	ASSERT_THROW(vector1 * vector2, length_error);
}

