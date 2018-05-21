#include "DatList.h"

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

void TDataList::InsertIntoEmptyList(pTDataValue pVal)
{
    pFirst = new TDataLink(pVal);
    pCurrentLink = pFirst;
    pLast = pFirst;
}

TDataList::TDataList()
{
    pFirst = pLast = pCurrentLink = pPreviousLink = pStop = nullptr;
    listLength = 0;
    //currentPosition = 0;
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

void TDataList::SetCurrentPosition(const int &position)
{
    if (position < 0 /* || position >= listLength */)
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
    // return 1;
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
    // if (pPreviousLink == pLast && pCurrentLink == pStop && !IsEmpty())
    // {
    //     return true;
    // }

    // return false;
    return pCurrentLink == pStop;
}

void TDataList::GoNext()
{
    // if (pCurrentLink == pStop)
    // {
    //     throw logic_error("Cannot move to the next link! List has ended");
    // }

    // if (IsListEnded() == false)
    // {
    //     pPreviousLink = pCurrentLink;
    //     pCurrentLink = pCurrentLink->GetNextDataLink();
    //     currentPosition++;
    // }
    // if (pCurrentLink == pStop)
    // {
    //     currentPosition = -1;
    // }

    if (!IsEmpty())
    {
        pPreviousLink = pCurrentLink;
        pCurrentLink = pCurrentLink->GetNextDataLink();
        currentPosition++;
        //return 1;
    }
    // else
    //     return -1;
}

void TDataList::InsertBeforeFirst(pTDataValue pVal)
{
    pTDataLink n_node = GetLink(pVal, pFirst);
    pFirst = n_node;
    listLength++;
    if (pLast == pStop) // List was empty
    {
        pLast = pCurrentLink = n_node;
        currentPosition = 0;
    }
    else if (currentPosition == 0) // Current node was the first
    {
        pPreviousLink = pFirst;
        currentPosition = 1;
    }
    else
        currentPosition++;
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

    if (pFirst == pStop) // List was empty
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
    // listLength++;

    // if (IsEmpty())
    // {
    //     InsertIntoEmptyList(pVal);
    //     return;
    // }

    // if (pCurrentLink == pFirst)
    // {
    //     InsertBeforeFirst(pVal);
    //     listLength--;
    //     return;
    // }

    // TDataLink *temp = pCurrentLink;
    // pCurrentLink = new TDataLink(pVal);
    // pCurrentLink->SetNextLink(temp);
    // pPreviousLink->SetNextLink(pCurrentLink);

    // if (pLast == temp)
    // {
    //     pLast = temp;
    // }

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

    // TDataLink *temp = pFirst;
    // pFirst = pFirst->GetNextDataLink();
    // DeleteLink(temp);
    // listLength--;

    // if (IsEmpty())
    // {
    //     pLast = pStop;
    //     Reset();
    // }
    // else if (currentPosition == 0)
    //     pCurrentLink = pFirst;

    // if (currentPosition)
    //     currentPosition--;

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
    } // Current node was the first
    else if (currentPosition == 1)
    {
        pPreviousLink = pStop;
    } // Current node was the second
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

    // if (listLength == 1)
    // {
    //     DeleteFirst();

    //     return;
    // }

    // if (pCurrentLink == pLast)
    // {
    //     DeleteLink(pCurrentLink);
    //     SetCurrentPosition(currentPosition - 1);
    //     pLast = pCurrentLink;
    //     pLast->SetNextLink(pStop);
    //     listLength--;
    //     currentPosition++;

    //     return;
    // }

    // TDataLink *temp = pCurrentLink;
    // pCurrentLink = pCurrentLink->GetNextDataLink();
    // DeleteLink(temp);
    // pPreviousLink->SetNextLink(pCurrentLink);
    // listLength--;

    if (pCurrentLink == pFirst)
    {
        DeleteFirst();
    } // Current node was the first
    else
    {
        auto old_cur = pCurrentLink;
        pCurrentLink = pCurrentLink->GetNextDataLink();
        pPreviousLink->SetNextLink(pCurrentLink);
        if (old_cur == pLast)
        {
            pLast = pPreviousLink;
        }
        DeleteLink(old_cur);
        listLength--;
    }
}

void TDataList::DeleteList()
{
    // while (listLength != 0)
    // {
    //     DeleteFirst();
    // }

    while (!IsEmpty())
    {
        DeleteFirst();
    }
    pPreviousLink = pCurrentLink = pFirst = pLast = pStop;
}
