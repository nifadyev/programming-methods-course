#include "TArrayHash.h"

TArrayHash::TArrayHash(int size, int step) : THashTable()
{
    if (size <= 0 || size > TABLE_MAX_SIZE || step < 1 || step >= size)
    {
        throw out_of_range("Error! Parameters is out of range");
    }

    pRecords = new pTTabRecord[size];
    for (int i = 0; i < size; i++)
    {
        pRecords[i] = nullptr;
    }
    maxTableSize = size;
    hashStep = step;
    pMark = new TTabRecord("DELETED");
}

TArrayHash::~TArrayHash()
{
    if (pRecords != nullptr)
    {
        for (int i = 0; i < maxTableSize; i++)
        {
            if (pRecords[i] != nullptr && pRecords[i] != pMark)
            {
                if (pRecords[i]->pValue != nullptr)
                {
                    delete pRecords[i]->pValue;
                }
                delete pRecords[i];
            }
        }

        delete[] pRecords;
    }

    delete pMark;
}

int TArrayHash::GetNextPosition(int position) 
{ 
    return (position + hashStep) % maxTableSize;
}

bool TArrayHash::IsFull() const
{
    return dataCount == maxTableSize;
}

TKey TArrayHash::GetKey(void) const
{
    return (currentPosition < 0 || IsTableEnded()) ? TKey("") : pRecords[currentPosition]->key;
}

pTDataValue TArrayHash::GetValuePTR(void) const
{
    return (currentPosition < 0 || IsTableEnded()) ? nullptr : pRecords[currentPosition]->pValue;
}

pTDataValue TArrayHash::FindRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot find record in empty table");
    }

    freePosition = -1;
    currentPosition = HashFunction(key) % maxTableSize;
    efficiency = 0;
    int originPosition = currentPosition;

    while (true)
    {
        efficiency++;
        if (pRecords[currentPosition] == nullptr)
        {
            throw runtime_error("Error! Record with such key was not found");
        }
        else if (pRecords[currentPosition] == pMark && freePosition < 0)
        {
            freePosition = currentPosition;
        }
        else if (pRecords[currentPosition]->key == key)
        {
            return pRecords[currentPosition]->pValue;
        }

        currentPosition = GetNextPosition(currentPosition);
        if (currentPosition == originPosition)
        {
            break;
        }
    }

    throw runtime_error("Error! Record with such key was not found");
}

void TArrayHash::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw runtime_error("Error! Cannot insert record into full table");
    }

    freePosition = -1;
    currentPosition = HashFunction(key) % maxTableSize;
    int originPosition = currentPosition;

    while (true)
    {
        if (pRecords[currentPosition] != nullptr && pRecords[currentPosition] != pMark)
        {
            if (pRecords[currentPosition]->key == key)
            {
                throw runtime_error("Error! Record with such key has already existed");
            }
        }
        else if (pRecords[currentPosition] == pMark && freePosition < 0)
        {
            freePosition = currentPosition;
        }
        else if (pRecords[currentPosition] == nullptr)
        {
            if (freePosition < 0)
            {
                pRecords[currentPosition] = new TTabRecord(key, value);
            }
            else
            {
                pRecords[freePosition] = new TTabRecord(key, value);
            }
            dataCount++;
            return;
        }

        currentPosition = GetNextPosition(currentPosition);
        if (currentPosition == originPosition)
        {
            if (freePosition > -1)
            {
                pRecords[freePosition] = new TTabRecord(key, value);
                dataCount++;
                return;
            }
            break;
        }

        throw runtime_error("Error! Cannot insert new record");
    }
}

void TArrayHash::DeleteRecord(TKey key)
{
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw logic_error("Error! Cannot delete unexisting record");
    }

    if (pRecords[currentPosition]->pValue != nullptr)
    {
        delete pRecords[currentPosition]->pValue;
        pRecords[currentPosition]->pValue = nullptr;
    }

    delete pRecords[currentPosition];
    pRecords[currentPosition] = pMark;
    dataCount--;
}

int TArrayHash::Reset(void)
{
    currentPosition = 0;
    while (!IsTableEnded() && (pRecords[currentPosition] == nullptr || pRecords[currentPosition] == pMark))
    {
        currentPosition++;
    }
    if (IsTableEnded())
    {
        return -1;
    }

    return currentPosition;
}

bool TArrayHash::IsTableEnded(void) const
{
    return currentPosition == maxTableSize;
}

int TArrayHash::GoNext(void)
{
    while (++currentPosition && !IsTableEnded())
    {
        if (pRecords[currentPosition] != nullptr && pRecords[currentPosition] != pMark)
        {
            break;
        }
    }

    if (IsTableEnded())
    {
        return 1;
    }

    return currentPosition;
}
