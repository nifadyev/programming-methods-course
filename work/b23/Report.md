# Отчет по лабораторной работе №1: Множества на овснове битовых полей
__Выполнил:__ студент группы 381608-1 Нифадьев Вадим
## Цели и задачи
* 	Реализация класса битового поля `TBitField` согласно заданному интерфейсу.
*	Реализация класса множества `TSet` согласно заданному интерфейсу.
*	Обеспечение работоспособности тестов и примера использования.
*	Реализация нескольких простых тестов на базе `Google Test`.
*	Публикация исходных кодов в личном репозитории на `BitBucket`.
## Описание работы программы
### Реализация класса `TBitField`
Битовое поле в данном классе выполнено в виде массива беззнаковых целых чисел(`TELEM`ов). 
* Подсчет длины массива происходит по формуле `len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8)`. Данный вид подсчета существенно экономит памать в случаях, когда `len` кратен количеству бит в `TELEM`, так как полученная длина не будет на 1 больше необходимой.
* Установка бита осуществляется с помощью поразрядной дизъюнкции соответствующих элемента массива `TELEM`'ов и маски.
* Удаление бита осуществляется с помощью поразрядной конъюнции соответствующих элемента массива `TELEM`'ов и инвертированной маски.
* Получение бита осуществляется с помощью поразрядной дизъюнкции элемента массива `TELEM`'ов и маски.
* Побитовые операции реализованы с помощью осуществления побитовых операций над элементами множества `TELEM`'ов.
* Потоковый ввод получает непрерывную последовательность 0 и 1 до момента, пока битовое поле не закончится либо пока не встретится посторонний символ.
* Потоковый вывод выводит непрерывную последовательность 0 и 1.
#### TBitField.cpp
```C++
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
	MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
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
		}
		else
		{
			bf.ClearBit(i);
		}
		bf.SetBit(i);
		i++;
	}
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
### Реализация класса `TSet`
В классе `TSet` множество базируется на битовом поле, только представлено в другом виде.
* Операция включение в множество происходит с помощью установки бита под заданным номером.
* Операция удаление в множество происходит с помощью очистки бита под заданным номером.
* Все операции над множествами основаны на схожих операций над битовыми полями (пересечение - конъюнкция, объединение - дизъюнкция и т.д.)
* Потоковый ввод считывает целые числа до появления в потоке постороннего символа.
* Потоковый вывод последовательно выводит индексы элементов, находящихся в множестве, и заключает их в фигурные скобки.
#### TSet.cpp
```C++
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

void TSet::InsertElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DeleteElem(const int Elem) // исключение элемента множества
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
	if ((MaxPower != s.GetMaxPower()) || (BitField != s.BitField))
	{
		return 0;
	}
	else
	{
		return 1;
	}
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
	TBitField temp(BitField);
	temp.SetBit(Elem);
	return TSet(temp);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TBitField temp(BitField);
	temp.ClearBit(Elem);
	return TSet(temp);
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
	int i;
	while (istr >> i)
	{
		if (!s.IsMember(i))
			s.InsertElem(i);
	}
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
			else
				ostr << i << ", ";
		}
	}
	ostr << '}';
	return ostr;
}
```
## Тестирование
### Тестирование класса `TBitField`
Функциональность созданных классов была протестирована с помощью библиотеки `Google Test`. К предоставленным тестам были добавлены 3 теста, проверяющие ход выполнения операций как в обычных, так и в недопустимых условиях.

![](https://image.ibb.co/nsVmJw/TBit_Field_Test.png "TBitFieldTest")
     _Результат прохождения предоставленных тестов класса `TBitField`_
    
К тестированию класса `TBitField` были добавлены 3 теста: проверка на равенство пустых битовых полей, проверка на корректность работы оператора & с пустым битовым полем и проверка корректности сравнения битовых полей разной длины. 
#### TBitFieldCustom
```C++
TEST(TBitFieldCustom, EmptyBitfieldsAreEqual)
{
	const int size = 4;
	TBitField bf1(size), bf2(size);
	EXPECT_EQ(bf1, bf2);
}

TEST(TBitFieldCustom, AndOperatorAppliedToEmptyBitfield)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), expectedBf(size);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	//bf2 = 0000
	EXPECT_EQ(expectedBf, bf1 & bf2);
}

TEST(TBitFieldCustom, CanCompareBitfieldsOfDifferentSizes)
{
	const int size1 = 2, size2 = 5;
	TBitField result(size1), bf(size2);
	// bf = 11
	bf.SetBit(0);
	bf.SetBit(1);
	//result = 11000
	result = bf;
	EXPECT_EQ(1, bf == result);
}
```

![](https://image.ibb.co/cAidWG/TBit_Field_Custom.png "TBitFieldCustom")
_Результат прохождения собственных тестов класса `TBitField`_

### Тестирование класса `TSet`
Класс `TSet` тестировался так же, как и класс `TBitField`: к предоставленым тестам были добавлены 3 собственных теста. 

![](https://image.ibb.co/hCBnQb/TSetTest.png "TSetTest")
_Результат прохождения предоставленных тестов класса `TSet`_

К предоставленному тестированию класса `TSet` были добавлены следующие тесты: проверка работоспособности оператора разности множества и элемента, проверка на выброс иключения при вычитании элемента, выходящего за пределы множества и проверка на возможность вычесть несуществующий элемент множества.
#### `TSetCustom`
```C++
TEST(TSetCustom, CheckDifferenceOperator)
{
	const int size = 4, elem = 2;
	TSet set(size), result(size), expectedSet(size);
	// set = {1, 2, 3}
	set.InsertElem(1);
	set.InsertElem(2);
	set.InsertElem(3);
	result = set - elem;
	//expectedSet = {1, 3}
	expectedSet.InsertElem(1);
	expectedSet.InsertElem(3);
	EXPECT_EQ(expectedSet, result);
	EXPECT_EQ(0, result.IsMember(elem));		
}

TEST(TSetCustom, ThrowsWhenSubstractTooLargeElement)
{
	const int size = 4;
	const int k = 6;
	TSet set(size), result(size);
	set.InsertElem(0);
	set.InsertElem(2);
	ASSERT_ANY_THROW(result = set - k);
}

TEST(TSetCustom, CanSubtractNonExistingElement)
{
	const int size = 4;
	const int k = 3;
	TSet set(size), result(size);
	//set = {0, 2}
	set.InsertElem(0);
	set.InsertElem(2);
	//result = {0, 2}
	result = set - k;
	EXPECT_NE(1, result.IsMember(k));
}
```

![](https://image.ibb.co/jj03yw/TSet_Custom.png "TSetCustom")
_Результат прохождения собственных тестов класса `TSet`_

### Результат работы `Решета Ератосфена`
Программа отработала возложенные на нее функции корректно. Единственное изменение, внесенное в файл `SamplePrimeNumbers.cpp` - в консоль печатается по 25 простых чисел в каждой строке, вместо 10.

![](https://image.ibb.co/fQwbJw/Eratosfen_TBit_Field.png "Eratosfen TBitField")
_Результат работы `Решета Ератосфена` при использовании битовых полей `TBitField`_

![](https://image.ibb.co/i01Adw/Eratosfen_TSet.png "Eratosfen TSet")
_Результат работы `Решета Ератосфена` при использовании множеств `TSet`_

## Выводы
Процесс реализации классов `TBitField` и `TSet` помог освоить основы работы с битовыми полями и с базовым тестированием с помощью библиотеки `Google Test`.
