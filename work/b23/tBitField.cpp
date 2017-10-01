// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

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

TBitField::TBitField(const TBitField &bf) // ����������� �����������
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

int TBitField::GetMemIndex(const int n) const // ���������� ����������� ����(TELEM��) / ������ ��� ��� ���� n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
	TELEM mask = 1;
	mask = mask << n % (sizeof(TELEM) * 8);
	return mask;
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
	if ((n < 0) || (n > BitLen))
		throw WRONG_RANGE;
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClearBit(const int n) // �������� ���
{
	if ((n < 0) || (n > BitLen))
		throw WRONG_RANGE;
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] = pMem[index] & ~mask;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
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

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) // ������������
{
	if (pMem != bf.pMem)
	{
		if (BitLen != bf.BitLen)
		{
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			delete[] pMem;
			pMem = new TELEM[MemLen]; // ����� ��������� ������
		}
		for (int i = 0; i < MemLen; i++) 
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // ���������
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

int TBitField::operator!=(const TBitField &bf) const // ���������
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

TBitField TBitField::operator|(const TBitField &bf) // �������� "���"
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

TBitField TBitField::operator&(const TBitField &bf) // �������� "�"
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

TBitField TBitField::operator~(void) // ���������
{
	TBitField result(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		result.pMem[i] = ~pMem[i];
	}
	return result;
}

// ����/�����

istream &operator>>(istream &istr, TBitField &bf) // ����
{
	// ��� ������������������ 0 � 1
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

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
	ostr << "Length = " << bf.BitLen << endl;
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}

