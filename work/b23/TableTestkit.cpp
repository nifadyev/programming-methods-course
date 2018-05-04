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

TEST(ArrayTable, DISABLED_Throw_When_Trying_To_Get_Key_Using_Invalid_Position)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    ASSERT_THROW(scanTable.GetKey(), invalid_argument);
}

TEST(ArrayTable, Get_Key_Returns_Correct_Value)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    EXPECT_EQ(scanTable.GetKey(), "qwerty");
}

TEST(ArrayTable, Can_Get_Value)
{
    TScanTable scanTable(6);
    TTabRecord record("example");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    ASSERT_NO_THROW(scanTable.GetKey());
}

TEST(ArrayTable, Throw_When_Trying_To_Get_Value_From_Empty_Table)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.GetValuePTR(), runtime_error);
}

TEST(ArrayTable, DISABLED_Throw_When_Trying_To_Get_Value_Using_Invalid_Position)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    ASSERT_THROW(scanTable.GetValuePTR(), invalid_argument);
}

TEST(ArrayTable, Get_Value_Returns_Correct_Value)
{
    TScanTable scanTable(5);
    TTabRecord record("qwerty");
    pTDataValue copy = record.GetCopy();

    scanTable.InsertRecord(record.GetKey(), copy);

    EXPECT_EQ(scanTable.GetValuePTR(), copy);
}

TEST(ArrayTable, Can_Reset)
{
    TScanTable scanTable;

    ASSERT_NO_THROW(scanTable.Reset());
}

TEST(ArrayTable, Reset_Set_Correct_Position)
{
    TScanTable scanTable;

    scanTable.SetCurrentPosition(3);
    scanTable.Reset();

    EXPECT_EQ(scanTable.GetCurrentPosition(), 0);
}

TEST(ArrayTable, Is_Table_Ended_Returns_True)
{
    TScanTable scanTable;

    EXPECT_TRUE(scanTable.IsTableEnded());
}

TEST(ArrayTable, Is_Table_Ended_Returns_False)
{
    TScanTable scanTable(3);
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    EXPECT_FALSE(scanTable.IsTableEnded());
}

TEST(ArrayTable, Can_Go_Next)
{
    TScanTable scanTable(3);
    TTabRecord record1("qwerty"), record2("example");

    scanTable.InsertRecord(record1.GetKey(), record1.GetCopy());
    scanTable.InsertRecord(record2.GetKey(), record2.GetCopy());
    scanTable.Reset();

    ASSERT_NO_THROW(scanTable.GoNext());
}

TEST(ArrayTable, Throw_When_Trying_To_Go_Next_In_Ended_Table)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.GoNext(), logic_error);
}

TEST(ArrayTable, Can_Set_Current_Position)
{
    TScanTable scanTable(5);

    ASSERT_NO_THROW(scanTable.SetCurrentPosition(3));
}

TEST(ArrayTable, Set_Correct_Value_As_Current_Position)
{
    TScanTable scanTable(17);

    scanTable.SetCurrentPosition(9);

    EXPECT_EQ(scanTable.GetCurrentPosition(), 9);
}

TEST(ArrayTable, Throw_When_Trying_To_Set_Negative_Current_Position)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.SetCurrentPosition(-3), invalid_argument);
}

TEST(ArrayTable, Throw_When_Trying_To_Set_Too_Big_Current_Position)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.SetCurrentPosition(26), invalid_argument);
}

TEST(ArrayTable, Can_Get_Current_Position)
{
    TScanTable scanTable;

    ASSERT_NO_THROW(scanTable.GetCurrentPosition());
}

TEST(ArrayTable, Get_Correct_Value_Of_Current_Position)
{
    TScanTable scanTable;

    scanTable.GetCurrentPosition();

    EXPECT_EQ(scanTable.GetCurrentPosition(), 0);
}

