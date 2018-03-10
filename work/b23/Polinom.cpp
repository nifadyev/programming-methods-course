#include "Polinom.h"

TPolinom::TPolinom(int monoms[][2], int monomsNumber)
{
	if (monomsNumber < 0)
	{
		throw invalid_argument("Error! Number of monoms must be positive");
	}

	TMonom *head = new TMonom(0, -1);
	pHead = new TDataLink();
	pHead->SetDataValue(head->GetCopy());
	delete head;

	if (monoms != nullptr)
	{
		for (int i = 0; i < monomsNumber; i++)
		{
			TMonom *monom = new TMonom(monoms[i][0], monoms[i][1]);
			InsertAfterLast(monom->GetCopy());
			delete monom;
		}
	}
	Reset();
}

TPolinom::TPolinom(TPolinom& polinom)
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

	Reset(); 
	polinom.Reset();

	while (true)
	{		
		if (IsListEnded() || polinom.IsListEnded())
		{
			break;
		}

		TMonom *lhs = GetMonom(), *rhs = polinom.GetMonom(), *currentMonom;

		if (rhs->GetIndex() > lhs->GetIndex())
		{
			currentMonom = new TMonom(rhs->GetCoefficient(), rhs->GetIndex());
			InsertBeforeCurrent(currentMonom);
			polinom.MoveNext();
			if (GetDataValue(CURRENT) != GetDataValue(LAST))
			{
				MoveNext();
			}
		}

		else if (rhs->GetIndex() < lhs->GetIndex())
		{
			if (GetDataValue(CURRENT) == GetDataValue(LAST))
			{
				currentMonom = new TMonom(rhs->GetCoefficient(), rhs->GetIndex());
				InsertAfterLast(currentMonom);
				polinom.MoveNext();
				continue;
			}

			MoveNext();
		}

		else
		{
			if (lhs->GetIndex() == -1)
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

TPolinom& TPolinom::operator=(TPolinom & polinom)
{
	if (this == &polinom)
	{
		return *this;
	}

	DeleteList();
	TPolinom *temp = new TPolinom(polinom);

	if (temp->IsEmpty())
	{		
		Reset();
		delete temp;

		return *this;
	}

	for (temp->Reset(); !temp->IsListEnded(); temp->MoveNext())
	{
		InsertAfterLast(temp->GetDataValue());
	}
	temp->DeleteList();
	delete temp;

	return *this;
}

TPolinom& TPolinom::Input()
{
	int monoms[20][2] = { 0 };
	int monomsNumber = 0;
	smatch result;
	string input;
	regex monom("(\\+?-?\\d+)\\*x\\^?([0-9]{1})\\*y\\^?([0-9]{1})\\*z\\^?([0-9]{1})");

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
			monoms[monomsNumber][0] = atoi(result[1].str().c_str());
			monoms[monomsNumber][1] = atoi(result[2].str().c_str()) * 100 + atoi(result[3].str().c_str()) * 10 + atoi(result[4].str().c_str());
			monomsNumber++;
		}

		input.clear();
	}

	cout << "Filling polinom is finished\n";

	TPolinom *polinom = new TPolinom(monoms, monomsNumber);
	*this = *polinom;
	polinom->DeleteList();
	delete polinom;

	return *this;
}

void TPolinom::Print()
{
	Reset();
	if (IsEmpty())
	{
		cout << "0\n";
		return;
	}

	while(!IsListEnded())
	{
		cout << GetMonom()->GetCoefficient() << "*x^" << GetMonom()->GetIndex() / 100 << "*y^" << (GetMonom()->GetIndex() % 100) / 10 
			 << "*z^" << GetMonom()->GetIndex() % 10;

		MoveNext();
		if (IsListEnded())
		{
			break;

		}	

		(GetMonom()->GetCoefficient() >= 0) ? cout << " +" : cout << " ";
	}

	cout << endl;
}

int TPolinom::Calculate(const int x, const int y, const int z)
{
	Reset();

	if (IsEmpty())
	{
		return 0;
	}

	int result = 0;

	while (!IsListEnded())
	{
		result += GetMonom()->GetCoefficient() * pow(x, GetMonom()->GetIndex() / 100)* pow(y, (GetMonom()->GetIndex() % 100) / 10)
			* pow(z, GetMonom()->GetIndex() % 10);
		MoveNext();

		if (IsListEnded())
		{
			break;

		}
	}

	return result;
}
