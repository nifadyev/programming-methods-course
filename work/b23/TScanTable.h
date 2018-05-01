#include "TArrayTable.h"

#ifndef TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H
#define TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H

class  TScanTable : public TArrayTable 
{
public:
    TScanTable(int size = TABLE_MAX_SIZE) : TArrayTable(size) {};

    //-----------------------------�������� ������-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

};
#endif // TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H
