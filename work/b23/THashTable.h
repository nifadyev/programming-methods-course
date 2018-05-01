#include "TTable.h"

#ifndef THASH_TABLE_INCLUDE_THASH_TABLE_H
#define THASH_TABLE_INCLUDE_THASH_TABLE_H

class  THashTable : public TTable 
{
protected:
    virtual unsigned long HashFunction(const TKey key);
public:
    THashTable() : TTable() {}
};

#endif // THASH_TABLE_INCLUDE_THASH_TABLE_H