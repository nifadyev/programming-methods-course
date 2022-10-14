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