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
