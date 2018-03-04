 //This is a personal academic project. Dear PVS-Studio, please check it.
 //PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <gtest/gtest.h>
#include <iostream>
#include <ctime>

#include "RootLink.h"
#include "DataLink.h"
#include "Monom.h"

#include "DataList.h"
#include "HeadRing.h"
#include "Polinom.h"


using namespace std;
//srand(time(0));


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


///*-----------------------TESTING TDataLink-----------------------*/

TEST(TDataLink, CanCreateDataLink)
{
	ASSERT_NO_THROW(TDataLink dataLink1);

	TMonom monom1(3, 121);
	ASSERT_NO_THROW(TDataLink dataLink1(monom1.GetCopy()));

	TMonom monom2(7, 398);
	TDataLink *dataLink2 = new TDataLink();
	ASSERT_NO_THROW(TDataLink dataLink(monom2.GetCopy(), dataLink2));
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
	
	//------------��������� �� ������ � �����������----------//
	//int v = 23;
	//int *p, *pp;
	//p = &v;
	//pp = p;

	//cout << endl <<"Adress: " << p << " value: " << *p << endl;
	//cout << endl << "Adress: " << pp << " value: " << *pp << endl;
	//-------------------------------------------------------//

	// monom.GetCopy() ������� ����� ��������� => ������
	//���������� �� ����� ���� �����

	TDataValue *pValue = monom.GetCopy();
	dataLink.SetDataValue(pValue);

	EXPECT_EQ(dataLink.GetDataValue(), pValue);

	//���������� �������� ������ ����������, exception 0xc00000fd
	/*EXPECT_EQ(*dataLink.GetDataValue() == *pValue, 1);*/
}

TEST(TDataLink, CanGetNextDataLink)
{
	TMonom *monom = new TMonom(3, 456);
	TDataLink *dataLink1 = new TDataLink();
	TDataLink *dataLink2 = new TDataLink(monom->GetCopy(), dataLink1);

	ASSERT_NO_THROW(dataLink2->GetNextDataLink());
	EXPECT_EQ(dataLink2->GetNextDataLink(), dataLink1);
}

///*-----------------------TESTING TMonom-----------------------*/

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
	ASSERT_ANY_THROW(TMonom monom(3, -461));

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
	EXPECT_EQ(list.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(list.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(list.GetDataValue(LAST), nullptr);
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, CanGetDataValue)
{
	TDataList list;

	ASSERT_NO_THROW(list.GetDataValue());
}

TEST(TDataList, GetDataValueReturnsCorrectValues)
{
	TDataList list;
	TMonom monom1(-7, 214), monom2(478, 6), monom3(124, 24);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);
	list.InsertBeforeCurrent(pValue3);

	EXPECT_EQ(list.GetDataValue(FIRST), pValue1);
	EXPECT_EQ(list.GetDataValue(CURRENT), pValue3);
	EXPECT_EQ(list.GetDataValue(LAST), pValue2);
}

TEST(TDataList, GetDataValueReturnsNullptr)
{
	TDataList list;

	EXPECT_EQ(list.GetDataValue(), nullptr);
}


TEST(TDataList, CanSetPosition)
{
	TDataList list;
	TMonom monom1(-7, 214), monom2(478, 6);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);

	ASSERT_NO_THROW(list.SetCurrentPosition(1));	
}

TEST(TDataList, ThrowWhenSetNegativePosition)
{
	TDataList list;

	ASSERT_THROW(list.SetCurrentPosition(-1), range_error);
}

TEST(TDataList, ThrowWhenSetOutOfRangePosition)
{
	TDataList list;

	ASSERT_THROW(list.SetCurrentPosition(10), logic_error);
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

	ASSERT_NO_THROW(list.Reset());
	EXPECT_EQ(list.GetCurrentPosition(), 0);
}

TEST(TDataList, ResetNotEmptyList)
{
	TDataList list;
	TMonom monom1(437, 2), monom2(-27, 357);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);

	list.Reset();

	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_EQ(list.GetDataValue(FIRST), list.GetDataValue(CURRENT));
}

//TODO: Add Reset test for ended list

