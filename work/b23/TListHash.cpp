#include "TListHash.h"

TListHash::TListHash(int size) : THashTable()
{
    if (size <= 0 || size > TABLE_MAX_SIZE)
    {
        throw out_of_range("Error! Size of list hash must be positive and less than max");
    }

    pList = new pTDataList[size];
    for (int i = 0; i < size; i++)
    {
        pList[i] = new TDataList();
    }
    tableSize = size;
    currentList = 0;
}

TListHash::~TListHash()
{
    if (pList != nullptr)
    {
        for (int i = 0; i < tableSize; i++)
        {
            delete pList[i];
        }
        delete[] pList;
    }
    // TabRecord->pValue must be deleted manually
}

bool TListHash::IsFull() const
{
    try
    {
        pTDataLink temp = new TDataLink();
        delete temp;
    }
    catch (...)
    {
        return true;
    }

    return false;
}

TKey TListHash::GetKey(void) const
{
    if (currentList < 0 || IsTableEnded())
    {
        return TKey("");
    }

    pTTabRecord temp = (pTTabRecord)(pList[currentList]->GetDataValue());
    return (temp == nullptr) ? TKey("") : temp->key;
}

pTDataValue TListHash::GetValuePTR(void) const
{
    if (currentList < 0 || IsTableEnded())
    {
        return nullptr;
    }

    pTTabRecord temp = (pTTabRecord)(pList[currentList]->GetDataValue/* GetDataValue */());
    return (temp == nullptr) ? nullptr : temp->pValue;
}

pTDataValue TListHash::FindRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot find record in empty list");
    }

    efficiency = 0;
    currentList = HashFunction(key) % tableSize;
    pTDataList actualList = pList[currentList];

    for (actualList->Reset(); !actualList->IsListEnded(); actualList->GoNext())
    {
        efficiency++;
        if (((pTTabRecord)(actualList->GetDataValue()))->key == key)
        {
            return ((pTTabRecord)(actualList->GetDataValue/* GetDataValue */()))->pValue;
        }
    }

    throw runtime_error("Error! Record with such key was not found");
}

void TListHash::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full list");
    }

    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        currentList = HashFunction(key) % tableSize;
        pList[currentList]->InsertBeforeFirst(new TTabRecord(key, value));
        dataCount++;
        return;
    }

    throw runtime_error("Error! Cannot insert already existing record");
}

void TListHash::DeleteRecord(TKey key)
{
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw logic_error("Error! Cannot find record with such key");
    }

    pList[currentList]->DeleteCurrent();
    dataCount--;
}

int TListHash::Reset(void)
{
    currentList = 0;
    while (!IsTableEnded() && pList[currentList]->IsEmpty())
    {
        currentList++;
    }

    if (IsTableEnded())
    {
        return -1;
    }
    else
    {
        pList[currentList]->Reset();
        return currentList;
    }
}

bool TListHash::IsTableEnded(void) const
{
    return currentList == tableSize;
}

int TListHash::GoNext(void)
{
    pList[currentList]->GoNext();
    if (!(pList[currentList]->IsListEnded()))
    {
        return currentList;
    }

    while (++currentList && !IsTableEnded())
    {
        if (!(pList[currentList]->IsEmpty()))
        {
            return pList[currentList]->Reset();
        }
    }

    return 1;
}
