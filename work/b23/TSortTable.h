#include "TScanTable.h"

#ifndef TSORT_TABLE_INCLUDE_TSORT_TABLE_H
#define TSORT_TABLE_INCLUDE_TSORT_TABLE_H

enum TSortMethod { INSERT_SORT, MERGE_SORT, QUIQ_SORT };

class  TSortTable : public TScanTable 
{
protected:
    TSortMethod sortMethod; // Метод сортировки

    void SortData(void);   // Сортировка данных
    void InsertSort(pTTabRecord *pMemory, int dataCount); // Метод вставок

    void MergeSort(pTTabRecord *pMemory, int dataCount);  // Метод слияния
    void MergeSorter(pTTabRecord * &pData, pTTabRecord * &pBuffer, int size);
    void MergeData(pTTabRecord *&pData, pTTabRecord *&pBuffer, int n1, int n2); //TODO: rename args

    void QuickSort(pTTabRecord *pMemory, int dataCount); // Быстрая сортировка
    void QuickSplit(pTTabRecord *pData, int size, int &Pivot); //TODO: What is pivot?
public:
    TSortTable(int size = TABLE_MAX_SIZE) : TScanTable(size) {};
    TSortTable(const TScanTable &table); // Из просматриваемой таблицы

    TSortTable & operator=(const TScanTable &table);

    TSortMethod GetSortMethod(void);    // Получить метод сортировки
    void SetSortMethod(TSortMethod srtMethod);// Установить метод сортировки

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

};
#endif // TSORT_TABLE_INCLUDE_TSORT_TABLE_H
