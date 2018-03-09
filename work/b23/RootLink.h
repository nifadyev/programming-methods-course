#include "DataValue.h"

#ifndef TROOTLINK
#define TROOTLINK
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
#endif