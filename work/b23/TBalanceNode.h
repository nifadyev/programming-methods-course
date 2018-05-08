#include "TTable.h"
#include "TTreeNode.h"

#ifndef TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H
#define TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H

// #define BALANCE_OK 0
// #define BALANCE_LEFT -1
// #define BALANCE_RIGHT 1

enum {BALANCE_LEFT = -1, BALANCE_OK, BALANCE_RIGHT};
class TBalanceNode;

class  TBalanceNode : public TTreeNode 
{
protected:
    int balanceIndex; // ������ ������������ ������� (-1, 0, 1)
public:
    TBalanceNode(TKey key = "", pTDataValue value = nullptr, pTTreeNode pLeft = nullptr,
        pTTreeNode pRight = nullptr, int balance = BALANCE_OK) : TTreeNode(key, value, pLeft, pRight),
        balanceIndex(balance) { };
    ~TBalanceNode() {}

    virtual TDataValue *GetCopy();
    int GetBalance(void) const;
    void SetBalance(int balance);
    friend class TBalanceTree;
};

typedef  TBalanceNode* pTBalanceNode;
#endif // TBALANCE_NODE_INCLUDE_TBALANCE_NODE_H