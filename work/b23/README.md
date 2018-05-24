# Лабораторная работа №6. Таблицы

## Цели и задачи

Целью лабораторной работы помимо изучения способов организации таблиц является начальное знакомство с принципами проектирования структур хранения, используемых в методах решения прикладных задач.

В рамках данной лабораторной работы ставится задача создания программных средств, поддерживающих табличные динамические структуры данных (таблицы) и базовые операции над ними:

-	поиск записи;
-	вставка записи (без дублирования);
-	удаление записи.

Выполнение операций над таблицами может осуществляться с различной степенью эффективности в зависимости от способа организации таблицы. 

В рамках лабораторной работы как показатель эффективности предлагается использовать количество операций, необходимых для выполнения операции поиска записи в таблице. Величина этого показателя должна определяться как аналитически (при использовании тех или иных упрощающих предположений), так и экспериментально на основе проведения вычислительных экспериментов.

В лабораторной работе предлагается реализовать следующие типы таблиц:

-	просмотровые (неупорядоченные);
-	упорядоченные (сортированные);
-	таблицы со структурами хранения на основе деревьев поиска;
-	хеш-таблицы или перемешанные (с вычисляемыми адресами).

Необходимо разработать интерфейс доступа к операциям поиска, вставки и удаления, не зависящий от способа организации таблицы.

## Описание работы
### Реализация класса `TTabRecord`
#### TTabRecord.h
```C++
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
```

#### TTabRecord.cpp
```C++
#include "TTabRecord.h"

TTabRecord::TTabRecord(TKey key, pTDataValue value)
{
    this->key = key;
    this->pValue = value;
}

void TTabRecord::SetKey(TKey key)
{
    this->key = key;
}

TKey TTabRecord::GetKey(void)
{
    return key;
}

void TTabRecord::SetValuePtr(pTDataValue ptr)
{
    pValue = ptr;
}

pTDataValue TTabRecord::GetValuePTR(void)
{
    return pValue;
}

TDataValue* TTabRecord::GetCopy()
{
    return new TTabRecord(key, pValue);
}

TTabRecord& TTabRecord::operator=(const TTabRecord &record)
{
    key = record.key;
    pValue = record.pValue;

    return *this;
}

int TTabRecord::operator==(const TTabRecord & record)
{
    return key == record.key;
}

int TTabRecord::operator<(const TTabRecord & record)
{
    return key < record.key;
}

int TTabRecord::operator>(const TTabRecord & record)
{
    return key > record.key;
}
```

### Реализация класса `TTable`
#### TTable.h
```C++
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
```

### Реализация класса `TArrayTable`
#### TArrayTable.h
```C++
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
```

#### TArrayTable.cpp
```C++
#include "TArrayTable.h"

TArrayTable::TArrayTable(int size)
{
    if (size <= 0 || size > TABLE_MAX_SIZE)
    {
        throw invalid_argument("Error! Size of array table must be positive and less than max");
    }

    currentPosition = 0;
    maxTableSize = size;
    pRecords = new pTTabRecord[maxTableSize];
    for (int i = 0; i < maxTableSize; i++)
    {
        pRecords[i] = nullptr;
    }
}

TArrayTable::~TArrayTable()
{
    if (pRecords != nullptr)
    {
        for (int i = 0; i < maxTableSize; ++i)
        {
            if (pRecords[i] != nullptr)
            {
                if (pRecords[i]->pValue != nullptr)
                {
                    delete pRecords[i]->pValue;
                }
                delete pRecords[i];
            }
        }
        delete[] pRecords;
    }
}

bool TArrayTable::IsFull() const
{
    return maxTableSize == dataCount;
}

int TArrayTable::GetTableSize() const
{
    return maxTableSize;
}

TKey TArrayTable::GetKey(void) const
{
    return GetKey(CURRENT_POS);
}

pTDataValue TArrayTable::GetValuePTR(void) const
{
    return GetValuePTR(CURRENT_POS);
}

TKey TArrayTable::GetKey(TDataPos mode) const
{
    if (IsEmpty())
    {
        throw runtime_error("Error! Table is empty");
    }

    int tempPosition = -1;

    switch (mode)
    {
    case FIRST_POS:
        tempPosition = 0;
        break;
    case CURRENT_POS:
        tempPosition = currentPosition;
        break;
    case LAST_POS:
        tempPosition = dataCount - 1;
        break;
    // Impossible to get wrong position because
    // it is already checked in SetCurrentPosition or in GoNext
    }

    return (pRecords[tempPosition] == nullptr) ? TKey("") : pRecords[tempPosition]->key;
}

pTDataValue TArrayTable::GetValuePTR(TDataPos mode) const
{
    if (IsEmpty())
    {
        throw runtime_error("Error! Table is empty");
    }

    int tempPosition = -1;

    switch (mode)
    {
    case FIRST_POS:
        tempPosition = 0;
        break;
    case CURRENT_POS:
        tempPosition = currentPosition;
        break;
    case LAST_POS:
        tempPosition = dataCount - 1;
        break;
    // Impossible to get wrong position because
    // it is already checked in SetCurrentPosition or in GoNext
    }

    return (pRecords[tempPosition] == nullptr) ? nullptr : pRecords[tempPosition]->pValue;
}

int TArrayTable::Reset(void)
{
    return currentPosition = 0;
}

bool TArrayTable::IsTableEnded(void) const
{
    return currentPosition == dataCount;
}

int TArrayTable::GoNext(void)
{
    if (IsTableEnded())
    {
        throw logic_error("Error! Cannot go next in ended table");
    }

    return currentPosition++;
}

void TArrayTable::SetCurrentPosition(int position)
{
    if (position < 0 || position > TABLE_MAX_SIZE)
    {
        throw invalid_argument("Error! Position must be positive and less than max");
    }

    currentPosition = position;
}

int TArrayTable::GetCurrentPosition(void) const
{
    return currentPosition;
}
```

### Реализация класса `TScanTable`
#### TScanTable.h
```C++
#include "TArrayTable.h"

#ifndef TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H
#define TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H

class  TScanTable : public TArrayTable
{
public:
    explicit TScanTable(int size = TABLE_MAX_SIZE) : TArrayTable(size) {};

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);
};
#endif  // TSCAN_TABLE_INCLUDE_TSCAN_TABLE_H
```

