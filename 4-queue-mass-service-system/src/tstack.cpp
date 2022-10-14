#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <vector>
#include "tstack.h"

using namespace std;

TStack::TStack(int size) : TDataRoot(size), top(-1)
{
	if (size < 0)
	{
		throw invalid_argument("Size must be positive");
	}

	if (size == 0)
		SetRetCode(DataEmpty);
}

bool TStack::IsEmpty(void) const
{
	return DataCount == 0;
}

bool TStack::IsFull(void) const
{
	return DataCount == MemSize;
}

void TStack::Put(const TData& val)
{
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
		throw logic_error("Cannot put the element. Memory wasn't allocated");
	}
	if (IsFull())
	{
		SetRetCode(DataFull);
		throw logic_error("Cannot put the element. Stack is full");
	}

	pMem[++top] = val;
	DataCount++;

	if (IsFull())
	{
		SetRetCode(DataFull);
	}
}

TData TStack::Get(void) // Взятие из стека с удалением
{
	if (IsEmpty())
	{
		SetRetCode(DataEmpty);
		throw logic_error("Cannot get the access to stack. Stack is empty");
	}
	if (pMem == nullptr)
	{
		SetRetCode(DataNoMem);
		throw logic_error("Cannot get the element. Stack is full");
	}

	TData last = pMem[top--];
	PTElem temp = new TElem[MemSize--]{};
	copy(pMem, pMem + MemSize, temp);
	SetMem(temp, MemSize);
	DataCount--;

	if (IsEmpty())
	{
		SetRetCode(DataEmpty);
	}

	return last;
}

int TStack::IsValid()
{
	return GetRetCode() == DataOK ? 0 : GetRetCode();
}

void TStack::Print()
{
	for (int i = 0; i < DataCount; i++)
	{
		cout << pMem[i] << " ";
	}
	cout << endl;
}