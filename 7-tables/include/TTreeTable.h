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
