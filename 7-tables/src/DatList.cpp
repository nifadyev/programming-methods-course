#include "DatList.h"

TDataList::TDataList()
{
    pFirst = pLast = pCurrentLink = pPreviousLink = pStop = nullptr;
    listLength = 0;
}

TDataList::~TDataList()
{
    DeleteList();
}

pTDataLink TDataList::GetLink(pTDataValue pVal, pTDataLink pLink)
{
    TDataLink *temp = new TDataLink(pVal, pLink);
    return temp;
}

void TDataList::DeleteLink(pTDataLink pLink)
{
    if (pLink != nullptr)
    {
        if (pLink->pValue != nullptr)
        {
            delete pLink->pValue;
        }
        delete pLink;
    }
}

pTDataValue TDataList::GetDataValue(TLinkPos mode) const
{
    pTDataLink temp = nullptr;

    switch (mode)
    {
    case FIRST:
        temp = pFirst;
        break;
    case LAST:
        temp = pLast;
        break;
    case CURRENT:
        temp = pCurrentLink;
        break;
    }

    return (temp == nullptr) ? nullptr : temp->pValue;
}

bool TDataList::IsEmpty() const
{
    return pFirst == pStop;
}

int TDataList::GetListLength() const
{
    return listLength;
}

void TDataList::SetCurrentPosition(const int &position)
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
        GoNext();
    }
    currentPosition = position;
}

int TDataList::GetCurrentPosition() const
{
    return currentPosition;
}

int TDataList::Reset()
{
    if (!IsEmpty())
    {
        currentPosition = 0;
        pCurrentLink = pFirst;
        pPreviousLink = pStop;
        return 1;
    }

    return -1;
}

bool TDataList::IsListEnded() const
{
    return pCurrentLink == pStop;
}

void TDataList::GoNext()
{
    if (!IsEmpty())
    {
        pPreviousLink = pCurrentLink;
        pCurrentLink = pCurrentLink->GetNextDataLink();
        currentPosition++;
    }
}

void TDataList::InsertBeforeFirst(pTDataValue pVal)
{
    pTDataLink n_node = GetLink(pVal, pFirst);
    pFirst = n_node;
    listLength++;

    // List was empty
    if (pLast == pStop)
    {
        pLast = pCurrentLink = n_node;
        currentPosition = 0;
    }
    // Current node was the first
    else if (currentPosition == 0)
    {
        pPreviousLink = pFirst;
        currentPosition = 1;
    }
    else
    {    
        currentPosition++;
    }
}

void TDataList::InsertAfterLast(pTDataValue pVal)
{
    if (IsListEnded())
    {
        throw "Cannot insert after last! List is ended";
    }

    pTDataLink n_node = GetLink(pVal, pStop);
    pTDataLink old_last = pLast;
    pLast = n_node;
    listLength++;

    // List was empty
    if (pFirst == pStop) 
    {
        pFirst = pCurrentLink = n_node;
        currentPosition = 0;
    }
    else
    {
        old_last->SetNextLink(pLast);
    }
    if (IsListEnded())
    {
        pCurrentLink = pLast;
    }
}

void TDataList::InsertBeforeCurrent(pTDataValue pVal)
{
    if (IsEmpty() || currentPosition == 0)
    {
        InsertBeforeFirst(pVal);
    }
    else if (IsListEnded())
    {
        InsertAfterLast(pVal);
    }
    else
    {
        pTDataLink n_node = GetLink(pVal, pCurrentLink);
        pPreviousLink->SetNextLink(n_node);
        pPreviousLink = n_node;
        currentPosition++;
        listLength++;
    }
}

void TDataList::DeleteFirst()
{
    if (IsEmpty())
    {
        throw logic_error("Cannot delete first element! List is empty");
    }

    pTDataLink old_first = pFirst;
    pFirst = pFirst->GetNextDataLink();
    listLength--;
    DeleteLink(old_first);

    if (IsEmpty())
    {
        pPreviousLink = pCurrentLink = pFirst = pLast = pStop;
    }
    else if (currentPosition == 0)
    {
        pCurrentLink = pFirst;
    }
    // Current node was the first
    else if (currentPosition == 1)
    {
        pPreviousLink = pStop;
    }
    // Current node was the second
    else
    {
        currentPosition--;
    }
}

void TDataList::DeleteCurrent()
{
    if (IsEmpty())
    {
        throw logic_error("Cannot delete current element! List is empty");
    }

    if (pCurrentLink == pFirst)
    {
        DeleteFirst();
    }
    // Current node was the first
    else
    {
        pTDataLink temp = pCurrentLink;
        pCurrentLink = pCurrentLink->GetNextDataLink();
        pPreviousLink->SetNextLink(pCurrentLink);
        if (temp == pLast)
        {
            pLast = pPreviousLink;
        }
        DeleteLink(temp);
        listLength--;
    }
}

void TDataList::DeleteList()
{
    while (!IsEmpty())
    {
        DeleteFirst();
    }
    
    pPreviousLink = pCurrentLink = pFirst = pLast = pStop;
}