TEST(TDataList, IsListEndedReturnsFalse)
{
	TDataList list;

	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, IsListEndedReturnsTrue)
{
	TDataList list;
	TMonom monom(4, 245);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);
	list.MoveNext();

	EXPECT_TRUE(list.IsListEnded());
}

TEST(TDataList, CanMoveNext)
{
	TDataList list;
	TMonom monom(-57, 993);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(list.MoveNext());
}

TEST(TDataList, ThrowWhenPCurrentIsPStop)
{
	TDataList list;
	TMonom monom(253, 1);
	TDataValue *pValue = monom.GetCopy();

	ASSERT_THROW(list.MoveNext(), logic_error);

	list.InsertBeforeFirst(pValue);
	list.MoveNext();

	ASSERT_THROW(list.MoveNext(), logic_error);
}

//TEST(TDataList, MoveNextToPStopIfPCurrentIsPLast)
//{
//	TDataList list;
//	TMonom monom(253, 1);
//	TDataValue *pValue = monom.GetCopy();
//
//	list.InsertBeforeFirst(pValue);
//	list.MoveNext();
//
//	EXPECT_EQ(list.GetCurrentPosition(), -1);
//	EXPECT_EQ(list.GetDataValue(), nullptr);
//}

TEST(TDataList, CanPrint)
{
	TDataList list;
	TMonom monom1(437, 2), monom2(-27, 357);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);

	ASSERT_NO_THROW(list.Print());
}

TEST(TDataList, CanInsertBeforeFirst)
{
	TDataList list;
	TMonom monom(34, 3);

	ASSERT_NO_THROW(list.InsertBeforeFirst());
	ASSERT_NO_THROW(list.InsertBeforeFirst(monom.GetCopy()));
}

TEST(TDataList, InsertBeforeFirstIntoEmptyList)
{
	TDataList list;
	TMonom monom(3, 111);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, InsertBeforeFirstInto1ElementList)
{
	TDataList list;
	TMonom monom1(3, 111), monom2(-22, 89);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertBeforeFirst(pValue2);

	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	//TODO: �������� ������ ������
	EXPECT_EQ(list.GetDataValue(LAST), pValue1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, InsertBeforeFirstIntoMultiElementsList)
{
	TDataList list;
	TMonom monom1(-63, 11), monom2(-2, 89), monom3(11, 43);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertBeforeFirst(pValue1); // pLast
	list.InsertBeforeFirst(pValue2);
	list.InsertBeforeFirst(pValue3); // pFirst

	EXPECT_EQ(list.GetListLength(), 3);
	EXPECT_EQ(list.GetDataValue(), pValue3);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue3);
	//TODO: �������� ������ ������
	EXPECT_EQ(list.GetDataValue(LAST), pValue1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, CanInsertAfterLast)
{
	TDataList list;
	TMonom monom(-34, 831);

	ASSERT_NO_THROW(list.InsertAfterLast());
	ASSERT_NO_THROW(list.InsertAfterLast(monom.GetCopy()));
}

TEST(TDataList, InsertAfterLastIntoEmptyList)
{
	TDataList list;
	TMonom monom(99, 1);
	TDataValue *pValue = monom.GetCopy();

	list.InsertAfterLast(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, InsertAfterLastInto1ElementList)
{
	TDataList list;
	TMonom monom1(99, 2), monom2(-31, 347);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertAfterLast(pValue1); // pFirst, pPrevious
	list.InsertAfterLast(pValue2); // pLast, pCurrent
	
	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue1);
	//TODO: �������� ������ ������
	EXPECT_EQ(list.GetDataValue(LAST), pValue2);
	EXPECT_EQ(list.GetCurrentPosition(), 1);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, InsertAfterLastIntoMultiElementsList)
{
	TDataList list;
	TMonom monom1(4, 8), monom2(-84, 689), monom3(251, 913);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertAfterLast(pValue1); // pFirst
	list.InsertAfterLast(pValue2);
	list.InsertAfterLast(pValue3); // pLast

	EXPECT_EQ(list.GetListLength(), 3);
	EXPECT_EQ(list.GetDataValue(), pValue3);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue1);
	//TODO: �������� ������ ������
	EXPECT_EQ(list.GetDataValue(LAST), pValue3);
	EXPECT_EQ(list.GetCurrentPosition(), 2);
	EXPECT_FALSE(list.IsEmpty());
}