#### TScanTable.cpp
```C++
#include "TScanTable.h"

pTDataValue TScanTable::FindRecord(TKey key)
{
    int i = 0;

    for (i = 0; i < dataCount; i++)
    {
        if (pRecords[i]->GetKey() == key)
        {
            break;
        }
    }

    efficiency = i + 1;
    if (i < dataCount)
    {
        currentPosition = i;
        return pRecords[i]->pValue;
    }
    else
    {
        throw runtime_error("Error! Requested record did not found");
    }
}

void TScanTable::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full table");
    }

    int i = 0;

    for (i = 0; i < dataCount; i++)
    {
        if (pRecords[i]->GetKey() == key)
        {
            break;
        }
    }
    if (i < dataCount)
    {
        throw runtime_error("Error! Record with specified key has already existed");
    }

    pRecords[dataCount++] = new TTabRecord(key, value);
}

void TScanTable::DeleteRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Table is empty");
    }

    for(int i = 0; i < dataCount; i++)
    {
        if (pRecords[i]->GetKey() == key)
        {
            if (pRecords[i]->pValue != nullptr)
            {
                delete pRecords[i]->pValue;
            }
            delete pRecords[i];
            pRecords[i] = nullptr;
            pRecords[--dataCount] = nullptr;

            return;
        }
    }

    throw runtime_error("Error! Requested record did not found");
}
```

### Реализация класса `TSortTable`
#### TSortTable.h
```C++
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
```
#### TSortTable.cpp
```C++
#include "TSortTable.h"

void TSortTable::SortData(void)
{
    switch (sortMethod)
    {
    case INSERT_SORT:
        InsertSort(pRecords, dataCount);
        break;
    case MERGE_SORT:
        MergeSort(pRecords, dataCount);
        break;
    case QUICK_SORT:
        QuickSort(pRecords, 0, dataCount - 1);
        break;
    default:
        throw runtime_error("Error! Sort method is not mentioned");
    }
}

void TSortTable::InsertSort(pTTabRecord *pMemory, int dataCount)
{
    for (int i = 0; i < dataCount; i++)
    {
        int j = i;
        pTTabRecord temp = pRecords[i];

        while (j > 0 && (temp->GetKey() < pRecords[i]->GetKey()))
        {
            pRecords[i] = pRecords[i - 1];
            j--;
        }
        pRecords[j] = temp;
    }
}

void TSortTable::MergeSort(pTTabRecord *pMemory, int dataCount)
{
    MergeSorter(pRecords, 0, dataCount - 1);
}

void TSortTable::MergeSorter(pTTabRecord *&pData, int left, int right)
{
    if (left == right)
    {
        return;
    }

    int middle = (right + left) / 2;
    MergeSorter(pData, left, middle);
    MergeSorter(pData, middle + 1, right);
    MergeData(pData, left, middle, right);
}

void TSortTable::MergeData(pTTabRecord *&pData, int left, int middle, int right)
{
    pTTabRecord *pBuffer = new pTTabRecord[right - left + 1];
    int i = left, j = middle + 1, k = 0;

    while (i <= middle && j <= right)
    {
        if (pData[i]->GetKey() < pData[j]->GetKey())
        {
            pBuffer[k++] = pData[i++];
        }
        else
        {
            pBuffer[k++] = pData[j++];
        }
    }

    if (i > middle)
    {
        while (j <= right)
        {
            pBuffer[k++] = pData[j++];
        }
    }
    else
    {
        while (i <= middle)
        {
            pBuffer[k++] = pData[i++];
        }
    }

    k = 0;
    for (i = left; i <= right; i++)
    {
        pData[i] = pBuffer[k++];
    }

    delete[] pBuffer;
}

void TSortTable::QuickSort(pTTabRecord *pMemory, int left, int right)
{
    if (left < right)
    {
        int temp = QuickSplit(pRecords, left, right);
        QuickSort(pRecords, left, temp - 1);
        QuickSort(pRecords, temp, right);
    }
}

int TSortTable::QuickSplit(pTTabRecord *pData, int left, int right)
{
    TKey pivot = pRecords[(left + right) / 2]->GetKey();
    int i = left, j = right;

    while (i <= j)
    {
        while (pRecords[i]->GetKey() < pivot)
        {
            i++;
        }
        while (pRecords[i]->GetKey() > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            pTTabRecord temp = pRecords[i];
            pRecords[i] = pRecords[j];
            pRecords[j] = temp;
            i++;
            j--;
        }
    }

    return i;
}

TSortTable::TSortTable(const TScanTable &table) : TScanTable(table.GetTableSize())
{
    dataCount = table.dataCount;
    for (int i = 0; i < dataCount; i++)
    {
        pRecords[i] = new TTabRecord(table.pRecords[i]->GetKey(), table.pRecords[i]->GetValuePTR());
    }

    sortMethod = INSERT_SORT;
    SortData();
    Reset();
}

TSortTable &TSortTable::operator=(const TScanTable &table)
{
    if (this != &table)
    {
        if (pRecords != nullptr)
        {
            for (int i = 0; i < maxTableSize; ++i)
            {
                if (pRecords[i] != nullptr)
                {
                    if (pRecords[i]->pValue != nullptr)
                    {
                        delete pRecords[i]->pValue;
                    }
                    delete pRecords[i];
                }
            }

            delete[] pRecords;
        }

        maxTableSize = table.maxTableSize;
        dataCount = table.dataCount;
        pRecords = new pTTabRecord[maxTableSize];
        for (int i = 0; i < maxTableSize; ++i)
        {
            if (table.pRecords[i] != nullptr)
            {
                pRecords[i] = new TTabRecord(table.pRecords[i]->GetKey(), table.pRecords[i]->GetValuePTR());
            }
            else
            {
                pRecords[i] = nullptr;
            }
        }

        SortData();
        Reset();
    }

    return *this;
}

TSortMethod TSortTable::GetSortMethod(void)
{
    return sortMethod;
}

void TSortTable::SetSortMethod(TSortMethod srtMethod)
{
    if (srtMethod != INSERT_SORT && srtMethod != MERGE_SORT && srtMethod != QUICK_SORT)
    {
        throw invalid_argument("Error! Chosed sort method is not supported");
    }

    sortMethod = srtMethod;
}

pTDataValue TSortTable::FindRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot find record in empty table");
    }

    Reset();
    efficiency = 0;
    int left = 0, right = dataCount;

    while ((right - left) > 0)
    {
        efficiency++;
        int middle = left + (right - left) / 2;
        if (pRecords[middle]->GetKey() == key)
        {
            currentPosition = middle;
            return pRecords[middle]->GetValuePTR();
        }

        if (pRecords[middle]->GetKey() > key)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    currentPosition = right;

    throw runtime_error("Error! There is no record with such key");
}

void TSortTable::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full table");
    }

    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        for (int i = dataCount; i > currentPosition; --i)
        {
            pRecords[i] = pRecords[i - 1];
        }
        pRecords[currentPosition] = new TTabRecord(key, value);
        dataCount++;
        return;
    }

    throw runtime_error("Error! Record with such data has already existed");
}

void TSortTable::DeleteRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot delete record from empty table");
    }

    // Nonexistent key
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw runtime_error("Error! Record with requested key is not found");
    }

    if (pRecords[currentPosition]->pValue != nullptr)
    {
        delete pRecords[currentPosition]->pValue;
    }
    delete pRecords[currentPosition];
    pRecords[currentPosition] = nullptr;

    for (int i = currentPosition; i < dataCount - 1; ++i)
    {
        pRecords[i] = pRecords[i + 1];
    }
    
    pRecords[dataCount - 1] = nullptr;
    dataCount--;
    Reset();
}
```

