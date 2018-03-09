// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "DataList.h"

#ifndef HEADRING
#define HEADRING
class THeadRing : public TDataList
{
protected:
	pTDataLink pHead; // заголовок, pFirst - звено за pHead
public:
	THeadRing();
	~THeadRing();
	
	virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
	virtual void InsertAfterLast(pTDataValue pVal = nullptr);
	virtual void DeleteFirst();
};
#endif
