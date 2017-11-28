#include <gtest/gtest.h>
#include "tformula.h"

using namespace std;

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
	int intExpression[25] {};
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