#include "Polinom.h"

TPolinom::TPolinom(int monoms[][2], int monomsNumber)/* : THeadRing()*/
{
	if (monomsNumber < 0)
	{
		throw invalid_argument("Error! Number of monoms must be positive");
	}

	TMonom *head = new TMonom(0, -1);
	pHead = new TDataLink(head->GetCopy());

	for (int i = 0; i < monomsNumber; i++)
	{
		TMonom *monom = new TMonom(monoms[i][0], monoms[i][1]);
		InsertAfterLast(monom->GetCopy());
	}
}

TPolinom::TPolinom(/*const*/ TPolinom& polinom)
{
	if (polinom.IsEmpty())
	{
		//TPolinom();
		//DeleteList();
		return;
	}

	else
	{
		pHead = polinom.pHead;

		for (int i = 0; i < polinom.GetListLength(); i++)
		{
			//polinom.SetCurrentPosition(i);
			InsertAfterLast(polinom.GetDataValue(CURRENT));
			polinom.MoveNext();
		}
	}
}

TPolinom & TPolinom::operator+(TPolinom & polinom)
{
	// TODO: вставьте здесь оператор return
	return *this;
}

TPolinom & TPolinom::operator=(TPolinom & polinom)
{
	// TODO: вставьте здесь оператор return
	return *this;
}