### Реализация класса `TreeNode`
#### TTreeNode.h
```C++
#ifndef TTREE_NODE_INCLUDE_TTREE_NODE_H
#define TTREE_NODE_INCLUDE_TTREE_NODE_H

#include "TTabRecord.h"

class  TTreeNode;
typedef  TTreeNode *pTTreeNode;

class  TTreeNode : public TTabRecord
{
 protected:
    pTTreeNode pLeft, pRight;  // Указатели на поддеревья
 public:
    TTreeNode(TKey key = "", pTDataValue value = nullptr, pTTreeNode pLft = nullptr,
        pTTreeNode pRght = nullptr) : TTabRecord(key, value), pLeft(pLft), pRight(pRght) {}

    pTTreeNode GetLeft(void) const;   // Указатель на левое поддерево
    pTTreeNode GetRight(void) const;  // Указатель на правое поддерево

    virtual TDataValue *GetCopy();
    friend class TTreeTable;
    friend class TBalanceTree;
};

#endif // TTREE_NODE_INCLUDE_TTREE_NODE_H
```
#### TTreeNode.cpp
```C++
#include "TTreeNode.h"

pTTreeNode TTreeNode::GetLeft(void) const
{
    return pLeft;
}

pTTreeNode TTreeNode::GetRight(void) const
{
    return pRight;
}

TDataValue * TTreeNode::GetCopy()
{
    if (pValue != nullptr)
    {
        return (pTDataValue)(new TTreeNode(key, pValue->GetCopy(), nullptr, nullptr));
    }

    return (pTDataValue)(new TTreeNode(key, nullptr, nullptr, nullptr));
}
```

