#include "TSortTable.h"

void TSortTable::SortData(void)
{
}

void TSortTable::InsertSort(pTTabRecord * pMemory, int dataCount)
{
}

void TSortTable::MergeSort(pTTabRecord * pMemory, int dataCount)
{
}

void TSortTable::MergeSorter(pTTabRecord *& pData, pTTabRecord *& pBuffer, int size)
{
}

void TSortTable::MergeData(pTTabRecord *& pData, pTTabRecord *& pBuffer, int n1, int n2)
{
}

void TSortTable::QuickSort(pTTabRecord * pMemory, int dataCount)
{
}

void TSortTable::QuickSplit(pTTabRecord * pData, int size, int & Pivot)
{
}

TSortTable::TSortTable(const TScanTable & table)
{
}

TSortTable & TSortTable::operator=(const TScanTable & table)
{
    // TODO: вставьте здесь оператор return
}

TSortMethod TSortTable::GetSortMethod(void)
{
    return TSortMethod();
}

void TSortTable::SetSortMethod(TSortMethod srtMethod)
{
}

pTDataValue TSortTable::FindRecord(TKey key)
{
    return pTDataValue();
}

void TSortTable::InsertRecord(TKey key, pTDataValue value)
{
}

void TSortTable::DeleteRecord(TKey key)
{
}
