#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TSortTable.h"
#include "TTreeNode.h"
#include "TTreeTable.h"
#include "TBalanceNode.h"
#include "TBalanceTree.h"
#include "TArrayHash.h"
#include "TListHash.h"
#include "StudentAchievements.h"

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
TEST(ArrayTable, Can_Create_Default_Array_Table)
{
    ASSERT_NO_THROW(TScanTable arrayTable);
}

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

TEST(ArrayTable, Can_Get_Key)
{
    TScanTable scanTable;

    scanTable.InsertRecord("key", nullptr);

    ASSERT_NO_THROW(scanTable.GetKey());
}

TEST(ArrayTable, Throw_When_Trying_To_Get_Key_From_Empty_Table)
{
    TScanTable scanTable;

    ASSERT_THROW(scanTable.GetKey(), runtime_error);
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

//----------------Testing class TSortTable----------------
TEST(SortTable, Can_Create_Default_Sort_Table)
{
    ASSERT_NO_THROW(TSortTable sortTable);
}

TEST(SortTable, Can_Create_Sort_Table_With_Custom_Parameter)
{
    ASSERT_NO_THROW(TSortTable sortTable(22));
}

TEST(SortTable, Can_Create_Sort_Table_Based_On_Scan_Table)
{
    TScanTable sourceTable(11);

    sourceTable.InsertRecord("qwerty", nullptr);
    sourceTable.InsertRecord("wasd", nullptr);
    sourceTable.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(TSortTable copiedTable(sourceTable));
}

TEST(SortTable, Can_Equal_Sort_Table_And_Scan_Table)
{
    TScanTable scanTable;
    TSortTable sortTable;

    scanTable.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(sortTable = scanTable);
}

TEST(SortTable, Equal_Sort_Table_And_Scan_Table_Correctly_Appoints_Values)
{
    TScanTable scanTable;
    TSortTable sortTable;
    TKey expectedKey = "example";

    scanTable.InsertRecord("example", nullptr);
    scanTable.InsertRecord("qwerty", nullptr);
    scanTable.InsertRecord("wasd", nullptr);
    scanTable.InsertRecord("dsaw", nullptr);

    sortTable = scanTable;

    EXPECT_EQ(sortTable.GetDataCount(), 4);
    EXPECT_EQ(sortTable.GetKey(), expectedKey);
}

TEST(SortTable, Can_Equal_Sort_Table_And_Empty_Scan_Table)
{
    TScanTable scanTable;
    TSortTable sortTable;

    ASSERT_NO_THROW(sortTable = scanTable);
}

TEST(SortTable, Can_Get_Sort_Method)
{
    TSortTable sortTable;

    ASSERT_NO_THROW(sortTable.GetSortMethod());
}

TEST(SortTable, Get_Correct_Sort_Method)
{
    TSortTable sortTable;

    EXPECT_EQ(sortTable.GetSortMethod(), INSERT_SORT);
}

TEST(SortTable, Can_Set_Sort_Method)
{
    TSortTable sortTable;

    ASSERT_NO_THROW(sortTable.SetSortMethod(MERGE_SORT));
}

TEST(SortTable, Set_Correct_Sort_Method)
{
    TSortTable sortTable;

    sortTable.SetSortMethod(QUICK_SORT);

    EXPECT_EQ(sortTable.GetSortMethod(), QUICK_SORT);
}

TEST(SortTable, Throw_When_Trying_To_Set_Unexisting_Sort_Method)
{
    TSortTable sortTable;
    TSortMethod MERJE_SORT;

    ASSERT_THROW(sortTable.SetSortMethod(MERJE_SORT), invalid_argument);
}

TEST(SortTable, Can_Find_Record)
{
    TSortTable sortTable;
    TKey requestedKey = "qwerty";

    sortTable.InsertRecord("qwerty", nullptr);

    ASSERT_NO_THROW(sortTable.FindRecord(requestedKey));
}

TEST(SortTable, Find_Correct_Record)
{
    TSortTable sortTable(5);
    TKey requestedKey = "wasd";
    TTabRecord requestedRecord("wasd", nullptr);
    pTDataValue requestedValue = requestedRecord.GetValuePTR();

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    EXPECT_EQ(sortTable.FindRecord(requestedKey), requestedValue);
}

TEST(SortTable, Throw_When_Trying_To_Find_Record_In_Empty_Table)
{
    TSortTable sortTable;

    ASSERT_THROW(sortTable.FindRecord("example"), logic_error);
}

TEST(SortTable, Throw_When_Trying_To_Find_Record_Using_Unexisting_Key)
{
    TSortTable sortTable(7);

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    ASSERT_THROW(sortTable.FindRecord("exampl"), runtime_error);
}

TEST(SortTable, Throw_When_Trying_To_Find_Record_Using_Too_Long_Key)
{
    TSortTable sortTable(9);

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    ASSERT_THROW(sortTable.FindRecord("qwertyui"), runtime_error);
}

TEST(SortTable, Throw_When_Trying_To_Find_Record_Using_Too_Short_Key)
{
    TSortTable sortTable(9);

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    ASSERT_THROW(sortTable.FindRecord("was"), runtime_error);
}

TEST(SortTable, Can_Insert_Record)
{
    TSortTable sortTable;

    ASSERT_NO_THROW(sortTable.InsertRecord("example", nullptr));
}

TEST(SortTable, Inserted_Record_Is_Correct)
{
    TSortTable sortTable(5);
    TKey expectedKey = "example";

    sortTable.InsertRecord("example", nullptr);

    EXPECT_EQ(sortTable.GetDataCount(), 1);
    EXPECT_EQ(sortTable.GetKey(), expectedKey);
    EXPECT_EQ(sortTable.GetValuePTR(), nullptr);
}

TEST(SortTable, Throw_When_Trying_To_Insert_Record_Into_Full_Table)
{
    TSortTable sortTable(2);

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);

    ASSERT_THROW(sortTable.InsertRecord("example", nullptr), logic_error);
}

