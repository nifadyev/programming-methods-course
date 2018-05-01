#include "THashTable.h"
#include "DatList.h"

#ifndef TLIST_HASH_INCLUDE_TLIST_HASH_H
#define TLIST_HASH_INCLUDE_TLIST_HASH_H

#define TABLE_MAX_SIZE 25
class  TListHash : public THashTable 
{
protected:
    pTDataList *pList; // ������ ��� ������� ���������� �� ������ ������� 
    int tableSize;        // ������ ������� ����������
    int currentList;       // ������, � ������� ���������� �����
public:
    TListHash(int Size = TABLE_MAX_SIZE);
    ~TListHash();
    //-----------------------------�������������� ������-----------------------------
    virtual /*int*/bool IsFull() const;

    //-----------------------------������-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;

    //-----------------------------�������� ������-----------------------------
    virtual pTDataValue FindRecord(TKey key);
    virtual void InsertRecord(TKey key, pTDataValue value);
    virtual void DeleteRecord(TKey key);

    //-----------------------------���������-----------------------------
    virtual /*int*/void Reset(void);   // ���������� �� ������ ������
    virtual /*int*/bool IsTableEnded(void) const;
    virtual /*int*/void GoNext(void); // ������� � ��������� ������, (=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // TLIST_HASH_INCLUDE_TLIST_HASH_H