### Реализация класса `TTreeTable`
#### TTreeTable.h
```C++
#ifndef TTREE_TABLE_INCLUDE_TTREE_TABLE_H
#define TTREE_TABLE_INCLUDE_TTREE_TABLE_H

#include "TTable.h"
#include "TTreeNode.h"
#include <stack>

class  TTreeTable : public TTable
{
 protected:
    pTTreeNode pRoot;              // Указатель на корень дерева
    pTTreeNode ppRef;              // Адрес указател€ на вершину-результата в FindRecord
    pTTreeNode pCurrent;           // Указатель на текущую вершину
    int currentPosition;           // Ќомер текущей вершины
    stack <pTTreeNode> iterators;  // Стек для итератора

    void DeleteTreeTable(pTTreeNode pNode);
 public:
    TTreeTable() : TTable(), currentPosition(0), pRoot(nullptr), pCurrent(nullptr), ppRef(nullptr) {}
    ~TTreeTable() { DeleteTreeTable(pRoot); }
    //-----------------------------Информационные методы-----------------------------
    virtual bool IsFull() const;

    //-----------------------------Основные методы-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------Навигация------------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;
    virtual int Reset(void);   // Установить на первую запись
    virtual bool IsTableEnded(void) const;
    virtual int GoNext(void);  // Переход к следующей записи, (=1 после применени€ дл€ последней записи таблицы)
};

#endif  // TTREE_TABLE_INCLUDE_TTREE_TABLE_H
```
#### TTreeTable.h
```C++
#include "TTreeTable.h"

void TTreeTable::DeleteTreeTable(pTTreeNode pNode)
{
    if (pNode == nullptr)
    {
        return;
    }

    if (pNode->pLeft != nullptr)
    {
        DeleteTreeTable(pNode->pLeft);
    }
    if (pNode->pRight != nullptr)
    {
        DeleteTreeTable(pNode->pRight);
    }
    if (pNode->pValue != nullptr)
    {
        delete pNode->pValue;
    }

    delete pNode;
    pNode = nullptr;
}

bool TTreeTable::IsFull() const
{
    // Change BY ALL MEANS
    try
    {
        pTTreeNode tmp = new TTreeNode();
        delete tmp;
    }
    catch (...)
    {
        return true;
    }
    return false;
}

pTDataValue TTreeTable::FindRecord(TKey key)
{
    pTTreeNode currentNode = pRoot;
    ppRef = nullptr;
    efficiency = 0;

    while (currentNode != nullptr)
    {
        efficiency++;
        if (currentNode->key == key)
        {
            // cout << "I AM HERE\n";
            return currentNode->GetValuePTR();
        }
        else
        {
            ppRef = currentNode;
            if (currentNode->key > key)
            {
                currentNode = currentNode->pLeft;
            }
            else
            {
                currentNode = currentNode->pRight;
            }
        }
    }

    throw runtime_error("Error! Record with requested key was not found");

    /*     pTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    efficiency = 0;
    while (pNode != nullptr)
    {
        efficiency++;
        if (pNode->key == key)
            break;
        if (pNode->key < key)
            ppRef = &pNode->pRight;
        else
            ppRef = &pNode->pLeft;
        pNode = *ppRef;
    }

    return (pNode == nullptr) ? nullptr : pNode->pValue; */
}

void TTreeTable::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full tree table");
    }

    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        if (ppRef == nullptr)
        {
            pRoot = new TTreeNode(key, value);
        }
        else
        {
            if (ppRef->key > key)
            {
                ppRef->pLeft = new TTreeNode(key, value);
            }
            else
            {
                ppRef->pRight = new TTreeNode(key, value);
            }
        }

        dataCount++;
        return;
    }

    throw runtime_error("Error! Record with such key has already existed");
}

void TTreeTable::DeleteRecord(TKey key)
{
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw invalid_argument("Error! Record with such key was not found");
    }

    pTTreeNode pTemp = nullptr; // Pointer which should be deleted

    if (ppRef == nullptr)
    {
        pTemp = pRoot;
    }
    else if (ppRef->key > key)
    {
        pTemp = ppRef->pLeft;
    }
    else
    {
        pTemp = ppRef->pRight;
    }

    // pTemp does not have a right child
    // Or pTemp is a leaf
    if (pTemp->pRight == nullptr)
    {
        // Delete root
        if (ppRef == nullptr)
        {
            pRoot = pTemp->pLeft;
        }
        else
        {
            if (pTemp == ppRef->pLeft)
            {
                ppRef->pLeft = pTemp->pLeft;
            }
            else
            {
                ppRef->pRight = pTemp->pLeft;
            }
        }

        pTemp->pLeft = nullptr;
        if (pTemp->pValue != nullptr)
        {
            delete pTemp->pValue;
        }
        delete pTemp;
    }

    // pTemp has right child
    else
    {
        pTTreeNode mostLeftNode = pTemp->pRight; // Most left node in right subtree
        ppRef = nullptr;

        while (mostLeftNode->pLeft != nullptr)
        {
            ppRef = mostLeftNode;
            mostLeftNode = mostLeftNode->pLeft;
        }
        if (ppRef != nullptr)
        {
            ppRef->pLeft = mostLeftNode->pRight;
        }
        else
        {
            pTemp->pRight = mostLeftNode->pRight;
        }

        if (pTemp->pValue != nullptr)
        {
            delete pTemp->pValue;
        }
        pTemp->pValue = mostLeftNode->pValue;
        mostLeftNode->pValue = nullptr;
        pTemp->key = mostLeftNode->key;
        delete mostLeftNode;
    }

    dataCount--;
}

// pTDataValue TTreeTable ::FindRecord(TKey k)
// {
//     pTTreeNode pNode = pRoot;
//     ppRef = &pRoot;
//     efficiency = 0;
//     while (pNode != nullptr)
//     {
//         efficiency++;
//         if (pNode->key == k)
//             break;
//         if (pNode->key < k)
//             ppRef = &pNode->pRight;
//         else
//             ppRef = &pNode->pLeft;
//         pNode = *ppRef;
//     }
//     return (pNode == nullptr) ? nullptr : pNode->pValue;
// }
// void TTreeTable::InsertRecord(TKey k, pTDataValue pVal)
// {
//     // if (IsFull())
//     //     SetRetCode(TabFull);
//     // else if (FindRecord(k) != nullptr)
//     //     SetRetCode(TabRecDbl);
//     // else
//     // {
//         *ppRef = new TTreeNode(k, pVal);
//         dataCount++;
//     //}
// }
// void TTreeTable ::DeleteRecord(TKey k)
// {
//     // if (IsEmpty())
//     //     SetRetCode(TabEmpty);
//     // else if (FindRecord(k) == nullptr)
//     //     SetRetCode(TabNoRec);
//     // else
//     // {
//         pTTreeNode pNode = *ppRef;
//         if (pNode->pRight == nullptr && pNode->pLeft == nullptr)
//             *ppRef = nullptr;
//         else if (pNode->pRight == nullptr)
//         {
//             pNode->key = pNode->pLeft->key;
//             pNode->pValue = pNode->pLeft->pValue;
//         }
//         else if (pNode->pLeft == nullptr)
//         {
//             pNode->key = pNode->pRight->key;
//             pNode->pValue = pNode->pRight->pValue;
//         }
//         else
//         {
//             pTTreeNode min = pNode->pLeft;
//             pTTreeNode minParent = pNode;
//             while (min->pRight != nullptr)
//             {
//                 minParent = min;
//                 min = min->pRight;
//             }
//             if (minParent != pNode)
//             {
//                 minParent->pRight = min->pLeft;
//                 pNode->key = min->key;
//                 pNode->pValue = min->pValue;
//                 pNode = min;
//             }
//             else
//             {
//                 pNode->key = min->key;
//                 pNode->pValue = min->pValue;
//                 pNode->pRight = min->pRight;
//                 pNode = min;
//             }
//             //delete min;
//             //delete minParent;
//         }
//         //delete pNode;
//         dataCount--;
//     //}
// }

TKey TTreeTable::GetKey(void) const
{
    return (pCurrent == nullptr) ? TKey("") : pCurrent->key;
}

pTDataValue TTreeTable::GetValuePTR(void) const
{
    return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

// After applying this method
// pCurrent leads to the most left tree node
int TTreeTable::Reset(void)
{
    while (!iterators.empty())
    {
        iterators.pop();
    }

    pTTreeNode currentNode = pCurrent = pRoot;
    while (currentNode != nullptr)
    {
        iterators.push(currentNode);
        pCurrent = currentNode;
        currentNode = currentNode->pLeft;
    }

    return currentPosition = 0;
}

bool TTreeTable::IsTableEnded(void) const
{
    return currentPosition == dataCount;
}

int TTreeTable::GoNext(void)
{
    if (!IsTableEnded() && (pCurrent != nullptr))
    {
        pTTreeNode currentNode = pCurrent = pCurrent->pRight;
        iterators.pop();
        while (currentNode != nullptr)
        {
            iterators.push(currentNode);
            pCurrent = currentNode;
            currentNode = currentNode->pLeft;
        }

        // There is no right subtree or tree has ended
        if (pCurrent == nullptr && !iterators.empty())
        {
            pCurrent = iterators.top();
        }
        return ++currentPosition;
    }

    return 1;
}
```