TEST(SortTable, Throw_When_Trying_To_Insert_Already_Existing_Record)
{
    TSortTable sortTable(7);

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    ASSERT_THROW(sortTable.InsertRecord("example", nullptr), runtime_error);
}

TEST(SortTable, Can_Delete_Record)
{
    TSortTable sortTable;

    sortTable.InsertRecord("wasd", nullptr);

    ASSERT_NO_THROW(sortTable.DeleteRecord("wasd"));
}

TEST(SortTable, Delete_Record_Change_The_Table)
{
    TSortTable sortTable(5);
    TKey expectedKey = "example";

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    sortTable.DeleteRecord("qwerty");

    EXPECT_EQ(sortTable.GetDataCount(), 2);
    EXPECT_EQ(sortTable.GetKey(), expectedKey);
    EXPECT_EQ(sortTable.GetValuePTR(), nullptr);
}

TEST(SortTable, Throw_When_Trying_To_Delete_Record_From_Empty_Table)
{
    TSortTable sortTable;

    ASSERT_THROW(sortTable.DeleteRecord("qwerty"), logic_error);
}

TEST(SortTable, Throw_When_Trying_To_Delete_Non_Existing_Record)
{
    TSortTable sortTable(7);

    sortTable.InsertRecord("qwerty", nullptr);
    sortTable.InsertRecord("wasd", nullptr);
    sortTable.InsertRecord("example", nullptr);

    ASSERT_THROW(sortTable.DeleteRecord("examplr"), runtime_error);
}

//----------------Testing class TTreeNode----------------
TEST(TreeNode, Can_Create_Default_Tree_Node)
{
    ASSERT_NO_THROW(TTreeNode treeNode);
}

TEST(TreeNode, Can_Create_Tree_Node_With_Custom_Parameters)
{
    pTTreeNode left = new TTreeNode("left");
    pTTreeNode right = new TTreeNode("right");

    ASSERT_NO_THROW(TTreeNode treeNode("root", nullptr, left, right));
}

TEST(TreeNode, Can_Get_Left)
{
    TTreeNode treeNode;

    ASSERT_NO_THROW(treeNode.GetLeft());
}

TEST(TreeNode, Get_Left_Returns_Correct_Value)
{
    pTTreeNode left = new TTreeNode("left");
    TTreeNode treeNode("root", nullptr, left);

    EXPECT_EQ(treeNode.GetLeft(), left);
}

TEST(TreeNode, Can_Get_Right)
{
    TTreeNode treeNode;

    ASSERT_NO_THROW(treeNode.GetRight());
}

TEST(TreeNode, Get_Right_Returns_Correct_Value)
{
    pTTreeNode right = new TTreeNode("right");
    TTreeNode treeNode("root", nullptr, nullptr, right);

    EXPECT_EQ(treeNode.GetRight(), right);
}

TEST(TreeNode, Can_Get_Copy_If_Value_Is_Nullptr)
{
    TTreeNode source;

    ASSERT_NO_THROW(source.GetCopy());
}

TEST(TreeNode, Can_Get_Copy_If_Value_Is_Not_Nullptr)
{
    TTreeNode copy;
    pTDataValue value = copy.GetCopy();
    TTreeNode source("source", value);

    ASSERT_NO_THROW(source.GetCopy());
}

