// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HeadRing.h"

THeadRing::THeadRing() : TDataList()
{
	//InsertAfterLast();
	//listLength++; // Уже все ломает. Каким-то образом чинит вылет в деструкторе 
	pHead = nullptr;
	pStop = pHead = pFirst;
	//Reset();
	//pFirst->SetNextLink(pFirst);
}

THeadRing::~THeadRing()
{
	DeleteList();
	if (pHead != nullptr)
	{
		DeleteLink(pHead);
	}	
	//pHead = nullptr;
}

void THeadRing::InsertBeforeFirst(pTDataValue pVal)
{
	//TODO: адаптировать для кольцевой очереди
	TDataList::InsertBeforeFirst(pVal);
	//if (listLength == 1)
	//{
		//pHead = pFirst;
	//}
	//if (listLength > 1)
	//{
	//	pHead->SetNextLink(pFirst);
	//}
}

void THeadRing::DeleteFirst()
{
	TDataList::DeleteFirst();
	if (pHead != nullptr)
	{
		pHead->SetNextLink(pFirst);
	}
}
