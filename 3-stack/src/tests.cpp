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




TEST(TFormula, CanCreateFormula)
{
	char* expression = "55+(4*8)";

	ASSERT_NO_THROW(TFormula formula(expression));
}

TEST(TFormula, ThrowWnenCreateFormulaFromEmptyString)
{
	char* expression = "";

	ASSERT_THROW(TFormula formula(expression), invalid_argument);
}

TEST(TFormula, ThrowWnenCreateFormulaFromTooBigString)
{
	char expression[256] = {};

	ASSERT_THROW(TFormula formula(expression), invalid_argument);
}

TEST(TFormula, CanCheckFormula)
{
	char* expression = "(a+b1)/2+6.5)*(4.8+sin(x)";
	int intExpression[25]{};
	TFormula formula(expression);

	for (unsigned int i = 0; i < strlen(expression); i++)
	{
		intExpression[i] = (int)expression[i];
	}

	ASSERT_NO_THROW(formula.FormulaChecker(intExpression, strlen(expression)));
}

TEST(TFormula, CanCatchErrorsFromFormulaWithForbiddenSymbols)
{
	char* expression = "~2134..12><4+-3535/436,34s";
	int intExpression[27]{};
	int expectedErrors = 6;
	TFormula formula(expression);

	for (unsigned int i = 0; i < strlen(expression); i++)
	{
		intExpression[i] = (int)expression[i];
	}

	EXPECT_EQ(expectedErrors, formula.FormulaChecker(intExpression, strlen(expression)));
}

TEST(TFormula, CanCatchErrorsWhileCheckingFormula)
{
	char* expression = "(23+41)/2+6.5)*(4.8+(2.3)";
	int intExpression[26]{};
	int expectedErrors = 2;
	TFormula formula(expression);

	for (unsigned int i = 0; i < strlen(expression); i++)
	{
		intExpression[i] = (int)expression[i];
	}

	EXPECT_EQ(expectedErrors, formula.FormulaChecker(intExpression, strlen(expression)));
}

TEST(TFormula, ThrowWhenCheckingFormulaWithNegativeSize)
{
	char* expression = "(a+b1)/2+6.5)*(4.8+sin(x)";
	int intExpression[25]{};
	TFormula formula(expression);

	for (unsigned int i = 0; i < strlen(expression); i++)
	{
		intExpression[i] = (int)expression[i];
	}

	ASSERT_THROW(formula.FormulaChecker(intExpression, -7), invalid_argument);
}

TEST(TFormula, CanConvertFormula)
{
	char* expression = "(1+2)/(3+4*6.7)-5.3*4.4";
	int intExpression[24]{};
	TFormula formula(expression);

	for (unsigned int i = 0; i < strlen(expression); i++)
	{
		intExpression[i] = (int)expression[i];
	}

	ASSERT_NO_THROW(formula.FormulaConverter());
	// 1 2+ 3 4 6.7*+/ 5.3 4.4* -
}

TEST(TFormula, CannotConvertWrongFormula)
{
	char* expression = "(1+2)/(3+4*6.7)-5.3*(4.4";
	int intExpression[25]{};
	TFormula formula(expression);

	for (unsigned int i = 0; i < strlen(expression); i++)
	{
		intExpression[i] = (int)expression[i];
	}

	EXPECT_EQ(formula.FormulaConverter(), 1);
	// 1 2+ 3 4 6.7*+/ 5.3 4.4* -
}

TEST(TFormula, CanCalculateFormula)
{
	char* expression = "(1+2)/(3+4*6.7)-5.3*4.4";
	TFormula formula(expression);

	if (formula.FormulaConverter() == 0)
	{
		ASSERT_NO_THROW(formula.FormulaCalculator());
	}
}

TEST(TFormula, CalculatedFormulaIsEqualToAnswer)
{
	char* expression = "(7.5+8.1)/(3+4*6.7)-5.3*4.4";
	TFormula formula(expression);
	float expectedResult = -22.82f;
	float inaccuracy = 0.01f; // Погрешность
	if (formula.FormulaConverter() == 0)
	{
		EXPECT_NEAR(formula.FormulaCalculator(), expectedResult, inaccuracy);
		/* 15.6 / 31.2 - 23.32 = 0.5 - 23.32 = -22.82*/
	}
}