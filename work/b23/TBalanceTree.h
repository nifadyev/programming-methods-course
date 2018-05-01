#include "TTreeTable.h"
#include "TBalanceNode.h"

#ifndef TBALANCE_TREE_INCLUDE_TBALANCE_TREE_H
#define TBALANCE_TREE_INCLUDE_TBALANCE_TREE_H

class  TBalanceTree : public TTreeTable 
{
protected:
    int InsertBalanceTree(pTBalanceNode &pNode, TKey key, pTBalanceNode value);
    int LeftTreeBalancing(pTBalanceNode &pNode);
    int RightTreeBalancing(pTBalanceNode &pNode);
public:
    TBalanceTree() :TTreeTable() {}

    //-----------------------------Основные методы-----------------------------
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);
};

#endif // TBALANCE_TREE_INCLUDE_TBALANCE_TREE_H