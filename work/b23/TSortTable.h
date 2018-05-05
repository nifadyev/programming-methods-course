#include "TScanTable.h"

#ifndef TSORT_TABLE_INCLUDE_TSORT_TABLE_H
#define TSORT_TABLE_INCLUDE_TSORT_TABLE_H

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

class  TSortTable : public TScanTable 
{
protected:
    TSortMethod sortMethod; // ����� ����������

    void SortData(void);   // ���������� ������
    void InsertSort(pTTabRecord *pMemory, int dataCount); // ����� �������

    void MergeSort(pTTabRecord *pMemory, int dataCount);  // ����� �������
    void MergeSorter(pTTabRecord * &pData, int left, int right);
    void MergeData(pTTabRecord *&pData,int left, int middle, int right); //TODO: rename args

    void QuickSort(pTTabRecord *pMemory, int left, int right); // ������� ����������
    int QuickSplit(pTTabRecord *pData, int left, int right); //TODO: What is pivot?
public:
    TSortTable(int size = TABLE_MAX_SIZE) : TScanTable(size) {sortMethod = INSERT_SORT;}
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
