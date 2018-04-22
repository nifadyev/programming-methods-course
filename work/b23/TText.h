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
	pTextLink pFirst; // ��������� ����� ������
	pTextLink pCurrent; // ��������� ������� ������
	stack<pTextLink> Path; // ���� ���������� �������� �� ������
	stack<pTextLink> iteratorStack; // ���� ��� ���������

	pTextLink GetFirstAtom(pTextLink textLink); // ����� ������� �����
	void PrintText(pTextLink textLink); // ������ ������ � ���������� �����
    void PrintTextInFile(pTextLink textLink, ofstream &output); // ������ ������ � ���������� �����
	pTextLink ReadText(ifstream &textFile); // ������ ������ �� �����
public:
	Text(pTextLink textLink = nullptr);
	~Text() { pFirst = nullptr; }
	pText GetCopy();

	// ���������
	int GoFirstLink();    // ������� � ������ ������
	int GoDownLink();     // ������� � ��������� ������ �� Down
	int GoNextLink();     // ������� � ��������� ������ �� Next
	int GoPreviousLink(); // ������� � ���������� ������� � ������

	// ������
	string GetLine(void);   // ������ ������� ������
	void SetLine(const string &s); // ������ ������� ������ 
							// �����������
    // Section = partition + subpartitions
    // Line = partition
	void InsertDownLine(const string &s);    // ������� ������ � ����������
	void InsertDownSection(const string &s); // ������� ������� � ����������
	void InsertNextLine(const string &s);    // ������� ������ � ��� �� ������
	void InsertNextSection(const string &s); // ������� ������� � ��� �� ������
	void DeleteDownLine(void);        // �������� ������ � ���������
	void DeleteDownSection(void);     // �������� ������� � ���������
	void DeleteNextLine(void);        // �������� ������ � ��� �� ������
	void DeleteNextSection(void);     // �������� ������� � ��� �� ������
	
	// ��������
	int Reset(void);              // ���������� �� ������ ������
	/*int*/bool IsTextEnded(void) const;  // ����� ��������?
	int GoNext(void);             // ������� � ��������� ������
	
	// ������ � �������
	void Read(const char * pFileName);  // ���� ������ �� �����
	void Write(char * pFileName); // ����� ������ � ����
	void Print(void);             // ������ ������
};
#endif
