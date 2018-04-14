// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef TEXT_LINK_H
#define TEXT_LINK_H

#include <fstream>
#include <iostream> 
#include <string>
#include "TDatValue.h"
//#include "TText.h"
using namespace std;

const enum {TextOK, TextWithoutDown = 101, TextWithoutNext, TextWithoutPrevious, TextError = -102, TextWithoutMemory};
const int TextLineLength = 20;
const int MemorySize = 20;

class Text;
class TextLink;
typedef TextLink *pTextLink;
typedef char TString[TextLineLength];

// Фиксация состояния памяти в класск TextLink
class TextMemory
{
	pTextLink pFirst; // Указатель на первое звено
	pTextLink pLast; // Указатель на последнее звено
	pTextLink pFree; // Указатель на первое свободное звено

	friend class TextLink;
};
typedef TextMemory *pTextMemory;

// Класс объектов-значений для строк текста
class TextLink : public TDataValue
{
protected:
	TString textString; // Поле для хранения строки текста
	pTextLink pNext; // Указатель на текущий уровень
	pTextLink pDown; //Указатель на подуровень
	static TextMemory MemoryHeader; // Система управления памятью
	
	virtual void Print(ostream &ostream) { ostream << textString; }
	
public:
	TextLink(TString string = nullptr, pTextLink pNext = nullptr, pTextLink pDown = nullptr);
	~TextLink() {}

	static void InitMemorySystem(int size = MemorySize); // Инициализация памяти
	static void PrintFreeLinks(); // Печать свободных звеньев

	void* operator new(const size_t size); // Выделение звена
	void operator delete(void *pLink); // Освобождение звена
	friend class Text;
	static void MemoryCleaner(Text& text); // Сборка мусора

	/*int*/bool IsAtomic() { return pDown == nullptr; } // Проверка атомарности звена
	pTextLink GetNext() { return pNext; }
	pTextLink GetDown() { return pDown; }
	//pTDataValue* GetCopy() { return new TextLink(string, pNext, pDown); }
};
#endif
