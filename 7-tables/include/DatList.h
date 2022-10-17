#ifndef TDATA_LIST_INCLUDE_TDATA_LIST_H
#define TDATA_LIST_INCLUDE_TDATA_LIST_H

#include <iostream>
#include "DatLink.h"
using namespace std;

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
    pTDataLink pStop;  // Указатель на элемент, означающий конец списка
    int currentPosition;  // Итератор
    int listLength;

    pTDataLink GetLink(pTDataValue pVal = nullptr, pTDataLink pLink = nullptr);
    void DeleteLink(pTDataLink pLink);

 public:
    TDataList();
    ~TDataList();

    pTDataValue GetDataValue(TLinkPos mode = CURRENT) const;
    virtual bool IsEmpty() const;

    int GetListLength() const;

    void SetCurrentPosition(const int &position);
    int GetCurrentPosition() const;

    virtual int Reset();
    virtual bool IsListEnded() const;
    void GoNext();  // Cдвиг вправо текущего звена

    virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
    virtual void InsertAfterLast(pTDataValue pVal = nullptr);
    virtual void InsertBeforeCurrent(pTDataValue pVal = nullptr);

    virtual void DeleteFirst();
    virtual void DeleteCurrent();
    virtual void DeleteList();
};

typedef TDataList *pTDataList;

#endif  // TDATA_LIST_INCLUDE_TDATA_LIST_H