//----------------Testing class TTreeTable----------------
TEST(TreeTable, Can_Create_Default_Tree_Table)
{
    ASSERT_NO_THROW(TTreeTable treeTable);
}

TEST(TreeTable, Is_Full_Returns_False)
{
    TTreeTable treeTable;

    EXPECT_FALSE(treeTable.IsFull());
}

TEST(TreeTable, Can_Find_Record)
{
    TTreeTable treeTable;
    TTabRecord record1("w");
    pTDataValue copy1 = record1.GetCopy() /* , copy2 = record2.GetCopy() */;
    TTabRecord record2("was", copy1), record3("wa", record2.GetCopy());

    treeTable.InsertRecord(record1.GetKey(), record1.GetValuePTR());
    treeTable.InsertRecord(record2.GetKey(), record2.GetValuePTR());
    treeTable.InsertRecord(record3.GetKey(), record3.GetValuePTR());

    ASSERT_NO_THROW(treeTable.FindRecord(record3.GetKey()));
}

TEST(TreeTable, Find_Record_Returns_Corrent_Record)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("qwe", nullptr);
    treeTable.InsertRecord("q", nullptr);
    treeTable.InsertRecord("qwert", nullptr);

    EXPECT_EQ(treeTable.FindRecord("qwert"), nullptr);
}

TEST(TreeTable, Throw_When_Trying_To_Find_Non_Existing_Record)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("qwe", nullptr);
    treeTable.InsertRecord("q", nullptr);
    treeTable.InsertRecord("qwert", nullptr);

    ASSERT_THROW(treeTable.FindRecord("qwer"), runtime_error);
}

TEST(TreeTable, Can_Insert_Record)
{
    TTreeTable treeTable;

    ASSERT_NO_THROW(treeTable.InsertRecord("example", nullptr));
}

TEST(TreeTable, Inserted_Record_Is_Correct)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("example", nullptr);
    treeTable.Reset();

    EXPECT_EQ(treeTable.GetKey(), "example");
    EXPECT_EQ(treeTable.GetValuePTR(), nullptr);
    EXPECT_EQ(treeTable.GetDataCount(), 1);
}

TEST(TreeTable, Throw_When_Trying_To_Insert_Already_Existing_Record)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("qwe", nullptr);
    treeTable.InsertRecord("q", nullptr);

    ASSERT_THROW(treeTable.InsertRecord("qwe", nullptr), runtime_error);
}

TEST(TreeTable, Can_Delete_Record)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("exampl", nullptr);

    ASSERT_NO_THROW(treeTable.DeleteRecord("exampl"));
}

TEST(TreeTable, Delete_Record_Changes_Table)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("wasd", nullptr);
    treeTable.InsertRecord("wasda", nullptr);
    treeTable.InsertRecord("wa", nullptr);

    treeTable.DeleteRecord("wasd");

    EXPECT_EQ(treeTable.GetDataCount(), 2);
    ASSERT_THROW(treeTable.FindRecord("wasd"), runtime_error);
}

TEST(TreeTable, Throw_When_Trying_To_Delete_Non_Existing_Record)
{
    TTreeTable treeTable;

    ASSERT_THROW(treeTable.DeleteRecord("exam"), invalid_argument);
}

TEST(TreeTable, Can_Correctly_Delete_Record_Without_Right_Child)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("example", nullptr);
    treeTable.InsertRecord("ex", nullptr);

    treeTable.DeleteRecord("ex");

    EXPECT_EQ(treeTable.GetDataCount(), 1);
    ASSERT_THROW(treeTable.FindRecord("ex"), runtime_error);
}

TEST(TreeTable, Can_Get_Key)
{
    TTreeTable treeTable;

    ASSERT_NO_THROW(treeTable.GetKey());
}

TEST(TreeTable, Get_Key_Returns_Correct_Empty_Value)
{
    TTreeTable treeTable;

    EXPECT_EQ(treeTable.GetKey(), "");
}

TEST(TreeTable, Get_Key_Returns_Correct_Value)
{
    TTreeTable treeTable;
    TKey key = "key";

    treeTable.InsertRecord(key, nullptr);
    treeTable.Reset();

    EXPECT_EQ(treeTable.GetKey(), key);
}

TEST(TreeTable, Can_Get_Value)
{
    TTreeTable treeTable;

    ASSERT_NO_THROW(treeTable.GetValuePTR());
}

TEST(TreeTable, Get_Value_Returns_Correct_Empty_Value)
{
    TTreeTable treeTable;

    EXPECT_EQ(treeTable.GetValuePTR(), nullptr);
}

