#include "tSet.h"
#include <gtest\gtest.h>

TEST(TSet, CanGetMaxPower)
{
	const int size = 5;
	TSet set(size);
	EXPECT_EQ(size, set.GetMaxPower());
}

TEST(TSet, CanInsertNonExistingElement)
{
	const int size = 5, k = 3;
	TSet set(size);
	set.InsertElem(k);
	EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, CanInsertExistingElement)
{
	const int size = 5;
	const int k = 3;
	TSet set(size);
	set.InsertElem(k);
	set.InsertElem(k);
	EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, CanDeleteNonExistingElement)
{
	const int size = 5, k = 3;
	TSet set(size);
	set.DeleteElem(k);
	EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, CanDeleteExistingElement)
{
	const int size = 5, k = 3;
	TSet set(size);
	set.InsertElem(k);
	EXPECT_GT(set.IsMember(k), 0);
	set.DeleteElem(k);
	EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, CompareTwoSetsOfNonEqualSizes)
{
	const int size1 = 4, size2 = 6;
	TSet set1(size1), set2(size2);
	EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, CompareTwoEqualSets)
{
	const int size = 4;
	TSet set1(size), set2(size);
	// set1 = set2 = {1, 3}
	set1.InsertElem(1);
	set1.InsertElem(3);
	set2.InsertElem(1);
	set2.InsertElem(3);
	EXPECT_EQ(set1, set2);
}

TEST(TSet, CompareTwoNonEqualSets)
{
	const int size = 4;
	TSet set1(size), set2(size);
	// set1 = {1, 3}
	set1.InsertElem(1);
	set1.InsertElem(3);
	// set2 = {1, 2}
	set2.InsertElem(1);
	set2.InsertElem(2);
	EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, CanAssignSetOfEqualSize)
{
	const int size = 4;
	TSet set1(size), set2(size);
	// set1 = {1, 3}
	set1.InsertElem(1);
	set1.InsertElem(3);
	set2 = set1;
	EXPECT_EQ(set1, set2);
}

TEST(TSet, CanAssignSetOfGreaterSize)
{
	const int size1 = 4, size2 = 6;
	TSet set1(size1), set2(size2);
	// set1 = {1, 3}
	set1.InsertElem(1);
	set1.InsertElem(3);
	set2 = set1;
	EXPECT_EQ(set1, set2);
}

TEST(TSet, CanAssignSetOfLessSize)
{
	const int size1 = 6, size2 = 4;
	TSet set1(size1), set2(size2);
	// set1 = {1, 3, 5}
	set1.InsertElem(1);
	set1.InsertElem(3);
	set1.InsertElem(5);
	set2 = set1;
	EXPECT_EQ(set1, set2);
}

TEST(TSet, CanInsertNonExistingElementUsingPlusOperator)
{
	const int size = 4;
	const int k = 3;
	TSet set(size), result(size);
	set.InsertElem(0);
	set.InsertElem(2);
	result = set + k;
	EXPECT_NE(0, result.IsMember(k));
}

TEST(TSet, ThrowsWhenInsertNonExistingElementOutOfRangeUsingPlusOperator)
{
	const int size = 4;
	const int k = 6;
	TSet set(size), result(size);
	set.InsertElem(0);
	set.InsertElem(2);
	ASSERT_ANY_THROW(result = set + k);
}

TEST(TSet, CanInsertExistingElementUsingPlusOperator)
{
	const int size = 4;
	const int k = 3;
	TSet set(size), result(size);
	set.InsertElem(0);
	set.InsertElem(k);
	result = set + k;
	EXPECT_NE(0, set.IsMember(k));
}

TEST(TSet, CheckSizeOfTheCombinationOfTwoSetsOfEqualSize)
{
	const int size = 5;
	TSet set1(size), set2(size), result(size);
	// set1 = {1, 2, 4}
	set1.InsertElem(1);
	set1.InsertElem(2);
	set1.InsertElem(4);
	// set2 = {0, 1, 2}
	set2.InsertElem(0);
	set2.InsertElem(1);
	set2.InsertElem(2);
	result = set1 + set2;
	EXPECT_EQ(size, result.GetMaxPower());
}

TEST(TSet, CanCombineTwoSetsOfEqualSize)
{
	const int size = 5;
	TSet set1(size), set2(size), result(size), expectedSet(size);
	// set1 = {1, 2, 4}
	set1.InsertElem(1);
	set1.InsertElem(2);
	set1.InsertElem(4);
	// set2 = {0, 1, 2}
	set2.InsertElem(0);
	set2.InsertElem(1);
	set2.InsertElem(2);
	result = set1 + set2;
	// expectedSet = {0, 1, 2, 4}
	expectedSet.InsertElem(0);
	expectedSet.InsertElem(1);
	expectedSet.InsertElem(2);
	expectedSet.InsertElem(4);
	EXPECT_EQ(expectedSet, result);
}

