# Лабораторная работа №6. Тексты

## Цели и задачи

В рамках лабораторной работы ставится задача разработки учебного редактора текстов с поддержкой следующих операций:

-	выбор текста для редактирования (или создание нового текста);
-	демонстрация текста на экране дисплея;
-	поддержка средств указания элементов (уровней) текста;
-	вставка, удаление и замена строк текста;
-	запись подготовленного текста в файл.

При выполнении операций чтения (при выборе для редактирования уже 
существующего текста) и записи редактор должен использовать 
стандартный формат, принятый в файловой системе для представления
 текстовых файлов, обеспечивая тем самым совместимость учебного 
редактора текстов и существующего программного обеспечения. 

## Описание работы
### Реализация класса `TTextLink`
#### ttextlink.h
```C++
#ifndef TEXT_LINK_H
#define TEXT_LINK_H

#include <fstream>
#include <iostream> 
#include <string>
#include "TDatValue.h"
using namespace std;

const int TextLineLength = 50; // Max line length
const int MemorySize = 50;

class Text;
class TextLink;
typedef TextLink *pTextLink;
typedef char TString[TextLineLength];


class TextMemory
{
	pTextLink pFirst; 
	pTextLink pLast; 
	pTextLink pFree;

	friend class TextLink;
};
typedef TextMemory *pTextMemory;


class TextLink : public TDataValue
{
protected:
	TString textString;
	pTextLink pNext; 
	pTextLink pDown; 
	static TextMemory MemoryHeader;
	
	virtual void Print(ostream &ostream) { ostream << textString; }
	
public:
	TextLink(TString string = nullptr, pTextLink pNext = nullptr, pTextLink pDown = nullptr);
	~TextLink() {}

	static void InitMemorySystem(int size = MemorySize);
	static void PrintFreeLinks();

	void* operator new(const size_t size);
	void operator delete(void *pLink);

	static void MemoryCleaner(Text& text);

	bool IsAtomic() { return pDown == nullptr; }
	pTextLink GetNext() { return pNext; }
	pTextLink GetDown() { return pDown; }

    friend class Text;
};
#endif
```

#### ttextlink.сpp
```C++
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

	// Упорядочивание списка свободных звеньев по памяти
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

void* TextLink::operator new(const size_t size)
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

    // Маркировка сторк текста маркером "&&&"
    for (text.Reset(); !text.IsTextEnded(); text.GoNext())
    {
        if (str.find("&&&") != 0)
        {
            text.SetLine("&&&" + text.GetLine());
        }
    }

    // Маркировка списка свободных звеньев
    pTextLink pLink = MemoryHeader.pFree;
    for(; pLink != nullptr; pLink = pLink->pNext)
    {
        strcpy(pLink->textString, "&&&");
    }

    // Сборка мусора
    pLink = MemoryHeader.pFirst;
    for (; pLink <= MemoryHeader.pLast; pLink++)
    {
        // Строка текста или свободное звено
        if (strstr(pLink->textString, "&&&") != nullptr)
        {
            // Снятие маркировки
            strcpy(pLink->textString, pLink->textString + 3);
        }
        else
        {
            // Неучтенное звено в список свободных
            delete pLink;
        }
    }
}
```

