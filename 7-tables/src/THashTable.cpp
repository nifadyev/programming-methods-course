#include "THashTable.h"

unsigned long THashTable::HashFunction(const TKey &key)
{
    // Gets numeric value from key
    unsigned long value = 0;
    for (size_t i = 0; i < key.size(); i++)
    {
        value = (value << 3) + key[i];
    }

    return value;
}