### Реализация класса `TBalanceNode`
#### TBalanceNode.h
```C++
#include "TTable.h"
#include "TTreeNode.h"

#ifndef TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H
#define TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H

enum
{
    BALANCE_LEFT = -1,
    BALANCE_OK,
    BALANCE_RIGHT
};

class TBalanceNode : public TTreeNode
{
 protected:
    int balanceIndex;  // Индекс балансировки вершины (-1, 0, 1)
 public:
    TBalanceNode(TKey key = "", pTDataValue value = nullptr, pTTreeNode pLeft = nullptr,
                 pTTreeNode pRight = nullptr, int balance = BALANCE_OK) : TTreeNode(key, value, pLeft, pRight),
                                                                          balanceIndex(balance){};
    ~TBalanceNode() {}

    virtual TDataValue *GetCopy();

    int GetBalance(void) const;
    void SetBalance(const int& balance);

    friend class TBalanceTree;
};

typedef TBalanceNode *pTBalanceNode;

#endif // TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H
```
#### TBalanceNode.cpp
```C++
#include "TBalanceNode.h"

TDataValue* TBalanceNode::GetCopy()
{
    if (pValue != nullptr)
    {
        return (pTDataValue)(new TBalanceNode(key, pValue->GetCopy(), nullptr, nullptr, balanceIndex));
    }
    else
    {
        return (pTDataValue)(new TBalanceNode(key, nullptr, nullptr, nullptr, balanceIndex));
    }
}

int TBalanceNode::GetBalance(void) const
{
    return balanceIndex;
}

void TBalanceNode::SetBalance(const int& balance)
{
    if (balance != BALANCE_LEFT && balance != BALANCE_OK && balance != BALANCE_RIGHT)
    {
        throw invalid_argument("Error! The balance value must be -1, 0 or 1");
    }

    balanceIndex = balance;
}
```

### Реализация класса `TBalanceTree`
#### TBalanceTree.h
```C++
#ifndef TBALANCE_TREE_INCLUDE_TBALANCE_TREE_H
#define TBALANCE_TREE_INCLUDE_TBALANCE_TREE_H

#include "TTreeTable.h"
#include "TBalanceNode.h"

class  TBalanceTree : public TTreeTable
{
 protected:
    int InsertBalanceTree(pTBalanceNode& pNode, TKey key, pTDataValue value);
    bool DeleteBalanceTree(pTBalanceNode pNode, TKey key, pTBalanceNode pParent);
    int LeftTreeBalancing(pTBalanceNode pNode);
    int RightTreeBalancing(pTBalanceNode pNode);
 public:
    TBalanceTree() : TTreeTable() {}

    //-----------------------------Основные методы-----------------------------
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);
};

#endif  // TBALANCE_TREE_INCLUDE_TBALANCE_TREE_H
```
#### TBalanceTree.cpp
```C++
#include "TBalanceTree.h"

int TBalanceTree::InsertBalanceTree(pTBalanceNode &pNode, TKey key, pTDataValue value)
{
    bool isHeightIncreased = false;

    if (pNode == nullptr)
    {
        pNode = new TBalanceNode(key, value);
        isHeightIncreased = true;
        dataCount++;
    }
    else if ((pNode->key > key) && InsertBalanceTree((pTBalanceNode &)(pNode->pLeft), key, value))
    {
        isHeightIncreased = LeftTreeBalancing(pNode);
    }
    else if ((pNode->key < key) && InsertBalanceTree((pTBalanceNode &)(pNode->pRight), key, value))
    {
        isHeightIncreased = RightTreeBalancing(pNode);
    }
    else
    {
        throw runtime_error("Error! Record with such key has alreadey existed");
    }

    return isHeightIncreased;
}

bool TBalanceTree::DeleteBalanceTree(pTBalanceNode pNode, TKey key, pTBalanceNode pParent)
{
    bool needBalancing = false;

    if (pNode == nullptr)
    {
        throw logic_error("Error! Cannot delete unexisting record");
    }

    else if (pNode->key > key)
    {
        DeleteBalanceTree((pTBalanceNode)(pNode->pLeft), key, pNode);
    }
    else if (pNode->key < key)
    {
        DeleteBalanceTree((pTBalanceNode)(pNode->pRight), key, pNode);
    }
    else
    {
        if (pNode->pRight == nullptr)
        {
            if (pParent == nullptr)
            {
                pRoot = pNode->pLeft;
            }
            else if (pNode == pParent->pLeft)
            {
                // Right tree balancing
                pParent->pLeft = pNode->pLeft;
            }
            else
            {
                // Left tree balancing
                pParent->pRight = pNode->pLeft;
            }

            pNode->pLeft = nullptr;
            if (pNode->pValue != nullptr)
            {
                delete pNode->pValue;
            }
            delete pNode;
        }

        else
        {
            pTBalanceNode mostLeftNode = (pTBalanceNode)(pNode->pRight);
            pTBalanceNode previous = nullptr;

            while (mostLeftNode->pLeft != nullptr)
            {
                previous = mostLeftNode;
                mostLeftNode = (pTBalanceNode)(mostLeftNode->pLeft);
            }

            if (previous != nullptr)
            {
                previous->pLeft = mostLeftNode->pRight;
            }
            else
            {
                pNode->pRight = mostLeftNode->pRight;
            }

            if (pNode->pValue != nullptr)
            {
                delete pNode->pValue;
            }

            pNode->pValue = mostLeftNode->pValue;
            mostLeftNode->pValue = nullptr;
            pNode->key = mostLeftNode->key;
            delete mostLeftNode;
        }

        dataCount--;
    }

    return needBalancing;
}

int TBalanceTree::LeftTreeBalancing(pTBalanceNode pNode)
{
    bool isHeightIncreased = false;

    switch (pNode->balanceIndex)
    {
    case BALANCE_RIGHT:
        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    case BALANCE_OK:
        pNode->SetBalance(BALANCE_LEFT);
        isHeightIncreased = true;
        break;
    case BALANCE_LEFT:
        pTBalanceNode leftSubtree = (pTBalanceNode)(pNode->pLeft);
        if (leftSubtree->balanceIndex == BALANCE_LEFT)
        {
            pNode->pLeft = leftSubtree->pRight;
            leftSubtree->pRight = pNode;
            pNode->SetBalance(BALANCE_OK);
            pNode = leftSubtree;
        }
        else
        {
            pTBalanceNode rightSubtree = (pTBalanceNode)(leftSubtree->pRight);
            leftSubtree->pRight = rightSubtree->pLeft;
            rightSubtree->pLeft = leftSubtree;
            pNode->pLeft = rightSubtree->pRight;
            rightSubtree->pRight = pNode;

            if (rightSubtree->balanceIndex == BALANCE_LEFT)
            {
                leftSubtree->SetBalance(BALANCE_RIGHT);
            }
            else
            {
                leftSubtree->SetBalance(BALANCE_OK);
            }

            if (rightSubtree->balanceIndex == BALANCE_RIGHT)
            {
                pNode->SetBalance(BALANCE_LEFT);
            }
            else
            {
                pNode->SetBalance(BALANCE_OK);
            }

            pNode = rightSubtree;
        }

        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    }

    return isHeightIncreased;
}

int TBalanceTree::RightTreeBalancing(pTBalanceNode pNode)
{
    bool isHeightIncreased = false;

    switch (pNode->balanceIndex)
    {
    case BALANCE_LEFT:
        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    case BALANCE_OK:
        pNode->SetBalance(BALANCE_RIGHT);
        isHeightIncreased = true;
        break;
    case BALANCE_RIGHT:
        pTBalanceNode rightSubtree = (pTBalanceNode)(pNode->pRight);
        if (rightSubtree->balanceIndex == BALANCE_RIGHT)
        {
            pNode->pRight = rightSubtree->pLeft;
            rightSubtree->pLeft = pNode;
            pNode->SetBalance(BALANCE_OK);
            pNode = rightSubtree;
        }
        else
        {
            pTBalanceNode leftSubtree = (pTBalanceNode)(rightSubtree->pLeft);
            rightSubtree->pLeft = leftSubtree->pRight;
            leftSubtree->pRight = rightSubtree;
            pNode->pRight = leftSubtree->pLeft;
            leftSubtree->pLeft = pNode;

            if (leftSubtree->balanceIndex == BALANCE_RIGHT)
            {
                rightSubtree->SetBalance(BALANCE_LEFT);
            }
            else
            {
                rightSubtree->SetBalance(BALANCE_OK);
            }

            if (leftSubtree->balanceIndex == BALANCE_LEFT)
            {
                pNode->SetBalance(BALANCE_RIGHT);
            }
            else
            {
                pNode->SetBalance(BALANCE_OK);
            }

            pNode = leftSubtree;
        }

        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    }

    return isHeightIncreased;
}

void TBalanceTree::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full tree table");
    }

    InsertBalanceTree((pTBalanceNode &)pRoot, key, value);
}

void TBalanceTree::DeleteRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot delete record from empty table");
    }

    DeleteBalanceTree((pTBalanceNode)pRoot, key, nullptr);
}
```

