#include "TScanTable.h"

pTDataValue TScanTable::FindRecord(TKey key)
{
    int i = 0;

    for (i = 0; i < dataCount; i++)
    {
        if (pRecords[i]->GetKey() == key)
        {
            break;
        }
    }

    efficiency = i + 1;
    if (i < dataCount)
    {
        currentPosition = i;
        return pRecords[i]->pValue;
    }
    else
    {
        throw runtime_error("Error! Requested record did not found");
    }
}

void TScanTable::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full table");
    }

    int i = 0;

    for (i = 0; i < dataCount; i++)
    {
        if (pRecords[i]->GetKey() == key)
        {
            break;
        }
    }
    if (i < dataCount)
    {
        throw runtime_error("Error! Record with specified key has already existed");
    }

    pRecords[dataCount++] = new TTabRecord(key, value);
}

void TScanTable::DeleteRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Table is empty");
    }

    for(int i = 0; i < dataCount; i++)
    {
        if (pRecords[i]->GetKey() == key)
        {
            if (pRecords[i]->pValue != nullptr)
            {
                delete pRecords[i]->pValue;
            }
            delete pRecords[i];
            pRecords[i] = nullptr;
            //TODO: try to --dataCount in next string
            pRecords[dataCount - 1] = nullptr;
            dataCount--;
            return;
        }
    }

    throw runtime_error("Error! Requested record did not found");
}
