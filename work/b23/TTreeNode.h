#include "TTabRecord.h"
#include "DatValue.h"

#ifndef TTREE_NODE_INCLUDE_TTREE_NODE_H
#define TTREE_NODE_INCLUDE_TTREE_NODE_H

class  TTreeNode;
typedef  TTreeNode *pTTreeNode;

class  TTreeNode : public TTabRecord 
{
 protected:
    pTTreeNode pLeft, pRight; // ��������� �� ����������
 public:
    TTreeNode(TKey key = "", pTDataValue value = nullptr, pTTreeNode pLft = nullptr,
        pTTreeNode pRght = nullptr) : TTabRecord(key, value), pLeft(pLft), pRight(pRght) {}

    pTTreeNode GetLeft(void) const; // ��������� �� ����� ���������
    pTTreeNode GetRight(void) const; // ��������� �� ������ ���������

    virtual TDataValue *GetCopy();
    friend class TTreeTable;
    friend class TBalanceTree;
};

#endif // TTREE_NODE_INCLUDE_TTREE_NODE_H
