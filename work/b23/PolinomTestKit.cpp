// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <gtest/gtest.h>
#include "RootLink.h"
#include "DataLink.h"
#include "Monom.h"

#include "DataList.h"
#include "HeadRing.h"
#include "Polinom.h"

#include <iostream>
using namespace std;

/*-----------------------TESTING TRootLink-----------------------*/
TEST(TRootLink, CanCreateRootLink)
{
	ASSERT_NO_THROW(TDataLink rootLink);
}

TEST(TRootLink, CanGetNextLink)
{
	TDataLink rootLink;
	ASSERT_NO_THROW(rootLink.GetNextLink());

	EXPECT_EQ(rootLink.GetNextLink(), nullptr);

	TDataLink *pRootLink1 = new TDataLink();
	TDataLink *pRootLink2 = new TDataLink();
	pRootLink1->SetNextLink(pRootLink2);
	EXPECT_EQ((pTRootLink)pRootLink1->GetNextLink(), pRootLink2);
}

TEST(TRootLink, CanSetNextLink)
{
	TDataLink rootLink;
	TDataLink *pRootLink = new TDataLink();
	ASSERT_NO_THROW(rootLink.SetNextLink(pRootLink));

	EXPECT_EQ(rootLink.GetNextLink(), pRootLink);
}

TEST(TRootLink, CanInsertNextLink)
{
	TDataLink rootLink;
	TMonom monom(3, 123);
	TDataLink *pRootLink = new TDataLink(monom.GetCopy());

	ASSERT_NO_THROW(rootLink.InsertNextLink(pRootLink));

	EXPECT_EQ(rootLink.GetNextLink(), pRootLink);
}


/*-----------------------TESTING TDataLink-----------------------*/

TEST(TDataLink, CanCreateDataLink)
{
	ASSERT_NO_THROW(TDataLink dataLink);

	TMonom monom1(3, 121);
	ASSERT_NO_THROW(TDataLink dataLink(monom1.GetCopy()));

	TMonom monom2(7, 398);
	TDataLink *dataLink1 = new TDataLink();
	ASSERT_NO_THROW(TDataLink dataLink(monom2.GetCopy(), dataLink1));
}

TEST(TDataLink, CanSetDataValue)
{
	TDataLink *dataLink = new TDataLink();
	TMonom monom(1, 23);
	ASSERT_NO_THROW(dataLink->SetDataValue(monom.GetCopy()));
}

TEST(TDataLink, CanGetDataValue)
{
	TDataLink dataLink;
	TMonom monom(4, 173);

	ASSERT_NO_THROW(dataLink.SetDataValue(monom.GetCopy()));
	
	//------------Подсказка по работе с указателями----------//
	int v = 23;
	int *p, *pp;
	p = &v;
	pp = p;

	cout << endl <<"Adress: " << p << " value: " << *p << endl;
	cout << endl << "Adress: " << pp << " value: " << *pp << endl;
	//-------------------------------------------------------//

	// monom.GetCopy() создает новый указатель => адреса
	//указателей не могут быть равны

	TDataValue *pValue = monom.GetCopy();
	dataLink.SetDataValue(pValue);
	//cout << pValue << endl;
	//cout << dataLink.GetDataValue() << endl;
	EXPECT_EQ(dataLink.GetDataValue(), pValue);

	//Невозможно сравнить адреса указателей, exception 0xc00000fd
	/*EXPECT_EQ(*dataLink.GetDataValue() == *pValue, 1);*/
}

TEST(TDataLink, CanGetNextDataLink)
{
	TMonom *monom = new TMonom(3, 456);
	TDataLink *dataLink1 = new TDataLink();
	TDataLink *dataLink = new TDataLink(monom->GetCopy(), dataLink1);

	ASSERT_NO_THROW(dataLink->GetNextDataLink());
	EXPECT_EQ(dataLink->GetNextDataLink(), nullptr);
}

/*-----------------------TESTING TMonom-----------------------*/

TEST(TMonom, CanCreateMonom)
{
	ASSERT_NO_THROW(TMonom monom);

	ASSERT_NO_THROW(TMonom monom(1, 2));

	ASSERT_NO_THROW(TMonom monom(1, 26));

	ASSERT_NO_THROW(TMonom monom(1, 269));

	ASSERT_NO_THROW(TMonom monom(9));
}

TEST(TMonom, ThrowWhenCreateMonomWithNegativeIndex)
{
	ASSERT_ANY_THROW(TMonom monom(3, -1));

	ASSERT_ANY_THROW(TMonom monom(3, -16));

	ASSERT_ANY_THROW(TMonom monom(3, -169));
}

TEST(TMonom, ThrowWhenCreateMonomWithTooBigIndex)
{
	ASSERT_ANY_THROW(TMonom monom(7, 1000));
}

TEST(TMonom, CanGetCopy)
{
	TMonom monom(2, 456);
	
	ASSERT_NO_THROW(monom.GetCopy());
}

