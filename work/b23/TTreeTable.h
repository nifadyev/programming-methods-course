#include "TTable.h"
#include "TTreeNode.h"
#include <stack>

#ifndef TTREE_TABLE_INCLUDE_TTREE_TABLE_H
#define TTREE_TABLE_INCLUDE_TTREE_TABLE_H

class  TTreeTable : public TTable 
{
protected:
    pTTreeNode pRoot;             // Указатель на корень дерева
    //TODO: Rename
    pTTreeNode *ppRef;            // Адрес указателя на вершину-результата в FindRecord
    pTTreeNode pCurrent;          // Указатель на текущую вершину
    int currentPosition;          // Номер текущей вершины
    stack <pTTreeNode> iterators; // Стек для итератора

    void DeleteTreeTable(pTTreeNode pNode); // Удаление
public:
    TTreeTable() : TTable() { currentPosition = 0; pRoot = pCurrent = nullptr; ppRef = nullptr; }
    ~TTreeTable() { DeleteTreeTable(pRoot); }
    //-----------------------------Информационные методы-----------------------------
    virtual /*int*/bool IsFull() const;

    //-----------------------------Основные методы-----------------------------
    virtual pTTreeNode FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------Навигация-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;
    virtual /*int*/void Reset(void);   // Установить на первую запись
    virtual /*int*/bool IsTableEnded(void) const;
    virtual /*int*/void GoNext(void); // Переход к следующей записи, (=1 после применения для последней записи таблицы)
};

#endif // TTREE_TABLE_INCLUDE_TTREE_TABLE_H