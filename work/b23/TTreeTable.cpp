#include "TTreeTable.h"

void TTreeTable::DeleteTreeTable(pTTreeNode pNode)
{
}

bool TTreeTable::IsFull() const
{
    return false;
}

pTTreeNode TTreeTable::FindRecord(TKey key)
{
    return pTTreeNode();
}

void TTreeTable::InsertRecord(TKey key, pTDataValue value)
{
}

void TTreeTable::DeleteRecord(TKey key)
{
}

TKey TTreeTable::GetKey(void) const
{
    return TKey();
}

pTDataValue TTreeTable::GetValuePTR(void) const
{
    return pTDataValue();
}

void TTreeTable::Reset(void)
{
}

bool TTreeTable::IsTableEnded(void) const
{
    return false;
}

void TTreeTable::GoNext(void)
{
}
