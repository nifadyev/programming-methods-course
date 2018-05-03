#include "TTabRecord.h"
#include "TArrayTable.h"
#include <gtest/gtest.h>

//----------------Testing class TTabRecord----------------   
TEST(TabRecord, Can_Create_Default_Table_Record)
{
    ASSERT_NO_THROW(TTabRecord tableRecord);
}

TEST(TabRecord, Can_Create_Table_Record_With_One_Parameter)
{
    ASSERT_NO_THROW(TTabRecord tableRecord("qwerty"));
}

TEST(TabRecord, Can_Create_Table_Record_With_All_Parameter)
{
    pTTabRecord record = new TTabRecord("wasd");

    ASSERT_NO_THROW(TTabRecord tableRecord("qwerty", record->GetCopy()));
}

TEST(TabRecord, Can_Set_Key)
{
    TTabRecord tableRecord("qwerty");
    TKey key = "wasd";

    ASSERT_NO_THROW(tableRecord.SetKey(key));
}

TEST(TabRecord, Can_Set_Key_Correctly)
{
    TTabRecord tableRecord("qwerty");
    TKey expectedKey = "wasd";

    tableRecord.SetKey(expectedKey);

    EXPECT_EQ(tableRecord.GetKey(), expectedKey);
}

TEST(TabRecord, Can_Get_Key)
{
    TTabRecord tableRecord("qwerty");

    ASSERT_NO_THROW(tableRecord.GetKey());
}

TEST(TabRecord, Can_Get_Key_Correctly)
{
    TKey expectedKey = "qwerty";
    TTabRecord tableRecord(expectedKey);

    EXPECT_EQ(tableRecord.GetKey(), expectedKey);
}

TEST(TabRecord, Can_Set_Value)
{
    TTabRecord tableRecord("");
    TTabRecord value("qwerty");

    ASSERT_NO_THROW(tableRecord.SetValuePtr(value.GetCopy()));
}

TEST(TabRecord, Can_Set_Value_Correctly)
{
    TTabRecord tableRecord("qwerty");
    TTabRecord expectedValue("wasd");
    pTDataValue copiedValue = expectedValue.GetCopy();

    tableRecord.SetValuePtr(copiedValue);

    EXPECT_EQ(tableRecord.GetValuePTR(), copiedValue);
}

TEST(TabRecord, Can_Get_Value)
{
    TTabRecord tableRecord("qwerty");

    ASSERT_NO_THROW(tableRecord.GetValuePTR());
}

TEST(TabRecord, Can_Get_Copy)
{
    TTabRecord tableRecord("qwerty");

    ASSERT_NO_THROW(tableRecord.GetCopy());
}

TEST(TabRecord, Can_Equal_Table_Records)
{
    TTabRecord tableRecord1("qwerty"), tableRecord2;

    ASSERT_NO_THROW(tableRecord2 = tableRecord1);
}

TEST(TabRecord, Equal_Table_Records_Correctly_Appoint_Values)
{
    TKey expectedKey = "qwerty";
    TTabRecord tableRecord1(expectedKey), tableRecord2;

    tableRecord2 = tableRecord1;

    EXPECT_EQ(tableRecord2.GetKey(), expectedKey);
    EXPECT_EQ(tableRecord2.GetValuePTR(), nullptr);
}

TEST(TabRecord, Can_Compare_Table_Records_Using_Comparison)
{
    TTabRecord tableRecord1("qwerty"), tableRecord2("example");

    ASSERT_NO_THROW(tableRecord1 == tableRecord2);
}

TEST(TabRecord, Can_Compare_Not_Equal_Table_Records_Using_Comparison)
{
    TTabRecord tableRecord1, tableRecord2("example");

    EXPECT_FALSE(tableRecord1 == tableRecord2);
}

TEST(TabRecord, Can_Compare_Equal_Table_Records_Using_Comparison)
{
    TTabRecord tableRecord1("wasd"), tableRecord2("wasd");

    EXPECT_TRUE(tableRecord1 == tableRecord2);
}

TEST(TabRecord, Can_Compare_Table_Record_With_Itself_Using_Comparison)
{
    TTabRecord tableRecord("wasd");

    EXPECT_TRUE(tableRecord == tableRecord);
}

TEST(TabRecord, Can_Compare_Table_Records_Using_Less)
{
    TTabRecord tableRecord1("qwerty"), tableRecord2("example");

    ASSERT_NO_THROW(tableRecord1 < tableRecord2);
}

TEST(TabRecord, Can_Compare_Not_Equal_Table_Records_Using_Less)
{
    TTabRecord tableRecord1, tableRecord2("example");

    EXPECT_TRUE(tableRecord1 < tableRecord2);
}

TEST(TabRecord, Can_Compare_Equal_Table_Records_Using_Less)
{
    TTabRecord tableRecord1("wasd"), tableRecord2("wasd");

    EXPECT_FALSE(tableRecord1 < tableRecord2);
}

TEST(TabRecord, Can_Compare_Table_Record_With_Itself_Using_Less)
{
    TTabRecord tableRecord("wasd");

    EXPECT_FALSE(tableRecord < tableRecord);
}

TEST(TabRecord, Can_Compare_Table_Records_Using_More)
{
    TTabRecord tableRecord1("qwerty"), tableRecord2("wasd");

    ASSERT_NO_THROW(tableRecord1 > tableRecord2);
}

//TODO: maybe its better to return int in operators
TEST(DISABLED_TabRecord, Can_Compare_Not_Equal_Table_Records_Using_More)
{
    TTabRecord tableRecord1("qwerty"), tableRecord2("wasd");

    EXPECT_TRUE(tableRecord1 > tableRecord2);
}

TEST(TabRecord, Can_Compare_Equal_Table_Records_Using_More)
{
    TTabRecord tableRecord1("wasd"), tableRecord2("wasd");

    EXPECT_FALSE(tableRecord1 > tableRecord2);
}

TEST(TabRecord, Can_Compare_Table_Record_With_Itself_Using_More)
{
    TTabRecord tableRecord("example");

    EXPECT_FALSE(tableRecord > tableRecord);
}


//----------------Testing class TArrayTable---------------- 
TEST(DISABLED_ArrayTable, Can_Create_Default_Array_Table)
{
    //TODO: TArrayTable is the parent of TScanTable
    ASSERT_NO_THROW(TArrayTable arrayTable);
}
