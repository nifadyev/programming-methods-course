// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define _CRT_SECURE_NO_WARNINGS

//#ifdef _WIN32
//#include <conio.h>
//#endif
//#ifdef __linux__
//#include <curses.h>
//#endif

#include <cstring>
#include "TText.h"

const int bufferSize = 100;
static int TextLevel; // ����� �������� ������ ������
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

void Text::PrintTextInFile(pTextLink textLink, ofstream &output)
{

    if (textLink != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
        {
            output << " ";
        }
        output << textLink->textString << endl;

        TextLevel++; 
        PrintTextInFile(textLink->GetDown(), output);

        TextLevel--; 
        PrintTextInFile(textLink->GetNext(), output);
    }
}

pTextLink Text::ReadText(ifstream & textFile)
{
    //FIXME: adding extra text level that break text structure
    //string buffer;
    pTextLink pLink, temp;
    pLink = temp = new TextLink();
    //pTextLink temp = pLink;
    //while (!textFile.eof())
    while (textFile.eof() == 0)
    {
        textFile.getline(stringBuffer, bufferSize, '\n');
        if (stringBuffer[0] == '}')
        {
            //Works well without textlevel -- & ++
            TextLevel--;
            break;
        }
        else if (stringBuffer[0] == '{')
        {
            TextLevel++;
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

    // Крашит большинство тестов
    //if (textLink == nullptr)
    //{
    //    textLink = new TextLink();
    //}
    //pFirst = textLink;


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
    //if (pCurrent != nullptr)
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
        throw logic_error("Error! Current link is empty\n");
        //return -1;
    }

    if (pCurrent->pDown == nullptr)
    {
        throw logic_error("Error! Current link has not got down links\n");
       // return -1;
    }

    Path.push(pCurrent);
    pCurrent = pCurrent->pDown;
	return 0;
}

int Text::GoNextLink()
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
        //return -1;
    }

    if (pCurrent->pNext == nullptr)
    {
        throw logic_error("Error! Current link has not got next links\n");
        //return -1;
    }

    Path.push(pCurrent);
    pCurrent = pCurrent->pNext;
	return 0;
}

int Text::GoPreviousLink()
{
    if (Path.empty())
    {
        throw logic_error("Error! Path is empty\n");
        return -1;
    }
    if (pCurrent == pFirst)
    {
        throw logic_error("Error! Cannot get previous link. Current link is the first one\n");
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

void Text::SetLine(const string &s)
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

void Text::InsertDownLine(const string &s)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }

    //if (strcmp(pCurrent->textString, ""))
    //{
    //    throw logic_error("Error! Current link is empty\n");
    //}

    char emptyString[] = "";
    pTextLink temp = new TextLink(emptyString, pCurrent->pDown);

    strncpy(temp->textString, s.c_str(), TextLineLength);
    temp->textString[TextLineLength - 1] = '\0';
    pCurrent->pDown = temp;
}

void Text::InsertDownSection(const string &s)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }

    //if (strcmp(pCurrent->textString, ""))
    //{
    //    throw logic_error("Error! Current link is empty\n");
    //}

    char emptyString[] = "";
    pTextLink temp = new TextLink(emptyString, nullptr, pCurrent->pDown);

    strncpy(temp->textString, s.c_str(), TextLineLength);
    temp->textString[TextLineLength - 1] = '\0';
    pCurrent->pDown = temp;
}

void Text::InsertNextLine(const string &s)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }

    //if (strlen(pCurrent->textString) == 0)
    //{
    //    throw logic_error("Error! Current link is empty\n");
    //}
    char emptyString[] = "";
    pTextLink temp = new TextLink(emptyString, pCurrent->pNext);

    strncpy(temp->textString, s.c_str(), TextLineLength);
    temp->textString[TextLineLength - 1] = '\0';
    pCurrent->pNext = temp;
}

void Text::InsertNextSection(const string &s)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }

    //if (strlen(pCurrent->textString) == 0)
    //{
    //    throw logic_error("Error! Current link is empty\n");
    //}
    char emptyString[] = "";
    pTextLink temp = new TextLink(emptyString, nullptr, pCurrent->pNext);

    strncpy(temp->textString, s.c_str(), TextLineLength);
    temp->textString[TextLineLength - 1] = '\0';
    pCurrent->pNext = temp;
}

void Text::DeleteDownLine(void)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }
    if (pCurrent->pDown == nullptr)
    {
        throw logic_error("Error! Current link has not got down links\n");
    }

    pTextLink temp = pCurrent->pDown->pNext;
    
    if (pCurrent->pDown->pDown == nullptr)
    {
        pCurrent->pDown = temp;
    }
}

void Text::DeleteDownSection(void)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }
    if (pCurrent->pDown == nullptr)
    {
        throw logic_error("Error! Current link has not got down links\n");
    }

    pTextLink temp = pCurrent->pDown->pNext;

    pCurrent->pDown = temp;

}

void Text::DeleteNextLine(void)
{
    if (pCurrent == nullptr)
    {
        //TODO: Maybe change logic_error to range_error
        throw logic_error("Error! Current link is empty\n");
    }
    if (pCurrent->pNext == nullptr)
    {
        throw logic_error("Error! Current link has not got next links\n");
    }

    if (!pCurrent->pNext->IsAtomic())
    {
        throw logic_error("Error! Cannot delete link which has down links\n");
    }

    pCurrent->pNext = pCurrent->pNext->pNext;
}

void Text::DeleteNextSection(void)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }
    if (pCurrent->pNext == nullptr)
    {
        throw logic_error("Error! Current link has not got next links\n");
    }

    pCurrent->pNext = pCurrent->pNext->pNext;
}

int Text::Reset(void)
{
    while (!iteratorStack.empty())
    {
        iteratorStack.pop();
    }
	pCurrent = pFirst;

	if (pCurrent != nullptr)
	{
        iteratorStack.push(pCurrent);
		if (pCurrent->pNext != nullptr)
		{
            iteratorStack.push(pCurrent->pNext);
		}

		if (pCurrent->pDown != nullptr)
		{
            iteratorStack.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

bool Text::IsTextEnded(void) const
{
	return !iteratorStack.size();
}

int Text::GoNext(void)
{
    if (!IsTextEnded()) 
    {
        pCurrent = iteratorStack.top();
        iteratorStack.pop();
        if (pCurrent != pFirst) 
        {
            if (pCurrent->pNext != nullptr)
            {
                iteratorStack.push(pCurrent->pNext);
            }
            if (pCurrent->pDown != nullptr)
            {
                iteratorStack.push(pCurrent->pDown);
            }
        }
    }
    return IsTextEnded();
}

void Text::Read(const char *pFileName)
{
    //TODO: add check for correct filename
    ifstream textFile(pFileName);
    TextLevel = 0;

    if (&textFile != NULL)
    {
        pFirst = ReadText(textFile);
    }
}

void Text::Write(const char * pFileName)
{
    //TODO: add check for empty text
    TextLevel = 0;
    ofstream TextFile(pFileName);
    PrintTextInFile(pFirst, TextFile);
}

void Text::Print(void)
{
    TextLevel = 0;
    PrintText(pFirst);
}
