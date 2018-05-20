#include <iostream>
#include "DatLink.h"
using namespace std;

#ifndef TDATA_LIST_INCLUDE_TDATA_LIST_H
#define TDATA_LIST_INCLUDE_TDATA_LIST_H
// class TDataList;
// typedef TDataList *pTDataList;
enum TLinkPos
{
    FIRST,
    CURRENT,
    LAST
};

class TDataList
{
  protected:
    pTDataLink pFirst;
    pTDataLink pLast;
    pTDataLink pCurrentLink;
    pTDataLink pPreviousLink;
    pTDataLink pStop; // ��������� �� �������, ���������� ����� ������

    int currentPosition; // ��������
    int listLength;

    pTDataLink GetLink(pTDataValue pVal = nullptr, pTDataLink pLink = nullptr);
    void DeleteLink(pTDataLink pLink);

    void InsertIntoEmptyList(pTDataValue pVal);

  public:
    TDataList();
    ~TDataList() { DeleteList(); }

    pTDataValue GetDataValue(TLinkPos mode = CURRENT) const;
    virtual bool IsEmpty() const { return pFirst == pStop; }

    int GetListLength() const { return listLength; }

    void SetCurrentPosition(const int &position);
    int GetCurrentPosition() const;

    virtual int Reset();
    virtual bool IsListEnded() const;
    void GoNext(); // ����� ������ �������� �����

    virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
    virtual void InsertAfterLast(pTDataValue pVal = nullptr);
    virtual void InsertBeforeCurrent(pTDataValue pVal = nullptr);

    virtual void DeleteFirst();
    virtual void DeleteCurrent();
    virtual void DeleteList();
};

typedef TDataList *pTDataList;
#endif // TDATA_LIST_INCLUDE_TDATA_LIST_H
