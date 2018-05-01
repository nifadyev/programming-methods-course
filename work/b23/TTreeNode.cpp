#include "TTreeNode.h"

pTTreeNode TTreeNode::GetLeft(void) const
{
    return pTTreeNode();
}

pTTreeNode TTreeNode::GetRight(void) const
{
    return pTTreeNode();
}

TDataValue * TTreeNode::GetCopy()
{
    return nullptr;
}
