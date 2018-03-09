// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "RootLink.h"

#ifndef TDATALINK
#define TDATALINK
class TDataLink;
typedef TDataLink *pTDataLink;

class TDataLink : public TRootLink
{
protected:
	pTDataValue pValue;
public:
	TDataLink(pTDataValue pVal = nullptr, pTRootLink pNxt = nullptr) : TRootLink(pNxt)
	{
		pValue = pVal;
	}

	void SetDataValue(const pTDataValue pVal) { pValue = pVal; }
	pTDataValue GetDataValue() const { return pValue; }

	pTDataLink GetNextDataLink() { return (pTDataLink)pNext; }

	friend class TDataList;
};
#endif
