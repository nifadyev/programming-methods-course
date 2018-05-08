#include "TBalanceTree.h"

int TBalanceTree::InsertBalanceTree(pTBalanceNode pNode, TKey key, pTBalanceNode value)
{
    bool isHeightIncreased = false;

    if (pNode == nullptr)
    {
        pNode = new TBalanceNode(key, value);
        isHeightIncreased = true;
        dataCount++;
    }
    else if ((pNode->key > key) && InsertBalanceTree((TBalanceNode*)pNode->pLeft, key, value))
    {
        isHeightIncreased = LeftTreeBalancing(pNode);
    }
    else if ((pNode->key < key) && InsertBalanceTree((TBalanceNode*)pNode->pRight, key, value))
    {
        isHeightIncreased = RightTreeBalancing(pNode);
    }

    return isHeightIncreased;
}

int TBalanceTree::LeftTreeBalancing(pTBalanceNode pNode)
{
    return 0;
}

int TBalanceTree::RightTreeBalancing(pTBalanceNode pNode)
{
    return 0;
}

void TBalanceTree::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full tree table");
    }

    try
    {
        FindRecord(key);
    }
    catch(...)
    {
        InsertBalanceTree((pTBalanceNode)pRoot, key, (pTBalanceNode)value);
        return;
    }

    throw runtime_error("Error! Record with such key has alreadey existed");
}

void TBalanceTree::DeleteRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot delete record from empty table");
    }

    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw;
    }
}