//TODO: Make tests with ended lists

TEST(TDataList, CanInsertBeforeCurrent)
{
	TDataList list;
	TMonom monom(123, 8);

	ASSERT_NO_THROW(list.InsertBeforeCurrent());
	ASSERT_NO_THROW(list.InsertBeforeCurrent(monom.GetCopy()));
}

TEST(TDataList, InsertBeforeCurrentIntoEmptyList)
{
	TDataList list;
	TMonom monom(1, 341);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeCurrent(pValue);

	EXPECT_EQ(list.GetListLength(), 1);
	EXPECT_EQ(list.GetDataValue(), pValue);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
	EXPECT_FALSE(list.IsListEnded());
}

TEST(TDataList, InsertBeforeCurrentInto1ElementList)
{
	TDataList list;
	TMonom monom1(7, 932), monom2(-315, 7);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	list.InsertBeforeCurrent(pValue1); // 
	list.InsertBeforeCurrent(pValue2); // 

	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetDataValue(), pValue2);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	//TODO: �������� ������ ������
	EXPECT_EQ(list.GetDataValue(LAST), pValue1);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, InsertBeforeCurrentIntoMultiElementsList)
{
	TDataList list;
	TMonom monom1(-32, 443), monom2(357, 9), monom3(553, 998), monom4(12, 783);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1); // 
	list.InsertBeforeCurrent(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4); // 

	EXPECT_EQ(list.GetListLength(), 4);
	EXPECT_EQ(list.GetDataValue(), pValue4);
	EXPECT_EQ(list.GetDataValue(FIRST), pValue2);
	//TODO: �������� ������ ������
	EXPECT_EQ(list.GetDataValue(LAST), pValue3);
	EXPECT_EQ(list.GetCurrentPosition(), 2);
	EXPECT_FALSE(list.IsEmpty());
}

TEST(TDataList, CanDeleteFirst)
{
	TDataList list;
	TMonom monom(-48, 82);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(list.DeleteFirst());
}

TEST(TDataList, ThrowWhenDeleleFirstFromEmptyList)
{
	TDataList list;

	ASSERT_THROW(list.DeleteFirst(), logic_error);
}

TEST(TDataList, DeleteFirstIn1ElementList)
{
	TDataList list;
	TMonom monom(-48, 82);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	TDataValue *first = list.GetDataValue(FIRST);

	ASSERT_NO_THROW(list.DeleteFirst());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_NE(first, list.GetDataValue(FIRST));
}

TEST(TDataList, DeleteFirstInMultiElementList)
{
	TDataList list;
	TMonom monom1(-48, 82), monom2(467, 124), monom3(67, 9);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();

	list.InsertBeforeFirst(pValue1);
	list.InsertAfterLast(pValue2);
	list.InsertBeforeCurrent(pValue3);

	TDataValue *first = list.GetDataValue(FIRST);

	list.DeleteFirst();

	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 2);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_NE(first, list.GetDataValue());
}

TEST(TDataList, CanDeleteCurrentLink)
{
	TDataList list;
	TMonom monom(-432, 3);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(list.DeleteCurrent());
}

TEST(TDataList, ThrowWhenDeleteCurrentFromEmptyList)
{
	TDataList list;

	ASSERT_THROW(list.DeleteCurrent(), logic_error);
}

TEST(TDataList, DeleteCurrentIn1ElementList)
{
	TDataList list;
	TMonom monom(89, 245);
	TDataValue *pValue = monom.GetCopy();

	list.InsertBeforeFirst(pValue);

	TDataValue *current = list.GetDataValue(CURRENT);

	ASSERT_NO_THROW(list.DeleteCurrent());
	EXPECT_TRUE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 0);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
	EXPECT_NE(current, list.GetDataValue(CURRENT));
}

