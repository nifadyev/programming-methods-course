#include "TArrayHash.h"

TArrayHash::TArrayHash(int size, int step)
{
}

TArrayHash::~TArrayHash()
{
}

bool TArrayHash::IsFull() const
{
    return false;
}

TKey TArrayHash::GetKey(void) const
{
    return TKey();
}

pTDataValue TArrayHash::GetValuePTR(void) const
{
    return pTDataValue();
}

pTDataValue TArrayHash::FindRecord(TKey key)
{
    return pTDataValue();
}

void TArrayHash::InsertRecord(TKey key, pTDataValue value)
{
}

void TArrayHash::DeleteRecord(TKey key)
{
}

void TArrayHash::Reset(void)
{
}

bool TArrayHash::IsTableEnded(void) const
{
    return false;
}

void TArrayHash::GoNext(void)
{
}
