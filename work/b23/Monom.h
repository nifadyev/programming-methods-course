// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//#include <iostream>
#include "DataValue.h"
using namespace std;
#ifndef TMONOM
#define TMONOM
class TMonom : public TDataValue
{
protected: 
	int coefficient;
	int index; // Сумма степеней (x^A * y^B * z^C => index = A * 100+ B * 10 + C)

public:
	TMonom(int coef = 1, int ind = 0)
	{
		if (ind < 0 || ind > 999)
		{
			throw invalid_argument("Cannot create monom. Indexes of x, y and z must be more or equal 0 and less than 10");
		}

		coefficient = coef;
		index = ind;
	};

	virtual TDataValue* GetCopy() const // Создание копии на основе Монома
	{
		TDataValue *temp = new TMonom(coefficient, index);
		return temp;
	}

	void SetCoefficient(const int& coef) { coefficient = coef; }
	int GetCoefficient() const { return coefficient; }

	void SetIndex(const int& ind) { index = ind; }
	int GetIndex() const { return index; }

	TMonom& operator=(const TMonom& monom)
	{
		if (coefficient != monom.coefficient && index != monom.index)
		{
			coefficient = monom.coefficient;
			index = monom.index;
		}
		return *this;
	}

	int operator==(const TMonom& monom)
	{
		return (coefficient == monom.coefficient) && (index == monom.index);
	}

	int operator<(const TMonom& monom)
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

	friend class TPolinom;
};

typedef TMonom *pTMonom;
#endif