### Реализация класса `THashTable`
#### THashTable.h
```C++
#include "TTable.h"

#ifndef THASH_TABLE_INCLUDE_THASH_TABLE_H
#define THASH_TABLE_INCLUDE_THASH_TABLE_H

class  THashTable : public TTable 
{
protected:
    virtual unsigned long HashFunction(const TKey& key);
public:
    THashTable() : TTable() {}
};

#endif // THASH_TABLE_INCLUDE_THASH_TABLE_H
```
#### THashTable.cpp
```C++
#include "THashTable.h"

unsigned long THashTable::HashFunction(const TKey &key)
{
    // Gets numeric value from key
    unsigned long value = 0;
    for (size_t i = 0; i < key.size(); i++)
    {
        value = (value << 3) + key[i];
    }

    return value;
}
```

### Реализация класса `TArrayHash`
#### TArrayHash.h
```C++
#ifndef TARRAY_HASH_INCLUDE_TARRAY_HASH_H
#define TARRAY_HASH_INCLUDE_TARRAY_HASH_H

#include "THashTable.h"

#define TABLE_MAX_SIZE 25
#define TABLE_HASH_STEP 5

class  TArrayHash : public THashTable
{
protected:
    pTTabRecord *pRecords;  // Память для записей таблицы
    pTTabRecord pMark;      // Маркер для индикации строк с удаленными записями
    int maxTableSize;       // Максимально возможное число записей
    int hashStep;           // Шаг вторичного перемешивания
    int freePosition;       // Первая свободная строка, обнаруженная при поиске
    int currentPosition;    // Строка памяти при завершении поиска

    int GetNextPosition(int position);
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
    virtual int Reset(void);   // Установить на первую запись
    virtual /*int*/bool IsTableEnded(void) const;
    virtual int GoNext(void);  // Переход к следующей записи, (=1 после применения для последней записи таблицы)
};

#endif // TARRAY_HASH_INCLUDE_TARRAY_HASH_H
```
#### TArrayHash.cpp
```C++
#include "TArrayHash.h"

TArrayHash::TArrayHash(int size, int step) : THashTable()
{
    if (size <= 0 || size > TABLE_MAX_SIZE || step < 1 || step >= size)
    {
        throw out_of_range("Error! Parameters is out of range");
    }

    pRecords = new pTTabRecord[size];
    for (int i = 0; i < size; i++)
    {
        pRecords[i] = nullptr;
    }
    maxTableSize = size;
    hashStep = step;
    pMark = new TTabRecord("DELETED");
}

TArrayHash::~TArrayHash()
{
    if (pRecords != nullptr)
    {
        for (int i = 0; i < maxTableSize; i++)
        {
            if (pRecords[i] != nullptr && pRecords[i] != pMark)
            {
                if (pRecords[i]->pValue != nullptr)
                {
                    delete pRecords[i]->pValue;
                }
                delete pRecords[i];
            }
        }

        delete[] pRecords;
    }

    delete pMark;
}

int TArrayHash::GetNextPosition(int position) 
{ 
    return (position + hashStep) % maxTableSize;
}

bool TArrayHash::IsFull() const
{
    return dataCount == maxTableSize;
}

TKey TArrayHash::GetKey(void) const
{
    return (currentPosition < 0 || IsTableEnded()) ? TKey("") : pRecords[currentPosition]->key;
}

pTDataValue TArrayHash::GetValuePTR(void) const
{
    return (currentPosition < 0 || IsTableEnded()) ? nullptr : pRecords[currentPosition]->pValue;
}

pTDataValue TArrayHash::FindRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot find record in empty table");
    }

    freePosition = -1;
    currentPosition = HashFunction(key) % maxTableSize;
    efficiency = 0;
    int originPosition = currentPosition;

    while (true)
    {
        efficiency++;
        if (pRecords[currentPosition] == nullptr)
        {
            throw runtime_error("Error! Record with such key was not found");
        }
        else if (pRecords[currentPosition] == pMark && freePosition < 0)
        {
            freePosition = currentPosition;
        }
        else if (pRecords[currentPosition]->key == key)
        {
            return pRecords[currentPosition]->pValue;
        }

        currentPosition = GetNextPosition(currentPosition);
        if (currentPosition == originPosition)
        {
            break;
        }
    }

    throw runtime_error("Error! Record with such key was not found");
}

void TArrayHash::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw runtime_error("Error! Cannot insert record into full table");
    }

    freePosition = -1;
    currentPosition = HashFunction(key) % maxTableSize;
    int originPosition = currentPosition;

    while (true)
    {
        if (pRecords[currentPosition] != nullptr && pRecords[currentPosition] != pMark)
        {
            if (pRecords[currentPosition]->key == key)
            {
                throw runtime_error("Error! Record with such key has already existed");
            }
        }
        else if (pRecords[currentPosition] == pMark && freePosition < 0)
        {
            freePosition = currentPosition;
        }
        else if (pRecords[currentPosition] == nullptr)
        {
            if (freePosition < 0)
            {
                pRecords[currentPosition] = new TTabRecord(key, value);
            }
            else
            {
                pRecords[freePosition] = new TTabRecord(key, value);
            }
            dataCount++;
            return;
        }

        currentPosition = GetNextPosition(currentPosition);
        if (currentPosition == originPosition)
        {
            if (freePosition > -1)
            {
                pRecords[freePosition] = new TTabRecord(key, value);
                dataCount++;
                return;
            }
            break;
        }

        throw runtime_error("Error! Cannot insert new record");
    }
}

void TArrayHash::DeleteRecord(TKey key)
{
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw logic_error("Error! Cannot delete unexisting record");
    }

    if (pRecords[currentPosition]->pValue != nullptr)
    {
        delete pRecords[currentPosition]->pValue;
        pRecords[currentPosition]->pValue = nullptr;
    }

    delete pRecords[currentPosition];
    pRecords[currentPosition] = pMark;
    dataCount--;
}

int TArrayHash::Reset(void)
{
    currentPosition = 0;
    while (!IsTableEnded() && (pRecords[currentPosition] == nullptr || pRecords[currentPosition] == pMark))
    {
        currentPosition++;
    }
    if (IsTableEnded())
    {
        return -1;
    }

    return currentPosition;
}

bool TArrayHash::IsTableEnded(void) const
{
    return currentPosition == maxTableSize;
}

int TArrayHash::GoNext(void)
{
    while (++currentPosition && !IsTableEnded())
    {
        if (pRecords[currentPosition] != nullptr && pRecords[currentPosition] != pMark)
        {
            break;
        }
    }

    if (IsTableEnded())
    {
        return 1;
    }

    return currentPosition;
}
```

