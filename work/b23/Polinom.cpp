#include "Polinom.h"

TPolinom::TPolinom(int monoms[][2], int monomsNumber)/* : THeadRing()*/
{
	if (monomsNumber < 0)
	{
		throw invalid_argument("Error! Number of monoms must be positive");
	}
	//listLength = monomsNumber;
	TMonom *head = new TMonom(0, -1);
	pHead = new TDataLink();
	pHead->SetDataValue(head->GetCopy());

	if (monoms != nullptr)
	{
		for (int i = 0; i < monomsNumber; i++)
		{
			TMonom *monom = new TMonom(monoms[i][0], monoms[i][1]);
			InsertAfterLast(monom->GetCopy());
		}
	}

	Reset();
}

TPolinom::TPolinom(/*const*/ TPolinom& polinom)
{
	if (polinom.IsEmpty())
	{
		return;
	}

	else
	{
		pHead = new TDataLink();
		pHead->SetDataValue(polinom.pHead->GetDataValue());

		for (int i = 0; i < polinom.GetListLength(); i++)
		{
			polinom.SetCurrentPosition(i);
			InsertAfterLast(polinom.GetDataValue(CURRENT));
		}
		polinom.Reset();
	}
}

//TPolinom::~TPolinom()
//{
//	DeleteList();
//	if (pHead != nullptr)
//	{
//		DeleteLink(pHead);
//	}
//	//pHead = nullptr;
//}

TPolinom& TPolinom::operator+(TPolinom & polinom)
{
	if (polinom.IsEmpty())
	{
		return *this;
	}
	
	if (IsEmpty())
	{
		return polinom;
	}

	TMonom *lhs, *rhs, *currentMonom;
	Reset(); polinom.Reset();
	//После вставки 121 curPos = 9, length = 8
	while (true)
	{
		if (IsListEnded() || polinom.IsListEnded())
		{
			if (IsListEnded() && polinom.IsListEnded())
			{
				break;
			}

			else if (IsListEnded())
			{
				//rhs = polinom.GetMonom();
				//InsertBeforeCurrent(rhs);
				//continue;
				//break;
			}
			else if (polinom.IsListEnded())
			{
				break;
			}

			//break;
		}
		lhs = GetMonom();
		rhs = polinom.GetMonom();

		if (rhs->GetIndex() > lhs->GetIndex())
		{
			currentMonom = new TMonom(rhs->GetCoefficient(), rhs->GetIndex());
			if ((GetDataValue(CURRENT) == GetDataValue(LAST) /*&&GetListLength()!=1*/) /*&& !polinom.IsListEnded()*/)
			{
				InsertBeforeCurrent(currentMonom);
				polinom.MoveNext();
				continue;
			}
			InsertBeforeCurrent(currentMonom);
			//currentPosition++;

			MoveNext();
			polinom.MoveNext();
		}

		else if (rhs->GetIndex() < lhs->GetIndex())
		{
			//на pLast сдвинулись на pStop
			// поетому plast из polinom не добавился
			if (GetDataValue(CURRENT) == GetDataValue(LAST))
			{
				currentMonom = new TMonom(rhs->GetCoefficient(), rhs->GetIndex());
				InsertAfterLast(currentMonom);
				//MoveNext();
				polinom.MoveNext();
				continue;
			}
			MoveNext();
		}

		else
		{
			if (lhs->GetIndex() == -1) // pHead
			{
				break;
			}

			lhs->SetCoefficient(lhs->GetCoefficient() + rhs->GetCoefficient());

			if (lhs->GetCoefficient() != 0)
			{
				MoveNext();
				polinom.MoveNext();
			}

			else
			{
				DeleteCurrent();
				polinom.MoveNext();
			}
			
		}
	}

	return *this;
}

TPolinom & TPolinom::operator=(TPolinom & polinom)
{
	TPolinom *temp = new TPolinom(polinom);

	if (temp->IsEmpty())
	{
		DeleteList();
		Reset();
		return *this;
	}

	DeleteList();
	for (temp->Reset(); !temp->IsListEnded(); temp->MoveNext())
	{
		InsertAfterLast(temp->GetDataValue());
	}
	temp->DeleteList();

	return *this;
}