TEST(TDataList, DeleteCurrentInMultiElementList)
{
	TDataList list;
	TMonom monom1(-42, 541), monom2(312, 124), monom3(4, 2), monom4(-21, 435);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeFirst(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	TDataValue *current = list.GetDataValue(CURRENT);
	list.DeleteCurrent();

	EXPECT_FALSE(list.IsEmpty());
	EXPECT_EQ(list.GetListLength(), 3);
	EXPECT_EQ(list.GetCurrentPosition(), 2);
	EXPECT_NE(current, list.GetDataValue(CURRENT));
}

TEST(TDataList, CanDeleteList)
{
	TDataList list;
	TMonom monom1(445, 6), monom2(-110, 1), monom3(9, 895), monom4(-899, 67);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeFirst(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	ASSERT_NO_THROW(list.DeleteList());
}

TEST(TDataList, DeleteListResetEverything)
{
	TDataList list;
	TMonom monom1(-2, 20), monom2(730, 402), monom3(-771, 999), monom4(2, 49);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	list.InsertBeforeCurrent(pValue1);
	list.InsertBeforeFirst(pValue2);
	list.InsertAfterLast(pValue3);
	list.InsertBeforeCurrent(pValue4);

	list.DeleteList();

	EXPECT_EQ(list.GetListLength(), 0);
	//EXPECT_EQ(list.IsListEnded(), true);
	EXPECT_EQ(list.IsEmpty(), true);
	EXPECT_EQ(list.GetCurrentPosition(), 0);
}


/*-----------------------TESTING THeadRing-----------------------*/


TEST(THeadRing, CanCreateHeadRingList)
{
	ASSERT_NO_THROW(THeadRing ring);
	
	ASSERT_NO_THROW(THeadRing ringList1);
	THeadRing ringList;
	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 0);
	EXPECT_EQ(ringList.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(ringList.GetDataValue(LAST), nullptr);
	EXPECT_TRUE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, CanInsertIntoHeadRingList)
{
	THeadRing ringList;
	TMonom monom(-32, 182);
	TDataValue *pValue = monom.GetCopy();

	ASSERT_NO_THROW(ringList.InsertBeforeFirst(pValue));
}

TEST(THeadRing, InsertIntoEmptyHeadRingList)
{
	THeadRing ringList;
	TMonom monom(999, 3);
	TDataValue *pValue = monom.GetCopy();

	ringList.InsertBeforeFirst(pValue);

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 1);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, InsertInto1ElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom1(-8, 67), monom2(3, 997);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();

	ringList.InsertBeforeFirst(pValue1);
	ringList.InsertBeforeFirst(pValue2);

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 2);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue2);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue2);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue1);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, InsertIntoMultiElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom1(12, 2), monom2(84, 770), monom3(1, 82), monom4(-921, 912);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	ringList.InsertBeforeFirst(pValue1);
	ringList.InsertAfterLast(pValue2);
	ringList.InsertBeforeCurrent(pValue3);
	ringList.InsertBeforeFirst(pValue4);

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 4);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue4);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue4);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue2);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, CanDeleteHeadRingList)
{
	THeadRing ringList;
	TMonom monom(2, 902);
	TDataValue *pValue = monom.GetCopy();

	ringList.InsertBeforeFirst(pValue);

	ASSERT_NO_THROW(ringList.DeleteFirst());
}

TEST(THeadRing, DeleteFrom1ElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom(0, 1);
	TDataValue *pValue = monom.GetCopy();

	ringList.InsertBeforeFirst(pValue);

	ringList.DeleteFirst();

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 0);
	EXPECT_EQ(ringList.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(ringList.GetDataValue(LAST), nullptr);
	EXPECT_TRUE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}

