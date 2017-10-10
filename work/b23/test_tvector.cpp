#include "utmatrix.h"

#include <gtest/gtest.h>

TEST(TVector, can_create_vector_with_positive_length)
{
	TVector<int> v(5);
	/*cout << endl << v << endl;*/
	ASSERT_NO_THROW(v);

}

TEST(TVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
	
}

TEST(TVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, throws_when_create_vector_with_negative_startindex)
{
	ASSERT_ANY_THROW(TVector<int> v(5, -2));
}

TEST(TVector, can_create_copied_vector)
{
	TVector<int> v(10);
	TVector<int> v1(v);
	//cout << endl << v << endl;
	//cout << endl << v1 << endl;
	ASSERT_NO_THROW(v1);
}

TEST(TVector, copied_vector_is_equal_to_source_one)
{
	TVector<int> sourceVector(10);
	sourceVector[2] = 5;
	sourceVector[4] = 2;
	sourceVector[9] = 7;
	TVector<int> copiedVector(sourceVector);
	cout << endl << sourceVector << endl;
	cout << endl << copiedVector << endl;
	EXPECT_EQ(sourceVector, copiedVector);
}

TEST(TVector, copied_vector_has_its_own_memory)
{
	// TODO: need to know what exactly owm memory means
	TVector<int> sourceVector(10);
	sourceVector[2] = 5;
	sourceVector[4] = 2;
	sourceVector[9] = 7;
	TVector<int> copiedVector(sourceVector);
	EXPECT_NE(copiedVector.GetSize(), 0);
}

TEST(TVector, can_get_size)
{
	TVector<int> v(4);
	EXPECT_EQ(4, v.GetSize());
}

TEST(TVector, can_get_start_index)
{
	TVector<int> v(4, 2);
	cout << v << endl;
	EXPECT_EQ(2, v.GetStartIndex());
}

TEST(TVector, can_set_and_get_element)
{
	TVector<int> v(4);
	v[0] = 4;

	EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_set_element_with_negative_index)
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[-1] = 1);
}

TEST(TVector, throws_when_set_element_with_too_large_index)
{
	TVector<int> v(5);
	ASSERT_ANY_THROW(v[5] = 1);
}

TEST(TVector, can_assign_vector_to_itself)
{
	ADD_FAILURE();
}

TEST(TVector, can_assign_vectors_of_equal_size)
{
	ADD_FAILURE();
}

TEST(TVector, assign_operator_change_vector_size)
{
	ADD_FAILURE();
}

TEST(TVector, can_assign_vectors_of_different_size)
{
	ADD_FAILURE();
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
	EXPECT_EQ(vector1 == vector2, true);
}

TEST(TVector, compare_vector_with_itself_return_true)
{
	TVector<int> vector1(10, 3);
	vector1[4] = 5;
	vector1[7] = 2;
	vector1[9] = 7;
	EXPECT_EQ(vector1 == vector1, true);
}

TEST(TVector, vectors_with_different_size_are_not_equal)
{
	TVector<int> vector1(10, 3), vector2(8, 3);
	EXPECT_NE(vector1, vector2);
}

TEST(TVector, can_add_scalar_to_vector)
{
	ADD_FAILURE();
}

TEST(TVector, can_subtract_scalar_from_vector)
{
	ADD_FAILURE();
}

TEST(TVector, can_multiply_scalar_by_vector)
{
	ADD_FAILURE();
}

TEST(TVector, can_add_vectors_with_equal_size)
{
	ADD_FAILURE();
}

TEST(TVector, cant_add_vectors_with_not_equal_size)
{
	ADD_FAILURE();
}

TEST(TVector, can_subtract_vectors_with_equal_size)
{
	ADD_FAILURE();
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size)
{
	ADD_FAILURE();
}

TEST(TVector, can_multiply_vectors_with_equal_size)
{
	ADD_FAILURE();
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size)
{
	ADD_FAILURE();
}

