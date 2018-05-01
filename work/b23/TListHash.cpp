#include "TListHash.h"

TListHash::TListHash(int Size)
{
}

TListHash::~TListHash()
{
}

bool TListHash::IsFull() const
{
    return false;
}

TKey TListHash::GetKey(void) const
{
    return TKey();
}

pTDataValue TListHash::GetValuePTR(void) const
{
    return pTDataValue();
}

pTDataValue TListHash::FindRecord(TKey key)
{
    return pTDataValue();
}

void TListHash::InsertRecord(TKey key, pTDataValue value)
{
}

void TListHash::DeleteRecord(TKey key)
{
}

void TListHash::Reset(void)
{
}

bool TListHash::IsTableEnded(void) const
{
    return false;
}

void TListHash::GoNext(void)
{
}
