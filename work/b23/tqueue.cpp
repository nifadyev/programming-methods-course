#define _SCL_SECURE_NO_WARNINGS

#include "tqueue.h"
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

TQueue::TQueue(int size) : TStack(size), bottom(0)
{
	SetRetCode(DataOK);
}

TQueue::TQueue(const TQueue & queue)
{
	MemSize = queue.MemSize;
	bottom = queue.bottom;
	top = queue.top;
	DataCount = queue.DataCount;
	SetRetCode(queue.RetCode);
	pMem = new TElem[MemSize]{};
	copy(queue.pMem, queue.pMem + MemSize, pMem);
}

TQueue& TQueue::operator=(const TQueue & queue)
{
	if (pMem != queue.pMem)
	{
		MemSize = queue.MemSize;
		DataCount = queue.DataCount;
		top = queue.top;
		bottom = queue.bottom;
		RetCode = queue.RetCode;
		delete[] pMem;
		pMem = new TElem[MemSize];
		copy(queue.pMem, queue.pMem + MemSize, pMem);
	}
	return *this;
}

void TQueue::Put(const int& value)
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

	if (top == MemSize - 1)
	{
		top = -1;

	}
	if (DataCount > 0)
	{
		SetRetCode(DataOK);
	}

	pMem[++top] = value;
	DataCount++;

	if (IsFull())
	{
		SetRetCode(DataFull);
	}
}

int TQueue::Get(void)
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

	if (bottom == MemSize)
	{
		bottom = 0;
	}

	int first = pMem[bottom];
	pMem[bottom++] = 0;
	DataCount--;

	if (IsEmpty())
	{
		SetRetCode(DataEmpty);
	}

	return first;
}

void TQueue::Print()
{
	for (int i = 0; i < MemSize; i++)
	{
		cout << pMem[i] << " ";
	}
	cout << endl;
}