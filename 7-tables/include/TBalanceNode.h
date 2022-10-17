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