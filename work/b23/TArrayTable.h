#include "TTable.h"

#ifndef TARRAY_TABLE_INCLUDE_TARRAY_TABLE_H
#define TARRAY_TABLE_INCLUDE_TARRAY_TABLE_H

#define TABLE_MAX_SIZE 25
enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

class  TArrayTable : public TTable {
protected:
    pTTabRecord *pRecords; // ������ ��� ������� �������
    int maxTableSize;      // ����. ����.���������� ������� � �������
    int currentPosition;   // ����� ������� ������ (��������� � 0)
public:
    TArrayTable(int size = TABLE_MAX_SIZE);
    ~TArrayTable();

    //-----------------------------�������������� ������-----------------------------
    virtual /*int*/bool IsFull() const;
    int GetTableSize() const;

    //-----------------------------������-----------------------------
    virtual TKey GetKey(void) const;
    virtual pTDataValue GetValuePTR(void) const;

    virtual TKey GetKey(TDataPos mode) const;
    virtual pTDataValue GetValuePTR(TDataPos mode) const;

    //-----------------------------�������� ������-----------------------------
    virtual pTDataValue FindRecord(TKey key) = 0;
    virtual void InsertRecord(TKey key, pTDataValue value) = 0;
    virtual void DeleteRecord(TKey key) = 0;

    //-----------------------------���������-----------------------------
    virtual /*int*/void Reset(void);   // ���������� �� ������ ������
    virtual /*int*/bool IsTableEnded(void) const;
    virtual /*int*/void GoNext(void); // ������� � ��������� ������, (=1 ����� ���������� ��� ��������� ������ �������)
    
    virtual /*int*/void SetCurrentPosition(int position);
    int GetCurrentPosition(void) const;
    friend class TSortTable;
};
#endif // TARRAY_TABLE_INCLUDE_TARRAY_TABLE_H
