#include "TTabRecord.h"
#include "TDatValue.h"

#ifndef TTREE_NODE_INCLUDE_TTREE_NODE_H
#define TTREE_NODE_INCLUDE_TTREE_NODE_H

class  TTreeNode;
typedef  TTreeNode *pTTreeNode;

class  TTreeNode : public TTabRecord 
{
protected:
    pTTreeNode pLeft, pRight; // ”казатели на поддеревь€
public:
    TTreeNode(TKey key = "", pTDataValue value = nullptr, pTTreeNode pLeft = nullptr,
        pTTreeNode pRight = nullptr) : TTabRecord(key, value), pLeft(pLeft), pRight(pRight) {};

    pTTreeNode GetLeft(void) const; // ”казатель на левое поддерево
    pTTreeNode GetRight(void) const; // ”казатель на правое поддерево

    virtual TDataValue *GetCopy();
    friend class TTreeTable;
    friend class TBalanceTree;
};

#endif // TTREE_NODE_INCLUDE_TTREE_NODE_H
