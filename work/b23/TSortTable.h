#include "TScanTable.h"

#ifndef TSORT_TABLE_INCLUDE_TSORT_TABLE_H
#define TSORT_TABLE_INCLUDE_TSORT_TABLE_H

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

class  TSortTable : public TScanTable
{
 protected:
    TSortMethod sortMethod;  // Метод сортировки

    void SortData(void);    // Сортировка данных
    void InsertSort(pTTabRecord *pMemory, int dataCount);  // Метод вставок

    void MergeSort(pTTabRecord *pMemory, int dataCount);  // Метод слияния
    void MergeSorter(pTTabRecord *&pData, int left, int right);
    void MergeData(pTTabRecord *&pData, int left, int middle, int right);

    void QuickSort(pTTabRecord *pMemory, int left, int right);  // Быстрая сортировка
    int QuickSplit(pTTabRecord *pData, int left, int right);
 public:
    TSortTable(int size = TABLE_MAX_SIZE) : TScanTable(size) {sortMethod = INSERT_SORT;}
    TSortTable(const TScanTable &table);  // Из просматриваемой таблицы

    TSortTable & operator=(const TScanTable &table);

    TSortMethod GetSortMethod(void);    // Получить метод сортировки
    void SetSortMethod(TSortMethod srtMethod);  // Установить метод сортировки

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);
};
#endif  // TSORT_TABLE_INCLUDE_TSORT_TABLE_H
