// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <conio.h>
#include "TText.h"

static int TextLevel; // номер текущего уровня текста
static char stringBuffer[100];

pTextLink Text::GetFirstAtom(pTextLink textLink)
{
    pTextLink temp = textLink;
    while (!temp->IsAtomic())
    {
        Path.push(temp);
        temp->GetDown();
    }

    return temp;
}

void Text::PrintText(pTextLink textLink)
{

    if (textLink != NULL)
    {
        for (size_t i = 0; i < TextLevel; i++)
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
    //FIXME: add extra text level that break text structure
    //string buffer;
    pTextLink pLink = new TextLink();
    pTextLink temp = pLink;
    while (!textFile.eof())
    {
        //getline(textFile, buffer);
        textFile.getline(stringBuffer, 100, '\n');
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
	return 0;
}

int Text::GoDownLink()
{
	return 0;
}

int Text::GoNextLink()
{
	return 0;
}

int Text::GoPreviousLink()
{
	return 0;
}

string Text::GetLine(void)
{
	return string();
}

void Text::SetLine(string s)
{
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
	return !Path.empty();
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