### Реализация класса `TText`
#### ttext.h
```C++
#ifndef TEXT_H
#define TEXT_H

#include "TTextLink.h"
#include <stack>

class Text;
typedef Text *pText;

class Text
{
protected:
	pTextLink pFirst;               // Указатель корня дерева
	pTextLink pCurrent;             // Указатель текущей строки
	stack<pTextLink> Path;          // Стек траектории движения по тексту
	stack<pTextLink> iteratorStack; // Стек для итератора

	pTextLink GetFirstAtom(pTextLink textLink); // Поиск первого атома
	void PrintText(pTextLink textLink);         // Печать текста с указанного звена
    void WriteText(pTextLink textLink, ofstream &output); // Печать текста с указанного звена
	pTextLink ReadText(ifstream &textFile);     // Чтение текста из файла
    pTextLink GetLinkCopy(pTextLink link);
public:
	Text(pTextLink textLink = nullptr);
	~Text() { pFirst = nullptr; }
	pText GetCopy();

	// Навигация
	int GoFirstLink();    // Переход к первой строке
	int GoDownLink();     // Переход к следующей строке по Down
	int GoNextLink();     // Переход к следующей строке по Next
	int GoPreviousLink(); // Переход к предыдущей позиции в тексте

	// Доступ
	string GetLine(void);          // чтение текущей строки
	void SetLine(const string &s); // замена текущей строки 
	
    // модификация
    // Section = partition + subpartitions
    // Line = partition
	void InsertDownLine(const string &s);    // Вставка строки в подуровень
	void InsertDownSection(const string &s); // Вставка раздела в подуровень
	void InsertNextLine(const string &s);    // Вставка строки в том же уровне
	void InsertNextSection(const string &s); // Вставка раздела в том же уровне
	
    void DeleteDownLine(void);               // Удаление строки в подуровне
	void DeleteDownSection(void);            // Удаление раздела в подуровне
	void DeleteNextLine(void);               // Удаление строки в том же уровне
	void DeleteNextSection(void);            // Удаление раздела в том же уровне
	
	// Итератор
	int Reset(void);               // Установить на первую запись
	bool IsTextEnded(void) const;  // Текст завершен?
	int GoNext(void);              // Переход к следующей записи
	
	// Работа с файлами
	void Read(const char *pFileName);  // Ввод текста из файла
	void Write(const char *pFileName); // Вывод текста в файл
	void Print(void);                   // Печать текста
};
#endif
```

#### ttext.cpp
```C++
// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "TText.h"

const int bufferSize = 100;
static int TextLevel; // ����� �������� ������ ������
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
```

### Реализация Main
#### main.cpp
```C++
#include <iostream>
#include "TText.h"
using namespace std;

int main()
{
    TextLink::InitMemorySystem();
    Text text;
    pText pCopiedText = nullptr;

    text.SetLine("A");
    text.InsertDownLine("c");
    text.InsertDownLine("b");
    text.InsertDownLine("a");
    text.InsertDownSection("a");
    text.GoFirstLink(); 
    text.InsertNextLine("B");
    text.GoNextLink();
    text.InsertDownLine("c");
    text.InsertDownLine("b");
    text.InsertDownLine("a");
    text.InsertNextLine("D");
    text.InsertNextLine("C");

    pCopiedText = text.GetCopy();

    text.Reset();
    text.GoNextLink();
    text.DeleteDownSection();
    text.DeleteNextLine();

    text.Write("output.txt");

    text.Print();

    return 0;
}
```

