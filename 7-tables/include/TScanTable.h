#include "TArrayTable.h"

#ifndef TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H
#define TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H

class  TScanTable : public TArrayTable
{
public:
    explicit TScanTable(int size = TABLE_MAX_SIZE) : TArrayTable(size) {};

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);
};
#endif  // TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H
