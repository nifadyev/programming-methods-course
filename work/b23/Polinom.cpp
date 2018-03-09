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

//TPolinom::TPolinom(int **monoms, int monomsNumber)/* : THeadRing()*/
//{
//	if (monomsNumber < 0)
//	{
//		throw invalid_argument("Error! Number of monoms must be positive");
//	}
//	//listLength = monomsNumber;
//	TMonom *head = new TMonom(0, -1);
//	pHead = new TDataLink();
//	pHead->SetDataValue(head->GetCopy());
//
//	if (monoms != nullptr)
//	{
//		for (int i = 0; i < monomsNumber; i++)
//		{
//			TMonom *monom = new TMonom(monoms[i][0], monoms[i][1]);
//			InsertAfterLast(monom->GetCopy());
//		}
//	}
//
//	Reset();
//}

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
	//if (IsEmpty() && temp->IsEmpty())
	//{
	//	return *this;
	//}
	//if (IsEmpty())
	//{
	//	return polinom;
	//}
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

TPolinom& TPolinom::Input()
{
	smatch result;
	string input;
	regex monom("(\\+?-?\\d+)\\*x\\^?([0-9]{1})\\*y\\^?([0-9]{1})\\*z\\^?([0-9]{1})");
	int monoms[20][2] = { 0 };
	int monomsNumber = 0;

	cout << "\n----------------------Polinom input----------------------\n";
	cout << "Print q to exit\n";
	cout << "Filling polinom(max number of monoms: 20)\n";
	cout << "Example: +|-1*x^2*y^3*z^4\n";
	while (true)
	{
		cout << "Enter monom: ";
		getline(cin, input);

		if (input == "q")
		{
			input.clear();
			break;
		}

		string::const_iterator begin = input.cbegin();
		string::const_iterator end = input.cend();

		for (; regex_search(begin, end, result, monom); begin = result.suffix().first)
		{
			//int index = atoi(result[2].str().c_str()) * 100 + atoi(result[3].str().c_str()) * 10 + atoi(result[4].str().c_str());
			//int coefficient = atoi(result[1].str().c_str());
			//cout << coefficient << endl;
			//cout << index << endl;
			monoms[monomsNumber][0] = atoi(result[1].str().c_str());
			monoms[monomsNumber][1] = atoi(result[2].str().c_str()) * 100 + atoi(result[3].str().c_str()) * 10 + atoi(result[4].str().c_str());
			monomsNumber++;
		}

		input.clear();
	}
	cout << "Filling polinom is finished\n";
	TPolinom polinom(monoms, monomsNumber);
	
	*this = polinom;

	return *this;
}

void TPolinom::Print()
{
	Reset();

	for (int i = 0; !IsListEnded()/*i < GetListLength() - 1*/; i++)
	{
		cout << GetMonom()->GetCoefficient() << "*x^" << GetMonom()->GetIndex() / 100 << "*y^" << (GetMonom()->GetIndex() % 100) / 10 << "*z^" << GetMonom()->GetIndex() % 10;
		MoveNext();
		if (!IsListEnded())
		{
			if (GetMonom()->GetCoefficient() >= 0)
			{
				cout << " +";
			}
			else
			{
				cout << " ";
			}			
		}	
	}

	cout << endl;
}
