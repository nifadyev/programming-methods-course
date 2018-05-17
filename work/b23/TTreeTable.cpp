#include "TTreeTable.h"

void TTreeTable::DeleteTreeTable(pTTreeNode pNode)
{
    if (pNode == nullptr)
    {
        return;
    }

    if (pNode->pLeft != nullptr)
    {
        DeleteTreeTable(pNode->pLeft);
    }
    if (pNode->pRight != nullptr)
    {
        DeleteTreeTable(pNode->pRight);
    }
    if (pNode->pValue != nullptr)
    {
        delete pNode->pValue;
    }

    delete pNode;
    pNode = nullptr;
}

bool TTreeTable::IsFull() const
{
    // Change BY ALL MEANS
    try
    {
        pTTreeNode tmp = new TTreeNode();
        delete tmp;
    }
    catch (...)
    {
        return true;
    }
    return false;
}

pTDataValue TTreeTable::FindRecord(TKey key)
{
    pTTreeNode currentNode = pRoot;
    ppRef = nullptr;
    efficiency = 0;

    while (currentNode != nullptr)
    {
        efficiency++;
        if (currentNode->key == key)
        {
            // cout << "I AM HERE\n";
            return currentNode->GetValuePTR();
        }
        else
        {
            ppRef = currentNode;
            if (currentNode->key > key)
            {
                currentNode = currentNode->pLeft;
            }
            else
            {
                currentNode = currentNode->pRight;
            }
        }
    }

    throw runtime_error("Error! Record with requested key was not found");

    /*     pTTreeNode pNode = pRoot;
    ppRef = &pRoot;
    efficiency = 0;
    while (pNode != nullptr)
    {
        efficiency++;
        if (pNode->key == key)
            break;
        if (pNode->key < key)
            ppRef = &pNode->pRight;
        else
            ppRef = &pNode->pLeft;
        pNode = *ppRef;
    }

    return (pNode == nullptr) ? nullptr : pNode->pValue; */
}

void TTreeTable::InsertRecord(TKey key, pTDataValue value)
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
        if (ppRef == nullptr)
        {
            pRoot = new TTreeNode(key, value);
        }
        else
        {
            if (ppRef->key > key)
            {
                ppRef->pLeft = new TTreeNode(key, value);
            }
            else
            {
                ppRef->pRight = new TTreeNode(key, value);
            }
        }

        dataCount++;
        return;
    }

    throw runtime_error("Error! Record with such key has already existed");
}

void TTreeTable::DeleteRecord(TKey key)
{
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw invalid_argument("Error! Record with such key was not found");
    }

    pTTreeNode pTemp = nullptr; // Pointer which should be deleted

    if (ppRef == nullptr)
    {
        pTemp = pRoot;
    }
    else if (ppRef->key > key)
    {
        pTemp = ppRef->pLeft;
    }
    else
    {
        pTemp = ppRef->pRight;
    }

    // pTemp does not have a right child
    // Or pTemp is a leaf
    if (pTemp->pRight == nullptr)
    {
        // Delete root
        if (ppRef == nullptr)
        {
            pRoot = pTemp->pLeft;
        }
        else
        {
            if (pTemp == ppRef->pLeft)
            {
                ppRef->pLeft = pTemp->pLeft;
            }
            else
            {
                ppRef->pRight = pTemp->pLeft;
            }
        }

        pTemp->pLeft = nullptr;
        if (pTemp->pValue != nullptr)
        {
            delete pTemp->pValue;
        }
        delete pTemp;
    }

    // pTemp has right child
    else
    {
        pTTreeNode mostLeftNode = pTemp->pRight; // Most left node in right subtree
        ppRef = nullptr;

        while (mostLeftNode->pLeft != nullptr)
        {
            ppRef = mostLeftNode;
            mostLeftNode = mostLeftNode->pLeft;
        }
        if (ppRef != nullptr)
        {
            ppRef->pLeft = mostLeftNode->pRight;
        }
        else
        {
            pTemp->pRight = mostLeftNode->pRight;
        }

        if (pTemp->pValue != nullptr)
        {
            delete pTemp->pValue;
        }
        pTemp->pValue = mostLeftNode->pValue;
        mostLeftNode->pValue = nullptr;
        pTemp->key = mostLeftNode->key;
        delete mostLeftNode;
    }

    dataCount--;
}

