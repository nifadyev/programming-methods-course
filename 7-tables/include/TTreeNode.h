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
