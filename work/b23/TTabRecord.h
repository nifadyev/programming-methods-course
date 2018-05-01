#include <iostream>
#include "TDatValue.h"
using namespace std;

#ifndef TTAB_RECORD_INCLUDE_TTAB_RECORD_H
#define TTAB_RECORD_INCLUDE_TTAB_RECORD_H

typedef string TKey;    // ��� ����� ������
typedef TTabRecord *pTTabRecord;

//----------------����� ��������-�������� ��� ������� �������----------------   
class TTabRecord : public TDataValue
{
protected:
    TKey key;             // ���� ������
    pTDataValue pValue;   // ��������� �� ��������
public:
    TTabRecord(TKey key = "", pTDataValue value = nullptr);

    void SetKey(TKey key);
    TKey GetKey(void);

    void SetValuePtr(pTDataValue ptr); // ���������� ��������� �� ������
    pTDataValue GetValuePTR(void);     // �������� ��������� �� ������

    virtual TDataValue* GetCopy();

    TTabRecord & operator = (TTabRecord &record);
    virtual int operator == (const TTabRecord &record);
    virtual int operator < (const TTabRecord &record);
    virtual int operator > (const TTabRecord &record);

    //----------------������������� ������ ��� ��������� ����� ������----------------
    friend class TArrayTable;
    friend class TScanTable;
    friend class TSortTable;
    friend class TTreeNode;
    friend class TTreeTable;
    friend class TArrayHash;
    friend class TListHash;
};

#endif // TTAB_RECORD_INCLUDE_TTAB_RECORD_H
