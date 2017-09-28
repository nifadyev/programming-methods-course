// ��������� - ���������� ����� ������� ����

#include "tSet.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}


TSet::TSet(const TSet &s) : BitField(s.GetMaxPower()) // ����������� �����������
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

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
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
	return BitField | s.BitField;
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
	if (Elem > BitField.GetLength())
	{
		throw ("Elem is out of allowed range");
	}
	TBitField temp(MaxPower);
	temp.SetBit(Elem);
	return BitField | temp;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
	//TBitField temp(MaxPower);
	//temp.SetBit(Elem);
	//return BitField & temp;
	TSet result = *this;
	//result.DelElem(Elem);
	result.BitField.ClearBit(Elem);
	return result;
}

TSet TSet::operator*(const TSet &s) // �����������
{
	return BitField & s.BitField;
}

TSet TSet::operator~(void) // ����������
{
	return ~BitField;
}

 //���������� �����/������
istream &operator>>(istream &istr, TSet &s) // ����
{
	//TODO: ��������� ���� �������� � ������
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
			ostr << i << ", ";
		}
	}
	ostr << '}';
	return ostr;
}

