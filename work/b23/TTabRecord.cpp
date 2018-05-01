#include "TTabRecord.h"

TTabRecord::TTabRecord(TKey key, pTDataValue value)
{
}

void TTabRecord::SetKey(TKey key)
{
}

TKey TTabRecord::GetKey(void)
{
    return TKey();
}

void TTabRecord::SetValuePtr(pTDataValue ptr)
{
}

pTDataValue TTabRecord::GetValuePTR(void)
{
    return pTDataValue();
}

TDataValue* TTabRecord::GetCopy()
{
    return (pTDataValue*)nullptr;
}

TTabRecord & TTabRecord::operator=(TTabRecord & record)
{
    // TODO: вставьте здесь оператор return
}

int TTabRecord::operator==(const TTabRecord & record)
{
    return 0;
}

int TTabRecord::operator<(const TTabRecord & record)
{
    return 0;
}

int TTabRecord::operator>(const TTabRecord & record)
{
    return 0;
}