TEST(TSet, CheckSizeChangesOfTheCombinationOfTwoSetsOfNonEqualSize)
{
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2), result(size1);
	// set1 = {1, 2, 4}
	set1.InsertElem(1);
	set1.InsertElem(2);
	set1.InsertElem(4);
	// set2 = {0, 1, 2}
	set2.InsertElem(0);
	set2.InsertElem(1);
	set2.InsertElem(2);
	result = set1 + set2;
	EXPECT_EQ(size2, result.GetMaxPower());
}

TEST(TSet, CanCombineTwoSetsOfNonEqualSize)
{
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2), result(size1), expectedSet(size2);
	// set1 = {1, 2, 4}
	set1.InsertElem(1);
	set1.InsertElem(2);
	set1.InsertElem(4);
	// set2 = {0, 1, 2, 6}
	set2.InsertElem(0);
	set2.InsertElem(1);
	set2.InsertElem(2);
	set2.InsertElem(6);
	result = set1 + set2;
	// expectedSet = {0, 1, 2, 4, 6}
	expectedSet.InsertElem(0);
	expectedSet.InsertElem(1);
	expectedSet.InsertElem(2);
	expectedSet.InsertElem(4);
	expectedSet.InsertElem(6);
	EXPECT_EQ(expectedSet, result);
}

TEST(TSet, CanIntersectTwoSetsOfEqualSize)
{
	const int size = 5;
	TSet set1(size), set2(size), result(size), expectedSet(size);
	// set1 = {1, 2, 4}
	set1.InsertElem(1);
	set1.InsertElem(2);
	set1.InsertElem(4);
	// set2 = {0, 1, 2}
	set2.InsertElem(0);
	set2.InsertElem(1);
	set2.InsertElem(2);
	result = set1 * set2;
	// expectedSet = {1, 2}
	expectedSet.InsertElem(1);
	expectedSet.InsertElem(2);
	EXPECT_EQ(expectedSet, result);
}

TEST(TSet, CanIntersectTwoSetsOfNonEqualSize)
{
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2), result(size1), expectedSet(size2);
	// set1 = {1, 2, 4}
	set1.InsertElem(1);
	set1.InsertElem(2);
	set1.InsertElem(4);
	// set2 = {0, 1, 2, 4, 6}
	set2.InsertElem(0);
	set2.InsertElem(1);
	set2.InsertElem(2);
	set2.InsertElem(4);
	set2.InsertElem(6);
	result = set1 * set2;
	// expectedSet = {1, 2, 4}
	expectedSet.InsertElem(1);
	expectedSet.InsertElem(2);
	expectedSet.InsertElem(4);
	EXPECT_EQ(expectedSet, result);
}

TEST(TSet, CheckNegationOperator)
{
	const int size = 4;
	TSet set(size), invertedSet(size), expectedSet(size);
	// set1 = {1, 3}
	set.InsertElem(1);
	set.InsertElem(3);
	invertedSet = ~set;
	// expectedSet = {0, 2}
	expectedSet.InsertElem(0);
	expectedSet.InsertElem(2);
	EXPECT_EQ(expectedSet, invertedSet);
}

TEST(TSetCustom, CheckDifferenceOperator)
{
	const int size = 4, elem = 2;
	TSet set(size), result(size), expectedSet(size);
	// set = {1, 2, 3}
	set.InsertElem(1);
	set.InsertElem(2);
	set.InsertElem(3);
	result = set - elem;
	//expectedSet = {1, 3}
	expectedSet.InsertElem(1);
	expectedSet.InsertElem(3);
	EXPECT_EQ(expectedSet, result);
	EXPECT_EQ(0, result.IsMember(elem));		
}

TEST(TSetCustom, ThrowsWhenSubstractTooLargeElement)
{
	const int size = 4;
	const int k = 6;
	TSet set(size), result(size);
	set.InsertElem(0);
	set.InsertElem(2);
	ASSERT_ANY_THROW(result = set - k);
}

TEST(TSetCustom, CanSubtractNonExistingElement)
{
	
	const int size = 4;
	const int k = 3;
	TSet set(size), result(size);
	//set = {0, 2}
	set.InsertElem(0);
	set.InsertElem(2);
	//result = {0, 2}
	result = set - k;
	EXPECT_NE(1, result.IsMember(k));
}