# Отчет по лабораторной работе №4: Очередь
__Выполнил:__ студент группы 381608-1 Нифадьев Вадим
## Цели и задачи
Для вычислительной системы (ВС) с одним процессором и однопрограммным 
последовательным режимом выполнения поступающих заданий требуется 
разработать программную систему для имитации процесса обслуживания 
заданий в ВС. При построении модели функционирования ВС должны 
учитываться следующие основные моменты обслуживания заданий:

* генерация нового задания;
* постановка задания в очередь для ожидания момента освобождения 
процессора;
* выборка задания из очереди при освобождении процессора после 
обслуживания очередного задания.

По результатам проводимых вычислительных экспериментов система имитации 
должна выводить информацию об условиях проведения эксперимента 
(интенсивность потока заданий, размер очереди заданий, производительность 
процессора, число тактов имитации) и полученные в результате имитации 
показатели функционирования вычислительной системы, в т.ч.

* количество поступивших в ВС заданий;
* количество отказов в обслуживании заданий из-за переполнения очереди;
* среднее количество тактов выполнения заданий;
* количество тактов простоя процессора из-за отсутствия в очереди заданий 
для обслуживания.

Показатели функционирования вычислительной системы, получаемые при помощи 
систем имитации, могут использоваться для оценки эффективности применения
ВС; по результатам анализа показателей могут быть приняты рекомендации о 
целесообразной модернизации характеристик ВС (например, при длительных 
простоях процессора и при отсутствии отказов от обслуживания заданий 
желательно повышение интенсивности потока обслуживаемых заданий и т.д.).

## Описание работы
### Реализация класса `TQueue`
#### tqueue.h
```C++
#ifndef TQUEUE_H
#define TQUEUE_H

#include "tstack.h"
#define MAX_QUEUE_SIZE 100

class TQueue : public TStack
{
private:
	int bottom; // Начало очереди
public:
	explicit TQueue(int size = MAX_QUEUE_SIZE); // explicit запрещает вызов конструктора в следующем виде- TQueue q = 5
	TQueue(const TQueue& queue);
	TQueue& operator=(const TQueue& queue);
	~TQueue() {};

	void  Put(const int& value);
	int Get(void);

	int GetBottom() const { return bottom; }
	int GetMemorySize() const { return MemSize; }

	void Print();
};
#endif
```


#### tqueue.cpp
```C++
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
```

### Реализация класса `TJobStream`
#### tjobstream.h
```C++
#ifndef TJOBSTREAM_H
#define TJOBSTREAM_H

#include "tqueue.h"

const float DEFAULT_INTENSITY = 0.5f; // Стандартная интенсивность потока

class TJobStream : public TQueue
{
private:
	float intensity;  // Интенсивность потока 
	int streamLength;
public:
	TJobStream(int size = DefMemSize, float intensity = DEFAULT_INTENSITY);
	~TJobStream() {};

	float GetIntensity() const { return intensity; }
	int GetStreamLength() const { return streamLength; }
};
#endif
```

#### tjobstream.cpp
```C++
#include "tjobstream.h"

TJobStream::TJobStream(int size, float intensity) : TQueue(size)
{
	if (intensity < 0.0f || intensity > 1.0f)
	{
		throw invalid_argument("Intensity of stream must be more than 0 and less than 1");
	}

	this->streamLength = size;
	this->intensity = intensity;
}
```

### Реализация класса `TProc`
#### tproc.h
```C++
#ifndef TPROC_H
#define TPROC_H

const float DEFAULT_PRODUCTIVITY = 0.5f; // Стандартная производительность процессора

class TProc
{
private:
	float productivity; // Производительность процессора
	int clocks;         // Количество тактов имитации
public:
	TProc(int clocks = 1000, float productivity = DEFAULT_PRODUCTIVITY); 
	~TProc() {};

	bool TaskIsReady(float factor);

	float GetProductivity() const { return productivity; }
	int GetClocks() const { return clocks; }
};
#endif
```

#### tproc.cpp
```C++
#include <iostream>
#include "tproc.h"

using namespace std;

TProc::TProc(int clocks, float productivity)
{
	if (clocks < 0)
	{
		throw invalid_argument("Amount of clocks must be positive");
	}
	if (productivity < 0.0f || productivity > 1.0f)
	{
		throw invalid_argument("Productivity must be more than 0 and less than 1");
	}

	this->clocks = clocks;
	this->productivity = productivity;
}

bool TProc::TaskIsReady(float factor)
{
	return factor < productivity;
}
```

