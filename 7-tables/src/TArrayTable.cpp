#include "TArrayTable.h"

TArrayTable::TArrayTable(int size)
{
    if (size <= 0 || size > TABLE_MAX_SIZE)
    {
        throw invalid_argument("Error! Size of array table must be positive and less than max");
    }

    currentPosition = 0;
    maxTableSize = size;
    pRecords = new pTTabRecord[maxTableSize];
    for (int i = 0; i < maxTableSize; i++)
    {
        pRecords[i] = nullptr;
    }
}

TArrayTable::~TArrayTable()
{
    if (pRecords != nullptr)
    {
        for (int i = 0; i < maxTableSize; ++i)
        {
            if (pRecords[i] != nullptr)
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
}

bool TArrayTable::IsFull() const
{
    return maxTableSize == dataCount;
}

int TArrayTable::GetTableSize() const
{
    return maxTableSize;
}

TKey TArrayTable::GetKey(void) const
{
    return GetKey(CURRENT_POS);
}

pTDataValue TArrayTable::GetValuePTR(void) const
{
    return GetValuePTR(CURRENT_POS);
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
    if (IsEmpty())
    {
        throw runtime_error("Error! Table is empty");
    }

    int tempPosition = -1;

    switch (mode)
    {
    case FIRST_POS:
        tempPosition = 0;
        break;
    case CURRENT_POS:
        tempPosition = currentPosition;
        break;
    case LAST_POS:
        tempPosition = dataCount - 1;
        break;
    // Impossible to get wrong position because
    // it is already checked in SetCurrentPosition or in GoNext
    }

    return (pRecords[tempPosition] == nullptr) ? TKey("") : pRecords[tempPosition]->key;
}

pTDataValue TArrayTable::GetValuePTR(TDataPos mode) const
{
    if (IsEmpty())
    {
        throw runtime_error("Error! Table is empty");
    }

    int tempPosition = -1;

    switch (mode)
    {
    case FIRST_POS:
        tempPosition = 0;
        break;
    case CURRENT_POS:
        tempPosition = currentPosition;
        break;
    case LAST_POS:
        tempPosition = dataCount - 1;
        break;
    // Impossible to get wrong position because
    // it is already checked in SetCurrentPosition or in GoNext
    }

    return (pRecords[tempPosition] == nullptr) ? nullptr : pRecords[tempPosition]->pValue;
}

int TArrayTable::Reset(void)
{
    return currentPosition = 0;
}

bool TArrayTable::IsTableEnded(void) const
{
    return currentPosition == dataCount;
}

int TArrayTable::GoNext(void)
{
    if (IsTableEnded())
    {
        throw logic_error("Error! Cannot go next in ended table");
    }

    return currentPosition++;
}

void TArrayTable::SetCurrentPosition(int position)
{
    if (position < 0 || position > TABLE_MAX_SIZE)
    {
        throw invalid_argument("Error! Position must be positive and less than max");
    }

    currentPosition = position;
}

int TArrayTable::GetCurrentPosition(void) const
{
    return currentPosition;
}
