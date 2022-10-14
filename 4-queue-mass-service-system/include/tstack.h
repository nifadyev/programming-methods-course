#ifndef TSTACK_H
#define TSTACK_H

#include <iostream>
#include "tdataroot.h"

#define MemorySize 25
#define StackSize 10
using namespace std;

class TStack : public TDataRoot
{
protected:
	int top; // Индекс последнего элемента в стеке

public:
	explicit TStack(int size = StackSize);
	~TStack() {};

	bool IsEmpty(void) const;
	bool IsFull(void) const;
	void  Put(const TData &val);
	TData Get(void);

	int  IsValid();
	void Print();

	int GetDataCount() const { return DataCount; }
	int GetTop() const { return top; }
};
#endif