// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
//#include <bitset>;

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLem = (int)ceil((double)len / sizeMem);
	pMem = new TELEM[MemLen];

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	//TODO:
	BitLen = bf.BitLen;
	pMem = bf.pMem;
	MemLen = bf.MemLen;
}

TBitField::~TBitField()
{
	//TODO:
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	//TODO:
	return 0;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	//TODO:
	TELEM mask;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	//TODO:
  return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	//TODO:
	//this->BitLen = n;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	//TODO:
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	//TODO:
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	TBitField result(bf);
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = bf.pMem;
	return TBitField(result);

	//result.BitLen = bf.BitLen;
	//result.MemLen = bf.MemLen;
	//result.pMem = bf.pMem;
	//return result;
	//TODO:
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	//TODO:
  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	//TODO:
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	//TODO:
	TBitField result(bf);
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	//TODO:
	TBitField result(bf);
}

TBitField TBitField::operator~(void) // отрицание
{
	//TODO:
	TBitField result();
	//return this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	//TODO:
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	//TODO:
	ostr << bf;
	return ostr;
}