TEST(TMonom, CanSetCoefficient)
{
	TMonom monom1;

	ASSERT_NO_THROW(monom1.SetCoefficient(3));

	monom1.SetCoefficient(-6);

	EXPECT_EQ(monom1.GetCoefficient(), -6);

	TMonom monom2(13, 456);
	monom2.SetCoefficient(9);

	EXPECT_EQ(monom2.GetCoefficient(), 9);
}

TEST(TMonom, CanGetCoefficient)
{
	TMonom monom1;

	ASSERT_NO_THROW(monom1.GetCoefficient());

	monom1.SetCoefficient(-45);

	EXPECT_EQ(monom1.GetCoefficient(), -45);

	TMonom monom2(-78, 4);
	monom2.SetCoefficient(99);

	EXPECT_EQ(monom2.GetCoefficient(), 99);
}

TEST(TMonom, CanSetIndex)
{
	TMonom monom1;

	ASSERT_NO_THROW(monom1.SetIndex(67));

	monom1.SetIndex(111);

	EXPECT_EQ(monom1.GetIndex(), 111);

	TMonom monom2(-1, 33);
	monom2.SetIndex(999);

	EXPECT_EQ(monom2.GetIndex(), 999);
}

TEST(TMonom, CanGetIndex)
{
	TMonom monom1;

	ASSERT_NO_THROW(monom1.GetIndex());

	monom1.SetIndex(312);

	EXPECT_EQ(monom1.GetIndex(), 312);

	TMonom monom2(1, 63);

	EXPECT_EQ(monom2.GetIndex(), 63);
}

TEST(TMonom, CanAssignMonom)
{
	TMonom monom1;
	TMonom monom2(23, 781);

	ASSERT_NO_THROW(monom1 = monom2);

	monom1 = monom2;

	EXPECT_EQ(monom1 == monom2, 1);

	EXPECT_EQ(monom2 == monom2, 1);
}

TEST(TMonom, CanCompareMonomsEqualOrNot)
{
	TMonom monom1(23, 780);
	TMonom monom2(23, 781);
	TMonom monom3(23, 780);

	ASSERT_NO_THROW(monom1 == monom2);

	EXPECT_EQ(monom1 == monom2, 0);

	EXPECT_EQ(monom1 == monom3, 1);
}

TEST(TMonom, CanCompareMonomsLessOrNot)
{
	TMonom monom1(4, 7);
	TMonom monom2(-34, 142);
	TMonom monom3(23, 780);
	TMonom monom4(-34, 21);
	TMonom monom5(77, 7);

	ASSERT_NO_THROW(monom1 < monom2);

	EXPECT_EQ(monom1 < monom2, 1);

	EXPECT_EQ(monom3 < monom1, 0);

	EXPECT_EQ(monom1 < monom1, 0);

	EXPECT_EQ(monom2 < monom4, 0);

	EXPECT_EQ(monom1 < monom5, 1);
}


/*-----------------------TESTING TDataList-----------------------*/

TEST(TDataList, CanCreateList)
{
	TDataList list;
	ASSERT_NO_THROW(TDataList list1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetDataValue(), nullptr);

	//int pos = 2;
	//list.SetCurrentPosition(pos);
	//cout << endl << list.GetCurrentPosition() << endl;
}

//TEST(TDataList, CanGetDataValue)
//{
//
//}


TEST(TDataList, CanSetPosition)
{
	TDataList list;

	ASSERT_THROW(list.SetCurrentPosition(10), logic_error);
	ASSERT_THROW(list.SetCurrentPosition(-1), range_error);
}

TEST(TDataList, CanGetPosition)
{
	TDataList list;

	ASSERT_NO_THROW(list.GetCurrentPosition());
	EXPECT_EQ(list.GetCurrentPosition(), 0);
}

TEST(TDataList, CanReset)
{
	TDataList list;
	list.Reset();

	EXPECT_EQ(list.GetCurrentPosition(), 0);
	//EXPECT_EQ(list.)

}

TEST(TDataList, CanMoveNext)
{
	TDataList list;

	ASSERT_THROW(list.MoveNext(), logic_error);
}

TEST(TDataList, CanInsertBeforeFirst)
{
	TDataList list;
	TMonom monom(34, 3);

	ASSERT_NO_THROW(list.InsertBeforeFirst());
	ASSERT_NO_THROW(list.InsertBeforeFirst(monom.GetCopy()));
}

TEST(TDataList, CorrectrlyInsertFirstLink)
{
	TDataList list;
	TMonom monom(3, 111);
	TDataValue *pValue = monom.GetCopy();

	//cout << *pValue << endl;
	list.InsertBeforeFirst(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
}

TEST(TDataList, CorrectrlyInsertFirst)
{
	TDataList list;
	TMonom monom(3, 111), monom2(-22, 89);
	TDataValue *pValue = monom.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	//cout << *pValue << endl;
	list.InsertBeforeFirst(pValue);
	list.InsertBeforeFirst(pValue2);

	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	EXPECT_EQ(list.GetDataValue(LAST), pValue2);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_EQ(list.IsEmpty(), false);
	
}
