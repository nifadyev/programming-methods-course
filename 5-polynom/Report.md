# Отчет по лабораторной работе №4: Полином
__Выполнил:__ студент группы 381608-1 Нифадьев Вадим
## Цели и задачи
В рамках лабораторной работы ставится задача создания программных средств, поддерживающих эффективное представление полиномов и выполнение следующих операций над ними:
* ввод полинома 
* организация хранения полинома
* удаление введенного ранее полинома;
* копирование полинома;
* сложение двух полиномов;
* вычисление значения полинома при заданных значениях переменных;
* вывод.

Предполагается, что в качестве структуры хранения будут использоваться списки.
 В качестве дополнительной цели в лабораторной работе ставится также задача разработки некоторого общего представления списков и операций по их обработке. В числе операций над списками должны быть реализованы следующие действия:
* поддержка понятия текущего звена;
* вставка звеньев в начало, после текущей позиции и в конец списков;
* удаление звеньев в начале и в текущей позиции списков;
* организация последовательного доступа к звеньям списка (итератор).

В ходе выполнения лабораторной работы должно быть выполнено сопоставление разработанных средств работы со списками с возможностями работы со списками в библиотеке STL.
Важной частью лабораторной работы должна являться разработка диалоговой управляющей программы с наглядным визуальным интерфейсом, который обеспечивает возможности создавать полиномы, выполнять реализованные операции обработки полиномов, демонстрировать вид имеющихся полиномов. 

## Описание работы
### Реализация класса `TMonom`
#### monom.h
```C++
#include <iostream>
#include "DataValue.h"
using namespace std;

#ifndef TMONOM
#define TMONOM
class TMonom : public TDataValue
{
protected: 
	int coefficient;
	int index;

public:
	TMonom(int coef = 1, int ind = 0);
	//TODO: Add copy constructor
	virtual TDataValue* GetCopy() const;

	void SetCoefficient(const int& coef) { coefficient = coef; }
	int GetCoefficient() const { return coefficient; }

	void SetIndex(const int& ind) { index = ind; }
	int GetIndex() const { return index; }

	TMonom& operator=(const TMonom& monom);
	int operator==(const TMonom& monom);
	int operator<(const TMonom& monom);

	friend class TPolinom;
};

typedef TMonom *pTMonom;
#endif
```

#### monom.cpp
```C++
#include "Monom.h"

TMonom::TMonom(int coef, int ind)
{
	if (ind < -1 || ind > 999)
	{
		throw invalid_argument("Cannot create monom. Indexes of x, y and z must be more or equal 0 and less than 10");
	}

	coefficient = coef;
	index = ind;
};

TDataValue* TMonom::GetCopy() const  // Создание копии на основе Монома
{
	TDataValue *temp = new TMonom(coefficient, index);

	return temp;
}


TMonom& TMonom::operator=(const TMonom& monom)
{
	if (coefficient != monom.coefficient && index != monom.index)
	{
		coefficient = monom.coefficient;
		index = monom.index;
	}

	return *this;
}

int TMonom::operator==(const TMonom& monom)
{
	return (coefficient == monom.coefficient) && (index == monom.index);
}

int TMonom::operator<(const TMonom& monom)
{
	if (coefficient == monom.coefficient && index == monom.index)
	{
		return 0;
	}
	else if (index == monom.index)
	{
		return coefficient < monom.coefficient;
	}
	else if (coefficient == monom.coefficient)
	{
		return index < monom.index;
	}

	return index < monom.index;
}
```

### Реализация класса `TDataList`
#### datalist.h
```C++
#include <iostream>
#include "DataLink.h"
using namespace std;

#ifndef TDATALIST
#define TDATALIST
enum TLinkPos { FIRST, CURRENT, LAST };

class TDataList
{
protected:
	pTDataLink pFirst;
	pTDataLink pLast;
	pTDataLink pCurrentLink;
	pTDataLink pPreviousLink;
	pTDataLink pStop; // Указатель на элемент, означающий конец списка

	int currentPosition; // Итератор
	int listLength;

	pTDataLink GetLink(pTDataValue pVal = nullptr, pTDataLink pLink = nullptr);
	void DeleteLink(pTDataLink pLink);

	void InsertIntoEmptyList(pTDataValue pVal);
public:
	TDataList();
	~TDataList() { DeleteList(); }
	 
	pTDataValue GetDataValue(TLinkPos mode = CURRENT) const;
	virtual bool IsEmpty() const { return  pFirst == pStop; }

	int GetListLength() const { return listLength; }

	void SetCurrentPosition(const int& position);
	int GetCurrentPosition() const;

	virtual void Reset(); 
	virtual bool IsListEnded() const;
	void MoveNext(); // Сдвиг вправо текущего звена 

	virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
	virtual void InsertAfterLast(pTDataValue pVal = nullptr);
	virtual void InsertBeforeCurrent(pTDataValue pVal = nullptr);

	virtual void DeleteFirst();
	virtual void DeleteCurrent();
	virtual void DeleteList();
};
typedef TDataList *pTDataList;
#endif
```

