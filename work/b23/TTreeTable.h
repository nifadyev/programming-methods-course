#ifndef TTREE_TABLE_INCLUDE_TTREE_TABLE_H
#define TTREE_TABLE_INCLUDE_TTREE_TABLE_H

#include "TTable.h"
#include "TTreeNode.h"
#include <stack>

class  TTreeTable : public TTable 
{
 protected:
    pTTreeNode pRoot;             // ��������� �� ������ ������
    //TODO: Rename
    pTTreeNode /* * */ppRef;            // ����� ��������� �� �������-���������� � FindRecord
    pTTreeNode pCurrent;          // ��������� �� ������� �������
    int currentPosition;          // ����� ������� �������
    stack <pTTreeNode> iterators; // ���� ��� ���������

    void DeleteTreeTable(pTTreeNode pNode); // ��������
 public:
    TTreeTable() : TTable(), currentPosition(0), pRoot(nullptr), pCurrent(nullptr), ppRef(nullptr) {}
    ~TTreeTable() { DeleteTreeTable(pRoot); }
    //-----------------------------�������������� ������-----------------------------
    virtual /*int*/bool IsFull() const;

    //-----------------------------�������� ������-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------���������-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;
    virtual void Reset(void);   // ���������� �� ������ ������
    virtual bool IsTableEnded(void) const;
    virtual void GoNext(void); // ������� � ��������� ������, (=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // TTREE_TABLE_INCLUDE_TTREE_TABLE_H