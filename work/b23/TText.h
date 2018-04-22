// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#ifndef TEXT_H
#define TEXT_H

#include "TTextLink.h"
#include <stack>

class Text;
typedef Text *pText;

class Text /*: public TDataCom*/
{
protected:
	pTextLink pFirst; // Указатель корня дерева
	pTextLink pCurrent; // Указатель текущей строки
	stack<pTextLink> Path; // Стек траектории движения по тексту
	stack<pTextLink> iteratorStack; // Стек для итератора

	pTextLink GetFirstAtom(pTextLink textLink); // Поиск первого атома
	void PrintText(pTextLink textLink); // Печать текста с указанного звена
    void PrintTextInFile(pTextLink textLink, ofstream &output); // Печать текста с указанного звена
	pTextLink ReadText(ifstream &textFile); // Чтение текста из файла
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
	string GetLine(void);   // чтение текущей строки
	void SetLine(const string &s); // замена текущей строки 
							// модификация
    // Section = partition + subpartitions
    // Line = partition
	void InsertDownLine(const string &s);    // Вставка строки в подуровень
	void InsertDownSection(const string &s); // Вставка раздела в подуровень
	void InsertNextLine(const string &s);    // Вставка строки в том же уровне
	void InsertNextSection(const string &s); // Вставка раздела в том же уровне
	void DeleteDownLine(void);        // Удаление строки в подуровне
	void DeleteDownSection(void);     // Удаление раздела в подуровне
	void DeleteNextLine(void);        // Удаление строки в том же уровне
	void DeleteNextSection(void);     // Удаление раздела в том же уровне
	
	// Итератор
	int Reset(void);              // Установить на первую запись
	/*int*/bool IsTextEnded(void) const;  // Текст завершен?
	int GoNext(void);             // Переход к следующей записи
	
	// Работа с файлами
	void Read(const char * pFileName);  // Ввод текста из файла
	void Write(char * pFileName); // Вывод текста в файл
	void Print(void);             // Печать текста
};
#endif
