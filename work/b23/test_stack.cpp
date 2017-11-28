#define _SCL_SECURE_NO_WARNINGS

#include <gtest/gtest.h>
#include <iostream>
#include "tstack.h"
#include "tformula.h"

using namespace std;

//Тестирование класса TStack
TEST(TStack, CanCreateStack)
{
	TStack stack(5);

	ASSERT_NO_THROW(stack);
}

TEST(TStack, ThrowsWhenCreateStackWithNegativeSize)
{
	ASSERT_ANY_THROW(TStack stack(-1));
}

TEST(TStack, IsEmptyReturnsTrue)
{
	TStack stack(5);

	EXPECT_TRUE(stack.IsEmpty());
}

TEST(TStack, IsEmptyReturnsFalse)
{
	TStack stack(2);
	stack.Put(1);

	EXPECT_FALSE(stack.IsEmpty());
}

TEST(TStack, IsFullReturnsTrue)
{
	TStack stack(3);
	stack.Put(1);
	stack.Put(7);
	stack.Put(2);

	EXPECT_TRUE(stack.IsFull());
}

TEST(TStack, IsFullReturnsFalse)
{
	TStack stack(3);
	stack.Put(1);
	stack.Put(7);

	EXPECT_FALSE(stack.IsFull());
}

TEST(TStack, CanPutIntoStack)
{
	TStack stack(3);

	ASSERT_NO_THROW(stack.Put(2));
}

TEST(TStack, AddedElementIsEqualToSourceOne)
{
	int expectedResult = 2;
	TStack stack(3);
	stack.Put(2);

	EXPECT_EQ(stack.Get(), expectedResult);
}

TEST(TStack, ThrowWhenTryingToPutIntoFullStack)
{
	TStack stack(1);
	stack.Put(7);

	ASSERT_ANY_THROW(stack.Put(5));
}

TEST(TStack, ThrowWhenTryingToPutIntoStackWithoutMemory)
{
	TStack stack(0);

	ASSERT_ANY_THROW(stack.Put(1));
}

TEST(TStack, CanGetFromStack)
{
	TStack stack(3);
	stack.Put(1);
	stack.Put(10);
	stack.Put(-1);

	ASSERT_NO_THROW(stack.Get());
}

TEST(TStack, GetElementIsEqualToSourceOne)
{
	int expectedResult = 10;
	TStack stack(3);
	stack.Put(1);
	stack.Put(10);

	EXPECT_EQ(stack.Get(), expectedResult);
}

TEST(TStack, ThrowWhenTryingToGetFromEmptyStack)
{
	TStack stack(1);
	
	ASSERT_ANY_THROW(stack.Get());
}

TEST(TStack, ThrowWhenTryingToGetFromStackWithoutMemory)
{
	TStack stack(0);

	ASSERT_ANY_THROW(stack.Get());
}

TEST(TStack, IsValidReturnDataOK)
{
	TStack stack(3);

	EXPECT_EQ(stack.GetRetCode(), stack.IsValid());
}

TEST(TStack, IsValidReturnDataFull)
{
	TStack stack(1);
	stack.Put(3);

	EXPECT_EQ(stack.GetRetCode(), stack.IsValid());
}

TEST(TStack, IsValidReturnDataEmpty)
{
	TStack stack(1);
	
	EXPECT_EQ(stack.GetRetCode(), stack.IsValid());
}

TEST(TStack, IsValidReturnDataNoMem)
{
	TStack stack(0);
	
	EXPECT_EQ(stack.GetRetCode(), stack.IsValid());
}




//Тестирование шаблонного класса Stack
TEST(Stack, CanCreateStack)
{
	ASSERT_NO_THROW(Stack<float> stack(5));
}

TEST(Stack, ThrowWhenCreateStackWithNegativeSize)
{
	ASSERT_ANY_THROW(Stack<float> stack(-1));
}

TEST(Stack, IsEmptyReturnsTrue)
{
	Stack<float> stack(5);

	EXPECT_TRUE(stack.IsEmpty());
}

TEST(Stack, IsEmptyReturnsFalse)
{
	Stack<double> stack(2);
	stack.Put(-13.33);

	EXPECT_FALSE(stack.IsEmpty());
}

TEST(Stack, IsFullReturnsTrue)
{
	Stack<double> stack(3);
	stack.Put(22.194);
	stack.Put(0.8332);
	stack.Put(-4.41222);

	EXPECT_TRUE(stack.IsFull());
}

TEST(Stack, IsFullReturnsFalse)
{
	Stack<double> stack(3);
	stack.Put(5.9933);
	stack.Put(-0.12467);

	EXPECT_FALSE(stack.IsFull());
}

TEST(Stack, CanPutIntoStack)
{
	Stack<double> stack(5);

	ASSERT_NO_THROW(stack.Put(0.2));
}

TEST(Stack, AddedElementIsEqualToSourceOne)
{
	double expectedResult = 0.2;
	Stack<double> stack(3);
	stack.Put(5.5);
	stack.Put(0.222);
	stack.Put(0.2);

	EXPECT_EQ(stack.Get(), expectedResult);
}

TEST(Stack, ThrowWhenTryingToPutIntoFullStack)
{
	Stack<double> stack(1);
	stack.Put(0.0001);

	ASSERT_ANY_THROW(stack.Put(-243.3535));
}

TEST(Stack, ThrowWhenTryingToPutIntoStackWithoutMemory)
{
	Stack<double> stack(0);

	ASSERT_ANY_THROW(stack.Put(1.1578));
}

TEST(Stack, CanGetFromStack)
{
	Stack<double> stack(3);
	stack.Put(8.66);

	ASSERT_NO_THROW(stack.Get());
}

TEST(Stack, GetElementIsEqualToSourceOne)
{
	double expectedResult = 10.33;
	Stack<double> stack(3);
	stack.Put(1);
	stack.Put(10.33);

	EXPECT_EQ(stack.Get(), expectedResult);
}

TEST(Stack, ThrowWhenTryingToGetFromEmptyStack)
{
	Stack<double> stack(1);

	ASSERT_ANY_THROW(stack.Get());
}

TEST(Stack, ThrowWhenTryingToGetFromStackWithoutMemory)
{
	Stack<double> stack(0);

	ASSERT_ANY_THROW(stack.Get());
}
