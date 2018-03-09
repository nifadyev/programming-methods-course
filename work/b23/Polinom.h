// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <regex>
#include <string>
#include "HeadRing.h"
#include "Monom.h"

#ifndef POLINOM
#define POLINOM
class TPolinom : public THeadRing
{
public:
	TPolinom(int monoms[][2] = nullptr, int monomsNumber = 0);
	//TPolinom(int **monoms, int monomsNumber);
	TPolinom(TPolinom &polinom);
	//~TPolinom();
	pTMonom GetMonom() { return (pTMonom)GetDataValue(); }

	TPolinom& operator+(TPolinom &polinom);
	TPolinom& operator=(TPolinom &polinom);

	TPolinom& Input();
	void Print();
};
#endif
