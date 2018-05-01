#include "THashTable.h"

#ifndef TARRAY_HASH_INCLUDE_TARRAY_HASH_H
#define TARRAY_HASH_INCLUDE_TARRAY_HASH_H

#define TABLE_MAX_SIZE 25
#define TABLE_HASH_STEP 5

class  TArrayHash : public THashTable 
{
protected:
    pTTabRecord * pRecords; // Память для записей таблицы
    pTTabRecord pMark;      // Маркер для индикации строк с удаленными записями
    int maxTableSize;       // Макс. возможное число записей
    int hashStep;           // Шаг вторичного перемешивания
    int freePosition;       // Первая свободная строка, обнаруженная при поиске
    int currentPosition;    // Строка памяти при завершении поиска

    int GetNextPosition(int position) { return (position + hashStep) % maxTableSize; };
public:
    TArrayHash(int size = TABLE_MAX_SIZE, int step = TABLE_HASH_STEP);
    ~TArrayHash();

    //-----------------------------Информационные методы-----------------------------
    virtual /*int*/bool IsFull() const;

    //-----------------------------Доступ-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------Навигация-----------------------------
    virtual /*int*/void Reset(void);   // Установить на первую запись
    virtual /*int*/bool IsTableEnded(void) const;
    virtual /*int*/void GoNext(void); // Переход к следующей записи, (=1 после применения для последней записи таблицы)
};

#endif // TARRAY_HASH_INCLUDE_TARRAY_HASH_H