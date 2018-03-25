// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TTextLink.h"
#include <string.h>
TextMemory TextLink::MemoryHeader;

TextLink::TextLink(TString string, pTextLink pNext, pTextLink pDown)
{
	this->pNext = pNext;
	this->pDown = pDown;
	if (string != nullptr)
	{
		strcpy_s(this->textString, string);
	}
	else
	{
		this->textString[0] = '\0';
	}
}

/*static*/ void TextLink::InitMemorySystem(const int size)
{
	/*
	 � ���� ������ ���������� ������ ��� �������� �������. 
	 ��������� pFirst ��������������� �� ������ ����� ������� 
	 (����� ���������� ���� � ���� ��������� �� �����), 
	 ��������� pLast �� ��������� ������� �������. 
	 ����� ���� ������ ����������� ��� ������ ��������� �������, 
	 � ����� ������ ������ ������ ��������� ������� ����� ���� 
	 ���������� �� ������.. 
	*/
	if (size < 0)
	{
		throw logic_error("Memory initialization failed! Size of memory must be positive\n");
	}

	MemoryHeader.pFirst = (pTextLink)(new char[sizeof(TextLink) * size]/* { '\0' }*/);
	//for (int i = 0; i < size - 1; i++)
	//{
	//	MemoryHeader.pFirst[i] = nullptr;
	//}
	MemoryHeader.pLast = MemoryHeader.pFirst + size - 1; /*&MemoryHeader.pFirst[size - 1]*/
	MemoryHeader.pFree = MemoryHeader.pFirst;

	// �������������� ������ ��������� ������� �� ������
	pTextLink pLink = MemoryHeader.pFree/*First*/;
	for (int i = 0; i < size - 1; i++)
	{
		pLink->pNext = ++pLink;
	}
	pLink->pNext = nullptr;
}

/*static*/ void TextLink::PrintFreeLinks()
{
	pTextLink pLink = MemoryHeader.pFree;
	// MemoryHeader.pFree �� ����� ���� ������
	if (strlen(pLink[0].textString) == 0)
	{
		cout << "List of free links is empty\n";
	}
	//if (pLink == nullptr)
	//{
	//	cout << "List of free links is empty\n";
	//}
	else
	{
		cout << "List of free links:\n";
		while (pLink != nullptr)
		{
			cout << pLink->textString << endl;
			pLink = pLink->pNext;
		}
	}
}

void *TextLink::operator new(const size_t size)
{
	pTextLink temp = MemoryHeader.pFree;
	if (MemoryHeader.pFree != nullptr)
	{
		MemoryHeader.pFree = temp->pNext;
	}

	return temp;
}

void TextLink::operator delete(void *pLink)
{
	pTextLink temp = (pTextLink)pLink;
	temp->pNext = MemoryHeader.pFree;
	MemoryHeader.pFree = temp;
}

void TextLink::MemoryCleaner(const Text& text)
{
}
