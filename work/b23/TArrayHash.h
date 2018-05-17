#include "THashTable.h"

#ifndef TARRAY_HASH_INCLUDE_TARRAY_HASH_H
#define TARRAY_HASH_INCLUDE_TARRAY_HASH_H

#define TABLE_MAX_SIZE 25
#define TABLE_HASH_STEP 5

class  TArrayHash : public THashTable 
{
protected:
    pTTabRecord *pRecords; // ������ ��� ������� �������
    pTTabRecord pMark;      // ������ ��� ��������� ����� � ���������� ��������
    int maxTableSize;       // ����. ��������� ����� �������
    int hashStep;           // ��� ���������� �������������
    int freePosition;       // ������ ��������� ������, ������������ ��� ������
    int currentPosition;    // ������ ������ ��� ���������� ������

    int GetNextPosition(int position) { return (position + hashStep) % maxTableSize; };
public:
    TArrayHash(int size = TABLE_MAX_SIZE, int step = TABLE_HASH_STEP);
    ~TArrayHash();

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
    virtual int Reset(void);   // ���������� �� ������ ������
    virtual /*int*/bool IsTableEnded(void) const;
    virtual int GoNext(void); // ������� � ��������� ������, (=1 ����� ���������� ��� ��������� ������ �������)
};

#endif // TARRAY_HASH_INCLUDE_TARRAY_HASH_H