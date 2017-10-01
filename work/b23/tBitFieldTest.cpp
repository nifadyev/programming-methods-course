#include "tBitField.h"
#include <gtest\gtest.h>

TEST(TBitField, CanCreateBitfieldWithPositiveLength)
{
	ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, CanGetLength)
{
	TBitField bf(3);
	EXPECT_EQ(3, bf.GetLength());
}

TEST(TBitField, NewBitfieldIsSetToZero)
{
	TBitField bf(100);
	int sum = 0;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		sum += bf.GetBit(i);
	}
	EXPECT_EQ(0, sum);
}

TEST(TBitField, CanSetBit)
{
	TBitField bf(10);
	EXPECT_EQ(0, bf.GetBit(3));
	bf.SetBit(3);
	EXPECT_NE(0, bf.GetBit(3));
}

TEST(TBitField, CanClearBit)
{
	TBitField bf(10);
	int bitIndex = 3;
	bf.SetBit(bitIndex);
	EXPECT_NE(0, bf.GetBit(bitIndex));
	bf.ClearBit(bitIndex);
	EXPECT_EQ(0, bf.GetBit(bitIndex));
}


TEST(TBitField, ThrowsWhenCreateBitfieldWithNegativeLength)
{
	ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, ThrowsWhenSetBitWithNegativeIndex)
{
	TBitField bf(10);
	ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(TBitField, ThrowsWhenSetBitWithTooLargeIndex)
{
	TBitField bf(10);
	ASSERT_ANY_THROW(bf.SetBit(11));
}

TEST(TBitField, ThrowsWhenGetBitWithNegativeIndex)
{
	TBitField bf(10);
	ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(TBitField, ThrowsWhenGetBitWithTooLargeIndex)
{
	TBitField bf(10);
	ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(TBitField, ThrowsWhenClearBitWithNegativeIndex)
{
	TBitField bf(10);
	ASSERT_ANY_THROW(bf.ClearBit(-3));
}

TEST(TBitField, ThrowsWhenClearBitWithTooLargeIndex)
{
	TBitField bf(10);
	ASSERT_ANY_THROW(bf.ClearBit(11));
}

TEST(TBitField, CanAssignBitfieldsOfEqualSize)
{
	const int size = 2;
	TBitField bf1(size), result(size);
	for (int i = 0; i < size; i++)
	{
		bf1.SetBit(i);
	}
	result = bf1;
	EXPECT_NE(0, result.GetBit(0));
	EXPECT_NE(0, result.GetBit(1));
}

TEST(TBitField, AssignOperatorChangesBitfieldSize)
{
	const int size1 = 2, size2 = 5;
	TBitField bf1(size1), result(size2);
	for (int i = 0; i < size1; i++)
	{
		bf1.SetBit(i);
	}
	result = bf1;
	EXPECT_EQ(2, result.GetLength());
}

TEST(TBitField, CanAssignBitfieldsOfNonEqualSize)
{
	const int size1 = 2, size2 = 5;
	TBitField bf1(size1), result(size2);
	for (int i = 0; i < size1; i++)
	{
		bf1.SetBit(i);
	}
	result = bf1;
	EXPECT_NE(0, result.GetBit(0));
	EXPECT_NE(0, result.GetBit(1));
}

TEST(TBitField, CompareEqualBitfieldsOfEqualSize)
{
	const int size = 2;
	TBitField bf1(size), result(size);
	for (int i = 0; i < size; i++)
	{
		bf1.SetBit(i);
	}
	result = bf1;
	EXPECT_EQ(bf1, result);
}

TEST(TBitField, OrOperatorAppliedToBitfieldsOfEqualSize)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), expectedBf(size);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 0101
	bf2.SetBit(1);
	bf2.SetBit(3);
	// expectedBf = 0111
	expectedBf.SetBit(1);
	expectedBf.SetBit(2);
	expectedBf.SetBit(3);
	EXPECT_EQ(expectedBf, bf1 | bf2);
}

TEST(TBitField, OrOperatorAppliedToBitfieldsOfNonEqualSize)
{
	const int size1 = 4, size2 = 5;
	TBitField bf1(size1), bf2(size2), expectedBf(size2);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 01010
	bf2.SetBit(1);
	bf2.SetBit(3);
	// expectedBf = 01110
	expectedBf.SetBit(1);
	expectedBf.SetBit(2);
	expectedBf.SetBit(3);

	EXPECT_EQ(expectedBf, bf1 | bf2);
}

TEST(TBitField, AndOperatorAppliedToBitfieldsOfEqualSize)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), expectedBf(size);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 0101
	bf2.SetBit(1);
	bf2.SetBit(3);
	// expectedBf = 0001
	expectedBf.SetBit(3);
	EXPECT_EQ(expectedBf, bf1 & bf2);
}

