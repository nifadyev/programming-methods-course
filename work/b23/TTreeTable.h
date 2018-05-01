#include "TTable.h"
#include "TTreeNode.h"
#include <stack>

#ifndef TTREE_TABLE_INCLUDE_TTREE_TABLE_H
#define TTREE_TABLE_INCLUDE_TTREE_TABLE_H

class  TTreeTable : public TTable 
{
protected:
    pTTreeNode pRoot;             // ��������� �� ������ ������
    //TODO: Rename
    pTTreeNode *ppRef;            // ����� ��������� �� �������-���������� � FindRecord
    pTTreeNode pCurrent;          // ��������� �� ������� �������
    int currentPosition;          // ����� ������� �������
    stack <pTTreeNode> iterators; // ���� ��� ���������

    void DeleteTreeTable(pTTreeNode pNode); // ��������
public:
    TTreeTable() : TTable() { currentPosition = 0; pRoot = pCurrent = nullptr; ppRef = nullptr; }
    ~TTreeTable() { DeleteTreeTable(pRoot); }
    //-----------------------------�������������� ������-----------------------------
    virtual /*int*/bool IsFull() const;

    //-----------------------------�������� ������-----------------------------
    virtual pTTreeNode FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------���������-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;
    virtual /*int*/void Reset(void);   // ���������� �� ������ ������
    virtual /*int*/bool IsTableEnded(void) const;
    virtual /*int*/void GoNext(void); // ������� � ��������� ������, (=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // TTREE_TABLE_INCLUDE_TTREE_TABLE_H