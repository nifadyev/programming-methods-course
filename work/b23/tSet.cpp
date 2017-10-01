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