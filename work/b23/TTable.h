#ifndef TTABLE_INCLUDE_TTABLE_H
#define TTABLE_INCLUDE_TTABLE_H

#include "TTabRecord.h"

class TTable
{
 protected:
    int dataCount;   // Количество записей в таблице
    int efficiency;  // Показатель эффективности выполнения операции
public:
    TTable() : dataCount(0), efficiency(0) {}
    virtual ~TTable() {}

    //-----------------------------Информационные методы-----------------------------
    int GetDataCount() const
    { 
        return dataCount;
    }
    int GetEfficiency() const
    { 
        return efficiency;
    }

    bool IsEmpty() const
    { 
        return dataCount == 0;
    }
    virtual bool IsFull() const = 0;

    //-----------------------------Доступ-----------------------------
    virtual TKey GetKey(void) const = 0;
    virtual pTDataValue GetValuePTR(void) const = 0;

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key) = 0;
    virtual void InsertRecord(TKey key, pTDataValue value) = 0;
    virtual void DeleteRecord(TKey key) = 0;

    //-----------------------------Навигация-----------------------------
    virtual int Reset(void) = 0;   // Установить на первую запись
    virtual bool IsTableEnded(void) const = 0;
    virtual int GoNext(void) = 0;  // Переход к следующей записи, (=1 после применения для последней записи таблицы)
};
#endif  // TTABLE_INCLUDE_TTABLE_H
