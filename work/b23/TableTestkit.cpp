#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
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

//----------------Testing class TTable----------------
TEST(TTable, Can_Get_Data_Count)
{
    TScanTable table;

    ASSERT_NO_THROW(table.GetDataCount());
}

TEST(TTable, Get_Data_Count_Returns_Correct_Value)
{
    TScanTable table(3);
    TTabRecord record("example");

    table.InsertRecord(record.GetKey(), record.GetCopy());

    EXPECT_EQ(table.GetDataCount(), 1);
}

TEST(TTable, Can_Get_Efficiency)
{
    TScanTable table;

    ASSERT_NO_THROW(table.GetEfficiency());
}

TEST(TTable, Get_Efficiency_Returns_Correct_Value)
{
    TScanTable table(7);

    EXPECT_EQ(table.GetEfficiency(), 0);
}

//----------------Testing class TArrayTable----------------
// TEST(ArrayTable, Can_Create_Default_Array_Table)
// {
//     //TODO: TArrayTable is the parent of TScanTable
//     ASSERT_NO_THROW(TArrayTable arrayTable);
// }

TEST(ArrayTable, Is_Full_Returns_True)
{
    TScanTable scanTable(2);
    TTabRecord record1("qwerty"), record2("wasd");

    scanTable.InsertRecord(record1.GetKey(), record1.GetCopy());
    scanTable.InsertRecord(record2.GetKey(), record2.GetCopy());

    EXPECT_TRUE(scanTable.IsFull());
}

TEST(ArrayTable, Is_Full_Returns_False)
{
    TScanTable scanTable;

    EXPECT_FALSE(scanTable.IsFull());
}

TEST(ArrayTable, Can_Get_Table_Size)
{
    TScanTable scanTable;

    ASSERT_NO_THROW(scanTable.GetTableSize());
}

TEST(ArrayTable, Get_Table_Size_Returns_Correct_Value)
{
    TScanTable scanTable(12);

    EXPECT_EQ(scanTable.GetTableSize(), 12);
}

TEST(ArrayTable, DISABLED_Can_Get_Key)
{
    TScanTable scanTable;

    ASSERT_NO_THROW(scanTable.GetKey());
}

TEST(ArrayTable, Throw_When_Trying_To_Get_Key_From_Empty_Table)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.GetKey(), runtime_error);
}

TEST(ArrayTable, Throw_When_Trying_To_Get_Key_Using_Invalid_Position)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    ASSERT_THROW(scanTable.GetKey(), invalid_argument);
}

TEST(ArrayTable, DISABLED_Get_Key_Returns_Correct_Value)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    EXPECT_EQ(scanTable.GetKey(), "qwerty");
}

TEST(ArrayTable, DISABLED_Can_Get_Value)
{
    TScanTable scanTable;

    ASSERT_NO_THROW(scanTable.GetKey());
}

TEST(ArrayTable, Throw_When_Trying_To_Get_Value_From_Empty_Table)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.GetValuePTR(), runtime_error);
}

TEST(ArrayTable, Throw_When_Trying_To_Get_Value_Using_Invalid_Position)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    ASSERT_THROW(scanTable.GetValuePTR(), invalid_argument);
}

TEST(ArrayTable, DISABLED_Get_Value_Returns_Correct_Value)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    EXPECT_EQ(scanTable.GetValuePTR(), nullptr);
}
