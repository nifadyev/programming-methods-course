#include "TTreeNode.h"

#ifndef TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H
#define TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H

#define BALANCE_OK 0
#define BALANCE_LEFT -1
#define BALANCE_RIGHT 1

typedef  TBalanceNode *pTBalanceNode;
class  TBalanceNode : public TTreeNode 
{
protected:
    int balanceIndex; // Индекс балансировки вершины (-1, 0, 1)
public:
    TBalanceNode(TKey key = "", pTDataValue value = nullptr, pTTreeNode pLeft = nullptr,
        pTTreeNode pRight = nullptr, int balance = BALANCE_OK) : TTreeNode(key, value, pLeft, pRight),
        balanceIndex(balance) {};

    virtual TDataValue *GetCopy();
    int GetBalance(void) const;
    void SetBalance(int balance);
    friend class TBalanceTree;
};

#endif // TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H