TEST(TreeTable, Get_Value_Returns_Correct_Value)
{
    TTreeTable treeTable;
    TTabRecord record("key", nullptr);
    pTDataValue copy = record.GetCopy();

    treeTable.InsertRecord("key", copy);
    treeTable.Reset();

    EXPECT_EQ(treeTable.GetValuePTR(), copy);
}

TEST(TreeTable, Can_Reset)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("qwerty", nullptr);
    treeTable.InsertRecord("example", nullptr);
    treeTable.InsertRecord("wasd", nullptr);

    ASSERT_NO_THROW(treeTable.Reset());
}

TEST(TreeTable, Reset_Works_Correctly)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("qwerty", nullptr);
    treeTable.InsertRecord("example", nullptr);
    treeTable.InsertRecord("wasd", nullptr);

    treeTable.Reset();

    EXPECT_EQ(treeTable.GetDataCount(), 3);
    EXPECT_EQ(treeTable.GetKey(), "example");
    EXPECT_EQ(treeTable.GetValuePTR(), nullptr);
}

TEST(TreeTable, Is_Table_Ended_Returns_True)
{
    TTreeTable treeTable;

    EXPECT_TRUE(treeTable.IsTableEnded());
}

TEST(TreeTable, Is_Table_Ended_Returns_False)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("example", nullptr);
    treeTable.InsertRecord("wasd", nullptr);
    treeTable.Reset();

    EXPECT_FALSE(treeTable.IsTableEnded());
}

TEST(TreeTable, Can_Go_Next)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("example", nullptr);
    treeTable.InsertRecord("wasd", nullptr);
    treeTable.Reset();

    ASSERT_NO_THROW(treeTable.GoNext());
}

TEST(TreeTable, Go_Next_Set_Correct_State_Of_Table)
{
    TTreeTable treeTable;

    treeTable.InsertRecord("example", nullptr);
    treeTable.InsertRecord("wasd", nullptr);
    treeTable.Reset();

    treeTable.GoNext();

    EXPECT_EQ(treeTable.GetKey(), "wasd");
    EXPECT_EQ(treeTable.GetValuePTR(), nullptr);
}

//----------------Testing class TBalanceNode----------------
TEST(BalanceNode, Can_Create_Default_Balance_Node)
{
    ASSERT_NO_THROW(TBalanceNode balanceNode);
}

TEST(BalanceNode, Can_Create_Balance_Node_With_Custom_Parameters)
{
    TTabRecord record("key", nullptr);
    pTTreeNode left = new TTreeNode("pk");
    pTTreeNode right = new TTreeNode("fk");

    ASSERT_NO_THROW(TBalanceNode balanceNode("turtle", record.GetCopy(), left, right, 0));
}

TEST(BalanceNode, Can_Get_Balance)
{
    TBalanceNode balanceNode;

    ASSERT_NO_THROW(balanceNode.GetBalance());
}

TEST(BalanceNode, Get_Balance_Returns_Correct_Value)
{
    TBalanceNode balanceNode("", nullptr, nullptr, nullptr, 1);

    EXPECT_EQ(balanceNode.GetBalance(), 1);
}

TEST(BalanceNode, Can_Set_Balance_Node)
{
    TBalanceNode balanceNode;

    ASSERT_NO_THROW(balanceNode.SetBalance(0));
}

TEST(BalanceNode, Set_Balance_Node_Change_Value_Correctly)
{
    TBalanceNode balanceNode;

    balanceNode.SetBalance(-1);

    EXPECT_EQ(balanceNode.GetBalance(), -1);
}

TEST(BalanceNode, Throw_When_Trying_To_Set_Incorrect_Balance)
{
    TBalanceNode balanceNode;

    ASSERT_THROW(balanceNode.SetBalance(-2), invalid_argument);
    ASSERT_THROW(balanceNode.SetBalance(4324), invalid_argument);
}

//----------------Testing class TBalanceTree----------------
TEST(BalanceTree, Can_Create_Default_Balance_Tree)
{
    ASSERT_NO_THROW(TBalanceTree balanceTree);
}

TEST(BalanceTree, Can_Insert_Record)
{
    TBalanceTree balanceTree;

    ASSERT_NO_THROW(balanceTree.InsertRecord("example", nullptr));
}

TEST(BalanceTree, Inserted_Record_Is_Correctly_Paste)
{
    TBalanceTree balanceTree;

    balanceTree.InsertRecord("qwerty", nullptr);
    balanceTree.InsertRecord("wasd", nullptr);
    balanceTree.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(balanceTree.FindRecord("wasd"));
}

TEST(BalanceTree, Throw_When_Trying_To_Insert_Already_Existing_Record)
{
    TBalanceTree balanceTree;

    balanceTree.InsertRecord("wasd", nullptr);

    ASSERT_THROW(balanceTree.InsertRecord("wasd", nullptr), runtime_error);
}

