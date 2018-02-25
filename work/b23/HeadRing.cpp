// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "HeadRing.h"

THeadRing::THeadRing() : TDataList()
{
	pHead = nullptr;
}

THeadRing::~THeadRing()
{
	DeleteList();
}

void THeadRing::InsertBeforeFirst(pTDataValue pVal)
{
	if (IsListEnded())
	{
		throw "Cannot insert before first! List is ended";
	}

	//TODO: адаптировать для кольцевой очереди
	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	TDataLink *temp = pFirst;
	//temp->SetNextLink(pFirst->GetNextLink());
	pFirst = new TDataLink(pVal);
	pFirst->SetNextLink(temp);
	pCurrentLink = pFirst;
	//pPreviousLink = pStop;

	if (temp->GetNextLink() == nullptr)
	{
		pLast = temp;
	}
}

void THeadRing::DeleteFirst()
{
}
