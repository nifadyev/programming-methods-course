# Отчет по лабораторной работе №2: Стек
__Выполнил:__ студент группы 381608-1 Нифадьев Вадим
## Цели и задачи
Выполнение работы предполагает решение следующих задач:
* Реализация методов класса TDataRoot согласно заданному интерфейсу.
* Разработка класса TStack, являющегося производным классом от TDataRoot.
* Разработка тестов для проверки работоспособности стеков.
* Реализация алгоритма проверки правильности введенного арифметического выражения.
* Реализация алгоритмов разбора и вычисления арифметического выражения.
* Обеспечение работоспособности тестов и примера использования.
* ## Описание работы
### Реализация класса `TDataRoot`
#### tdataroot.cpp
```C++
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

bool TDataRoot::IsEmpty() const // Проверка структуры данных на пустоту
{
	return DataCount == 0;
}

bool TDataRoot::IsFull() const // Проверка структуры данных на полноту
{
	return DataCount == MemSize;
}
```
### Реализация класса `TStack` и `Stack`
#### tstack.h
```C++
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
```
#### tstack.cpp
```C++
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <algorithm>
#include <vector>
#include "tstack.h"

using namespace std;

TStack::TStack(int size) : TDataRoot(size)
{
	if (size < 0)
	{
		throw invalid_argument("Size must be positive");
	}
	if (size != 0)
		SetRetCode(DataEmpty);

	top = -1;
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
	return GetRetCode() == DataOK ?  0 : GetRetCode();
}

void TStack::Print()
{
	for (int i = 0; i < DataCount; i++)
	{
		cout << pMem[i] << " ";
	}
	cout << endl;
}
```

