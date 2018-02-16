// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
	TRootLink(pTRootLink pNxt = nullptr /*NULL*/) { pNext = pNxt; }
	
	pTRootLink GetNextLink() const { return pNext; }
	void SetNextLink(const pTRootLink pLink) { pNext = pLink; }

	void InsertNextLink(pTRootLink pLink)
	{
		pTRootLink p = pNext;
		pNext = pLink;
		if (pLink != nullptr /*NULL*/)
		{
			pLink->pNext = p;
		}
	}

	virtual void SetDataValue(const pTDataValue pValue) = 0;
	virtual pTDataValue GetDataValue() const = 0;

	friend class TDataList;
};
#endif