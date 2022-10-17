#include <iostream>
#include "DatValue.h"
using namespace std;

#ifndef TMONOM
#define TMONOM
class TMonom : public TDataValue
{
protected:
	int coefficient;
	int index; // ����� �������� (x^A * y^B * z^C => index = A * 100+ B * 10 + C)

public:
	TMonom(int coef = 1, int ind = 0);
	//TODO: Add copy constructor
	virtual TDataValue* GetCopy() const; // �������� ����� �� ������ ������

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