## Тестирование
#### TextTestKit.cpp
```C++
#include <gtest/gtest.h>
#include"TTextLink.h"
#include "TText.h"
#include "TTextViewer.h"

/*-------------------------------Testing_TextLink_class-------------------------------*/
TEST(TextLink, Can_Create_TextLink_Without_Parameters)
{
	TextLink textLink;

	ASSERT_NO_THROW(TextLink textLink);
	EXPECT_EQ(textLink.GetDown(), nullptr);
	EXPECT_EQ(textLink.GetNext(), nullptr);
	EXPECT_TRUE(textLink.IsAtomic());
}

TEST(TextLink, Can_Create_TextLink_With_First_Parameter)
{
	TString string = "qwerty";
	TextLink textLink;

	ASSERT_NO_THROW(TextLink textLink(string));
}

TEST(TextLink, Can_Create_TextLink_With_Second_Parameter)
{
    TString string = "qwerty", emptyString = "";
    pTextLink textLinkNext = new TextLink(string);
    TextLink textLink(emptyString, textLinkNext);
   
    EXPECT_EQ(textLink.GetDown(), nullptr);
    EXPECT_EQ(textLink.GetNext(), textLinkNext);
    EXPECT_TRUE(textLink.IsAtomic());
}

TEST(TextLink, Can_Create_TextLink_With_Third_Parameter)
{
    TString string = "qwerty", emptyString = "";
    pTextLink textLinkDown = new TextLink(string);
    TextLink textLink(emptyString, nullptr, textLinkDown);
   
    EXPECT_EQ(textLink.GetNext(), nullptr);
    EXPECT_EQ(textLink.GetDown(), textLinkDown);
    EXPECT_TRUE(textLink.IsAtomic());
}

TEST(TextLink, Can_Create_TextLink_With_All_Parameters)
{
    TString string = "qwerty", emptyString = "";
    pTextLink textLinkNext = new TextLink(string);
    pTextLink textLinkDown = new TextLink(string);
    TextLink textLink(emptyString, textLinkNext, textLinkDown);
   
    EXPECT_EQ(textLink.GetNext(), textLinkNext);
    EXPECT_EQ(textLink.GetDown(), textLinkDown);
    EXPECT_TRUE(textLink.IsAtomic());
}

TEST(TextLink, Can_Initialaze_Memory_System_Without_Parameters)
{
	TextLink textLink;

	ASSERT_NO_THROW(textLink.InitMemorySystem());
}

TEST(TextLink, Throw_When_Initialazing_Memory_System_With_Neagative_Parameter)
{
	TextLink textLink;

	ASSERT_THROW(textLink.InitMemorySystem(-12), logic_error);
}

TEST(TextLink, Can_Initialaze_Memory_System_With_Parameters)
{
	TextLink textLink;

	ASSERT_NO_THROW(textLink.InitMemorySystem(698));
	ASSERT_NO_THROW(textLink.InitMemorySystem(2));
	ASSERT_NO_THROW(textLink.InitMemorySystem(47));
	ASSERT_NO_THROW(textLink.InitMemorySystem(2351));
}

TEST(TextLink, Can_Create_Text_Link_Using_Operator_New)
{
    TextLink::InitMemorySystem();
	TextLink *textLink; 

	ASSERT_NO_THROW(textLink = new TextLink[24]);
}

/*-------------------------------Testing_TText_class-------------------------------*/

TEST(Text, Can_Create_Empty_Text)
{
    ASSERT_NO_THROW(Text text);
}

TEST(Text, Can_Create_Text_From_Text_Link)
{
    TString string = "wasd";
    pTextLink link = new TextLink(string);

    ASSERT_NO_THROW(Text text(link));
}

TEST(Text, Can_Read_Text_From_File)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_NO_THROW(text.Read("input.txt"));
}

TEST(Text, Can_Go_To_The_First_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "1";
   
    text.Read("input.txt");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoFirstLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_To_The_First_Link_Returns_0_If_Everything_Is_Correct)
{
    Text text;
    TextLink::InitMemorySystem();
    text.Read("input.txt");

    EXPECT_EQ(text.GoFirstLink(), 0);
}

TEST(Text, Throw_When_Trying_To_Go_To_The_First_Link_In_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    EXPECT_EQ(text.GoFirstLink(), -1);
}

TEST(Text, Can_Go_Down_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "1.1";
    
    text.Read("input.txt");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoDownLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Down_Link_Returns_0_If_Success)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();

    EXPECT_EQ(text.GoDownLink(), 0);
}


TEST(Text, Throws_If_Go_Down_Link_In_Lowest_Level)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");

    ASSERT_THROW(text.GoDownLink(), logic_error);
}

TEST(Text, Throws_If_Go_Down_Link_With_Empty_Current_Link)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.GoDownLink(), logic_error);
}

TEST(Text, Can_Go_Next_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "2";

    text.Read("input.txt");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoNextLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Next_Link_Returns_0_If_Success)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();

    EXPECT_EQ(text.GoNextLink(), 0);
}

TEST(Text, Throws_If_Go_Next_Link_In_Lowest_Level)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");

    ASSERT_THROW(text.GoNextLink(), logic_error);
}

TEST(Text, Throws_If_Go_Next_Link_With_Empty_Current_Link)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.GoNextLink(), logic_error);
}

TEST(Text, Can_Go_Previous_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "1";

    text.Read("input.txt");
    text.GoFirstLink();
    text.GoNextLink();

    ASSERT_NO_THROW(text.GoPreviousLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Previous_Link_Returns_0_If_Success)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();
    text.GoNextLink();

    EXPECT_EQ(text.GoPreviousLink(), 0);
}

TEST(Text, Throws_If_Go_Next_Link_In_Highest_Level)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();

    ASSERT_THROW(text.GoPreviousLink(), logic_error);
}

TEST(Text, Throws_If_Go_Previous_Link_With_Empty_Current_Link)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.GoNextLink(), logic_error);
}


TEST(Text, Can_Insert_Down_Line_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "example";

    ASSERT_NO_THROW(text.InsertDownLine("example"));

    text.GoDownLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Muptiple_Down_Line)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "1.1.1";

    text.InsertDownLine("1");
    text.InsertDownLine("1.1");
    text.InsertDownLine("1.1.1");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Down_Line_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "1.0";

    text.Read("input.txt");
    text.GoFirstLink();
    text.InsertDownLine("1.0");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Line_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_NO_THROW(text.InsertNextLine("A"));

    text.GoNextLink();
    EXPECT_EQ(text.GetLine(), "A");
}

TEST(Text, Can_Insert_Muptiple_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "15";

    text.InsertNextLine("13");
    text.InsertNextLine("14");
    text.InsertNextLine("15");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Line_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "A";

    text.Read("input.txt");
    text.InsertNextLine("A");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}


TEST(Text, Can_Insert_Down_Section_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "0.1";

    ASSERT_NO_THROW(text.InsertDownSection("0.1"));

    text.GoDownLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Muptiple_Down_Sections)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "0.1.1";

    text.InsertDownSection("0");
    text.InsertDownSection("0.1");
    text.InsertDownSection("0.1.1");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Down_Section_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "0.0";

    text.Read("input.txt");
    text.GoFirstLink();
    text.InsertDownSection("0.0");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Section_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "A";

    ASSERT_NO_THROW(text.InsertNextSection("A"));

    text.GoNextLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Muptiple_Next_Sections)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "15";

    text.InsertNextSection("13");
    text.InsertNextSection("14");
    text.InsertNextSection("15");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Section_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "3";

    text.Read("input.txt");
    text.InsertNextSection("3");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}


TEST(Text, Throw_When_Delete_Down_Line_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteDownLine(), logic_error);
}

TEST(Text, Throw_When_Delete_Down_Line_Text_Without_Down_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("A");

    ASSERT_ANY_THROW(text.DeleteDownLine());
}

TEST(Text, Can_Delete_Down_Line_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();
    text.GoNextLink();
    text.GoDownLink();

    ASSERT_NO_THROW(text.DeleteDownLine());
}

TEST(Text, Can_Delete_Muptiple_Down_Lines)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.DeleteDownLine());
    ASSERT_NO_THROW(text.DeleteDownLine());
    ASSERT_NO_THROW(text.DeleteDownLine());
}

TEST(Text, Throw_When_Delete_Next_Line_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextLine(), logic_error);
}

TEST(Text, Throw_When_Delete_Next_Line_From_Text_Without_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextLine(), logic_error);
}

TEST(Text, Throw_When_Delete_Not_Atomic_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");

    ASSERT_THROW(text.DeleteNextLine(), logic_error);
}

TEST(Text, Can_Delete_Next_Line_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextLine("QWERTY");

    ASSERT_NO_THROW(text.DeleteNextLine());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Delete_Muptiple_Next_Lines)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextLine("Q");
    text.InsertNextLine("W");
    text.InsertNextLine("E");

    ASSERT_NO_THROW(text.DeleteNextLine());
    ASSERT_NO_THROW(text.DeleteNextLine());
    ASSERT_NO_THROW(text.DeleteNextLine());
    EXPECT_EQ(text.GetLine(), expectedString);
}


TEST(Text, Throw_When_Delete_Down_Section_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteDownSection(), logic_error);
}

TEST(Text, Throw_When_Delete_Down_Section_Text_Without_Down_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("A");

    ASSERT_ANY_THROW(text.DeleteDownSection());
}

TEST(Text, Can_Delete_Down_Section_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();
    text.GoNextLink();
    text.GoDownLink();

    ASSERT_NO_THROW(text.DeleteDownSection());
}

TEST(Text, Can_Delete_Muptiple_Down_Section)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoFirstLink();
    text.GoNextLink();

    ASSERT_NO_THROW(text.DeleteDownSection());
}


TEST(Text, Throw_When_Delete_Next_Sections_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextSection(), logic_error);
}

TEST(Text, Throw_When_Delete_Next_Section_From_Text_Without_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextSection(), logic_error);
}

TEST(Text, Can_Delete_Next_Section_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextSection("QWERTY");

    ASSERT_NO_THROW(text.DeleteNextSection());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Delete_Muptiple_Next_Sections)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextSection("Q");
    text.InsertNextSection("W");
    text.InsertNextSection("E");

    ASSERT_NO_THROW(text.DeleteNextSection());
    EXPECT_EQ(text.GetLine(), expectedString);
}


TEST(Text, Can_Reset_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    text.InsertNextLine("3");

    ASSERT_NO_THROW(text.Reset());
    EXPECT_EQ(text.Reset(), 0);
}

TEST(Text, Can_Reset_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    ASSERT_NO_THROW(text.Reset());
    EXPECT_EQ(text.Reset(), 0);
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Is_Text_Ended_Returns_True)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.GoNext();

    ASSERT_NO_THROW(text.IsTextEnded());
    EXPECT_TRUE(text.IsTextEnded());
}

TEST(Text, Is_Text_Ended_Returns_False)
{
    TextLink::InitMemorySystem();
    Text text;

    text.Read("input.txt");
    text.Reset();

    ASSERT_NO_THROW(text.IsTextEnded());
    EXPECT_FALSE(text.IsTextEnded());
}

TEST(Text, Can_Go_Next)
{
    TextLink::InitMemorySystem();
    TString a = "1", expectedString = "2";
    Text txt(new TextLink(a));
    
    txt.GoFirstLink();
    txt.InsertNextLine("2");
    txt.GoNextLink();
    txt.InsertNextLine("3");
    txt.GoNextLink();   
    txt.Reset();
    txt.GoNext();
    
    EXPECT_EQ(txt.GetLine(), expectedString);
}

TEST(Text, Can_Read_Text_File)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_NO_THROW(text.Read("input.txt"));
}

TEST(Text, Throw_If_Trying_To_Read_From_Non_Existing_File)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.Read("nput.txt"), invalid_argument);
}

TEST(Text, Can_Write_Text_To_File)
{
    TextLink::InitMemorySystem();
    Text text;

    text.SetLine("A");
    text.InsertDownLine("a");

    ASSERT_NO_THROW(text.Write("output.txt"));
}

TEST(Text, Can_Get_Copy)
{
    TextLink::InitMemorySystem();
    Text text;
    pText copiedText = nullptr;

    text.SetLine("A");
    text.InsertDownLine("a");
    text.InsertDownLine("b");
    text.InsertDownLine("c");
    text.InsertNextLine("B");
    
    ASSERT_NO_THROW(copiedText = text.GetCopy());
}

```

#### Результат прохождения тестов
![](https://bytebucket.org/VadimNifadyev/lab6-texts/raw/8d7d980f7acb2060a98f7634a2b11d9e01651a81/work/b23/TestResult.png)
#### Результат работы программы
![](https://bytebucket.org/VadimNifadyev/lab6-texts/raw/8d7d980f7acb2060a98f7634a2b11d9e01651a81/work/b23/MainResult.png)
## Вывод
В рамках данной лабораторной работы были изучены способы представления и хранения текста с использованием стека и списка, были реализованы различные операции над текстом.