### Реализация класса `TListHash`
#### TListHash.h
```C++
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
```

#### TListHash.cpp
```C++
#include "TListHash.h"

TListHash::TListHash(int size) : THashTable()
{
    if (size <= 0 || size > TABLE_MAX_SIZE)
    {
        throw out_of_range("Error! Size of list hash must be positive and less than max");
    }

    pList = new pTDataList[size];
    for (int i = 0; i < size; i++)
    {
        pList[i] = new TDataList();
    }

    tableSize = size;
    currentList = 0;
}

TListHash::~TListHash()
{
    if (pList != nullptr)
    {
        for (int i = 0; i < tableSize; i++)
        {
            delete pList[i];
        }
        delete[] pList;
    }
}

bool TListHash::IsFull() const
{
    try
    {
        pTDataLink temp = new TDataLink();
        delete temp;
    }
    catch (...)
    {
        return true;
    }

    return false;
}

TKey TListHash::GetKey(void) const
{
    if (currentList < 0 || IsTableEnded())
    {
        return TKey("");
    }

    pTTabRecord temp = (pTTabRecord)(pList[currentList]->GetDataValue());
    return (temp == nullptr) ? TKey("") : temp->key;
}

pTDataValue TListHash::GetValuePTR(void) const
{
    if (currentList < 0 || IsTableEnded())
    {
        return nullptr;
    }

    pTTabRecord temp = (pTTabRecord)(pList[currentList]->GetDataValue());
    return (temp == nullptr) ? nullptr : temp->pValue;
}

pTDataValue TListHash::FindRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot find record in empty list");
    }

    efficiency = 0;
    currentList = HashFunction(key) % tableSize;
    pTDataList actualList = pList[currentList];

    for (actualList->Reset(); !actualList->IsListEnded(); actualList->GoNext())
    {
        efficiency++;
        if (((pTTabRecord)(actualList->GetDataValue()))->key == key)
        {
            return ((pTTabRecord)(actualList->GetDataValue()))->pValue;
        }
    }

    throw runtime_error("Error! Record with such key was not found");
}

void TListHash::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full list");
    }

    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        currentList = HashFunction(key) % tableSize;
        pList[currentList]->InsertBeforeFirst(new TTabRecord(key, value));
        dataCount++;

        return;
    }

    throw runtime_error("Error! Cannot insert already existing record");
}

void TListHash::DeleteRecord(TKey key)
{
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw logic_error("Error! Cannot find record with such key");
    }

    pList[currentList]->DeleteCurrent();
    dataCount--;
}

int TListHash::Reset(void)
{
    currentList = 0;
    while (!IsTableEnded() && pList[currentList]->IsEmpty())
    {
        currentList++;
    }

    if (IsTableEnded())
    {
        return -1;
    }
    else
    {
        pList[currentList]->Reset();
        
        return currentList;
    }
}

bool TListHash::IsTableEnded(void) const
{
    return currentList == tableSize;
}

int TListHash::GoNext(void)
{
    pList[currentList]->GoNext();
    if (!(pList[currentList]->IsListEnded()))
    {
        return currentList;
    }

    while (++currentList && !IsTableEnded())
    {
        if (!(pList[currentList]->IsEmpty()))
        {
            return pList[currentList]->Reset();
        }
    }

    return 1;
}
```

### Реализация класса `StudentInfo`
#### StudentInfo.h
```C++
#ifndef STUDENT_INFO_INCLUDE_STUDENT_INFO_H
#define STUDENT_INFO_INCLUDE_STUDENT_INFO_H

#include "DatValue.h"
static const int NUMBER_OF_MARKS = 5;

class StudentInfo : public TDataValue
{
 private:
    enum
    {
        MATH,
        AaDS,
        OS,
        ENGLISH,
        MNO
    };

 public:
    int marks[NUMBER_OF_MARKS];

    StudentInfo(int math = 4, int aads = 4, int os = 4, int english = 4, int mno = 4)
    {
        if (math < 0 || math > 5 || aads < 0 || aads > 5 || os < 0 || os > 5 || english < 0 || english > 5 || mno < 0 || mno > 5)
        {
            throw invalid_argument("Error! Marks should be more than 0 and less than 6");
        }

        marks[MATH] = math;
        marks[AaDS] = aads;
        marks[OS] = os;
        marks[ENGLISH] = english;
        marks[MNO] = mno;
    }

    TDataValue *GetCopy()
    {
        return new StudentInfo(marks[MATH], marks[AaDS], marks[OS], marks[ENGLISH], marks[MNO]);
    }

    int GetMark(int course)
    {
        return marks[course];
    }
};

#endif // STUDENT_INFO_INCLUDE_STUDENT_INFO_H
```

