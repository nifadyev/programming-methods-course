#ifndef DATA_LINK_INCLUDE_DATA_LINK_H
#define DATA_LINK_INCLUDE_DATA_LINK_H

#include "RootLink.h"

class TDataLink;
typedef TDataLink *pTDataLink;

class TDataLink : public TRootLink
{
 protected:
    pTDataValue pValue;

 public:
    explicit TDataLink(pTDataValue pVal = nullptr, pTRootLink pNxt = nullptr) : TRootLink(pNxt)
    {
        pValue = pVal;
    }

    void SetDataValue(const pTDataValue pVal)
    {
        pValue = pVal;
    }
    pTDataValue GetDataValue() const 
    { 
        return pValue;
        }

    pTDataLink GetNextDataLink() 
    { 
        return (pTDataLink)pNext;
    }

    friend class TDataList;
};

#endif // DATA_LINK_INCLUDE_DATA_LINK_H
