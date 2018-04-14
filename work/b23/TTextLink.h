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

// �������� ��������� ������ � ������ TextLink
class TextMemory
{
	pTextLink pFirst; // ��������� �� ������ �����
	pTextLink pLast; // ��������� �� ��������� �����
	pTextLink pFree; // ��������� �� ������ ��������� �����

	friend class TextLink;
};
typedef TextMemory *pTextMemory;

// ����� ��������-�������� ��� ����� ������
class TextLink : public TDataValue
{
protected:
	TString textString; // ���� ��� �������� ������ ������
	pTextLink pNext; // ��������� �� ������� �������
	pTextLink pDown; //��������� �� ����������
	static TextMemory MemoryHeader; // ������� ���������� �������
	
	virtual void Print(ostream &ostream) { ostream << textString; }
	
public:
	TextLink(TString string = nullptr, pTextLink pNext = nullptr, pTextLink pDown = nullptr);
	~TextLink() {}

	static void InitMemorySystem(int size = MemorySize); // ������������� ������
	static void PrintFreeLinks(); // ������ ��������� �������

	void* operator new(const size_t size); // ��������� �����
	void operator delete(void *pLink); // ������������ �����
	friend class Text;
	static void MemoryCleaner(Text& text); // ������ ������

	/*int*/bool IsAtomic() { return pDown == nullptr; } // �������� ����������� �����
	pTextLink GetNext() { return pNext; }
	pTextLink GetDown() { return pDown; }
	//pTDataValue* GetCopy() { return new TextLink(string, pNext, pDown); }
};
#endif