### Реализация класса `StudentAchievements`
#### StudentAchievements.h
```C++
#ifndef STUDENT_ACHIEVEMENTS_INCLUDE_STUDENT_ACHIEVEMENTS_H
#define STUDENT_ACHIEVEMENTS_INCLUDE_STUDENT_ACHIEVEMENTS_H

#include <fstream>
#include <vector>
#include <string>
#include "StudentInfo.h"
#include "TTable.h"

template <class Table>
class StudentAchievements
{
 private:
    vector<TTable *> tables;
    int groupNumber;

    int GetGroupNumber()
    {
        ifstream file;
        int result = 0;

        for (int i = 1;; i++)
        {
            file.open(GetFileName(i));
            if (file.is_open())
            {
                result++;
                file.close();
            }
            else
            {
                return result;
            }
        }
    }

    void LoadStudentsProgress()
    {
        ifstream file;

        for (int i = 1; i <= groupNumber; i++)
        {
            TTable *tempTable = new Table();
            file.open(GetFileName(i));
            while (!file.eof())
            {
                string name;
                int math, aads, os, english, mno;

                file >> name;
                file >> math >> aads >> os >> english >> mno;
                tempTable->InsertRecord(name, new StudentInfo(math, aads, os, english, mno));
            }

            tempTable->Reset();
            tables.push_back(tempTable);
            file.close();
        }
    }

    string GetFileName(int groupID)
    {
        string filename = "students/group";
        filename += '0' + groupID;
        filename += ".txt";

        return filename;
    }

 public:
    StudentAchievements()
    {
        groupNumber = GetGroupNumber();
        LoadStudentsProgress();
    }

    // Student marks
    StudentInfo *GetStudentInfo(TKey studentName)
    {
        for (auto /* TTable */ i = tables.begin(); i != tables.end(); i++)
        {
            try
            {
                (*i)->FindRecord(studentName);
                return (StudentInfo*)((*i)->FindRecord(studentName));
            }
            catch (...)
            {
                return 0;
            }
            
        }
    }

    // Student mark
    int GetStudentMark(TKey studentName, int course)
    {
        if (course < 0 || course > NUMBER_OF_MARKS)
        {
            throw invalid_argument("Error! Cannot get mark on unexisting course");
        }

        return GetStudentInfo(studentName)->marks[course];
    }

    // Average student mark on on all courses
    double CalculateStudentAverageMark(TKey studentName)
    {
        if (!GetStudentInfo(studentName))
        {
            throw;
        }

        StudentInfo *info = GetStudentInfo(studentName);
        double result = 0;

        for (int i = 0; i < NUMBER_OF_MARKS; i++)
        {
            result += info->marks[i];
        }

        return result / NUMBER_OF_MARKS;
    }

    // Average student mark among all students of all groups
    double CalculateAverageMark(int course = -1)
    {
        double result = 0;
        double count = 0;

        for (int i = 0; i < groupNumber; i++)
        {
            result += CalculateAverageGroupMark(i, course);
            count++;
        }

        return result / count;
    }

    // Average mark among students of concrete group
    // If course != -1 then calculate on concrete course
    double CalculateAverageGroupMark(int group, int course = -1)
    {
        double result = 0;
        double count = 0;
        TTable *table = tables[group];
        table->Reset();
        
        while (!table->IsTableEnded())
        {
            StudentInfo *info = (StudentInfo *)(table->GetValuePTR());

            if (info)
            {
                for (int i = 0; i < NUMBER_OF_MARKS; i++)
                {
                    if (course == -1 || course == i)
                    {
                        result += info->marks[i];
                        count++;
                    }
                }

                table->GoNext();
            }
        }

        return result / count;
    }

    // Get group ID with best achievements on concrete course or on all courses
    int GetGroupIDWithBestMarks(int course = -1)
    {
        double max = 0;
        int bestGroup = -1;

        for (int i = 0; i < groupNumber; i++)
        {
            double mark = CalculateAverageGroupMark(i, course);
            if (mark > max)
            {
                max = mark;
                bestGroup = 1;
            }
        }

        return ++bestGroup; // Group numeration starts from 1
    }

    // Group numeration starts from 1 that's why if group = 0 =>
    // Calculate number of students with perfect marks in all groups
    int GetExcellentStudentsNumber(int group = 0)
    {
        int result = 0;

        for (int i = 0; i < groupNumber; i++)
        {
            if (group == 0 || group == (i + 1))
            {
                TTable *table = tables[i];
                table->Reset();

                while (!table->IsTableEnded())
                {
                    int markSum = 0;
                    StudentInfo *info = (StudentInfo *)table->GetValuePTR();
                    if (info != 0)
                    {
                        for (int j = 0; j < NUMBER_OF_MARKS; j++)
                        {
                            markSum += info->marks[i];
                        }
                    }

                    // if every mark is five
                    if (markSum == NUMBER_OF_MARKS * 5)
                    {
                        result++;
                    }
                    table->GoNext();
                }
            }
        }

        return result;
    }
};

#endif // STUDENT_ACHIEVEMENTS_INCLUDE_STUDENT_ACHIEVEMENTS_H
```

## Результаты тестирования и работы программы 
### Результаты тестирования
![](https://bytebucket.org/VadimNifadyev/lab7-tables/raw/be71f263d6cfa8d97afae498fcaa7410eb6cf2ad/work/b23/tests_result.png)
### Демонстрация работы программы
![](https://bytebucket.org/VadimNifadyev/lab7-tables/raw/be71f263d6cfa8d97afae498fcaa7410eb6cf2ad/work/b23/main_result.png)
## Вывод
В рамках данной лабораторной работы были изучены способы организации таблиц, а также принципы проектирования структур хранения, используемых в методах решения прикладных задач.