//----------------Testing class TScanTable----------------
TEST(ScanTable, Can_Find_Record)
{
    TScanTable scanTable;
    TKey key = "qwerty";
    TTabRecord record(key);

    scanTable.InsertRecord(record.GetKey(), record.GetCopy());

    ASSERT_NO_THROW(scanTable.FindRecord(key));
}

TEST(ScanTable, Find_Record_Returns_Correct_Value)
{
    TScanTable scanTable;
    TKey key = "wasd";
    TTabRecord record(key);

    scanTable.InsertRecord(record.GetKey(), record.GetValuePTR());

    EXPECT_EQ(scanTable.FindRecord(key), record.GetValuePTR());
}

TEST(ScanTable, Throw_When_Trying_To_Find_Wrong_Record)
{
    TScanTable scanTable;
    TKey key = "wasf";
    TTabRecord record("wasd");

    scanTable.InsertRecord(record.GetKey(), record.GetValuePTR());

    ASSERT_THROW(scanTable.FindRecord(key), runtime_error);
}

TEST(ScanTable, Can_Insert_Record)
{
    TScanTable scanTable;
    TTabRecord record("example");

    ASSERT_NO_THROW(scanTable.InsertRecord(record.GetKey(), record.GetValuePTR()));
}

TEST(ScanTable, Inserted_Record_Is_Correctly_Paste)
{
    TScanTable scanTable;
    TKey expectedKey = "example";
    TTabRecord record(expectedKey);

    scanTable.InsertRecord(record.GetKey(), record.GetValuePTR());

    EXPECT_EQ(scanTable.GetKey(), expectedKey);
    EXPECT_EQ(scanTable.GetValuePTR(), nullptr);
    EXPECT_EQ(scanTable.GetDataCount(), 1);
}

TEST(ScanTable, Throw_When_Trying_To_Insert_Record_Into_Full_Table)
{
    TScanTable scanTable(1);
    TTabRecord record1("qwerty"), record2("wasd");

    scanTable.InsertRecord(record1.GetKey(), record1.GetValuePTR());

    ASSERT_THROW(scanTable.InsertRecord(record2.GetKey(), record2.GetValuePTR()), logic_error);
}

TEST(ScanTable, Throw_When_Trying_To_Insert_Record_Already_Existing_Record)
{
    TScanTable scanTable;
    TTabRecord record("wasd");

    scanTable.InsertRecord(record.GetKey(), record.GetValuePTR());

    ASSERT_THROW(scanTable.InsertRecord(record.GetKey(), record.GetValuePTR()), runtime_error);
}

TEST(ScanTable, Can_Delete_Record)
{
    TScanTable scanTable;
    TKey key = "qwerty";
    TTabRecord record(key);

    scanTable.InsertRecord(record.GetKey(), record.GetValuePTR());

    ASSERT_NO_THROW(scanTable.DeleteRecord(key));
}

TEST(ScanTable, Deleted_Record_Is_Correctly_Removed)
{
    TScanTable scanTable;
    TKey expectedKey = "example";
    TTabRecord record1(expectedKey), record2("wasd");

    scanTable.InsertRecord(record1.GetKey(), record1.GetValuePTR());
    scanTable.InsertRecord(record2.GetKey(), record2.GetValuePTR());
    scanTable.DeleteRecord("wasd");

    EXPECT_EQ(scanTable.GetKey(), expectedKey);
    EXPECT_EQ(scanTable.GetValuePTR(), nullptr);
    EXPECT_EQ(scanTable.GetDataCount(), 1);
}

TEST(ScanTable, Throw_When_Trying_To_Delete_Record_From_Empty_Table)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.DeleteRecord("example"), logic_error);
}

TEST(ScanTable, Throw_When_Trying_To_Delete_Non_Existing_Record)
{
    TScanTable scanTable;
    TKey wrongKey = "qqwerty";
    TTabRecord record("qwerty");

    scanTable.InsertRecord(record.GetKey(), record.GetValuePTR());

    ASSERT_THROW(scanTable.DeleteRecord(wrongKey), runtime_error);
}
