#include "TTable.h"

#ifndef TARRAY_TABLE_INCLUDE_TARRAY_TABLE_H
#define TARRAY_TABLE_INCLUDE_TARRAY_TABLE_H

#define TABLE_MAX_SIZE 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
    pTTabRecord *pRecords;  // Память для записей таблицы
    int maxTableSize;       // Максимально возможное число записей в таблице
    int currentPosition;    // Номер текущей записи (нумерация с 0)
public:
    explicit TArrayTable(int size = TABLE_MAX_SIZE);
    ~TArrayTable();

    //-----------------------------Информационные методы-----------------------------
    virtual /*int*/bool IsFull() const;
    int GetTableSize() const;

    //-----------------------------Доступ-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;

    virtual TKey GetKey(TDataPos mode) const;
    virtual pTDataValue GetValuePTR(TDataPos mode) const;

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key) = 0;
    virtual void InsertRecord(TKey key, pTDataValue value) = 0;
    virtual void DeleteRecord(TKey key) = 0;

    //-----------------------------Навигация-----------------------------
    virtual int Reset(void);   // Установить на первую запись
    virtual bool IsTableEnded(void) const;
    virtual int GoNext(void);  // Переход к следующей записи, (=1 после применения для последней записи таблицы)
    
    virtual void SetCurrentPosition(int position);
    int GetCurrentPosition(void) const;
    
    friend class TSortTable;
};
#endif // TARRAY_TABLE_INCLUDE_TARRAY_TABLE_H
