#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "TText.h"

const int bufferSize = 100;
static int TextLevel;
static char stringBuffer[bufferSize + 1];

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
}

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

pText Text::GetCopy()
{
	return new Text(GetLinkCopy(pFirst));
}

pTextLink Text::GetLinkCopy(pTextLink link)
{
    if (link == nullptr)
    {
        throw invalid_argument("Error! Empty agrument\n");
    }

    pTextLink pNxt = nullptr, pDwn = nullptr;

    if (link->pDown != nullptr)
    {
        pDwn = GetLinkCopy(link->pDown);
    }
    if (link->pNext != nullptr)
    {
        pNxt = GetLinkCopy(link->pNext);
    }

    return new TextLink(link->textString, pNxt, pDwn);
}

int Text::GoFirstLink()
{
    while (!Path.empty())
    {
        Path.pop();
    }

    pCurrent = pFirst;
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
    }
    if (pCurrent->pDown == nullptr)
    {
        throw logic_error("Error! Current link has not got down links\n");
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
    }

    if (pCurrent->pNext == nullptr)
    {
        throw logic_error("Error! Current link has not got next links\n");
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
    }
    if (pCurrent == pFirst)
    {
        throw logic_error("Error! Cannot get previous link. Current link is the first one\n");
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

    strncpy(pCurrent->textString, s.c_str(), TextLineLength);
    pCurrent->textString[TextLineLength - 1] = '\0';
}

void Text::InsertDownLine(const string &s)
{
    if (pCurrent == nullptr)
    {
        throw logic_error("Error! Current link is empty\n");
    }

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
    ifstream textFile(pFileName);

    if (textFile.is_open())
    {
        TextLevel = 0;

        if (&textFile != NULL)
        {
            pFirst = ReadText(textFile);
        }
        textFile.close();
    }
    else
    {
        textFile.close();
        throw invalid_argument("Error! File with this name wasn't found\n");
    }
}

pTextLink Text::ReadText(ifstream &textFile)
{
    pTextLink pLink, temp;
    pLink = temp = new TextLink();

    while (textFile.eof() == 0)
    {
        textFile.getline(stringBuffer, bufferSize, '\n');
        if (stringBuffer[0] == '}')
        {
            break;
        }
        else if (stringBuffer[0] == '{')
        {
            pLink->pDown = ReadText(textFile);
        }
        else
        {
            pLink->pNext = new TextLink(stringBuffer);
            pLink = pLink->pNext;
        }
    }

    pLink = temp;
    if (temp->pDown == nullptr)
    {
        temp = temp->pNext;
        delete pLink;
    }

    return temp;
}

void Text::Write(const char *pFileName)
{
    TextLevel = 0;
    ofstream TextFile(pFileName);
    WriteText(pFirst, TextFile);
}

void Text::WriteText(pTextLink textLink, ofstream &output)
{
    if (textLink != NULL)
    {
        for (int i = 0; i < TextLevel; i++)
        {
            output << " ";
        }
        output << textLink->textString << endl;

        TextLevel++;
        WriteText(textLink->GetDown(), output);

        TextLevel--;
        WriteText(textLink->GetNext(), output);
    }
}

void Text::Print(void)
{
    TextLevel = 0;
    PrintText(pFirst);
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
