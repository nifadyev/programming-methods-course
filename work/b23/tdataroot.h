// ������������ ��������� ������ - ������� (�����������) ����� - ������ 3.2
// ������ ���������� ����������� ��� �������� ������� SetMem

#ifndef __DATAROOT_H__
#define __DATAROOT_H__

#include "tdatacom.h"

#define DefMemSize   25  // ������ ������ �� ���������
#define DataEmpty  -101  // �� �����
#define DataFull   -102  // �� �����������
#define DataNoMem  -103  // ��� ������

typedef int    TElem;    // ��� �������� ��
typedef TElem* PTElem;
typedef int    TData;    // ��� �������� � ��

enum TMemType { MEM_HOLDER, MEM_RENTER };

class TDataRoot : public TDataCom
{
protected:
	PTElem pMem;      // ������ ��� ��
	int MemSize;      // ������ ������ ��� ��
	int DataCount;    // ���������� ��������� � ��
	TMemType MemType; // ����� ���������� �������

	void SetMem(void *p, int Size)  // ������� ������
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

public:
	virtual ~TDataRoot();
	{
		if (MemType == MEM_HOLDER)
		{
			delete[] pMem;
		}
		pMem = nullptr;
	}

	TDataRoot(int Size = DefMemSize)
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
			pMem = new TElem[MemSize]{};
			MemType = MEM_HOLDER;
		}
	}
	virtual bool IsEmpty(void) const     // �������� ������� ��
	{
		return DataCount == 0;
	}

	virtual bool IsFull(void) const         // �������� ������������ ��
	{
		return DataCount == MemSize;
	}

	virtual void  Put(const TData &val) = 0; // �������� ��������
	virtual TData Get(void) = 0;             // ������� ��������

	// ��������� ������
	virtual int  IsValid() = 0; // ������������ ���������
	virtual void Print() = 0;   // ������ ��������
};
#endif