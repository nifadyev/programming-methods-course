// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
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
	TMonom(int coef = 1, int ind = 0);
	//TODO: Add copy constructor
	virtual TDataValue* GetCopy() const; // Создание копии на основе Монома

	void SetCoefficient(const int& coef) { coefficient = coef; }
	int GetCoefficient() const { return coefficient; }

	void SetIndex(const int& ind) { index = ind; }
	int GetIndex() const { return index; }

	TMonom& operator=(const TMonom& monom);
	int operator==(const TMonom& monom);
	int operator<(const TMonom& monom);

	friend class TPolinom;
};

typedef TMonom *pTMonom;
#endif