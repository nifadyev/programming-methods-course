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

//TPolinom& TPolinom::operator+(TPolinom & polinom)
//{
//	TPolinom res(*this);
//	res.Reset();
//	polinom.Reset();
//	while (true)
//	{
//		TMonom *left = res.GetMonom();
//		TMonom *right = polinom.GetMonom();
//		if (right < left)
//		{
//			res.MoveNext();
//
//		}
//		else if (left < right)
//		{
//			res.InsertBeforeCurrent(right->GetCopy());
//			polinom.MoveNext();
//
//		}
//		else
//		{
//			if (left->GetIndex() == -1) break;
//			int resCoeff = left->GetCoefficient() + right->GetCoefficient();
//			if (resCoeff == 0)
//			{
//				res.DeleteCurrent();
//				polinom.MoveNext();
//			}
//			else
//			{
//				left->SetCoefficient(resCoeff);
//				res.MoveNext(); polinom.MoveNext();
//			}
//		}
//	}
//	return res;
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
			}
			else if (polinom.IsListEnded())
			{

			}

			//break;
		}
		lhs = GetMonom();
		rhs = polinom.GetMonom();
		//if (IsListEnded())
		//{
		//	break;
		//}

		if (rhs->GetIndex() > lhs->GetIndex())
		{
			currentMonom = new TMonom(rhs->GetCoefficient(), rhs->GetIndex());
			InsertBeforeCurrent(currentMonom);
			currentPosition++;
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
				MoveNext();
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
			//if (IsListEnded() /*|| polinom.IsListEnded()*/)
			//{
			//	break;
			//}
	}

	return *this;
}

//TPolinom& TPolinom::operator+(TPolinom & polinom)
//{
//	//TODO: pHead does not have pNext
//
//	if (polinom.IsEmpty())
//	{
//		return *this;
//	}
//
//	if (IsEmpty())
//	{
//		return polinom;
//	}
//
//	TPolinom *result = new TPolinom();
//	TMonom *lhs, *rhs, *currentMonom;
//	bool IsFilled = true;
//
//	Reset(); polinom.Reset();
//	while(!(IsListEnded() && polinom.IsListEnded()))
//	{
//		//SetCurrentPosition(i);
//		//polinom.SetCurrentPosition(i);
//		if (IsEmpty())
//		{
//			lhs = GetMonom();
//			rhs = polinom.GetMonom();
//			if (lhs->GetIndex() > rhs->GetIndex())
//			{
//				result->InsertAfterLast(lhs->GetCopy());
//				//MoveNext();
//				continue;
//			}
//
//			else if (lhs->GetIndex() == rhs->GetIndex())
//			{
//				TMonom *temp = lhs; // Could be incorrent
//				if (lhs->GetCoefficient() != rhs->GetCoefficient())
//				{
//
//					temp->SetCoefficient(lhs->GetCoefficient() + rhs->GetCoefficient());
//					//result->InsertAfterLast(temp->GetCopy());
//				}
//
//				if (result->GetMonom()->GetCoefficient() >= temp->GetCoefficient())
//				{
//					result->InsertAfterLast(temp->GetCopy());
//				}
//
//				else
//				{
//					result->InsertBeforeCurrent(temp->GetCopy());
//				}
//				//MoveNext();
//				//polinom.MoveNext();
//				continue;
//			}
//
//			else /*if (lhs->GetIndex() < rhs->GetIndex())*/
//			{
//				result->InsertAfterLast(rhs->GetCopy());
//				//polinom.MoveNext();
//				continue;
//			}
//		}
//			if (IsListEnded() || polinom.IsListEnded())
//			{
//				if (IsListEnded() && polinom.IsListEnded())
//				{
//					break;
//				}
//
//				else if (IsListEnded())
//				{
//					result->InsertAfterLast(polinom.GetDataValue());
//					continue;
//				}
//
//				else if (polinom.IsListEnded())
//				{
//					result->InsertAfterLast(GetDataValue());
//					continue;
//				}
//				/*continue;*/
//			}
//
//			MoveNext();
//			polinom.MoveNext();
//		
//		lhs = GetMonom();
//		rhs = polinom.GetMonom();
//
//
//
//		if (lhs->GetIndex() > rhs->GetIndex())
//		{
//			result->InsertAfterLast(lhs->GetCopy());
//			//MoveNext();
//			continue;
//		}
//
//		else if (lhs->GetIndex() == rhs->GetIndex())
//		{
//			TMonom *temp = lhs; // Could be incorrent
//			if (lhs->GetCoefficient() != rhs->GetCoefficient())
//			{
//
//				temp->SetCoefficient(lhs->GetCoefficient() + rhs->GetCoefficient());
//				//result->InsertAfterLast(temp->GetCopy());
//			}
//			
//			if (result->GetMonom()->GetCoefficient() >= temp->GetCoefficient())
//			{
//				result->InsertAfterLast(temp->GetCopy());
//			}
//
//			else
//			{
//				result->InsertBeforeCurrent(temp->GetCopy());
//			}
//			//MoveNext();
//			//polinom.MoveNext();
//			continue;
//		}
//
//		else /*if (lhs->GetIndex() < rhs->GetIndex())*/
//		{
//			result->InsertAfterLast(rhs->GetCopy());
//			//polinom.MoveNext();
//			continue;
//		}
//		
//	}
//
//
//	return *result;
//}

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
