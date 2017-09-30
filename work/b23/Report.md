# Отчет по лабораторной работе №1: Множества на овснове битовых полей
//Выполнил студент группы 381608-1 Нифадьев Вадим
## Цели и задачи
* 	Реализация класса битового поля TBitField согласно заданному интерфейсу.
*	Реализация класса множества TSet согласно заданному интерфейсу.
*	Обеспечение работоспособности тестов и примера использования.
*	Реализация нескольких простых тестов на базе Google Test.
*	Публикация исходных кодов в личном репозитории на BitBucket.
## Описание работы программы
* ### Реализация класса TBitField
* ### Реализация класса TSet
* ### Тестирование класса TBitField
* ### Тестирование класса TSet
## Исходный код программы
* ### TBitField.cpp
``` C++
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
// Битовое поле

#include "tBitField.h"

enum ERRORS {WRONG_LENGTH, WRONG_RANGE, LENGHTS_NOT_EQUAL};

TBitField::TBitField(int len)
{
	if (len < 1)
	{
		throw WRONG_LENGTH;
	}
	BitLen = len;
	MemLen = (len + sizeof(int) - 1) / sizeof(int);
	pMem = new TELEM[BitLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // Количество необходимых байт(TELEMов) / индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	mask = mask << n % (sizeof(TELEM) * 8);
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen))
		throw WRONG_RANGE;
	//int index = GetMemIndex(n);
	//TELEM mask = GetMemMask(n);
	//pMem[index] = pMem[index] | mask;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClearBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
		throw WRONG_RANGE;
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] = pMem[index] & ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen))
		throw WRONG_RANGE;
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	TELEM result = pMem[index] & mask;
	if (result)
		return 1;
	else 
		return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (pMem != bf.pMem)
	{
		if (BitLen != bf.BitLen)
		{
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			delete[] pMem;
			pMem = new TELEM[MemLen]; // Новое выделение памяти
		}
		for (int i = 0; i < MemLen; i++) 
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if ((MemLen != bf.MemLen) || (BitLen != bf.BitLen))
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				return 0;
			}
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int maxLength;
	if (BitLen >= bf.BitLen)
	{
		maxLength = BitLen;
	}
	else
	{
		maxLength = bf.BitLen;
	}
	TBitField result(maxLength);
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		result.pMem[i] = result.pMem[i] | bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxLength;
	if (BitLen >= bf.BitLen)
	{
		maxLength = BitLen;
	}
	else
	{
		maxLength = bf.BitLen;
	}
	TBitField result(maxLength);
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		result.pMem[i] = result.pMem[i] & bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = ~pMem[i];
	}
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	// как последовательность 0 и 1
	char ch;
	int i = 0;
	istr >> ch;
	while ((ch == '1') || (ch == '0'))
	{
		if (ch == '1')
		{
			bf.SetBit(i);
			//i++;
		}
		else
		{
			bf.ClearBit(i);
			//i++;
		}
		bf.SetBit(i);
		i++;
	}
	//for (int i = 0; (ch == '1') || (ch == '0'); i++)
	//	bf.SetBit(i);
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	ostr << "Length = " << bf.BitLen << endl;
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}


```

