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
	//if (monoms == nullptr)
	//{
	//	listLength = monomsNumber;
	//}
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

	const int maxLength = GetListLength() > polinom.GetListLength() ? GetListLength() : polinom.GetListLength();
	TPolinom *result = new TPolinom(nullptr, maxLength);

	for (int i = 0; i < maxLength; i++)
	{
		if (IsListEnded() || polinom.IsListEnded())
		{
			if (IsListEnded())
			{
				result->InsertAfterLast(polinom.GetDataValue());
			}

			if (polinom.IsListEnded())
			{
				result->InsertAfterLast(GetDataValue());
			}
			continue;
		}
		//if (!IsListEnded())
		//{
		//	SetCurrentPosition(i);
		//}
		//if (!polinom.IsListEnded())
		//{
		//	polinom.SetCurrentPosition(i);
		//}
		SetCurrentPosition(i);
		polinom.SetCurrentPosition(i);
		TMonom *lhs = GetMonom();
		TMonom *rhs = polinom.GetMonom();

		if (lhs->GetIndex() > rhs->GetIndex())
		{
			result->InsertAfterLast(lhs->GetCopy());
			continue;
		}

		else if (lhs->GetIndex() == rhs->GetIndex())
		{
			TMonom *temp = lhs; // Could be incorrent
			if (lhs->GetCoefficient() != rhs->GetCoefficient())
			{

				temp->SetCoefficient(lhs->GetCoefficient() + rhs->GetCoefficient());
				//result->InsertAfterLast(temp->GetCopy());
			}
			
			if (result->GetMonom()->GetCoefficient() >= temp->GetCoefficient())
			{
				result->InsertAfterLast(temp->GetCopy());
			}

			else
			{
				result->InsertBeforeCurrent(temp->GetCopy());
			}

			continue;
		}

		else /*if (lhs->GetIndex() < rhs->GetIndex())*/
		{
			result->InsertAfterLast(rhs->GetCopy());
			continue;
		}
	}


	return *result;
}

TPolinom & TPolinom::operator=(TPolinom & polinom)
{
	if (polinom.IsEmpty())
	{
		DeleteList();
		Reset();
		return *this;
	}

	DeleteList();
	for (polinom.Reset(); !polinom.IsListEnded(); polinom.MoveNext())
	{
		InsertAfterLast(polinom.GetDataValue());
	}

	return *this;
}
