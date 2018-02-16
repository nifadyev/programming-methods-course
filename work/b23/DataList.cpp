// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include "DataList.h"

using namespace std;

pTDataLink TDataList::GetLink(pTDataValue pVal, pTDataLink pLink)
{
	TDataLink *temp = new TDataLink(pVal, pLink);
	return temp;
}

void TDataList::DeleteLink(pTDataLink pLink)
{
	//if (pLink->GetDataValue() != nullptr)
	//{
	delete pLink->GetDataValue();
	//}
	delete pLink;
}

TDataList::TDataList()
{
	pFirst = pLast = pCurrentLink = pPreviousLink = nullptr;
	pStop = /*0*/ nullptr;
	listLength = 0;
	currentPosition = /*-1*/0;
	//Reset();
}

pTDataValue TDataList::GetDataValue(TLinkPos mode) const
{
	// Если в списке нет ни одного элемента
	if (pFirst == nullptr) 
	{
		return nullptr;
	}

	TDataValue *temp = nullptr;
	switch (mode)
	{
	case FIRST:
		temp = pFirst->GetDataValue();
		break;
	case LAST:
		temp = pLast->GetDataValue();
		break;
	case CURRENT:
	
		temp = pCurrentLink->GetDataValue();
		break;
	}

	return (temp == nullptr) ? nullptr : temp;
}

/*int*/void  TDataList::SetCurrentPosition(const int& position)
{
	if (position < 0)
	{
		throw range_error("Cannot set position! Position must be positive");
	}
	if (listLength == 0 /*IsListEnded()*/)
	{
		throw logic_error("Cannot set position! List is empty");
	}

	//TODO: Reset->for->MoveNext till position

	Reset();

	for (int i = 0; i < position; i++)
	{
		MoveNext();
	}

	//currentPosition = position;

}

int TDataList::GetCurrentPosition() const
{
	return currentPosition;
}

/*int*/void TDataList::Reset()
{
	//delete pFirst, pLast, pCurrentLink, pPreviousLink, pStop;
	//pFirst = pLast = pCurrentLink = pPreviousLink = nullptr;
	//pStop = /*0*/ nullptr;
	//listLength = 0;
	currentPosition = 0;
	pCurrentLink = pFirst;
	pPreviousLink = pStop;

}

bool TDataList::IsListEnded() const
{
	if (pPreviousLink == pLast && pCurrentLink == pStop)
	{
		return true;
	}
	return false;
}

/*int*/void TDataList::MoveNext()
{
	if (pCurrentLink/*->GetNextDataLink()*/ == pStop)
	{
		//currentPosition = 0;
		//return 1;
		throw logic_error("Cannot move to the next link! List has ended");
	}

	// pPrev pCur temp => pPrev=pCur pCur=temp temp->GetNextDataLink()
	//
	currentPosition++;
	//TODO: попробовать без tempNXT(через temp->GetNextDataLink())
	TDataLink *tempNxt = pCurrentLink->GetNextDataLink();
	TDataLink *temp = pCurrentLink;
	delete pCurrentLink;
	pPreviousLink = temp;
	pCurrentLink = tempNxt;

	//return 0;
}

void TDataList::Print(const TDataList & list)
{
	for (int i = 0; i < listLength; i++)
	{
		SetCurrentPosition(i);
		cout << GetDataValue() << " ";
	}
	cout << endl;
}

void TDataList::InsertBeforeFirst(pTDataValue pVal)
{
	//TODO: ?????

	listLength++;
	Reset();

	//if (pVal == nullptr)
	//{
	//	TDataLink *temp = new TDataLink();
	//	pFirst = temp;
	//	pCurrentLink = pFirst;
	//	return;
	//}

	// Список пуст
	if (pFirst == nullptr)
	{
		pFirst = new TDataLink(pVal);
		pCurrentLink = pFirst;
		pPreviousLink = pStop; // Уже прописано в Reset()
		pLast = pFirst;
		//listLength++;
		return;
	}	

	// В списке 1 элемент
	if (pFirst == pLast)
	{
		TDataLink *tempFirst = pFirst;
		pLast = tempFirst;
	}

	TDataLink *temp = pFirst;
	delete pFirst;
	pFirst = new TDataLink(pVal);
	pFirst->SetNextLink(temp);
	pCurrentLink = pFirst;
	pPreviousLink = pStop;

	//if (temp->GetNextDataLink() == nullptr)
	//{
	//	pLast = temp;
	//}
	
}

void TDataList::InsertAfterLast(pTDataValue pVal)
{
	TDataLink *temp = new TDataLink(pVal, pStop);
	pLast->SetNextLink(temp);
	SetCurrentPosition(++listLength);
}

void TDataList::InsertBeforeCurrent(pTDataValue pVal)
{
	//SetCurrentPosition(--currentPosition);
	//TDataLink *temp = new TDataLink(pVal, pCurrentLink);

	//pPreviousLink = pCurrentLink;

}

void TDataList::DeleteFirst()
{
	pStop->SetNextLink(pFirst->GetNextLink());
	pFirst = pFirst->GetNextDataLink();
	pCurrentLink = pFirst;

	currentPosition = 0; /*SetCurrentPosition(0);*/
	listLength--;
	DeleteLink(pFirst);
}

void TDataList::DeleteCurrent()
{
	pCurrentLink = pCurrentLink->GetNextDataLink();
	pPreviousLink->SetNextLink(pCurrentLink);

	currentPosition--;
	listLength--;
	DeleteLink(pCurrentLink);
}

void TDataList::DeleteList()
{

}
