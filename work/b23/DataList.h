// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataLink.h"

#ifndef TDATALIST
#define TDATALIST

enum TLinkPos { FIRST, CURRENT, LAST };
class TDataList
{
protected:
	pTDataLink pFirst;
	pTDataLink pLast;
	pTDataLink pCurrentLink; // CurrentPosition
	pTDataLink pPreviousLink;
	pTDataLink pStop; // Указатель на элемент, означающий конец списка

	int currentPosition; // Итератор
	int listLength;

	pTDataLink GetLink(pTDataValue pVal = nullptr /*NULL*/, pTDataLink pLink = nullptr /*NULL*/);
	void DeleteLink(pTDataLink pLink);
public:
	TDataList();
	~TDataList() { DeleteList(); }
	 
	pTDataValue GetDataValue(TLinkPos mode = CURRENT) const;
	virtual /*int*/  bool IsEmpty() const { return  pFirst == pStop; }

	int GetListLength() const { return listLength; }

	/*int*/void SetCurrentPosition(const int& position);
	int GetCurrentPosition() const;

	virtual /*int*/void Reset(); // Установка на currentPosition на первое звено(pFirst)
	virtual /*int*/ bool IsListEnded() const;

	/*int*/void MoveNext(); // Сдвиг вправо текущего звена (=1 после применения MoveNext для последнего звена списка)

	void Print(const TDataList& list);

	virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
	virtual void InsertAfterLast(pTDataValue pVal = nullptr);
	virtual void InsertBeforeCurrent(pTDataValue pVal = nullptr);

	virtual void DeleteFirst();
	virtual void DeleteCurrent();
	virtual void DeleteList();

	typedef TDataList *pTDataList;
};
#endif