TEST(BalanceTree, Can_Delete_Record)
{
    TBalanceTree balanceTree;

    balanceTree.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(balanceTree.DeleteRecord("example"));
}

TEST(BalanceTree, Deleted_Record_Is_Correctly_Removed)
{
    TBalanceTree balanceTree;

    balanceTree.InsertRecord("qwerty", nullptr);
    balanceTree.InsertRecord("wasd", nullptr);
    balanceTree.InsertRecord("example", nullptr);

    balanceTree.DeleteRecord("example");

    ASSERT_THROW(balanceTree.FindRecord("example"), runtime_error);
}

TEST(BalanceTree, Throw_When_Trying_To_Delete_Record_From_Empty_Balance_Tree)
{
    TBalanceTree balanceTree;

    ASSERT_THROW(balanceTree.DeleteRecord("qwerty"), logic_error);
}

//----------------Testing class TArrayHash----------------
TEST(ArrayHash, Can_Create_Default_Array_Hash)
{
    ASSERT_NO_THROW(TArrayHash arrayHash);
}

TEST(ArrayHash, Can_Create_Array_Hash_With_Custom_Parameters)
{
    ASSERT_NO_THROW(TArrayHash arrayHash(12, 3));
}

TEST(ArrayHash, Throw_When_Trying_To_Create_Array_Hash_With_Negative_Size)
{
    ASSERT_THROW(TArrayHash arrayHash(-1), logic_error);
}

TEST(ArrayHash, Throw_When_Trying_To_Create_Array_Hash_With_Negative_Step)
{
    ASSERT_THROW(TArrayHash arrayHash(4, -33), logic_error);
}

TEST(ArrayHash, Throw_When_Trying_To_Create_Array_Hash_With_Step_More_Than_Size)
{
    ASSERT_THROW(TArrayHash arrayHash(2, 5), logic_error);
}

TEST(ArrayHash, Is_Full_Returns_False)
{
    TArrayHash arrayHash;

    EXPECT_FALSE(arrayHash.IsFull());
}

TEST(ArrayHash, Can_Get_Key)
{
    TArrayHash arrayHash;
    TTabRecord record("wasd");
    pTDataValue copy = record.GetCopy();

    arrayHash.InsertRecord("example", copy);

    ASSERT_NO_THROW(arrayHash.GetKey());
}

TEST(ArrayHash, Get_Key_Returns_Correct_Value)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);

    EXPECT_EQ(arrayHash.GetKey(), "qwerty");
}

TEST(ArrayHash, Get_Key_Returns_Empty_Key)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("", nullptr);

    EXPECT_EQ(arrayHash.GetKey(), "");
}

TEST(ArrayHash, Can_Get_Value)
{
    TArrayHash arrayHash;
    TTabRecord record("wasd");
    pTDataValue copy = record.GetCopy();

    arrayHash.InsertRecord("example", copy);

    ASSERT_NO_THROW(arrayHash.GetValuePTR());
}

TEST(ArrayHash, Get_Value_Returns_Correct_Value)
{
    TArrayHash arrayHash;
    TTabRecord record("wasd");
    pTDataValue copy = record.GetCopy();

    arrayHash.InsertRecord("example", copy);

    EXPECT_EQ(arrayHash.GetValuePTR(), copy);
}

TEST(ArrayHash, Get_Value_Returns_Nullptr)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);

    EXPECT_EQ(arrayHash.GetValuePTR(), nullptr);
}

TEST(ArrayHash, Can_Find_Record)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("key", nullptr);

    ASSERT_NO_THROW(arrayHash.FindRecord("key"));
}

TEST(ArrayHash, Find_Record_Returns_Correct_Value)
{
    TArrayHash arrayHash;
    TTabRecord record("wasd");
    pTDataValue copy = record.GetCopy();

    arrayHash.InsertRecord("key", nullptr);
    arrayHash.InsertRecord(record.GetKey(), copy);

    EXPECT_EQ(arrayHash.FindRecord("wasd"), copy);
}

TEST(ArrayHash, Throw_When_Trying_To_Find_Record_In_Empty_Array)
{
    TArrayHash arrayHash;

    ASSERT_THROW(arrayHash.FindRecord("key"), logic_error);
}

TEST(ArrayHash, Throw_When_Trying_To_Find_Unexisting_Record)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);

    ASSERT_THROW(arrayHash.FindRecord("qwert"), runtime_error);
}

TEST(ArrayHash, Can_Insert_Record)
{
    TArrayHash arrayHash;

    ASSERT_NO_THROW(arrayHash.InsertRecord("key", nullptr));
}