#### datalist.cpp
```C++
#include "DataList.h"

pTDataLink TDataList::GetLink(pTDataValue pVal, pTDataLink pLink)
{
	TDataLink *temp = new TDataLink(pVal, pLink);
	return temp;
}

void TDataList::DeleteLink(pTDataLink pLink)
{
	delete pLink;
}

void TDataList::InsertIntoEmptyList(pTDataValue pVal)
{
	pFirst = new TDataLink(pVal);
	pCurrentLink = pFirst;
	pLast = pFirst;
}

TDataList::TDataList()
{
	pFirst = pLast = pCurrentLink = pPreviousLink = nullptr;
	pStop = nullptr;
	listLength = 0;
	currentPosition = 0;
}

pTDataValue TDataList::GetDataValue(TLinkPos mode) const
{
	// Если в списке нет ни одного элемента
	if (pFirst == nullptr)
	{
		return nullptr;
	}

	TDataValue *temp = nullptr;
	switch (mode)
	{
	case FIRST:
		temp = pFirst->GetDataValue();
		break;
	case LAST:
		temp = pLast->GetDataValue();
		break;
	case CURRENT:
		temp = pCurrentLink->GetDataValue();
		break;
	}

	return (temp == nullptr) ? nullptr : temp;
}

void  TDataList::SetCurrentPosition(const int& position)
{
	if (position < 0)
	{
		throw range_error("Cannot set position! Position must be positive");
	}
	if (IsEmpty())
	{
		throw logic_error("Cannot set position! List is empty");
	}

	Reset();

	for (int i = 0; i < position; i++)
	{
		MoveNext();
	}
}

int TDataList::GetCurrentPosition() const
{
	return currentPosition;
}

void TDataList::Reset()
{
	currentPosition = 0;
	pCurrentLink = pFirst;
	pPreviousLink = pStop;
}

bool TDataList::IsListEnded() const
{
	if (pPreviousLink == pLast && pCurrentLink == pStop && !IsEmpty())
	{
		return true;
	}

	return false;
}

void TDataList::MoveNext()
{
	if (pCurrentLink == pStop)
	{
		throw logic_error("Cannot move to the next link! List has ended");
	}
	
	if (IsListEnded() == false) 
	{
		pPreviousLink = pCurrentLink;
		pCurrentLink = pCurrentLink->GetNextDataLink();
		currentPosition++;
	}
	if (pCurrentLink == pStop)
	{
		currentPosition = -1;
	}
}

void TDataList::InsertBeforeFirst(pTDataValue pVal)
{
	if (IsListEnded())
	{
		throw "Cannot insert before first! List is ended";
	}

	listLength++;
	Reset();

	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	TDataLink *temp = pFirst;
	pFirst = new TDataLink(pVal);
	pFirst->SetNextLink(temp);
	pCurrentLink = pFirst;

	if (temp->GetNextLink() == nullptr)
	{
		pLast = temp;
	}
}

void TDataList::InsertAfterLast(pTDataValue pVal)
{
	if (IsListEnded())
	{
		throw "Cannot insert after last! List is ended";
	}

	listLength++;

	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	TDataLink *temp = pLast;
	temp->SetNextLink(pStop);
	pLast = new TDataLink(pVal);
	pLast->SetNextLink(pStop);
	pCurrentLink = pLast;
	pPreviousLink = temp;
	pPreviousLink->SetNextLink(pCurrentLink);
	currentPosition = listLength - 1;

	if (pFirst == temp)
	{
		pFirst = temp;
		pFirst->SetNextLink(pLast);
	}
}

void TDataList::InsertBeforeCurrent(pTDataValue pVal)
{
	listLength++;

	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	if (pCurrentLink == pFirst)
	{
		InsertBeforeFirst(pVal);
		listLength--;
		return;
	}

	TDataLink* temp = pCurrentLink;
	pCurrentLink = new TDataLink(pVal);
	pCurrentLink->SetNextLink(temp);
	pPreviousLink->SetNextLink(pCurrentLink);

	if (pLast == temp)
	{
		pLast = temp;
	}
}

void TDataList::DeleteFirst()
{
	if (IsEmpty())
	{
		throw logic_error("Cannot delete first element! List is empty");
	}

	TDataLink *temp = pFirst;
	pFirst = pFirst->GetNextDataLink();
	DeleteLink(temp);
	listLength--;

	if (IsEmpty()) 
	{
		pLast = pStop;
		Reset();
	}
	else if (currentPosition == 0)
		pCurrentLink = pFirst;

	if (currentPosition)
		currentPosition--;
}

void TDataList::DeleteCurrent()
{
	if (IsEmpty())
	{
		throw logic_error("Cannot delete current element! List is empty");
	}
	
	if (listLength == 1)
	{
		DeleteFirst();

		return;
	}
	
	if (pCurrentLink == pLast)
	{
		DeleteLink(pCurrentLink);
		SetCurrentPosition(currentPosition-1);
		pLast = pCurrentLink;
		pLast->SetNextLink(pStop);
		listLength--;
		currentPosition++;

		return;
	}
	
	TDataLink *temp = pCurrentLink;
	pCurrentLink = pCurrentLink->GetNextDataLink();
	DeleteLink(temp);
	pPreviousLink->SetNextLink(pCurrentLink);
	listLength--;
}

void TDataList::DeleteList()
{
	while(listLength !=0)
	{
		DeleteFirst();
	}
}
```

### Реализация класса `THeadRing`
#### headring.h
```C++
#include "DataList.h"

#ifndef HEADRING
#define HEADRING
class THeadRing : public TDataList
{
protected:
	pTDataLink pHead; // заголовок, pFirst - звено за pHead
public:
	THeadRing();
	~THeadRing();
	
	virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
	virtual void InsertAfterLast(pTDataValue pVal = nullptr);
	virtual void DeleteFirst();
};
#endif
```