* ### TSet.cpp
``` C++
// Множество - реализация через битовые поля

#include "tSet.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}


TSet::TSet(const TSet &s) : BitField(s.BitField) // конструктор копирования
{
	MaxPower = s.MaxPower;
}


TSet::TSet(const TBitField &bf) : BitField(bf) // конструктор преобразования типа
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() // преобразование типа к битовому полю
{
	TBitField result(BitField);
	return result;
}

int TSet::GetMaxPower(void) const // получить максимальное количество элементов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // проверка элемента на принадлежность множеству
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClearBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((MaxPower != s.MaxPower) || (BitField != s.BitField))
	{
		return 0;
	}
	else
	{
		return 1;
	}
	/*return BitField == s.BitField;*/
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

TSet TSet::operator+(const TSet &s) // объединение с множеством
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > BitField.GetLength())
	{
		throw ("Elem is out of allowed range");
	}
	TBitField temp(MaxPower);
	temp.SetBit(Elem);
	return BitField | temp;

	//TSet tmp(*this);
	//tmp.InsElem(Elem);
	//return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	//TBitField temp(MaxPower);
	//temp.SetBit(Elem);
	//return BitField & temp;
	TSet result = *this;
	result.DelElem(Elem);
	//result.BitField.ClearBit(Elem);
	//return result.BitField;
	return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // дополнение
{
	return TSet(~BitField);
}

 //перегрузка ввода/вывода
istream &operator>>(istream &istr, TSet &s) // ввод
{
	//TODO: Упростить либо вникнуть в логику
	int i = 0;
	char ch;
	do
	{
		istr >> ch;
	} while (ch != '{');
	do
	{
		istr >> i;
		s.InsElem(i);
		do
		{
			istr >> ch;
		} while ((ch = ',') && (ch = '}'));
	} while (ch != '}');
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << '{';
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		if (s.IsMember(i) == 1)
		{ 
			if (i == s.GetMaxPower() - 1)
			{
				ostr << i;
				break;
			}
			ostr << i << ", ";
		}
	}
	ostr << '}';
	return ostr;
}
```
* ### TBitFieldTest.cpp
``` C++
#include "tBitField.h"

#include <gtest\gtest.h>

TEST(TBitFieldCustom, EmptyBitfieldsAreEqual)
{
	const int size = 4;
	TBitField bf1(size), bf2(size);
	//bf1.SetBit(1);
	//bf1.SetBit(3);
	//bf2.SetBit(1);
	//bf2.SetBit(2);
	EXPECT_EQ(bf1, bf2);
}

TEST(TBitFieldCustom, AndOperatorAppliedToEmptyBitfield)
{
	const int size1 = 4, size2 = 5;
	TBitField bf1(size1), bf2(size2), expBf(size2);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 01010
	//bf2.SetBit(1);
	//bf2.SetBit(3);
	// expBf = 00010
	//expBf.SetBit(1);
	//expBf.SetBit(2);
	//expBf.SetBit(3);
	EXPECT_EQ(expBf, bf1 & bf2);
}
```
* ### TSetTest.cpp
``` C++
TEST(TSetCustom, CheckDifferenceOperator)
{
	const int size = 4, elem = 2;
	TSet set(size), result(size), expectedSet(size);
	// set = {1, 2, 3}
	set.InsElem(1);
	set.InsElem(2);
	set.InsElem(3);
	//result.InsElem(1);
	//result.InsElem(2);
	//result.InsElem(3);
	result = set -elem;
	//expectedSet = {1, 3}
	expectedSet.InsElem(1);
	expectedSet.InsElem(3);
	EXPECT_EQ(expectedSet, result);
	EXPECT_EQ(0, result.IsMember(elem));		
}

TEST(TSetCustom, ThrowsWhenSubstractNonExistingElement)
{
	const int size = 4;
	const int k = 6;
	TSet set(size), result(size);
	set.InsElem(0);
	set.InsElem(2);
	ASSERT_ANY_THROW(result = set - k);
}

TEST(TSetCustom, CanSubtractNonExistingElement)
{
	
	const int size = 4;
	const int k = 3;
	TSet set(size), result(size);
	set.InsElem(0);
	set.InsElem(k);
	result = set - k;
	//cout << result;
	EXPECT_NE(1, result.IsMember(k));
}

//TEST(TSetCustom, CanDealWithMultipleOperators)
//{
//	const int size1 = 5, size2 = 7;
//	TSet set1(size1), set2(size2), result(size1), expectedSet(size2);
//	// set1 = {1, 2, 4}
//	set1.InsElem(1);
//	set1.InsElem(2);
//	set1.InsElem(4);
//	// set2 = {0, 1, 2, 4, 6}
//	set2.InsElem(0);
//	set2.InsElem(1);
//	set2.InsElem(2);
//	set2.InsElem(4);
//	set2.InsElem(6);
//	result = set1 * set2 * (~set1);
//	// expectedSet = { }
//	//expectedSet.InsElem(1);
//	//expectedSet.InsElem(2);
//	//expectedSet.InsElem(4);
//	EXPECT_EQ(expectedSet, result);
//}
```
## Выводы
