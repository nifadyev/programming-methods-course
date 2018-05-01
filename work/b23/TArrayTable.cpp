#include "TArrayTable.h"

TArrayTable::TArrayTable(int size)
{
}

bool TArrayTable::IsFull() const
{
    return false;
}

int TArrayTable::GetTableSize() const
{
    return 0;
}

TKey TArrayTable::GetKey(void) const
{
    return TKey();
}

pTDataValue TArrayTable::GetValuePTR(void) const
{
    return pTDataValue();
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
    return TKey();
}

pTDataValue TArrayTable::GetValuePTR(TDataPos mode) const
{
    return nullptr;
}

void TArrayTable::Reset(void)
{
}

bool TArrayTable::IsTableEnded(void) const
{
    return false;
}

void TArrayTable::GoNext(void)
{
}

int TArrayTable::SetCurrentPosition(int position)
{
    return 0;
}

int TArrayTable::GetCurrentPosition(void) const
{
    return 0;
}
