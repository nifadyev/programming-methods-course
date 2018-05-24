#ifndef TTAB_RECORD_INCLUDE_TTAB_RECORD_H
#define TTAB_RECORD_INCLUDE_TTAB_RECORD_H

#include <iostream>
#include "DatValue.h"
using namespace std;

typedef string TKey;  // Тип ключа записи


//----------------Класс объектов-значений для записей таблицы----------------   
class TTabRecord : public TDataValue
{
 protected:
    TKey key;            // Ключ записи
    pTDataValue pValue;  // Указатель на значение
 public:
    explicit TTabRecord(TKey key = "", pTDataValue value = nullptr);

    void SetKey(TKey key);
    TKey GetKey(void);

    void SetValuePtr(pTDataValue ptr);  // Установить указатель на данные
    pTDataValue GetValuePTR(void);      // Получить указатель на данные

    virtual TDataValue* GetCopy();

    TTabRecord & operator = (const TTabRecord &record);
    virtual int operator == (const TTabRecord &record);
    virtual int operator < (const TTabRecord &record);
    virtual int operator > (const TTabRecord &record);

    //----------------Дружественные классы для различных типов таблиц----------------
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};

typedef TTabRecord *pTTabRecord;
#endif  // TTAB_RECORD_INCLUDE_TTAB_RECORD_H
