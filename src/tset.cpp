// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(-1)
{
	//TODO:
}


TSet::TSet(const TSet &s) : BitField(-1) // конструктор копирования
{
	//TODO:
}


TSet::TSet(const TBitField &bf) : BitField(-1) // конструктор преобразования типа
{
	//TODO:
}

TSet::operator TBitField()
{
	//TODO:
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	//TODO:
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	//TODO:
    return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	//TODO:
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	//TODO:
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	//TODO:
}

int TSet::operator==(const TSet &s) const // сравнение
{
	//TODO:
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	//TODO:
}

TSet TSet::operator+(const TSet &s) // объединение
{
	//TODO:
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	//TODO:
	//TELEM mask = 1 << 3;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	//TODO:
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	//TODO:
}

TSet TSet::operator~(void) // дополнение
{
	//TODO:
}

// перегрузка ввода/вывода
istream &operator>>(istream &istr, TSet &s) // ввод
{
	//TODO:
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	//TODO:
}
