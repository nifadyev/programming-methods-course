// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include "DataLink.h"
using namespace std;

#ifndef TDATALIST
#define TDATALIST
enum TLinkPos { FIRST, CURRENT, LAST };

class TDataList
{
protected:
	pTDataLink pFirst;
	pTDataLink pLast;
	pTDataLink pCurrentLink;
	pTDataLink pPreviousLink;
	pTDataLink pStop; // Указатель на элемент, означающий конец списка

	int currentPosition; // Итератор
	int listLength;

	pTDataLink GetLink(pTDataValue pVal = nullptr, pTDataLink pLink = nullptr);
	void DeleteLink(pTDataLink pLink);

	void InsertIntoEmptyList(pTDataValue pVal);
public:
	TDataList();
	~TDataList() { DeleteList(); }
	 
	pTDataValue GetDataValue(TLinkPos mode = CURRENT) const;
	virtual bool IsEmpty() const { return  pFirst == pStop; }

	int GetListLength() const { return listLength; }

	void SetCurrentPosition(const int& position);
	int GetCurrentPosition() const;

	virtual void Reset(); 
	virtual bool IsListEnded() const;
	void MoveNext(); // Сдвиг вправо текущего звена 

	virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
	virtual void InsertAfterLast(pTDataValue pVal = nullptr);
	virtual void InsertBeforeCurrent(pTDataValue pVal = nullptr);

	virtual void DeleteFirst();
	virtual void DeleteCurrent();
	virtual void DeleteList();
};
typedef TDataList *pTDataList;
#endif