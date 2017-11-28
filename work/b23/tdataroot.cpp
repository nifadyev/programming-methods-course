#include "tdataroot.h"

TDataRoot::TDataRoot(int Size)
{
	MemSize = Size;
	DataCount = 0;
	SetRetCode(DataOK);
	if (MemSize == 0)
	{
		pMem = nullptr;
		SetRetCode(DataNoMem);
		MemType = MEM_RENTER;
	}
	else
	{
		pMem = new TElem[MemSize] {};
		MemType = MEM_HOLDER;
	}
}

TDataRoot::~TDataRoot()
{
	if (MemType == MEM_HOLDER)
	{
		delete[] pMem;
	}
	pMem = nullptr;
}

void TDataRoot::SetMem(void *p, int Size)
{
	if (MemType == MEM_HOLDER)
	{
		delete[] pMem;	
	}

	pMem = (TElem*)p;
	MemSize = Size;
	MemType = MEM_RENTER;
	SetRetCode(DataOK);

	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
	}
}

bool TDataRoot::IsEmpty() const // ѕроверка структуры данных на пустоту
{
	return DataCount == 0;
}

bool TDataRoot::IsFull() const // ѕроверка структуры данных на полноту
{
	return DataCount == MemSize;
}