TEST(THeadRing, DeleteFromMultiElementHeadRingList)
{
	THeadRing ringList;
	TMonom monom1(363, 921), monom2(-235, 7), monom3(1, 2), monom4(86, 4);
	TDataValue *pValue1 = monom1.GetCopy();
	TDataValue *pValue2 = monom2.GetCopy();
	TDataValue *pValue3 = monom3.GetCopy();
	TDataValue *pValue4 = monom4.GetCopy();

	ringList.InsertBeforeFirst(pValue1);
	ringList.InsertAfterLast(pValue2);
	ringList.InsertBeforeCurrent(pValue3);
	ringList.InsertBeforeFirst(pValue4);

	ringList.DeleteFirst();

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 3);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue1);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue1);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue2);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());

	ringList.DeleteFirst();

	EXPECT_EQ(ringList.GetCurrentPosition(), 0);
	EXPECT_EQ(ringList.GetListLength(), 2);
	EXPECT_EQ(ringList.GetDataValue(FIRST), pValue3);
	EXPECT_EQ(ringList.GetDataValue(CURRENT), pValue3);
	EXPECT_EQ(ringList.GetDataValue(LAST), pValue2);
	EXPECT_FALSE(ringList.IsEmpty());
	EXPECT_FALSE(ringList.IsListEnded());
}


/*-----------------------TESTING THeadRing-----------------------*/


TEST(TPolinom, CanCreatePolinom)
{
	ASSERT_NO_THROW(TPolinom polinom);

	srand(time(0));
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monoms[i][1] = 1 + rand() % 1000;
	}

	TPolinom polinom(monoms, 10);

	EXPECT_EQ(polinom.GetCurrentPosition(), 0);
	EXPECT_EQ(polinom.GetListLength(), 10);
	EXPECT_FALSE(polinom.IsEmpty());
	EXPECT_FALSE(polinom.IsListEnded());
}

TEST(TPolinom, ThrowWhenMonomsNumberIsNegative)
{
	ASSERT_THROW(TPolinom polinom(nullptr, -11), invalid_argument);
}

TEST(TPolinom, CanCopyEmptyPolinom)
{
	TPolinom copiedPolinom;

	ASSERT_NO_THROW(TPolinom emptyPolinom(copiedPolinom));
}

TEST(TPolinom, CanCopyPolinom)
{
	//srand(time(0));
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monoms[i][1] = 1 + rand() % 1000;
	}

	TPolinom polinom(monoms, 10);
	TPolinom copiedPolinom(polinom);

	EXPECT_EQ(polinom.GetDataValue(FIRST), copiedPolinom.GetDataValue(FIRST));
	EXPECT_EQ(polinom.GetDataValue(LAST), copiedPolinom.GetDataValue(LAST));

	EXPECT_EQ(copiedPolinom.GetCurrentPosition(), 9);
	EXPECT_EQ(copiedPolinom.GetListLength(), 10);
	EXPECT_FALSE(copiedPolinom.IsEmpty());
	EXPECT_FALSE(copiedPolinom.IsListEnded());

	EXPECT_EQ(polinom.GetCurrentPosition(), 0);
	EXPECT_EQ(polinom.GetListLength(), 10);
	EXPECT_FALSE(polinom.IsEmpty());
	EXPECT_FALSE(polinom.IsListEnded());
}

TEST(TPolinom, CanAddEmptyPolinoms)
{
	TPolinom lhs, rhs;

	ASSERT_NO_THROW(lhs = lhs + rhs);
}

TEST(TPolinom, CanAddEmptyPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monoms[i][1] = 1 + rand() % 1000;
	}

	TPolinom lhs(monoms, 10), rhs;

	ASSERT_NO_THROW(lhs = lhs + rhs);

	EXPECT_EQ(lhs.GetCurrentPosition(), 0);
	EXPECT_EQ(lhs.GetListLength(), 10);
	EXPECT_FALSE(lhs.IsEmpty());
	EXPECT_FALSE(lhs.IsListEnded());
}

//TEST(TPolinom, AddToEmptyPolinom)
//{
//	int monoms[10][2];
//	for (int i = 0; i < 10; i++)
//	{
//		monoms[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
//		monoms[i][1] = 1 + rand() % 1000;
//	}
//
//	TPolinom lhs, rhs(monoms, 10);
//
//	/*ASSERT_NO_THROW(lhs = lhs + rhs);*/
//	lhs = lhs + rhs;
//
//	EXPECT_EQ(lhs.GetCurrentPosition(), 0);
//	EXPECT_EQ(lhs.GetListLength(), 10);
//	EXPECT_FALSE(lhs.IsEmpty());
//	EXPECT_FALSE(lhs.IsListEnded());
//}

