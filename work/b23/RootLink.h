#ifndef TROOT_LINK_INCLUDE_TROOT_LINK_H
#define TROOT_LINK_INCLUDE_TROOT_LINK_H

#include "DatValue.h"

class TRootLink;
typedef TRootLink *pTRootLink;

class TRootLink
{
 protected:
    pTRootLink pNext;

 public:
    explicit TRootLink(pTRootLink pNxt = nullptr) { pNext = pNxt; }

    pTRootLink GetNextLink() const { return pNext; }
    void SetNextLink(const pTRootLink pLink) { pNext = pLink; }

    void InsertNextLink(pTRootLink pLink)
    {
        pTRootLink p = pNext;
        pNext = pLink;
        if (pLink != nullptr)
        {
            pLink->pNext = p;
        }
    }

    virtual void SetDataValue(const pTDataValue pValue) = 0;
    virtual pTDataValue GetDataValue() const = 0;

    friend class TDataList;
};

#endif  // TROOT_LINK_INCLUDE_TROOT_LINK_H
