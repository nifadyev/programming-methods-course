// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "Monom.h"

TMonom::TMonom(int coef, int ind)
{
	if (ind < -1 || ind > 999)
	{
		throw invalid_argument("Cannot create monom. Indexes of x, y and z must be more or equal 0 and less than 10");
	}

	coefficient = coef;
	index = ind;
};

TDataValue* TMonom::GetCopy() const  // Создание копии на основе Монома
{
	TDataValue *temp = new TMonom(coefficient, index);

	return temp;
}


TMonom& TMonom::operator=(const TMonom& monom)
{
	if (coefficient != monom.coefficient && index != monom.index)
	{
		coefficient = monom.coefficient;
		index = monom.index;
	}

	return *this;
}

int TMonom::operator==(const TMonom& monom)
{
	return (coefficient == monom.coefficient) && (index == monom.index);
}

int TMonom::operator<(const TMonom& monom)
{
	if (coefficient == monom.coefficient && index == monom.index)
	{
		return 0;
	}
	else if (index == monom.index)
	{
		return coefficient < monom.coefficient;
	}
	else if (coefficient == monom.coefficient)
	{
		return index < monom.index;
	}

	return index < monom.index;
}