// pTDataValue TTreeTable ::FindRecord(TKey k)
// {
//     pTTreeNode pNode = pRoot;
//     ppRef = &pRoot;
//     efficiency = 0;
//     while (pNode != nullptr)
//     {
//         efficiency++;
//         if (pNode->key == k)
//             break;
//         if (pNode->key < k)
//             ppRef = &pNode->pRight;
//         else
//             ppRef = &pNode->pLeft;
//         pNode = *ppRef;
//     }
//     return (pNode == nullptr) ? nullptr : pNode->pValue;
// }
// void TTreeTable::InsertRecord(TKey k, pTDataValue pVal)
// {
//     // if (IsFull())
//     //     SetRetCode(TabFull);
//     // else if (FindRecord(k) != nullptr)
//     //     SetRetCode(TabRecDbl);
//     // else
//     // {
//         *ppRef = new TTreeNode(k, pVal);
//         dataCount++;
//     //}
// }
// void TTreeTable ::DeleteRecord(TKey k)
// {
//     // if (IsEmpty())
//     //     SetRetCode(TabEmpty);
//     // else if (FindRecord(k) == nullptr)
//     //     SetRetCode(TabNoRec);
//     // else
//     // {
//         pTTreeNode pNode = *ppRef;
//         if (pNode->pRight == nullptr && pNode->pLeft == nullptr)
//             *ppRef = nullptr;
//         else if (pNode->pRight == nullptr)
//         {
//             pNode->key = pNode->pLeft->key;
//             pNode->pValue = pNode->pLeft->pValue;
//         }
//         else if (pNode->pLeft == nullptr)
//         {
//             pNode->key = pNode->pRight->key;
//             pNode->pValue = pNode->pRight->pValue;
//         }
//         else
//         {
//             pTTreeNode min = pNode->pLeft;
//             pTTreeNode minParent = pNode;
//             while (min->pRight != nullptr)
//             {
//                 minParent = min;
//                 min = min->pRight;
//             }
//             if (minParent != pNode)
//             {
//                 minParent->pRight = min->pLeft;
//                 pNode->key = min->key;
//                 pNode->pValue = min->pValue;
//                 pNode = min;
//             }
//             else
//             {
//                 pNode->key = min->key;
//                 pNode->pValue = min->pValue;
//                 pNode->pRight = min->pRight;
//                 pNode = min;
//             }
//             //delete min;
//             //delete minParent;
//         }
//         //delete pNode;
//         dataCount--;
//     //}
// }

TKey TTreeTable::GetKey(void) const
{
    return (pCurrent == nullptr) ? TKey("") : pCurrent->key;
}

pTDataValue TTreeTable::GetValuePTR(void) const
{
    return (pCurrent == nullptr) ? nullptr : pCurrent->pValue;
}

// After applying this method
// pCurrent leads to the most left tree node
int TTreeTable::Reset(void)
{
    while (!iterators.empty())
    {
        iterators.pop();
    }

    pTTreeNode currentNode = pCurrent = pRoot;
    while (currentNode != nullptr)
    {
        iterators.push(currentNode);
        pCurrent = currentNode;
        currentNode = currentNode->pLeft;
    }

    return currentPosition = 0;
}

bool TTreeTable::IsTableEnded(void) const
{
    return currentPosition == dataCount;
}

int TTreeTable::GoNext(void)
{
    if (!IsTableEnded() && (pCurrent != nullptr))
    {
        pTTreeNode currentNode = pCurrent = pCurrent->pRight;
        iterators.pop();
        while (currentNode != nullptr)
        {
            iterators.push(currentNode);
            pCurrent = currentNode;
            currentNode = currentNode->pLeft;
        }

        // There is no right subtree or tree has ended
        if (pCurrent == nullptr && !iterators.empty())
        {
            pCurrent = iterators.top();
        }
        return ++currentPosition;
    }

    return 1;
}