TEST(ArrayHash, Inserted_Record_Is_Correctly_Paste)
{
    TArrayHash arrayHash;
    TTabRecord record("key");
    pTDataValue copy = record.GetCopy();

    arrayHash.InsertRecord(record.GetKey(), copy);

    EXPECT_EQ(arrayHash.FindRecord("key"), copy);
}

TEST(ArrayHash, Throw_When_Trying_To_Insert_Already_Existing_Record)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("example", nullptr);

    ASSERT_THROW(arrayHash.InsertRecord("example", nullptr), runtime_error);
}

TEST(ArrayHash, Can_Delete_Record)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);

    ASSERT_NO_THROW(arrayHash.DeleteRecord("qwerty"));
}

TEST(ArrayHash, Deleted_Record_Is_Correctly_Removed)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);
    arrayHash.InsertRecord("qwert", nullptr);

    arrayHash.DeleteRecord("qwerty");

    ASSERT_THROW(arrayHash.FindRecord("qwerty"), runtime_error);
    EXPECT_EQ(arrayHash.GetDataCount(), 1);
}

TEST(ArrayHash, Throw_When_Trying_To_Delete_Non_Existing_Record)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("example", nullptr);

    ASSERT_THROW(arrayHash.DeleteRecord("examp"), logic_error);
}

TEST(ArrayHash, Can_Reset)
{
    TArrayHash arrayHash;

    ASSERT_NO_THROW(arrayHash.Reset());
}

TEST(ArrayHash, Reset_Changes_Array_Condition)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);
    arrayHash.InsertRecord("qwert", nullptr);

    arrayHash.Reset();

    EXPECT_EQ(arrayHash.GetKey(), "qwerty");
}

TEST(ArrayHash, Reset_Returns_Correct_Current_Position)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("qwerty", nullptr);
    arrayHash.InsertRecord("qwert", nullptr);

    EXPECT_EQ(arrayHash.Reset(), 15);
}

TEST(ArrayHash, Is_Table_Ended_Returns_False)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("example", nullptr);
    arrayHash.InsertRecord("key", nullptr);

    EXPECT_FALSE(arrayHash.IsTableEnded());
}

TEST(ArrayHash, Can_Go_Next)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("example", nullptr);
    arrayHash.InsertRecord("qwerty", nullptr);
    arrayHash.Reset();

    ASSERT_NO_THROW(arrayHash.GoNext());
}

TEST(ArrayHash, Go_Next_Set_Correct_State_Of_Table)
{
    TArrayHash arrayHash;

    arrayHash.InsertRecord("example", nullptr);
    arrayHash.InsertRecord("qwerty", nullptr);
    arrayHash.Reset();

    arrayHash.GoNext();

    EXPECT_EQ(arrayHash.GetKey(), "qwerty");
}

//----------------Testing class TListHash----------------
TEST(ListHash, Can_Create_List_Hash)
{
    ASSERT_NO_THROW(TListHash listHash);
}

TEST(ListHash, Throw_When_Trying_To_Create_List_Hash_With_Negative_Size)
{
    ASSERT_THROW(TListHash listHash(-2), out_of_range);
}

TEST(ListHash, Throw_When_Trying_To_Create_List_Hash_With_Too_Big_Size)
{
    ASSERT_THROW(TListHash listHash(27), out_of_range);
}

TEST(ListHash, Is_Full_Returns_False)
{
    TListHash listHash;

    EXPECT_FALSE(listHash.IsFull());
}

TEST(ListHash, Can_Get_Key)
{
    TListHash listHash;

    listHash.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(listHash.GetKey());
}

TEST(ListHash, Get_Key_Returns_Correct_Value)
{
    TListHash listHash;

    listHash.InsertRecord("example", nullptr);

    EXPECT_EQ(listHash.GetKey(), "example");
}

TEST(ListHash, Get_Key_Returns_Empty_Key)
{
    TListHash listHash;

    EXPECT_EQ(listHash.GetKey(), "");
}

TEST(ListHash, Can_Get_Value)
{
    TListHash listHash;

    listHash.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(listHash.GetValuePTR());
}

TEST(ListHash, Get_Value_Returns_Correct_Value)
{
    TListHash listHash;
    TTabRecord record("qwerty");
    pTDataValue copy = record.GetCopy();

    listHash.InsertRecord("qwerty", copy);

    EXPECT_EQ(listHash.GetValuePTR(), copy);
}

TEST(ListHash, Get_Key_Returns_Nullptr_Value)
{
    TListHash listHash;

    EXPECT_EQ(listHash.GetValuePTR(), nullptr);
}

