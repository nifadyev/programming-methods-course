#include "DatList.h"

#ifndef HEADRING
#define HEADRING
class THeadRing : public TDataList
{
protected:
	pTDataLink pHead; // ���������, pFirst - ����� �� pHead
public:
	THeadRing();
	~THeadRing();

	virtual void InsertBeforeFirst(pTDataValue pVal = nullptr);
	virtual void InsertAfterLast(pTDataValue pVal = nullptr);
	virtual void DeleteFirst();
};
#endif
