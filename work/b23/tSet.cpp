// ��������� - ���������� ����� ������� ����

#include "tSet.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}


TSet::TSet(const TSet &s) : BitField(s.BitField) // ����������� �����������
{
	MaxPower = s.MaxPower;
}


TSet::TSet(const TBitField &bf) : BitField(bf) // ����������� �������������� ����
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() // �������������� ���� � �������� ����
{
	TBitField result(BitField);
	return result;
}

int TSet::GetMaxPower(void) const // �������� ������������ ���������� ���������
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // �������� �������� �� �������������� ���������
{
	return BitField.GetBit(Elem);
}

void TSet::InsertElem(const int Elem) // ��������� �������� ���������
{
	BitField.SetBit(Elem);
}

void TSet::DeleteElem(const int Elem) // ���������� �������� ���������
{
	BitField.ClearBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // ���������
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

int TSet::operator!=(const TSet &s) const // ���������
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

TSet TSet::operator+(const TSet &s) // ����������� � ����������
{
	return TSet(BitField | s.BitField);
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
	if (Elem > BitField.GetLength())
	{
		throw ("Elem is out of allowed range");
	}
	TBitField temp(BitField);
	temp.SetBit(Elem);
	return TSet(temp);
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
	TBitField temp(BitField);
	temp.ClearBit(Elem);
	return TSet(temp);
}

TSet TSet::operator*(const TSet &s) // �����������
{
	return TSet(BitField & s.BitField);
}

TSet TSet::operator~(void) // ����������
{
	return TSet(~BitField);
}

 //���������� �����/������
istream &operator>>(istream &istr, TSet &s) // ����
{
	int i;
	while (istr >> i)
	{
		if (!s.IsMember(i))
			s.InsertElem(i);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // �����
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