TEST(TBitField, AndOperatorAppliedToBitfieldsOfNonEqualSize)
{
	const int size1 = 4, size2 = 5;
	TBitField bf1(size1), bf2(size2), expectedBf(size2);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 01010
	bf2.SetBit(1);
	bf2.SetBit(3);
	// expectedBf = 00010
	expectedBf.SetBit(1);
	expectedBf.SetBit(2);
	expectedBf.SetBit(3);
	EXPECT_EQ(expectedBf, bf1 | bf2);
}

TEST(TBitField, CanInvertBitfield)
{
	const int size = 2;
	TBitField bf(size), negativeBf(size), expectedBf(size);
	// bf = 01
	bf.SetBit(1);
	negativeBf = ~bf;
	// expectedBf = 10
	expectedBf.SetBit(0);
	EXPECT_EQ(expectedBf, negativeBf);
}

TEST(TBitField, CanInvertLargeBitfield)
{
	const int size = 38;
	TBitField bf(size), negativeBf(size), expectedBf(size);
	bf.SetBit(35);
	negativeBf = ~bf;
	for (int i = 0; i < size; i++)
		expectedBf.SetBit(i);
	expectedBf.ClearBit(35);
	EXPECT_EQ(expectedBf, negativeBf);
}

TEST(TBitField, CanInvertManyRandomBitsBitfield)
{
	const int size = 38;
	TBitField bf(size), negativeBf(size), expectedBf(size);
	std::vector<int> bits;
	bits.push_back(0);
	bits.push_back(1);
	bits.push_back(14);
	bits.push_back(16);
	bits.push_back(33);
	bits.push_back(37);
	for (unsigned int i = 0; i < bits.size(); i++)
		bf.SetBit(bits[i]);
	negativeBf = ~bf;
	for (int i = 0; i < size; i++)
		expectedBf.SetBit(i);
	for (unsigned int i = 0; i < bits.size(); i++)
		expectedBf.ClearBit(bits[i]);
	EXPECT_EQ(expectedBf, negativeBf);
}

TEST(TBitField, BitfieldsWithDifferentBitsAreNotEqual)
{
	const int size = 4;
	TBitField bf1(size), bf2(size);
	bf1.SetBit(1);
	bf1.SetBit(3);
	bf2.SetBit(1);
	bf2.SetBit(2);
	EXPECT_NE(bf1, bf2);
}



TEST(TBitFieldCustom, EmptyBitfieldsAreEqual)
{
	const int size = 4;
	TBitField bf1(size), bf2(size);
	EXPECT_EQ(bf1, bf2);
}

TEST(TBitFieldCustom, AndOperatorAppliedToEmptyBitfield)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), expectedBf(size);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	//bf2 = 0000
	EXPECT_EQ(expectedBf, bf1 & bf2);
}

TEST(TBitFieldCustom, CanCompareBitfieldsOfDifferentSizes)
{
	const int size1 = 2, size2 = 5;
	TBitField result(size1), bf(size2);
	// bf = 11
	bf.SetBit(0);
	bf.SetBit(1);
	//result = 11000
	result = bf;
	EXPECT_EQ(1, bf == result);
}
