// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define _CRT_SECURE_NO_WARNINGS
#include "TTextLink.h"
#include <string.h>
#include "TText.h"
TextMemory TextLink::MemoryHeader;

TextLink::TextLink(TString string, pTextLink pNext, pTextLink pDown)
{
	this->pNext = pNext;
	this->pDown = pDown;
	if (string != nullptr)
	{
        //strcpy_s breaks up when trying to read from file
		strcpy(this->textString, string);
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

	MemoryHeader.pFirst = (pTextLink) new char[sizeof(TextLink) * size]/* { '\0' }*/;
	//for (int i = 0; i < size - 1; i++)
	//{
	//	MemoryHeader.pFirst[i] = nullptr;
	//}
    MemoryHeader.pFree = MemoryHeader.pFirst;
	MemoryHeader.pLast = MemoryHeader.pFirst + size - 1; /*&MemoryHeader.pFirst[size - 1]*/
	

	// �������������� ������ ��������� ������� �� ������
	pTextLink pLink = MemoryHeader./*pFree*/pFirst;
	for (int i = 0; i < size - 1; i++, pLink++)
	{
		pLink->pNext = pLink + 1;
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

        //for (; pLink != NULL; pLink = pLink->pNext)
        //    cout << pLink->textString << endl;
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

void TextLink::MemoryCleaner(Text& text)
{
    string str;

    // ���������� ����� ������ �������� "&&&"
    for (text.Reset(); !text.IsTextEnded(); text.GoNext())
    {
        if (str.find("&&&") != 0)
        {
            text.SetLine("&&&" + text.GetLine());
        }
    }

    // ���������� ������ ��������� �������
    pTextLink pLink = MemoryHeader.pFree;
    for(; pLink != nullptr; pLink = pLink->pNext)
    {
        strcpy(pLink->textString, "&&&");
    }

    // ������ ������
    pLink = MemoryHeader.pFirst;
    for (; pLink <= MemoryHeader.pLast; pLink++)
    {
        // ������ ������ ��� ��������� �����
        if (strstr(pLink->textString, "&&&") != nullptr)
        {
            // ������ ����������
            strcpy(pLink->textString, pLink->textString + 3);
        }
        else
        {
            // ���������� ����� � ������ ���������
            delete pLink;
        }
    }
}