#### headring.cpp
```C++
#include "HeadRing.h"

THeadRing::THeadRing() : TDataList()
{
	pHead = nullptr;
	pStop = pHead = pFirst;
}

THeadRing::~THeadRing()
{
	DeleteList();
	if (pHead != nullptr)
	{
		DeleteLink(pHead);
	}	
}

void THeadRing::InsertBeforeFirst(pTDataValue pVal)
{
	if (listLength == 0)
	{
		pHead = new TDataLink();
	}
	TDataList::InsertBeforeFirst(pVal);

	pHead->SetNextLink(pFirst);
}

void THeadRing::InsertAfterLast(pTDataValue pVal)
{
	TDataList::InsertAfterLast(pVal);

	pHead->SetNextLink(pFirst);
}

void THeadRing::DeleteFirst()
{
	TDataList::DeleteFirst();
	if (pHead != nullptr)
	{
		pHead->SetNextLink(pFirst);
	}
}
```

### Реализация класса `TPolinom`
#### polinom.h
```C++
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
	TPolinom(TPolinom &polinom);

	pTMonom GetMonom() { return (pTMonom)GetDataValue(); }

	TPolinom& operator+(TPolinom &polinom);
	TPolinom& operator=(TPolinom &polinom);

	TPolinom& Input();
	void Print();
	int Calculate(const int x, const int y, const int z);
};
#endif
```

#### polinom.cpp
```C++
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
```

### Реализация Main
#### main.cpp
```C++
#include "Polinom.h"

int main()
{ 
	TPolinom polinom1, polinom2, sum;
	const int x = 3, y = -6, z = 2;

	polinom1.Input();
	polinom2.Input();

	cout << "\nFirst polinom: ";
	polinom1.Print();
	cout << "Second polinom: ";
	polinom2.Print();

	sum = polinom1 + polinom2;
	cout << "Sum of polinoms: ";
	sum.Print();

	cout << "Sum of polinoms(if x = " << x << ", y = " << y << " and z = " << z << "): " << sum.Calculate(x, y, z) << endl;

	return 0;
}
```