TEST(ListHash, Can_Find_Record)
{
    TListHash listHash;
    TTabRecord record1("qwerty");
    TTabRecord record2("key");

    listHash.InsertRecord("wasd", record1.GetCopy());
    listHash.InsertRecord("example", record2.GetCopy());

    ASSERT_NO_THROW(listHash.FindRecord("example"));
}

TEST(ListHash, Find_Record_Returns_Correct_Value)
{
    TListHash listHash;
    TTabRecord record1("qwerty");
    TTabRecord record2("key");
    pTDataValue copy = record2.GetCopy();

    listHash.InsertRecord("wasd", record1.GetCopy());
    listHash.InsertRecord("key", copy);

    EXPECT_EQ(listHash.FindRecord("key"), copy);
}

TEST(ListHash, Throw_When_Trying_To_Find_Record_In_Empty_List)
{
    TListHash listHash;

    ASSERT_THROW(listHash.FindRecord("key"), logic_error);
}

TEST(ListHash, Throw_When_Trying_To_Find_Unexisting_Record)
{
    TListHash listHash;

    listHash.InsertRecord("qwerty", nullptr);

    ASSERT_THROW(listHash.FindRecord("qwertu"), runtime_error);
}

TEST(ListHash, Can_Insert_Record)
{
    TListHash listHash;

    ASSERT_NO_THROW(listHash.InsertRecord("key", nullptr));
}

TEST(ListHash, Inserted_Record_Is_Correctly_Paste)
{
    TListHash listHash;
    TTabRecord record("key", nullptr);
    pTDataValue copy = record.GetCopy();

    listHash.InsertRecord(record.GetKey(), copy);

    EXPECT_EQ(listHash.FindRecord("key"), copy);
    EXPECT_EQ(listHash.GetDataCount(), 1);
}

TEST(ListHash, Throw_When_Trying_To_Insert_Existing_Record)
{
    TListHash listHash(2);

    listHash.InsertRecord("record1", nullptr);
    listHash.InsertRecord("record2", nullptr);

    ASSERT_THROW(listHash.InsertRecord("record2", nullptr), runtime_error);
}

TEST(ListHash, Can_Delete_Record)
{
    TListHash listHash;

    listHash.InsertRecord("key", nullptr);
    listHash.InsertRecord("example", nullptr);

    ASSERT_NO_THROW(listHash.DeleteRecord("key"));
}

TEST(ListHash, Deleted_Record_Is_Correctly_Removed)
{
    TListHash listHash;

    listHash.InsertRecord("key", nullptr);
    listHash.InsertRecord("example", nullptr);

    listHash.DeleteRecord("key");

    ASSERT_THROW(listHash.FindRecord("key"), runtime_error);
    EXPECT_EQ(listHash.GetDataCount(), 1);
}

TEST(ListHash, Throw_When_Trying_To_Delete_Non_Existing_Record)
{
    TListHash listHash;

    listHash.InsertRecord("key", nullptr);
    listHash.InsertRecord("example", nullptr);

    ASSERT_THROW(listHash.DeleteRecord("kay"), logic_error);
}

TEST(ListHash, Can_Reset)
{
    TListHash listHash;

    listHash.InsertRecord("wasd", nullptr);

    ASSERT_NO_THROW(listHash.Reset());
}

TEST(ListHash, Reset_Changes_List_Condition)
{
    TListHash listHash;

    listHash.InsertRecord("wasd", nullptr);
    listHash.InsertRecord("was", nullptr);
    listHash.InsertRecord("wa", nullptr);

    listHash.Reset();

    EXPECT_EQ(listHash.GetKey(), "wasd");
}

TEST(ListHash, Reset_Returns_Current_List)
{
    TListHash listHash(3);

    listHash.InsertRecord("wasd", nullptr);
    listHash.InsertRecord("was", nullptr);
    listHash.InsertRecord("wa", nullptr);

    EXPECT_EQ(listHash.Reset(), 2);
}


TEST(ListHash, Is_Table_Ended_Returns_False)
{
    TListHash listHash;

    EXPECT_FALSE(listHash.IsTableEnded());
}

TEST(ListHash, Can_Go_Next)
{
    TListHash listHash;

    listHash.InsertRecord("example", nullptr);
    listHash.InsertRecord("exampl", nullptr);
    listHash.InsertRecord("exam", nullptr);

    listHash.Reset();

    ASSERT_NO_THROW(listHash.GoNext());
}

TEST(ListHash, Go_Next_Set_Correct_State_Of_List)
{
    TListHash listHash;

    listHash.InsertRecord("example", nullptr);
    listHash.InsertRecord("exampl", nullptr);
    listHash.InsertRecord("exam", nullptr);

    listHash.Reset();

    listHash.GoNext();

    EXPECT_EQ(listHash.GetKey(), "exampl");
}

