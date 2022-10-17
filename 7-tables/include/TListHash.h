#include "THashTable.h"
#include "DatList.h"

#ifndef TLIST_HASH_INCLUDE_TLIST_HASH_H
#define TLIST_HASH_INCLUDE_TLIST_HASH_H

#define TABLE_MAX_SIZE 25
class TListHash : public THashTable
{
 protected:
    pTDataList *pList;  // Память для массива указателей на списки записей
    int tableSize;      // Размер массива указателей
    int currentList;    // Список, в котором выполнялся поиск
 public:
    explicit TListHash(int size = TABLE_MAX_SIZE);
    ~TListHash();
    //-----------------------------Информационные методы-----------------------------
    virtual bool IsFull() const;

    //-----------------------------Доступ-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------Навигация-----------------------------
    virtual int Reset(void);  // Установить на первую запись
    virtual bool IsTableEnded(void) const;
    virtual int GoNext(void);  // Переход к следующей записи, (=1 после применения для последней записи таблицы)
};

#endif  // TLIST_HASH_INCLUDE_TLIST_HASH_H
