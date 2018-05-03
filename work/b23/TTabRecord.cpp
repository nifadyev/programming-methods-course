#include "TTabRecord.h"

TTabRecord::TTabRecord(TKey key, pTDataValue value)
{
    this->key = key;
    this->pValue = value;
}

void TTabRecord::SetKey(TKey key)
{
    this->key = key;
}

TKey TTabRecord::GetKey(void)
{
    return key;
}

void TTabRecord::SetValuePtr(pTDataValue ptr)
{
    pValue = ptr;
}

pTDataValue TTabRecord::GetValuePTR(void)
{
    return pValue;
}

TDataValue* TTabRecord::GetCopy()
{
    return new TTabRecord(key, pValue);
}

TTabRecord& TTabRecord::operator=(const TTabRecord &record)
{
    key = record.key;
    pValue = record.pValue;

    return *this;
}

/* int */bool TTabRecord::operator==(const TTabRecord & record)
{
    return key == record.key;
}

/* int */bool TTabRecord::operator<(const TTabRecord & record)
{
    return key < record.key;
}

/* int */bool TTabRecord::operator>(const TTabRecord & record)
{
    return key > record.key;
}
