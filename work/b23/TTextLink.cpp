#include "TText.h"

TextMemory TextLink::MemoryHeader;

TextLink::TextLink(TString string, pTextLink pNext, pTextLink pDown)
{
    this->pNext = pNext;
    this->pDown = pDown;
    if (string != nullptr)
    {
        strcpy(this->textString, string);
    }
    else
    {
        this->textString[0] = '\0';
    }
}

void TextLink::InitMemorySystem(const int size)
{
    if (size < 0)
    {
        throw logic_error("Memory initialization failed! Size of memory must be positive\n");
    }

    MemoryHeader.pFirst = (pTextLink) new char[sizeof(TextLink) * size];
    MemoryHeader.pFree = MemoryHeader.pFirst;
    MemoryHeader.pLast = MemoryHeader.pFirst + size - 1;

    // �������������� ������ ��������� ������� �� ������
    pTextLink pLink = MemoryHeader.pFirst;
    for (int i = 0; i < size - 1; i++, pLink++)
    {
        pLink->pNext = pLink + 1;
    }
    pLink->pNext = nullptr;
}

void TextLink::PrintFreeLinks()
{
    pTextLink pLink = MemoryHeader.pFree;

    cout << "List of free links:\n";
    while (pLink != nullptr)
    {
        cout << pLink->textString << endl;
        pLink = pLink->pNext;
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

void TextLink::MemoryCleaner(Text &text)
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
    for (; pLink != nullptr; pLink = pLink->pNext)
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