## Тестирование
#### QueueTestkit.cpp
```C++
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#include <gtest\gtest.h>
#include "tjobstream.h"
#include "tproc.h"

//Тестирование класса TQueue

TEST(TQueue, CanCreateQueue)
{
	ASSERT_NO_THROW(TQueue queue(3));
}

TEST(TQueue, ThrowWhenCreateQueueWithNegativeSize)
{
	ASSERT_ANY_THROW(TQueue queue(-9));
}

TEST(TQueue, ResetBottomWhenCreateQueue)
{
	TQueue queue(8);

	EXPECT_EQ(queue.GetBottom(), 0);
}

TEST(TQueue, ResetTopWhenCreateQueue)
{
	TQueue queue(8);

	EXPECT_EQ(queue.GetTop(), -1);
}

TEST(TQueue, CanCopyQueue)
{
	TQueue sourceQueue(3);

	ASSERT_NO_THROW(TQueue copyQueue(sourceQueue));
}

TEST(TQueue, SizeOfCopiedQueueIsEqualToSourceQueue)
{
	TQueue sourceQueue(3);
	TQueue copyQueue(sourceQueue);

	EXPECT_EQ(sourceQueue.GetMemorySize(), copyQueue.GetMemorySize());
}

TEST(TQueue, OperatorEqual)
{
	TQueue queue(8);

	queue.Put(54354);
	queue.Get();
	queue.Put(-44);
	queue.Put(3);
	queue.Put(-774);

	queue.Print();

	TQueue copy(2);
	copy = queue;

	EXPECT_EQ(queue.GetTop(), 3);
	EXPECT_EQ(queue.GetBottom(), 1);
	EXPECT_EQ(queue.GetDataCount(), 3);
	EXPECT_EQ(queue.GetMemorySize(), 8);
	EXPECT_EQ(queue.GetRetCode(), DataOK);
}

TEST(TQueue, CanPutIntoQueue)
{
	TQueue queue(4);

	ASSERT_NO_THROW(queue.Put(3));
}

TEST(TQueue, PutValueIsEqualToSource)
{
	TQueue queue(15);
	queue.Put(4656);

	EXPECT_EQ(queue.Get(), 4656);
}


TEST(TQueue, CanAssignValuesWhenPutIntoStack)
{
	TQueue queue(4);

	queue.Put(12);

	EXPECT_EQ(queue.GetTop(), 0);
	EXPECT_EQ(queue.GetBottom(), 0);
	EXPECT_EQ(queue.GetDataCount(), 1);
	EXPECT_EQ(queue.GetMemorySize(), 4);
	EXPECT_EQ(queue.GetRetCode(), DataOK);
}

TEST(TQueue, ThrowWhenPutIntoQueueWithoutMemory)
{
	TQueue queue(0);

	ASSERT_ANY_THROW(queue.Put(-21));
}

TEST(TQueue, ThrowWhenPutIntoFullQueue)
{
	TQueue queue(3);
	queue.Put(54354);
	queue.Get();
	queue.Put(-44);
	queue.Put(3);
	queue.Put(-774);

	ASSERT_ANY_THROW(queue.Put(139009));
}


TEST(TQueue, CanGetFromQueue)
{
	TQueue queue(2);
	queue.Put(2412);
	queue.Put(-57);

	ASSERT_NO_THROW(queue.Get());
}
TEST(TQueue, RetrievedValueIsEqualToSource)
{
	TQueue queue(2);
	queue.Put(-932);
	queue.Put(45);

	EXPECT_EQ(queue.Get(), -932);
}

TEST(TQueue, ThrowWhenGetFromEmptyQueue)
{
	TQueue queue(49);

	ASSERT_ANY_THROW(queue.Get());
}

TEST(TQueue, ThrowWhenGetFromQueueWithoutMemory)
{
	TQueue queue(0);

	ASSERT_ANY_THROW(queue.Get());
}

TEST(TQueue, ChangeTopWhenItReachesEdge)
{
	TQueue queue(5);

	queue.Put(2412);
	queue.Put(-57);
	queue.Put(-54347);
	queue.Put(144637);
	queue.Put(55);
	queue.Get();
	queue.Get();
	queue.Put(5465);
	queue.Put(-25);

	EXPECT_EQ(queue.GetDataCount(), 5);
}

TEST(TQueue, ChangeBottomWhenItReachesEdge)
{
	TQueue queue(4);

	queue.Put(2412);
	queue.Put(-57);
	queue.Put(-54347);
	queue.Put(144637);
	queue.Get();
	queue.Get();
	queue.Put(5465);
	queue.Get();
	queue.Get();

	EXPECT_EQ(queue.GetDataCount(), 1);
}

TEST(TQueue, CanCleanAndFillQueue)
{
	TQueue queue(5);

	queue.Put(2412);
	queue.Put(-57);
	queue.Put(-54347);
	queue.Put(144637);
	queue.Put(55);
	queue.Get();
	queue.Get();
	queue.Put(5465);

	queue.Get();
	queue.Get();
	queue.Get();
	queue.Get();

	queue.Put(214235);
	queue.Put(12);
	queue.Put(7);
	queue.Put(59074);
	queue.Put(-2148);

	EXPECT_EQ(queue.GetDataCount(), 5);
}

TEST(TQueue, CanCleanQueue)
{
	TQueue queue(5);

	queue.Put(2412);
	queue.Put(-57);
	queue.Put(-54347);
	queue.Put(144637);
	queue.Put(55);
	queue.Get();
	queue.Get();
	queue.Put(5465);

	while (queue.GetDataCount() > 0)
	{
		queue.Get();
	}

	EXPECT_EQ(queue.GetDataCount(), 0);
}

TEST(TQueue, ThrowWhenPutIntoFullQueueCircleBuffer)
{
	TQueue queue(3);

	queue.Put(2412);
	queue.Put(-57);
	queue.Put(-54347);
	queue.Get();
	queue.Get();
	queue.Put(5465);
	queue.Put(-25);

	ASSERT_ANY_THROW(queue.Put(-2148));
}

// Тестирование класса TJobStream

TEST(TJobStream, CanCreateJobStream)
{
	ASSERT_NO_THROW(TJobStream jobStream(10, 0.7f));
}

TEST(TJobStream, ThrowWhenCreateJobStreamWithNegativeSize)
{
	ASSERT_ANY_THROW(TJobStream jobStream(-13, 0.7f));
}

TEST(TJobStream, ThrowWhenCreateJobStreamWithWrongIntensity)
{
	ASSERT_ANY_THROW(TJobStream jobStream(5, 1.98f));
	ASSERT_ANY_THROW(TJobStream jobStream(5, -121.0f));
}

TEST(TJobStream, CanGetIntensity)
{
	TJobStream jobStream(12, 0.4f);

	ASSERT_NO_THROW(jobStream.GetIntensity());
	EXPECT_EQ(jobStream.GetIntensity(), 0.4f);
}

TEST(TJobStream, CanGetStreamLength)
{
	TJobStream jobStream(30, 0.2f);

	ASSERT_NO_THROW(jobStream.GetStreamLength());
	EXPECT_EQ(jobStream.GetStreamLength(), 30);
}

// Тестирование класса TProc

TEST(TProc, CanCreateProc)
{
	ASSERT_NO_THROW(TProc proccessor(1000, 0.5f));
}

TEST(TProc, ThrowWhenCreateProcWithNegativeClocks)
{
	ASSERT_ANY_THROW(TProc proccessor(-1, 0.4354f));
}

TEST(TProc, ThrowWhenCreateProcWithWrongProductivity)
{
	ASSERT_ANY_THROW(TProc proccessor(400, 4.3f));
	ASSERT_ANY_THROW(TProc proccessor(400, -0.12f));
}

TEST(TProc, TaskIsReadyReturnTrue)
{
	TProc proccessor(1000, 0.5f);

	EXPECT_TRUE(proccessor.TaskIsReady(0.2f));
}

TEST(TProc, TaskIsReadyReturnFalse)
{
	TProc proccessor(1000, 0.5f);

	EXPECT_FALSE(proccessor.TaskIsReady(0.8f));
}

TEST(TProc, CanGetProductivity)
{
	TProc proccessor(1000, 0.5f);

	ASSERT_NO_THROW(proccessor.GetProductivity());
	EXPECT_EQ(proccessor.GetProductivity(), 0.5f);
}

TEST(TProc, CanGetClocks)
{
	TProc proccessor(1000, 0.5f);

	ASSERT_NO_THROW(proccessor.GetClocks());
	EXPECT_EQ(proccessor.GetClocks(), 1000);
}

```

#### Сравнительная таблица зависимости от интенсивности потока заданий
![](https://bytebucket.org/Neaph/lab4-queue/raw/763e2d91282e57009943c46049e460673767fb06/work/b23/IntensityTable.png)
#### Сравнительная таблица зависимости от производительности процессора
![](https://bytebucket.org/Neaph/lab4-queue/raw/763e2d91282e57009943c46049e460673767fb06/work/b23/ProductivityTable.png)
#### Сравнительная таблица зависимости от размера потока заданий
![](https://bytebucket.org/Neaph/lab4-queue/raw/763e2d91282e57009943c46049e460673767fb06/work/b23/StreamSizeTable.png)
#### Результат работы программы
![](https://bytebucket.org/Neaph/lab4-queue/raw/763e2d91282e57009943c46049e460673767fb06/work/b23/main.png)

## Вывод
В данной работе были изучены различные варианты структуры хранения 
очереди, разрабатаны методы и программы решения задач с использованием 
очередей, была построена схема имитации массового обслуживания.