### Реализация класса `TFormula`
#### tformula.cpp
```C++
#define _SCL_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include "tformula.h"
#include "tstack.h"

using namespace std;

TFormula::TFormula(char *form)
{
	int length = strlen(form);
	if (length == 0)
	{
		throw invalid_argument("String is empty");
	}
	if (length > 255)
	{
		throw invalid_argument("Size of expression is too big. Max size is 255");
	}

	strcpy_s(Formula, form);
	for (int i = 0; i < MaxLen; i++)
	{
		PostfixForm[i] = 0;
	}
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	if (size < 0)
	{
		throw invalid_argument("Size must be positive");
	}
	if (ForbiddenSymbolsChecker() > 0) // Формула содержит контрукции типа +-, .* или похожие
	{
		return ForbiddenSymbolsChecker();
	}

	TStack parentheses(size);
	int errors = 0;
	int resultTableIndex = 0; // Количество столбцов в resultTable
	int bracketNumber = 1; // Номер скобки в формуле
	int flag = 0; // Триггер для завершения цикла проверки в случае полноты/пустоты стека
	int **resultTable = new int*[2]; // Массив позиций открывающих и закрывающих скобок
	for (int i = 0; i < 2; i++)
	{
		resultTable[i] = new int[size] {};
	}
	
	//Цикл проверки сбобок в формуле
	for (int i = 0; i < size; i++)
	{
		if (flag == 1)
		{ 
			break;
		}

		switch (Brackets[i])
		{
		case (int)'(':
		{
			if (parentheses.IsFull())
			{
				errors++;
				flag = 1;
				break;
			}

			parentheses.Put(bracketNumber++);
			break;
		}

		case (int)')':
		{
			if (parentheses.IsEmpty())
			{
				resultTable[0][resultTableIndex] = 0; // Открывающие скобки
				resultTable[1][resultTableIndex] = bracketNumber++; // Закрывающие скобки
				errors++;
			}
			else
			{
				resultTable[0][resultTableIndex] = parentheses.Get();
				resultTable[1][resultTableIndex] = bracketNumber++;
			}

			resultTableIndex++;
			break;
		}
		}
	}

	// Если стек после провеки не пуст, то заполняем resultTable согласно правилам
	while(!parentheses.IsEmpty())
	{
		resultTable[0][resultTableIndex] = parentheses.Get();
		resultTable[1][resultTableIndex] = 0;
		errors++;
		resultTableIndex++;
	}

	// Печать resultTable
	//for (int i = 0; i < 2; i++) 
	//{
	//	for (int j = 0; j < resultTableIndex; j++)
	//		cout << resultTable[i][j] << " ";
	//	cout << endl;
	//}

	delete[] resultTable;

	return errors;
}

int TFormula::FormulaConverter()
{
	int formulaLength = strlen(Formula);
	int* intFormula = new int[formulaLength]; // Численное представление Formula
	for (int i = 0; i < formulaLength; i++)
	{
		intFormula[i] = (int)Formula[i];
	}

	if (FormulaChecker(intFormula, formulaLength) > 0)
	{
		return 1;
	}

	int flag = 0; // Триггер для перехода к следующей итерации цикла конвертации, если не встретилось операции
	int index = 0; // Индекс массива PostfixForm
	int operationPriority = -1;
	int previousOperationPriority = -2;
	TStack operations(formulaLength);
	
	// Цикл конвертации формулы в постфиксный вид
	for (int i = 0; i < formulaLength; i++)
	{
		flag = 0;

		switch (Formula[i]) // Расстановка приоритетов операций
		{
			case '(':
			{
				operationPriority = OpenBracket;
				break;
			}
			case ')':
			{
				operationPriority = CloseBracket;
				break;
			}
			case '+':
			{
				operationPriority = AddOrSubstract;
				break;
			}
			case '-':
			{
				operationPriority = AddOrSubstract;
				break;
			}
			case '*':
			{
				operationPriority = MultiplicateOrDivide;
				break;
			}
			case '/':
			{
				operationPriority = MultiplicateOrDivide;
				break;
			}
			default: // Если операции не нашлось, то помещаем цифру/точку в PostfixForm
			{
				operationPriority = -1;
				PostfixForm[index++] = Formula[i];
				flag = 1;
				break;
			}
			
		}

		if (flag == 1)
		{
			continue;
		}

		if (operationPriority == OpenBracket)
		{
			operations.Put((int)'(');
			previousOperationPriority = operationPriority;
			continue;
		}

		if (operationPriority > previousOperationPriority)
		{
			if (operationPriority == CloseBracket)
			{
				while (!operations.IsEmpty()) // Выталкивание оставшихся в стеке операции
				{
					int temp = operations.Get();
					if (temp != (int)'(') // Пока не встретится открывающая скобка
					{
						PostfixForm[index++] = (char)temp;					
					}
				}
			}

			else
			{
				PostfixForm[index++] = ' ';
				operations.Put((int)Formula[i]);
			}
		}

		if (operations.IsEmpty())
		{
			operations.Put((int)Formula[i]);
		}

		else if (operationPriority <= previousOperationPriority)
		{
			while(!operations.IsEmpty())
			{
				int temp = operations.Get();
				if (temp != (int)'(')
				{
					PostfixForm[index++] = (char)temp;
				}
			}
		}

		previousOperationPriority = operationPriority;
	}


	while (!operations.IsEmpty()) // Если после цикла остались операции в стеке
	{
		PostfixForm[index++] = (char)operations.Get();
	}

	return 0;
}

double TFormula::FormulaCalculator()
{
	const int defaultOperandLength = 16;
	int formulaLength = strlen(PostfixForm); 
	int index = 0; // Индекс charOperand1 и charOperand2
	int operandNumber = 1; // Номер операнда
	Stack<double> operands(formulaLength); // Стек для вещественных чисел
	char charOperand1[defaultOperandLength]; // Символьное представление первого операнда
	char charOperand2[defaultOperandLength]; // Символьное представление второго операнда	
	for (int i = 0; i < defaultOperandLength; i++) 
	{
		charOperand1[i] = 0;
		charOperand2[i] = 0;
 	}

	//Вычисление формулы постфиксного вида
	for (int i = 0; i < formulaLength; i++)
	{

		switch (PostfixForm[i])
		{
		case ' ':
		{
			// Если присутсвуют оба операнда
			if (strlen(charOperand1) > 0 && strlen(charOperand2) > 0) 
			{
				// Кладем первый операнд в стек
				operands.Put(atof(charOperand1));
				// Меняем операнды местами
				copy(charOperand2, charOperand2 + strlen(charOperand2), charOperand1); 
				// Обнуляем второй операнд
				for (unsigned int i = 0; i < strlen(charOperand2); i++) 
					charOperand2[i] = 0;
			}

			// Если есть первый операнд
			if (charOperand1 != "") 
			{
				operandNumber = 2;
			}

			// Оба операнда отсутствуют
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0) 
			{
				operandNumber = 1;
			}

			index = 0;
			break;
		}

		case '+':
		{
			// Если оба операнда отсутствуют
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0) 
			{
				operands.Put((operands.Get() + operands.Get())); 
			}

			// Иначе в стек помещается приведеннная к int сумма операндов
			else
			{
				operands.Put(atof(charOperand1) + atof(charOperand2));
			}
			
			ResetOperands(charOperand1, charOperand2); // Обнуление операндов
			operandNumber = 1;
			break;
		}

		case '-':
		{
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0)
			{
				double substractor = operands.Get(); // Вычитаемое
				operands.Put(operands.Get() - substractor);
			}

			else
			{
				operands.Put(atof(charOperand1) - atof(charOperand2));
			}

			ResetOperands(charOperand1, charOperand2);
			operandNumber = 1;
			break;
		}

		case '*':
		{
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0)
			{
				operands.Put(operands.Get() * operands.Get());
			}

			else
			{
				operands.Put(atof(charOperand1) * atof(charOperand2));
			}

			ResetOperands(charOperand1, charOperand2);
			operandNumber = 1;
			break;
		}

		case '/':
		{
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0)
			{
				double divider = operands.Get(); // Делитель
				operands.Put(operands.Get() / divider);
			}

			else
			{
				operands.Put(atof(charOperand1) / atof(charOperand2));
			}

			ResetOperands(charOperand1, charOperand2);
			operandNumber = 1;
			break;
		}

		// Не встретилось операций
		default:
		{
			if (operandNumber == 1)
			{
				charOperand1[index++] = PostfixForm[i];
			}

			else
			{
				charOperand2[index++] = PostfixForm[i];
			}

			break;
		}
		}
	}

	return operands.Get();
}

void TFormula::Print()
{
	cout << "Infix formula: " << Formula << endl;
	cout << "Postfix formula: " << PostfixForm << endl;
}

void TFormula::ResetOperands(char * operand1, char * operand2) // Обнуление операндов
{
	for (unsigned int i = 0; i < strlen(operand1); i++)
	{
		operand1[i] = 0;
	}
	for (unsigned int i = 0; i < strlen(operand2); i++)
	{
		operand2[i] = 0;
	}
}


int TFormula::ForbiddenSymbolsChecker() // Проверка на посторонние символы и недопустимую последовательность операций
{
	int errors = 0;

	for (unsigned int i = 0; i < strlen(Formula); i++)
	{
		char symbol = Formula[i];
		char nextSymbol = Formula[i + 1];

		// Проверка на посторонние символы
		if ((symbol < '0' || symbol > '9') && symbol != '.' &&
			symbol != '(' && symbol != ')' &&
			symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/')
		{
			errors++;
		}

		// Проверка на недопустимую последовательность операций
		if ((symbol == nextSymbol) && (symbol == '.' || symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'))
		{
			errors++;
		}
	}

	return errors;
}
```
## Тестирование
### Тестирование класса `TStack`
![](https://bytebucket.org/Neaph/lab-3/raw/0b4d3eced3873be7d44788d023b9d9d68e5f75a0/work/b23/TStackTest.png)
### Тестирование класса `Stack`
![](https://bytebucket.org/Neaph/lab-3/raw/0b4d3eced3873be7d44788d023b9d9d68e5f75a0/work/b23/TemplateStackTest.png)
### Тестирование класса `TFormula`
![](https://bytebucket.org/Neaph/lab-3/raw/0b4d3eced3873be7d44788d023b9d9d68e5f75a0/work/b23/FormulaTest.png)
## Вывод
В данной работе были разработаны классы стек с кодами завешения, шаблонный стек, и на их основе был создан класс, преобразующий формулу в инфиксной форме записи, к постфиксной форме. Вычисление приведенной к постфикному виду формулы также представлено в классе.