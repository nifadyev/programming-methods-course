// Множество - реализация через битовые поля

#include "tSet.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}


TSet::TSet(const TSet &s) : BitField(s.GetMaxPower()) // конструктор копирования
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
	return BitField | s.BitField;
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
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	//TBitField temp(MaxPower);
	//temp.SetBit(Elem);
	//return BitField & temp;
	TSet result = *this;
	//result.DelElem(Elem);
	result.BitField.ClearBit(Elem);
	return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	return BitField & s.BitField;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
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

