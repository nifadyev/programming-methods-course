#include "HeadRing.h"
#include "Monom.h"

#ifndef POLINOM
#define POLINOM
class TPolinom : public THeadRing
{
public:
	TPolinom(int monoms[][2] = nullptr/*NULL*/, int monomsNumber = 0);
	TPolinom(/*const*/ TPolinom &polinom);
	pTMonom GetMonom() { return (pTMonom)GetDataValue(); }

	TPolinom& operator+(TPolinom &polinom);
	TPolinom& operator=(TPolinom &polinom);
};
#endif
