// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TText.h"



pTextLink Text::GetFirstAtom(pTextLink textLink)
{
	return pTextLink();
}

void Text::PrintText(pTextLink textLink)
{
}

pTextLink Text::ReadText(ifstream & textFile)
{
	return pTextLink();
}

Text::Text(pTextLink textLink)
{
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

void Text::Read(char * pFileName)
{
}

void Text::Write(char * pFileName)
{
}

void Text::Print(void)
{
}
