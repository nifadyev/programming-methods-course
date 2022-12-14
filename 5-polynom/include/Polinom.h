#include <regex>
#include <string>
#include <cmath>
#include "HeadRing.h"
#include "Monom.h"

#ifndef POLINOM
#define POLINOM
class TPolinom : public THeadRing
{
public:
	TPolinom(int monoms[][2] = nullptr, int monomsNumber = 0);
	TPolinom(TPolinom &polinom);

	pTMonom GetMonom() { return (pTMonom)GetDataValue(); }

	TPolinom& operator+(TPolinom &polinom);
	TPolinom& operator=(TPolinom &polinom);

	TPolinom& Input();
	void Print();
	int Calculate(const int x, const int y, const int z);
};
#endif
