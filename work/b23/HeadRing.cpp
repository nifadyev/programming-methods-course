// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HeadRing.h"

THeadRing::THeadRing() : TDataList()
{
	pHead = nullptr;
	pStop = pHead = pFirst;
}

THeadRing::~THeadRing()
{
	DeleteList();
	if (pHead != nullptr)
	{
		DeleteLink(pHead);
	}	
}

void THeadRing::InsertBeforeFirst(pTDataValue pVal)
{
	if (listLength == 0)
	{
		pHead = new TDataLink();
	}
	TDataList::InsertBeforeFirst(pVal);

	pHead->SetNextLink(pFirst);
}

void THeadRing::InsertAfterLast(pTDataValue pVal)
{
	TDataList::InsertAfterLast(pVal);

	pHead->SetNextLink(pFirst);
}

void THeadRing::DeleteFirst()
{
	TDataList::DeleteFirst();
	if (pHead != nullptr)
	{
		pHead->SetNextLink(pFirst);
	}
}
