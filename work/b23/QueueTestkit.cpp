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
