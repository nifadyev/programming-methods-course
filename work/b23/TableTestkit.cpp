#include "TTabRecord.h"
#include "TArrayTable.h"
#include "TScanTable.h"
#include "TSortTable.h"
#include "TTreeNode.h"
#include "TTreeTable.h"
#include "TBalanceNode.h"
#include "TBalanceTree.h"

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
// TODO: All comparison methods return const value than cannot be changed
TEST(TabRecord, DISABLED_Can_Compare_Not_Equal_Table_Records_Using_More)
{
    TKey str("b"), str1("ab");
    TTabRecord tableRecord1(str1), tableRecord2(str);

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
    // TODO: Check expectedKey again
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

TEST(TreeTable, DISABLED_Is_Full_Returns_True)
{
    TTreeTable treeTable;

    EXPECT_TRUE(treeTable.IsFull());
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

TEST(TreeTable, DISABLED_Throw_When_Trying_To_Insert_Record_Into_Full_Table)
{
    // TODO:
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
    // TODO: treeTable.GetKey() should be "qwerty"
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

TEST(BalanceTree, DISABLED_Throw_When_Trying_To_Insert_Record_Into_Full_Balance_Tree)
{
    TBalanceTree balanceTree;
    // TODO: How to make balance tree full?
    for (int i = 0; i < 25; i++)
    {
        balanceTree.InsertRecord(to_string(i), nullptr);
    }

    ASSERT_ANY_THROW(balanceTree.InsertRecord("abc", nullptr));
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
