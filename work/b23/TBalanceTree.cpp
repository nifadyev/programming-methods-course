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
    else if ((pNode->key > key) && InsertBalanceTree((TBalanceNode *)pNode->pLeft, key, value))
    {
        isHeightIncreased = LeftTreeBalancing(pNode);
    }
    else if ((pNode->key < key) && InsertBalanceTree((TBalanceNode *)pNode->pRight, key, value))
    {
        isHeightIncreased = RightTreeBalancing(pNode);
    }

    return isHeightIncreased;
}

int TBalanceTree::LeftTreeBalancing(pTBalanceNode pNode)
{
    bool isHeightIncreased = false;

    switch (pNode->balanceIndex)
    {
    case BALANCE_RIGHT:
        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    case BALANCE_OK:
        pNode->SetBalance(BALANCE_LEFT);
        isHeightIncreased = true;
        break;
    case BALANCE_LEFT:
        pTBalanceNode leftSubtree = (pTBalanceNode)(pNode->pLeft);
        if (leftSubtree->balanceIndex == BALANCE_LEFT)
        {
            pNode->pLeft = leftSubtree->pRight;
            leftSubtree->pRight = pNode;
            pNode->SetBalance(BALANCE_OK);
            pNode = leftSubtree;
        }
        else
        {
            pTBalanceNode rightSubtree = (pTBalanceNode)(leftSubtree->pRight);
            leftSubtree->pRight = rightSubtree->pLeft;
            rightSubtree->pLeft = leftSubtree;
            pNode->pLeft = rightSubtree->pRight;
            rightSubtree->pRight = pNode;

            if (rightSubtree->balanceIndex == BALANCE_LEFT)
            {
                leftSubtree->SetBalance(BALANCE_RIGHT);
            }
            else
            {
                leftSubtree->SetBalance(BALANCE_OK);
            }

            if (rightSubtree->balanceIndex == BALANCE_RIGHT)
            {
                pNode->SetBalance(BALANCE_LEFT);
            }
            else
            {
                pNode->SetBalance(BALANCE_OK);
            }

            pNode = rightSubtree;
        }

        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    }

    return isHeightIncreased;
}

int TBalanceTree::RightTreeBalancing(pTBalanceNode pNode)
{
    bool isHeightIncreased = false;

    switch (pNode->balanceIndex)
    {
    case BALANCE_LEFT:
        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    case BALANCE_OK:
        pNode->SetBalance(BALANCE_RIGHT);
        isHeightIncreased = true;
        break;
    case BALANCE_RIGHT:
        pTBalanceNode rightSubtree = (pTBalanceNode)(pNode->pRight);
        if (rightSubtree->balanceIndex == BALANCE_RIGHT)
        {
            pNode->pRight = rightSubtree->pLeft;
            rightSubtree->pLeft = pNode;
            pNode->SetBalance(BALANCE_OK);
            pNode = rightSubtree;
        }
        else
        {
            pTBalanceNode leftSubtree = (pTBalanceNode)(rightSubtree->pLeft);
            rightSubtree->pLeft = leftSubtree->pRight;
            leftSubtree->pRight = rightSubtree;
            pNode->pRight = leftSubtree->pLeft;
            leftSubtree->pLeft = pNode;

            if (leftSubtree->balanceIndex == BALANCE_RIGHT)
            {
                rightSubtree->SetBalance(BALANCE_LEFT);
            }
            else
            {
                rightSubtree->SetBalance(BALANCE_OK);
            }

            if (leftSubtree->balanceIndex == BALANCE_LEFT)
            {
                pNode->SetBalance(BALANCE_RIGHT);
            }
            else
            {
                pNode->SetBalance(BALANCE_OK);
            }

            pNode = leftSubtree;
        }

        pNode->SetBalance(BALANCE_OK);
        isHeightIncreased = false;
        break;
    }

    return isHeightIncreased;
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
    catch (...)
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
