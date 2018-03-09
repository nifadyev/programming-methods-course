// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataList.h"

pTDataLink TDataList::GetLink(pTDataValue pVal, pTDataLink pLink)
{
	TDataLink *temp = new TDataLink(pVal, pLink);
	return temp;
}

void TDataList::DeleteLink(pTDataLink pLink)
{
	delete pLink;
}

void TDataList::InsertIntoEmptyList(pTDataValue pVal)
{
	pFirst = new TDataLink(pVal);
	pCurrentLink = pFirst;
	pLast = pFirst;
}

TDataList::TDataList()
{
	pFirst = pLast = pCurrentLink = pPreviousLink = nullptr;
	pStop = nullptr;
	listLength = 0;
	currentPosition = 0;
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

void  TDataList::SetCurrentPosition(const int& position)
{
	if (position < 0)
	{
		throw range_error("Cannot set position! Position must be positive");
	}
	if (IsEmpty())
	{
		throw logic_error("Cannot set position! List is empty");
	}

	Reset();

	for (int i = 0; i < position; i++)
	{
		MoveNext();
	}
}

int TDataList::GetCurrentPosition() const
{
	return currentPosition;
}

void TDataList::Reset()
{
	currentPosition = 0;
	pCurrentLink = pFirst;
	pPreviousLink = pStop;
}

bool TDataList::IsListEnded() const
{
	if (pPreviousLink == pLast && pCurrentLink == pStop && !IsEmpty())
	{
		return true;
	}

	return false;
}

void TDataList::MoveNext()
{
	if (pCurrentLink == pStop)
	{
		throw logic_error("Cannot move to the next link! List has ended");
	}
	
	if (IsListEnded() == false) 
	{
		pPreviousLink = pCurrentLink;
		pCurrentLink = pCurrentLink->GetNextDataLink();
		currentPosition++;
	}
	if (pCurrentLink == pStop)
	{
		currentPosition = -1;
	}
}

void TDataList::InsertBeforeFirst(pTDataValue pVal)
{
	if (IsListEnded())
	{
		throw "Cannot insert before first! List is ended";
	}

	listLength++;
	Reset();

	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	TDataLink *temp = pFirst;
	pFirst = new TDataLink(pVal);
	pFirst->SetNextLink(temp);
	pCurrentLink = pFirst;

	if (temp->GetNextLink() == nullptr)
	{
		pLast = temp;
	}
}

void TDataList::InsertAfterLast(pTDataValue pVal)
{
	if (IsListEnded())
	{
		throw "Cannot insert after last! List is ended";
	}

	listLength++;

	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	TDataLink *temp = pLast;
	temp->SetNextLink(pStop);
	pLast = new TDataLink(pVal);
	pLast->SetNextLink(pStop);
	pCurrentLink = pLast;
	pPreviousLink = temp;
	pPreviousLink->SetNextLink(pCurrentLink);
	currentPosition = listLength - 1;

	if (pFirst == temp)
	{
		pFirst = temp;
		pFirst->SetNextLink(pLast);
	}
}

void TDataList::InsertBeforeCurrent(pTDataValue pVal)
{
	listLength++;

	if (IsEmpty())
	{
		InsertIntoEmptyList(pVal);
		return;
	}

	if (pCurrentLink == pFirst)
	{
		InsertBeforeFirst(pVal);
		listLength--;
		return;
	}

	TDataLink* temp = pCurrentLink;
	pCurrentLink = new TDataLink(pVal);
	pCurrentLink->SetNextLink(temp);
	pPreviousLink->SetNextLink(pCurrentLink);

	if (pLast == temp)
	{
		pLast = temp;
	}
}

void TDataList::DeleteFirst()
{
	if (IsEmpty())
	{
		throw logic_error("Cannot delete first element! List is empty");
	}

	TDataLink *temp = pFirst;
	pFirst = pFirst->GetNextDataLink();
	DeleteLink(temp);
	listLength--;

	if (IsEmpty()) 
	{
		pLast = pStop;
		Reset();
	}
	else if (currentPosition == 0)
		pCurrentLink = pFirst;

	if (currentPosition)
		currentPosition--;
}

void TDataList::DeleteCurrent()
{
	if (IsEmpty())
	{
		throw logic_error("Cannot delete current element! List is empty");
	}
	
	if (listLength == 1)
	{
		DeleteFirst();

		return;
	}
	
	if (pCurrentLink == pLast)
	{
		DeleteLink(pCurrentLink);
		SetCurrentPosition(currentPosition-1);
		pLast = pCurrentLink;
		pLast->SetNextLink(pStop);
		listLength--;
		currentPosition++;

		return;
	}
	
	TDataLink *temp = pCurrentLink;
	pCurrentLink = pCurrentLink->GetNextDataLink();
	DeleteLink(temp);
	pPreviousLink->SetNextLink(pCurrentLink);
	listLength--;
}

void TDataList::DeleteList()
{
	while(listLength !=0)
	{
		DeleteFirst();
	}
}
