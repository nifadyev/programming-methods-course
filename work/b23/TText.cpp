// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#include "TText.h"

const int bufferSize = 100;
static int TextLevel; // номер текущего уровня текста
static char stringBuffer[bufferSize + 1];

pTextLink Text::GetFirstAtom(pTextLink textLink)
{
    pTextLink temp = textLink;
    while (!temp->IsAtomic())
    {
        iteratorStack.push(temp);
        temp->GetDown();
    }

    return temp;
}

void Text::PrintText(pTextLink textLink)
{

    if (textLink != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
        {
            cout << " ";
        }
        cout << textLink->textString << endl;

        TextLevel++; 
        PrintText(textLink->GetDown());

        TextLevel--; 
        PrintText(textLink->GetNext());
    }
}

pTextLink Text::ReadText(ifstream & textFile)
{
    //FIXME: adding extra text level that break text structure
    //string buffer;
    pTextLink pLink = new TextLink();
    pTextLink temp = pLink;
    while (!textFile.eof())
    {
        //getline(textFile, buffer);
        textFile.getline(stringBuffer, bufferSize, '\n');
        //if (buffer.front() == '}')
        if (stringBuffer[0] == '}')
        {
            //TextLevel--;
            break;
        }
        //else if (buffer.front() == '{')
        else if (stringBuffer[0] == '{')
        {
            //TextLevel++;
            pLink->pDown = ReadText(textFile);
        }
        else
        {
            //pLink->pNext = new TextLink((char*)buffer.c_str());
            pLink->pNext = new TextLink(stringBuffer);
            pLink = pLink->pNext;
        }
    }

    pLink = temp;
    if (temp->pDown == /*NULL*/nullptr)
    {
        temp = temp->pNext;
        delete pLink;
    }
	return temp;
}

Text::Text(pTextLink textLink)
{
    if (textLink != nullptr)
    {
        pFirst = pCurrent = textLink;
    }
    else
    {
        pFirst = new TextLink();
        pCurrent = pFirst;
    }
    //Path.push(pFirst);
    //iteratorStack.push(pFirst);
}

pText Text::GetCopy()
{
	return pText();
}

int Text::GoFirstLink()
{
    //Reset();
    while (!Path.empty())
    {
        Path.pop();
    }

    pCurrent = pFirst;
    //if (pCurrent == nullptr)
    if (pCurrent->textString[0] == '\0')
    {
        return -1;
    }

	return 0;
}

int Text::GoDownLink()
{
    if (pCurrent == nullptr)
    {
        throw "Error! Current link is empty\n";
        return -1;
    }

    if (pCurrent->pDown == nullptr)
    {
        throw "Error! Current link has not got down links\n";
        return -1;
    }

    Path.push(pCurrent);
    pCurrent = pCurrent->pDown;
	return 0;
}

int Text::GoNextLink()
{
    if (pCurrent == nullptr)
    {
        throw "Error! Current link is empty\n";
        return -1;
    }

    if (pCurrent->pNext == nullptr)
    {
        throw "Error! Current link has not got next links\n";
        return -1;
    }

    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
	return 0;
}

int Text::GoPreviousLink()
{
    if (Path.empty())
    {
        throw "Error! Path is empty\n";
        return -1;
    }
    if (pCurrent == pFirst)
    {
        throw "Error! Cannot get previous link. Current link is the first one\n";
        return -1;
    }

    pCurrent = Path.top();
    Path.pop();
	return 0;
}

string Text::GetLine(void)
{
    if (pCurrent == nullptr)
    {
        return "";
    }

	return pCurrent->textString;
}

void Text::SetLine(string s)
{
    if (s.size() > bufferSize)
    {
        throw("Error! Size of the string must be less than ...\n");
    }
    //if (s.empty())
    //{

    //}
    //strcpy(pCurrent->textString, s.c_str());
    strncpy(pCurrent->textString, s.c_str(), TextLineLength);
    pCurrent->textString[TextLineLength - 1] = '\0';
}

void Text::InsertDownLine(string s)
{
}

void Text::InsertDownSection(string s)
{
}

void Text::InsertNextLine(string s)
{
}

void Text::InsertNextSection(string s)
{
}

void Text::DeleteDownLine(void)
{
}

void Text::DeleteDownSection(void)
{
}

void Text::DeleteNextLine(void)
{
}

void Text::DeleteNextSection(void)
{
}

int Text::Reset(void)
{
	pCurrent = pFirst;

	if (pCurrent != nullptr)
	{
		Path.push(pCurrent);
		if (pCurrent->pNext != nullptr)
		{
			Path.push(pCurrent->pNext);
		}

		if (pCurrent->pDown != nullptr)
		{
			Path.push(pCurrent->pDown);
		}
	}
	return 0;
}

bool Text::IsTextEnded(void) const
{
	return !iteratorStack.empty();
}

int Text::GoNext(void)
{
	return 0;
}

void Text::Read(const char * pFileName)
{
    ifstream textFile(pFileName);
    TextLevel = 0;
    if (&textFile != NULL)
        pFirst = ReadText(textFile);
}

void Text::Write(char * pFileName)
{
}

void Text::Print(void)
{
    TextLevel = 0;
    PrintText(pFirst);
}