TEST(TPolinom, CanEqualEmptyPolinomToFilledPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monoms[i][1] = 1 + rand() % 1000;
	}

	TPolinom lhs(monoms, 10), rhs;

	ASSERT_NO_THROW(lhs = rhs);
	EXPECT_EQ(lhs.GetDataValue(FIRST), nullptr);
	EXPECT_EQ(lhs.GetDataValue(CURRENT), nullptr);
	EXPECT_EQ(lhs.GetDataValue(LAST), nullptr);
	EXPECT_EQ(lhs.GetCurrentPosition(), 0);
	EXPECT_EQ(lhs.GetListLength(), 0);
	EXPECT_TRUE(lhs.IsEmpty());
	EXPECT_FALSE(lhs.IsListEnded());
}

TEST(TPolinom, CanEqualFilledPolinomToEmptyPolinom)
{
	int monoms[10][2];
	for (int i = 0; i < 10; i++)
	{
		monoms[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monoms[i][1] = 1 + rand() % 1000;
	}

	TPolinom lhs(monoms, 10), rhs;
	TDataValue *first = lhs.GetDataValue(FIRST);
	TDataValue *last = lhs.GetDataValue(LAST);

	ASSERT_NO_THROW(rhs = lhs);
	EXPECT_EQ(rhs.GetDataValue(FIRST), first);
	EXPECT_EQ(rhs.GetDataValue(LAST), last);
	EXPECT_EQ(rhs.GetCurrentPosition(), 9);
	EXPECT_EQ(rhs.GetListLength(), 10);
	EXPECT_FALSE(rhs.IsEmpty());
	EXPECT_FALSE(rhs.IsListEnded());
}

TEST(TPolinom, CanEqualTwoFilledPolinomsWithDifferentLength)
{
	int monomsLhs[10][2], monomsRhs[10][2];
	for (int i = 0; i < 10; i++)
	{
		monomsLhs[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monomsLhs[i][1] = 1 + rand() % 1000;

		monomsRhs[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monomsRhs[i][1] = 1 + rand() % 1000;
	}

	TPolinom lhs(monomsLhs, 7), rhs(monomsRhs, 10);
	TDataValue *first = lhs.GetDataValue(FIRST);
	TDataValue *last = lhs.GetDataValue(LAST);

	ASSERT_NO_THROW(rhs = lhs);
	EXPECT_EQ(rhs.GetDataValue(FIRST), first);
	EXPECT_EQ(rhs.GetDataValue(LAST), last);
	EXPECT_EQ(rhs.GetCurrentPosition(), 6);
	EXPECT_EQ(rhs.GetListLength(), 7);
	EXPECT_FALSE(rhs.IsEmpty());
	EXPECT_FALSE(rhs.IsListEnded());
}

TEST(TPolinom, CanEqualTwoFilledPolinomsWithEqualLength)
{
	int monomsLhs[10][2], monomsRhs[10][2];
	for (int i = 0; i < 10; i++)
	{
		monomsLhs[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monomsLhs[i][1] = 1 + rand() % 1000;

		monomsRhs[i][0] = -1000 + rand() % 2000; // [-1000; 1000]
		monomsRhs[i][1] = 1 + rand() % 1000;
	}

	TPolinom lhs(monomsLhs, 10), rhs(monomsRhs, 10);
	TDataValue *first = lhs.GetDataValue(FIRST);
	TDataValue *last = lhs.GetDataValue(LAST);

	ASSERT_NO_THROW(rhs = lhs);
	EXPECT_EQ(rhs.GetDataValue(FIRST), first);
	EXPECT_EQ(rhs.GetDataValue(LAST), last);
	EXPECT_EQ(rhs.GetCurrentPosition(), 9);
	EXPECT_EQ(rhs.GetListLength(), 10);
	EXPECT_FALSE(rhs.IsEmpty());
	EXPECT_FALSE(rhs.IsListEnded());
}