## Тестирование
#### PolinomTestkit.cpp
```C++
#include <gtest/gtest.h>
#include <ctime>

#include "RootLink.h"
#include "DataLink.h"
#include "Monom.h"

#include "DataList.h"
#include "HeadRing.h"
#include "Polinom.h"


/*-----------------------TESTING TRootLink-----------------------*/


TEST(TRootLink, CanCreateRootLink)
{
	ASSERT_NO_THROW(TDataLink rootLink);
}

TEST(TRootLink, CanGetNextLink)
{
	TDataLink rootLink;
	TDataLink *pRootLink1 = new TDataLink();
	TDataLink *pRootLink2 = new TDataLink();

	pRootLink1->SetNextLink(pRootLink2);

	ASSERT_NO_THROW(rootLink.GetNextLink());
	EXPECT_EQ(rootLink.GetNextLink(), nullptr);
	EXPECT_EQ((pTRootLink)pRootLink1->GetNextLink(), pRootLink2);
}

TEST(TRootLink, CanSetNextLink)
{
	TDataLink rootLink;
	TDataLink *pRootLink = new TDataLink();

	ASSERT_NO_THROW(rootLink.SetNextLink(pRootLink));
	EXPECT_EQ(rootLink.GetNextLink(), pRootLink);
}

TEST(TRootLink, CanInsertNextLink)
{
	TDataLink rootLink;
	TMonom monom(3, 123);
	TDataLink *pRootLink = new TDataLink(monom.GetCopy());

	ASSERT_NO_THROW(rootLink.InsertNextLink(pRootLink));
	EXPECT_EQ(rootLink.GetNextLink(), pRootLink);
}


/*-----------------------TESTING TDataLink-----------------------*/


TEST(TDataLink, CanCreateDataLink)
{
	TMonom monom1(3, 121);
	TMonom monom2(7, 398);
	TDataLink *pDataLink2 = new TDataLink();

	ASSERT_NO_THROW(TDataLink dataLink1);
	ASSERT_NO_THROW(TDataLink dataLink1(monom1.GetCopy()));
	ASSERT_NO_THROW(TDataLink dataLink(monom2.GetCopy(), pDataLink2));
}

TEST(TDataLink, CanSetDataValue)
{
	TDataLink *pDataLink = new TDataLink();
	TMonom monom(1, 23);

	ASSERT_NO_THROW(pDataLink->SetDataValue(monom.GetCopy()));
}

TEST(TDataLink, CanGetDataValue)
{
	TDataLink dataLink;
	TMonom monom(4, 173);
	TDataValue *pValue = monom.GetCopy();

	ASSERT_NO_THROW(dataLink.SetDataValue(pValue));
	EXPECT_EQ(dataLink.GetDataValue(), pValue);
}

TEST(TDataLink, CanGetNextDataLink)
{
	TMonom *pMonom = new TMonom(3, 456);
	TDataLink *pDataLink1 = new TDataLink();
	TDataLink *pDataLink2 = new TDataLink(pMonom->GetCopy(), pDataLink1);

	ASSERT_NO_THROW(pDataLink2->GetNextDataLink());
	EXPECT_EQ(pDataLink2->GetNextDataLink(), pDataLink1);
}


/*-----------------------TESTING TMonom-----------------------*/


TEST(TMonom, CanCreateMonom)
{
	ASSERT_NO_THROW(TMonom monom);
	ASSERT_NO_THROW(TMonom monom(1, 2));
	ASSERT_NO_THROW(TMonom monom(1, 26));
	ASSERT_NO_THROW(TMonom monom(1, 269));
	ASSERT_NO_THROW(TMonom monom(9));
}

TEST(TMonom, ThrowWhenCreateMonomWithNegativeIndex)
{
	ASSERT_ANY_THROW(TMonom monom(3, -461));
}

TEST(TMonom, ThrowWhenCreateMonomWithTooBigIndex)
{
	ASSERT_ANY_THROW(TMonom monom(7, 1000));
}

TEST(TMonom, CanGetCopy)
{
	TMonom monom(2, 456);
	
	ASSERT_NO_THROW(monom.GetCopy());
}

TEST(TMonom, CanSetCoefficient)
{
	TMonom monom1;
	TMonom monom2(13, 456);
	monom2.SetCoefficient(9);

	ASSERT_NO_THROW(monom1.SetCoefficient(3));
	EXPECT_EQ(monom1.GetCoefficient(), 3);
	EXPECT_EQ(monom2.GetCoefficient(), 9);
}

TEST(TMonom, CanGetCoefficient)
{
	TMonom monom1;
	TMonom monom2(-78, 4);

	monom1.SetCoefficient(-45);
	monom2.SetCoefficient(99);

	ASSERT_NO_THROW(monom1.GetCoefficient());
	EXPECT_EQ(monom1.GetCoefficient(), -45);
	EXPECT_EQ(monom2.GetCoefficient(), 99);
}

TEST(TMonom, CanSetIndex)
{
	TMonom monom1;
	TMonom monom2(-1, 33);

	ASSERT_NO_THROW(monom1.SetIndex(67));
	EXPECT_EQ(monom1.GetIndex(), 67);
	ASSERT_NO_THROW(monom2.SetIndex(999));
	EXPECT_EQ(monom2.GetIndex(), 999);
}

TEST(TMonom, CanGetIndex)
{
	TMonom monom1;
	TMonom monom2(1, 63);

	monom1.SetIndex(312);

	ASSERT_NO_THROW(monom1.GetIndex());
	EXPECT_EQ(monom1.GetIndex(), 312);
	EXPECT_EQ(monom2.GetIndex(), 63);
}

TEST(TMonom, CanAssignMonom)
{
	TMonom monom1;
	TMonom monom2(23, 781);

	ASSERT_NO_THROW(monom1 = monom2);
	EXPECT_EQ(monom1 == monom2, 1);
	EXPECT_EQ(monom2 == monom2, 1);
}

TEST(TMonom, CanCompareMonomsEqualOrNot)
{
	TMonom monom1(23, 780);
	TMonom monom2(23, 781);
	TMonom monom3(23, 780);

	ASSERT_NO_THROW(monom1 == monom2);
	EXPECT_EQ(monom1 == monom2, 0);
	EXPECT_EQ(monom1 == monom3, 1);
}

TEST(TMonom, CanCompareMonomsLessOrNot)
{
	TMonom monom1(4, 7);
	TMonom monom2(-34, 142);
	TMonom monom3(23, 780);
	TMonom monom4(-34, 21);
	TMonom monom5(77, 7);

	ASSERT_NO_THROW(monom1 < monom2);
	EXPECT_EQ(monom1 < monom2, 1);
	EXPECT_EQ(monom3 < monom1, 0);
	EXPECT_EQ(monom1 < monom1, 0);
	EXPECT_EQ(monom2 < monom4, 0);
	EXPECT_EQ(monom1 < monom5, 1);
}


/*-----------------------TESTING TDataList-----------------------*/


TEST(TDataList, CanCreateList)
{
	TDataList list;

	ASSERT_NO_THROW(TDataList list1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(list.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(list.GetDataValue(LAST), nullptr);
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, CanGetDataValue)
{
	TDataList list;

	ASSERT_NO_THROW(list.GetDataValue());
}

TEST(TDataList, GetDataValueReturnsCorrectValues)
{
	TDataList list;
	TMonom monom1(-7, 214), monom2(478, 6), monom3(124, 24);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);
	list.InsertBeforeCurrent(pValue3);

	EXPECT_EQ(list.GetDataValue(FIRST), pValue1);
	EXPECT_EQ(list.GetDataValue(CURRENT), pValue3);
	EXPECT_EQ(list.GetDataValue(LAST), pValue2);
}

TEST(TDataList, GetDataValueReturnsNullptr)
{
	TDataList list;

	EXPECT_EQ(list.GetDataValue(), nullptr);
}


TEST(TDataList, CanSetPosition)
{
	TDataList list;
	TMonom monom1(-7, 214), monom2(478, 6);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);

	ASSERT_NO_THROW(list.SetCurrentPosition(1));	
	EXPECT_EQ(list.GetCurrentPosition(), 1);
}

TEST(TDataList, ThrowWhenSetNegativePosition)
{
	TDataList list;

	ASSERT_THROW(list.SetCurrentPosition(-1), range_error);
}

TEST(TDataList, ThrowWhenSetOutOfRangePosition)
{
	TDataList list;

	ASSERT_THROW(list.SetCurrentPosition(10), logic_error);
}

TEST(TDataList, CanGetPosition)
{
	TDataList list;

	ASSERT_NO_THROW(list.GetCurrentPosition());
	EXPECT_EQ(list.GetCurrentPosition(), 0);
}

TEST(TDataList, CanReset)
{
	TDataList list;

	ASSERT_NO_THROW(list.Reset());
	EXPECT_EQ(list.GetCurrentPosition(), 0);
}

TEST(TDataList, ResetNotEmptyList)
{
	TDataList list;
	TMonom monom1(437, 2), monom2(-27, 357);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);

	list.Reset();

	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_EQ(list.GetDataValue(FIRST), list.GetDataValue(CURRENT));
}

//TODO: Add Reset test for ended list

TEST(TDataList, IsListEndedReturnsFalse)
{
	TDataList list;

	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, IsListEndedReturnsTrue)
{
	TDataList list;
	TMonom monom(4, 245);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);
	list.MoveNext();

	EXPECT_TRUE(list.IsListEnded());
}

TEST(TDataList, CanMoveNext)
{
	TDataList list;
	TMonom monom(-57, 993);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(list.MoveNext());
	EXPECT_TRUE(list.IsListEnded());
}

TEST(TDataList, ThrowWhenPCurrentIsPStop)
{
	TDataList list;
	TMonom monom(253, 1);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);
	list.MoveNext();

	ASSERT_THROW(list.MoveNext(), logic_error);
}

TEST(TDataList, MoveNextToPStopIfPCurrentIsPLast)
{
	TDataList list;
	TMonom monom(253, 1);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);
	list.MoveNext();

	EXPECT_EQ(list.GetCurrentPosition(), -1);
}

TEST(TDataList, CanInsertBeforeFirst)
{
	TDataList list;
	TMonom monom(34, 3);

	ASSERT_NO_THROW(list.InsertBeforeFirst());
	ASSERT_NO_THROW(list.InsertBeforeFirst(monom.GetCopy()));
}

TEST(TDataList, InsertBeforeFirstIntoEmptyList)
{
	TDataList list;
	TMonom monom(3, 111);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, InsertBeforeFirstInto1ElementList)
{
	TDataList list;
	TMonom monom1(3, 111), monom2(-22, 89);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertBeforeFirst(pValue2);

	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	EXPECT_EQ(list.GetDataValue(LAST), pValue1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, InsertBeforeFirstIntoMultiElementsList)
{
	TDataList list;
	TMonom monom1(-63, 11), monom2(-2, 89), monom3(11, 43);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertBeforeFirst(pValue1); // pLast
	list.InsertBeforeFirst(pValue2);
	list.InsertBeforeFirst(pValue3); // pFirst

	EXPECT_EQ(list.GetListLength(), 3);
	EXPECT_EQ(list.GetDataValue(), pValue3);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue3);
	EXPECT_EQ(list.GetDataValue(LAST), pValue1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, CanInsertAfterLast)
{
	TDataList list;
	TMonom monom(-34, 831);

	ASSERT_NO_THROW(list.InsertAfterLast());
	ASSERT_NO_THROW(list.InsertAfterLast(monom.GetCopy()));
}

TEST(TDataList, InsertAfterLastIntoEmptyList)
{
	TDataList list;
	TMonom monom(99, 1);
	TDataValue *pValue = monom.GetCopy();

	list.InsertAfterLast(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, InsertAfterLastInto1ElementList)
{
	TDataList list;
	TMonom monom1(99, 2), monom2(-31, 347);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertAfterLast(pValue1); // pFirst, pPrevious
	list.InsertAfterLast(pValue2); // pLast, pCurrent
	
	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue1);
	EXPECT_EQ(list.GetDataValue(LAST), pValue2);
	EXPECT_EQ(list.GetCurrentPosition(), 1);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, InsertAfterLastIntoMultiElementsList)
{
	TDataList list;
	TMonom monom1(4, 8), monom2(-84, 689), monom3(251, 913);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertAfterLast(pValue1); // pFirst
	list.InsertAfterLast(pValue2);
	list.InsertAfterLast(pValue3); // pLast

	EXPECT_EQ(list.GetListLength(), 3);
	EXPECT_EQ(list.GetDataValue(), pValue3);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue1);
	EXPECT_EQ(list.GetDataValue(LAST), pValue3);
	EXPECT_EQ(list.GetCurrentPosition(), 2);
	EXPECT_FALSE(list.IsEmpty());
}

//TODO: Make tests with ended lists

TEST(TDataList, CanInsertBeforeCurrent)
{
	TDataList list;
	TMonom monom(123, 8);

	ASSERT_NO_THROW(list.InsertBeforeCurrent());
	ASSERT_NO_THROW(list.InsertBeforeCurrent(monom.GetCopy()));
}

TEST(TDataList, InsertBeforeCurrentIntoEmptyList)
{
	TDataList list;
	TMonom monom(1, 341);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeCurrent(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, InsertBeforeCurrentInto1ElementList)
{
	TDataList list;
	TMonom monom1(7, 932), monom2(-315, 7);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeCurrent(pValue2);

	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	EXPECT_EQ(list.GetDataValue(LAST), pValue1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, InsertBeforeCurrentIntoMultiElementsList)
{
	TDataList list;
	TMonom monom1(-32, 443), monom2(357, 9), monom3(553, 998), monom4(12, 783);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeCurrent(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	EXPECT_EQ(list.GetListLength(), 4);
	EXPECT_EQ(list.GetDataValue(), pValue4);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	EXPECT_EQ(list.GetDataValue(LAST), pValue3);
	EXPECT_EQ(list.GetCurrentPosition(), 2);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, CanDeleteFirst)
{
	TDataList list;
	TMonom monom(-48, 82);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(list.DeleteFirst());
}

TEST(TDataList, ThrowWhenDeleleFirstFromEmptyList)
{
	TDataList list;

	ASSERT_THROW(list.DeleteFirst(), logic_error);
}

TEST(TDataList, DeleteFirstIn1ElementList)
{
	TDataList list;
	TMonom monom(-48, 82);
	TDataValue *pValue = monom.GetCopy();
	TDataValue *first;

	list.InsertBeforeFirst(pValue);
	first = list.GetDataValue(FIRST);

	ASSERT_NO_THROW(list.DeleteFirst());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_NE(first, list.GetDataValue(FIRST));
}

TEST(TDataList, DeleteFirstInMultiElementList)
{
	TDataList list;
	TMonom monom1(-48, 82), monom2(467, 124), monom3(67, 9);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *first;

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);
	list.InsertBeforeCurrent(pValue3);

	first = list.GetDataValue(FIRST);
	list.DeleteFirst();

	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_NE(first, list.GetDataValue());
}

TEST(TDataList, CanDeleteCurrent)
{
	TDataList list;
	TMonom monom(-432, 3);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(list.DeleteCurrent());
}

TEST(TDataList, ThrowWhenDeleteCurrentFromEmptyList)
{
	TDataList list;

	ASSERT_THROW(list.DeleteCurrent(), logic_error);
}

TEST(TDataList, DeleteCurrentIn1ElementList)
{
	TDataList list;
	TMonom monom(89, 245);
	TDataValue *pValue = monom.GetCopy();
	TDataValue *current;

	list.InsertBeforeFirst(pValue);

	current = list.GetDataValue(CURRENT);

	ASSERT_NO_THROW(list.DeleteCurrent());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_NE(current, list.GetDataValue(CURRENT));
}

TEST(TDataList, DeleteCurrentInMultiElementList)
{
	TDataList list;
	TMonom monom1(-42, 541), monom2(312, 124), monom3(4, 2), monom4(-21, 435);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();
	TDataValue *current;

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeFirst(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	current = list.GetDataValue(CURRENT);
	list.DeleteCurrent();

	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 3);
	EXPECT_EQ(list.GetCurrentPosition(), 2);
	EXPECT_NE(current, list.GetDataValue(CURRENT));
}

TEST(TDataList, CanDeleteList)
{
	TDataList list;
	TMonom monom1(445, 6), monom2(-110, 1), monom3(9, 895), monom4(-899, 67);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeFirst(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	ASSERT_NO_THROW(list.DeleteList());
}

TEST(TDataList, DeleteListResetEverything)
{
	TDataList list;
	TMonom monom1(-2, 20), monom2(730, 402), monom3(-771, 999), monom4(2, 49);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeFirst(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	list.DeleteList();

	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsListEnded());
	EXPECT_TRUE(list.IsEmpty());
}


/*-----------------------TESTING THeadRing-----------------------*/


TEST(THeadRing, CanCreateHeadRingList)
{
	THeadRing ringList;
	
	ASSERT_NO_THROW(THeadRing ringList1);
	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 0);
	EXPECT_EQ(ringList.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(ringList.GetDataValue(LAST), nullptr);
	EXPECT_TRUE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, CanInsertIntoHeadRingList)
{
	THeadRing ringList;
	TMonom monom(-32, 182);
	TDataValue *pValue = monom.GetCopy();

	ASSERT_NO_THROW(ringList.InsertBeforeFirst(pValue));
}

TEST(THeadRing, InsertIntoEmptyHeadRingList)
{
	THeadRing ringList;
	TMonom monom(999, 3);
	TDataValue *pValue = monom.GetCopy();

	ringList.InsertBeforeFirst(pValue);

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 1);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, InsertInto1ElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom1(-8, 67), monom2(3, 997);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	ringList.InsertBeforeFirst(pValue1);
	ringList.InsertBeforeFirst(pValue2);

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 2);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue2);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue2);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue1);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, InsertIntoMultiElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom1(12, 2), monom2(84, 770), monom3(1, 82), monom4(-921, 912);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	ringList.InsertBeforeFirst(pValue1);
	ringList.InsertAfterLast(pValue2);
	ringList.InsertBeforeCurrent(pValue3);
	ringList.InsertBeforeFirst(pValue4);

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 4);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue4);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue4);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue2);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, CanDeleteHeadRingList)
{
	THeadRing ringList;
	TMonom monom(2, 902);
	TDataValue *pValue = monom.GetCopy();

	ringList.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(ringList.DeleteFirst());
}

TEST(THeadRing, DeleteFrom1ElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom(0, 1);
	TDataValue *pValue = monom.GetCopy();

	ringList.InsertBeforeFirst(pValue);

	ringList.DeleteFirst();

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 0);
	EXPECT_EQ(ringList.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(ringList.GetDataValue(LAST), nullptr);
	EXPECT_TRUE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, DeleteFromMultiElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom1(363, 921), monom2(-235, 7), monom3(1, 2), monom4(86, 4);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	ringList.InsertBeforeFirst(pValue1);
	ringList.InsertAfterLast(pValue2);
	ringList.InsertBeforeCurrent(pValue3);
	ringList.InsertBeforeFirst(pValue4);

	ringList.DeleteFirst();

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 3);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue1);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue1);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue2);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());

	ringList.DeleteFirst();

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 2);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue3);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue3);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue2);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}


/*-----------------------TESTING TPolinom-----------------------*/


TEST(TPolinom, CanCreatePolinom)
{
	srand(time(0));

	ASSERT_NO_THROW(TPolinom polinom);

	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;
	}

	TPolinom polinom(monoms, 10);

	EXPECT_EQ(polinom.GetCurrentPosition(), 0);
	EXPECT_EQ(polinom.GetListLength(), 10);
	EXPECT_FALSE(polinom.IsEmpty());
	EXPECT_FALSE(polinom.IsListEnded());
}

TEST(TPolinom, ThrowWhenMonomsNumberIsNegative)
{
	ASSERT_THROW(TPolinom polinom(nullptr, -11), invalid_argument);
}

TEST(TPolinom, CanCopyEmptyPolinom)
{
	TPolinom copiedPolinom;

	ASSERT_NO_THROW(TPolinom emptyPolinom(copiedPolinom));
}

TEST(TPolinom, CanCopyPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;
	}

	TPolinom polinom(monoms, 10);
	TPolinom copiedPolinom(polinom);

	EXPECT_EQ(polinom.GetDataValue(FIRST), copiedPolinom.GetDataValue(FIRST));
	EXPECT_EQ(polinom.GetDataValue(LAST), copiedPolinom.GetDataValue(LAST));

	EXPECT_EQ(copiedPolinom.GetCurrentPosition(), 9);
	EXPECT_EQ(copiedPolinom.GetListLength(), 10);
	EXPECT_FALSE(copiedPolinom.IsEmpty());
	EXPECT_FALSE(copiedPolinom.IsListEnded());

	EXPECT_EQ(polinom.GetCurrentPosition(), 0);
	EXPECT_EQ(polinom.GetListLength(), 10);
	EXPECT_FALSE(polinom.IsEmpty());
	EXPECT_FALSE(polinom.IsListEnded());
}

TEST(TPolinom, CanAddEmptyPolinoms)
{
	TPolinom lhs, rhs;

	ASSERT_NO_THROW(lhs = lhs + rhs);
}

TEST(TPolinom, CanAddEmptyPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;
	}

	TPolinom lhs(monoms, 10), rhs;
	TDataValue *first = lhs.GetDataValue(FIRST);

	ASSERT_NO_THROW(lhs = lhs + rhs);
	EXPECT_EQ(first, lhs.GetDataValue(FIRST));
	EXPECT_EQ(lhs.GetCurrentPosition(), 0);
	EXPECT_EQ(lhs.GetListLength(), 10);
	EXPECT_FALSE(lhs.IsEmpty());
	EXPECT_FALSE(lhs.IsListEnded());
}

TEST(TPolinom, AddToEmptyPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;
	}

	TPolinom lhs, rhs(monoms, 10);
	TDataValue *first = rhs.GetDataValue(FIRST);

	ASSERT_NO_THROW(lhs = lhs + rhs);
	EXPECT_EQ(first, lhs.GetDataValue(FIRST));
	EXPECT_EQ(lhs.GetCurrentPosition(), 9);
	EXPECT_EQ(lhs.GetListLength(), 10);
	EXPECT_FALSE(lhs.IsEmpty());
	EXPECT_FALSE(lhs.IsListEnded());
}

TEST(TPolinom, AddPolinomsWithEqualLength)
{
	int monomsLhs[5][2] = { -324, 871,
							3, 650,
							-2,509,
							761, 121,
							99, 56 };

	int	monomsRhs[5][2] = { 97, 811,
							-22, 509, 
							992,311, 
							352, 123,
							5, 2 };

	TPolinom lhs(monomsLhs, 5), rhs(monomsRhs, 5), result;

	ASSERT_NO_THROW(result = lhs + rhs);
	EXPECT_EQ(result.GetListLength(), 9);
}

TEST(TPolinom, AddPolinomsWithDifferentLengthFirstIsBigger)
{
	int monomsLhs[7][2] = { 23, 900,
							-564, 712,
							8,700,
							-74, 650,
							1, 399 ,
							999, 41,
							-7, 8 };

	int	monomsRhs[4][2] = { 97, 702,
							657, 403,
							-4,41,
							3, 9};

	TPolinom lhs(monomsLhs, 7), rhs(monomsRhs, 4), result;

	ASSERT_NO_THROW(result = lhs + rhs);
	EXPECT_EQ(result.GetListLength(), 10);
}

TEST(TPolinom, AddPolinomsWithDifferentLengthSecondIsBigger)
{
	int monomsLhs[4][2] = { -124, 812,
							881, 810,
							-2,751,
							-82, 661};

	int	monomsRhs[7][2] = { 11, 902,
							214, 812,
							-24, 602,
							124, 412,
							-15, 335,
							55, 202,
							99, 52};

	TPolinom lhs(monomsLhs, 4), rhs(monomsRhs, 7), result;
	
	ASSERT_NO_THROW(result = lhs + rhs);
	EXPECT_EQ(result.GetListLength(), 10);
}


TEST(TPolinom, CanEqualEmptyPolinomToFilledPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;
	}

	TPolinom lhs(monoms, 10), rhs;

	ASSERT_NO_THROW(lhs = rhs);
	EXPECT_EQ(lhs.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(lhs.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(lhs.GetDataValue(LAST), nullptr);
	EXPECT_EQ(lhs.GetCurrentPosition(), 0);
	EXPECT_EQ(lhs.GetListLength(), 0);
	EXPECT_TRUE(lhs.IsEmpty());
	EXPECT_FALSE(lhs.IsListEnded());
}

TEST(TPolinom, CanEqualFilledPolinomToEmptyPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;
	}

	TPolinom lhs(monoms, 10), rhs;
	TDataValue *first = lhs.GetDataValue(FIRST);
	TDataValue *last = lhs.GetDataValue(LAST);

	ASSERT_NO_THROW(rhs = lhs);
	EXPECT_EQ(rhs.GetDataValue(FIRST), first);
	EXPECT_EQ(rhs.GetDataValue(LAST), last);
	EXPECT_EQ(rhs.GetCurrentPosition(), 9);
	EXPECT_EQ(rhs.GetListLength(), 10);
	EXPECT_FALSE(rhs.IsEmpty());
	EXPECT_FALSE(rhs.IsListEnded());
}

TEST(TPolinom, CanEqualTwoFilledPolinomsWithDifferentLength)
{
	int monomsLhs[10][2], monomsRhs[10][2];
	for (int i = 0; i < 10; i++)
	{
		monomsLhs[i][0] = -1000 + rand() % 2000;
		monomsLhs[i][1] = 1 + rand() % 999;

		monomsRhs[i][0] = -1000 + rand() % 2000;
		monomsRhs[i][1] = 1 + rand() % 999;
	}

	TPolinom lhs(monomsLhs, 7), rhs(monomsRhs, 10);
	TDataValue *first = lhs.GetDataValue(FIRST);
	TDataValue *last = lhs.GetDataValue(LAST);

	ASSERT_NO_THROW(rhs = lhs);
	EXPECT_EQ(rhs.GetDataValue(FIRST), first);
	EXPECT_EQ(rhs.GetDataValue(LAST), last);
	EXPECT_EQ(rhs.GetCurrentPosition(), 6);
	EXPECT_EQ(rhs.GetListLength(), 7);
	EXPECT_FALSE(rhs.IsEmpty());
	EXPECT_FALSE(rhs.IsListEnded());
}

TEST(TPolinom, CanEqualTwoFilledPolinomsWithEqualLength)
{
	int monomsLhs[10][2], monomsRhs[10][2];
	for (int i = 0; i < 10; i++)
	{
		monomsLhs[i][0] = -1000 + rand() % 2000;
		monomsLhs[i][1] = 1 + rand() % 999;

		monomsRhs[i][0] = -1000 + rand() % 2000;
		monomsRhs[i][1] = 1 + rand() % 999;
	}

	TPolinom lhs(monomsLhs, 10), rhs(monomsRhs, 10);
	TDataValue *first = lhs.GetDataValue(FIRST);
	TDataValue *last = lhs.GetDataValue(LAST);

	ASSERT_NO_THROW(rhs = lhs);
	EXPECT_EQ(rhs.GetDataValue(FIRST), first);
	EXPECT_EQ(rhs.GetDataValue(LAST), last);
	EXPECT_EQ(rhs.GetCurrentPosition(), 9);
	EXPECT_EQ(rhs.GetListLength(), 10);
	EXPECT_FALSE(rhs.IsEmpty());
	EXPECT_FALSE(rhs.IsListEnded());
}

TEST(TPolinom, CanPrintPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000;
		monoms[i][1] = 1 + rand() % 999;

	}

	TPolinom polinom(monoms, 10);

	ASSERT_NO_THROW(polinom.Print());
}

TEST(TPolinom, CanPrintEmptyPolinom)
{
	TPolinom polinom;
	
	ASSERT_NO_THROW(polinom.Print());
}

TEST(TPolinom, CalculateEmptyPolinomReturns0)
{
	TPolinom polinom;

	ASSERT_NO_THROW(polinom.Calculate(1, 2, 3));
	EXPECT_EQ(polinom.Calculate(1, 2, 3), 0);
}

TEST(TPolinom, CanCalculatePolinom)
{
	int monoms[4][2] = {34, 863,
						-8, 702,
						401, 342,
						6, 7};

	TPolinom polinom(monoms, 4);

	EXPECT_EQ(polinom.Calculate(-2, 4, 1), 34831366);
}
```

#### Результат прохождения тестов
![](https://bytebucket.org/VadimNifadyev/lab5-polynom/raw/feb0b1e319fa74535e40a30d95c7be488f4dc9a2/work/b23/PolinomTests.png)
#### Результат работы программы
![](https://bytebucket.org/VadimNifadyev/lab5-polynom/raw/feb0b1e319fa74535e40a30d95c7be488f4dc9a2/work/b23/PolinomMain.png)

## Вывод
В рамках данной лабораторной работы были изучены способы представления и хранения полинома в виде кольцевого односвязного списка, были реализованы различные операции над полиномами, а также были получены базовые знания работы с регулярными выражениями.