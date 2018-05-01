#include "TScanTable.h"

#ifndef TSORT_TABLE_INCLUDE_TSORT_TABLE_H
#define TSORT_TABLE_INCLUDE_TSORT_TABLE_H

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUIQ_SORT };

class  TSortTable : public TScanTable 
{
protected:
    TSortMethod sortMethod; // ����� ����������

    void SortData(void);   // ���������� ������
    void InsertSort(pTTabRecord *pMemory, int dataCount); // ����� �������

    void MergeSort(pTTabRecord *pMemory, int dataCount);  // ����� �������
    void MergeSorter(pTTabRecord * &pData, pTTabRecord * &pBuffer, int size);
    void MergeData(pTTabRecord *&pData, pTTabRecord *&pBuffer, int n1, int n2); //TODO: rename args

    void QuickSort(pTTabRecord *pMemory, int dataCount); // ������� ����������
    void QuickSplit(pTTabRecord *pData, int size, int &Pivot); //TODO: What is pivot?
public:
    TSortTable(int size = TABLE_MAX_SIZE) : TScanTable(size) {};
    TSortTable(const TScanTable &table); // �� ��������������� �������

    TSortTable & operator=(const TScanTable &table);

    TSortMethod GetSortMethod(void);    // �������� ����� ����������
    void SetSortMethod(TSortMethod srtMethod);// ���������� ����� ����������

    //-----------------------------�������� ������-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

};
#endif // TSORT_TABLE_INCLUDE_TSORT_TABLE_H
