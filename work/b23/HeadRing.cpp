// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HeadRing.h"

THeadRing::THeadRing() : TDataList()
{
	//listLength++; // Уже все ломает. Каким-то образом чинит вылет в деструкторе 
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
	//COMMIT: InsertBeforeFirst: pHead->SetNextLink() now works
	if (listLength == 0)
	{
		pHead = new TDataLink();
		//pHead->SetNextLink(pFirst);
	}
	TDataList::InsertBeforeFirst(pVal);
	//if (listLength == 1)
	//{
		//pHead = pFirst;
	//}

	pHead->SetNextLink(pFirst);
}

void THeadRing::InsertAfterLast(pTDataValue pVal)
{
	//COMMIT: InsertBeforeFirst: pHead->SetNextLink() now works
	//if (listLength == 0)
	//{
	//	pHead = new TDataLink();
	//	//pHead->SetNextLink(pFirst);
	//}
	TDataList::InsertAfterLast(pVal);
	//if (listLength == 1)
	//{
	//pHead = pFirst;
	//}
	//pLast->SetNextLink(pHead);

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
