#include "TTabRecord.h"

#ifndef TTABLE_INCLUDE_TTABLE_H
#define TTABLE_INCLUDE_TTABLE_H

class  TTable
{
protected:
    int dataCount;  // ���������� ������� � �������
    int efficiency; // ���������� ������������� ���������� ��������
public:
    TTable() { dataCount = 0; efficiency = 0; }
    virtual ~TTable() {};

    //-----------------------------�������������� ������-----------------------------
    int GetDataCount() const { return dataCount; }
    int GetEfficiency() const { return efficiency; }
    /*int*/bool IsEmpty() const { return dataCount == 0; }
    virtual /*int*/bool IsFull() const = 0;

    //-----------------------------������-----------------------------
    virtual TKey GetKey(void) const = 0;
    virtual pTDataValue GetValuePTR(void) const = 0;

    //-----------------------------�������� ������-----------------------------
    virtual pTDataValue FindRecord(TKey key) = 0;
    virtual void InsertRecord(TKey key, pTDataValue value) = 0;
    virtual void DeleteRecord(TKey key) = 0;

    //-----------------------------���������-----------------------------
    virtual void Reset(void) = 0;   // ���������� �� ������ ������
    virtual /*int*/bool IsTableEnded(void) const = 0;
    virtual void GoNext(void) = 0; // ������� � ��������� ������, (=1 ����� ���������� ��� ��������� ������ �������)
};
#endif // TTABLE_INCLUDE_TTABLE_H
