#include <iostream>
#include "tproc.h"

using namespace std;

TProc::TProc(int clocks, float productivity)
{
	if (clocks < 0)
	{
		throw invalid_argument("Amount of clocks must be positive");
	}
	if (productivity < 0.0f || productivity > 1.0f)
	{
		throw invalid_argument("Productivity must be more than 0 and less than 1");
	}

	this->clocks = clocks;
	this->productivity = productivity;
}

bool TProc::TaskIsReady(float factor)
{
	return factor < productivity;
}