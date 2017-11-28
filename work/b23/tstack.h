#include "tdataroot.h"

#define MemorySize 25
#define StackSize 10

class TStack : public TDataRoot
{
private:
	int top; // Индекс последнего элемента в стеке

public:
	TStack(int size = StackSize);
	~TStack() {};

	bool IsEmpty(void) const;
	bool IsFull(void) const;
	void  Put(const TData &Val);
	TData Get(void);

	int  IsValid();
	void Print();

	int GetDataCount() { return DataCount; }
	int GetTop() { return top; };
};


template<class T>
class Stack
{
private:
	T* pMemory; // Память
	int elementsCounter; // Количество элементов в стеке
	int MemoryLength; // Длина стека
	int top; // Индекс последнего элемента в стеке
public:
	Stack(int size)
	{
		if (size < 0)
		{
			throw invalid_argument("Size must be positive");
		}

		top = -1;
		MemoryLength = size;
		elementsCounter = 0;
		if (MemoryLength == 0)
		{
			pMemory = nullptr;
		}
		else
		{
			pMemory = new T[MemoryLength]{};
		}
	}

	~Stack() { delete[] pMemory; }

	bool IsEmpty(void) const
	{
		return elementsCounter == 0;
	}


	bool IsFull(void) const
	{
		return elementsCounter == MemoryLength;
	}

	void Put(const T & value)
	{
		if (pMemory == nullptr)
		{
			throw logic_error("Cannot put the element. Memory wasn't allocated");
		}
		if (IsFull())
		{
			throw logic_error("Cannot put the element. Stack is full");
		}

		pMemory[++top] = value;
		elementsCounter++;
	}

	T Get(void)
	{
		if (IsEmpty())
		{
			throw logic_error("Cannot get the access to stack. Stack is empty");
		}
		if (pMemory == nullptr)
		{
			throw logic_error("Cannot get the element. Stack is full");
		}

		T last = pMemory[top--];
		elementsCounter--;
		T* temp = new T[MemoryLength--]{};
		copy(pMemory, pMemory + MemoryLength, temp);
		delete[] pMemory;
		pMemory = temp;
		
		return last;
	}

	void Print()
	{
		for (int i = 0; i < elementsCounter; i++)
		{
			cout << pMemory[i] << " ";
		}
		cout << endl;
	}

	int GetDataCount() { return elementsCounter; }

	int GetTop() { return top; };
};