#ifndef TEXT_LINK_H
#define TEXT_LINK_H

#include <fstream>
#include <iostream> 
#include <cstring>
#include "DatValue.h"
using namespace std;

const int TextLineLength = 50; // Max line length
const int MemorySize = 50;

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

	static void MemoryCleaner(Text& text); // ������ ������

	bool IsAtomic() { return pDown == nullptr; } // �������� ����������� �����
	pTextLink GetNext() { return pNext; }
	pTextLink GetDown() { return pDown; }

    friend class Text;
};
#endif