TEST(ListHash, Go_Next_Returns_Current_List)
{
    TListHash listHash;

    listHash.InsertRecord("example", nullptr);
    listHash.InsertRecord("exampl", nullptr);
    listHash.InsertRecord("exam", nullptr);

    listHash.Reset();

    EXPECT_EQ(listHash.GoNext(), 1);
}

//----------------Testing class StudentInfo----------------
TEST(StudentInfo, Can_Create_Default_Student_Info)
{
    ASSERT_NO_THROW(StudentInfo info);
}

TEST(StudentInfo, Can_Create_Student_Info_With_Custom_Paremeters)
{
    ASSERT_NO_THROW(StudentInfo info(1, 2, 3, 4, 5));
}

TEST(StudentInfo, Can_Get_Copy)
{
    StudentInfo info;

    ASSERT_NO_THROW(info.GetCopy());
}

//----------------Testing class StudentAchievements----------------
TEST(StudentAchievements, Can_Create_Default_Student_Achievements)
{
    ASSERT_NO_THROW(StudentAchievements<TSortTable> achivements);
}

TEST(StudentAchievements, Can_Get_Student_Info)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_NO_THROW(achievements.GetStudentInfo("????????????"));
}

TEST(StudentAchievements, Get_Student_Info_Returns_Correct_Info)
{
    StudentAchievements<TScanTable> achievements;
    StudentInfo *info;
    int expectedMarks[] = {5, 5, 4, 3, 5};

    info = achievements.GetStudentInfo("Zobova");

    for (int i = 0; i < 5; i++)
    {
        EXPECT_EQ(info->GetMark(i), expectedMarks[i]);
    }
}

TEST(StudentAchievements, Can_Get_Student_Mark)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_NO_THROW(achievements.GetStudentMark("Filipov", 2));
}

TEST(StudentAchievements, Get_Student_Mark_Returns_Correct_Value)
{
    StudentAchievements<TScanTable> achievements;

    EXPECT_EQ(achievements.GetStudentMark("Filipov", 2), 5);
}

TEST(StudentAchievements, Throw_When_Trying_To_Get_Mark_For_Unexisting_Course)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_THROW(achievements.GetStudentMark("Filipov", -1), invalid_argument);
}

TEST(StudentAchievements, Can_Calculate_Student_Average_Mark)
{
    StudentAchievements<TSortTable> achievements;

    ASSERT_NO_THROW(achievements.CalculateStudentAverageMark("Pronicheva"));
}

TEST(StudentAchievements, Calculated_Student_Average_Mark_Is_Correct)
{
    StudentAchievements<TScanTable> achievements;

    EXPECT_DOUBLE_EQ(achievements.CalculateStudentAverageMark("Sysnin"), 3);
}

TEST(StudentAchievements, Can_Calculate_Average_Mark)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_NO_THROW(achievements.CalculateAverageMark(0));
}

TEST(StudentAchievements, Calculated_Average_Mark_Is_Correct)
{
    StudentAchievements<TScanTable> achievements;
    double expectedResult = 3.9000000000000004;

    EXPECT_DOUBLE_EQ(achievements.CalculateAverageMark(0), expectedResult);
}

TEST(StudentAchievements, Can_Calculate_Average_Group_Mark)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_NO_THROW(achievements.CalculateAverageGroupMark(1, 3));
}

TEST(StudentAchievements, Calculated_Average_Group_Mark_Is_Correct)
{
    StudentAchievements<TScanTable> achievements;
    double expectedResult = 3.7999999999999998;

    EXPECT_DOUBLE_EQ(achievements.CalculateAverageGroupMark(1, 3), expectedResult);
}

TEST(StudentAchievements, Can_Get_Group_ID_With_Best_Marks)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_NO_THROW(achievements.GetGroupIDWithBestMarks(2));
}

TEST(StudentAchievements, Get_Group_ID_With_Best_Marks_Is_Correct)
{
    StudentAchievements<TScanTable> achievements;

    EXPECT_EQ(achievements.GetGroupIDWithBestMarks(2), 2);
}

TEST(StudentAchievements, Can_Get_Excellent_Students_Number)
{
    StudentAchievements<TScanTable> achievements;

    ASSERT_NO_THROW(achievements.GetExcellentStudentsNumber(1));
}

TEST(StudentAchievements, Get_Excellent_Students_Number_Returns_Correct_Value)
{
    StudentAchievements<TScanTable> achievements;

    EXPECT_EQ(achievements.GetExcellentStudentsNumber(1), 2);
}
