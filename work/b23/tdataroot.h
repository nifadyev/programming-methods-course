// Динамические структуры данных - базовый (абстрактный) класс - версия 3.2
// Память выделяется динамически или задается методом SetMem

#ifndef __DATAROOT_H__
#define __DATAROOT_H__

#include "tdatacom.h"

#define DefMemSize   25  // Размер памяти по умолчанию
#define DataEmpty  -101  // СД пуста
#define DataFull   -102  // СД переполнена
#define DataNoMem  -103  // Нет памяти

typedef int    TElem;    // Тип элемента СД
typedef TElem* PTElem;
typedef int    TData;    // Тип значений в СД

enum TMemType { MEM_HOLDER, MEM_RENTER };

class TDataRoot : public TDataCom
{
protected:
	PTElem pMem;      // Память для СД
	int MemSize;      // Размер памяти для СД
	int DataCount;    // Количество элементов в СД
	TMemType MemType; // Режим управления памятью

	void SetMem(void *p, int Size)  // Задание памяти
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
	virtual bool IsEmpty(void) const     // Контроль пустоты СД
	{
		return DataCount == 0;
	}

	virtual bool IsFull(void) const         // Контроль переполнения СД
	{
		return DataCount == MemSize;
	}

	virtual void  Put(const TData &val) = 0; // Добавить значение
	virtual TData Get(void) = 0;             // Извлечь значение

	// Служебные методы
	virtual int  IsValid() = 0; // Тестирование структуры
	virtual void Print() = 0;   // Печать значений
};
#endif