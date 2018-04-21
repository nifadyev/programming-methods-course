// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <gtest/gtest.h>
#include"TTextLink.h"
#include "TText.h"
#include "TTextViewer.h"

/*-------------------------------Testing_TextLink_class-------------------------------*/
TEST(TextLink, Can_Create_TextLink_Without_Parameters)
{
	TextLink textLink;

	ASSERT_NO_THROW(TextLink textLink);
	EXPECT_EQ(textLink.GetDown(), nullptr);
	EXPECT_EQ(textLink.GetNext(), nullptr);
	EXPECT_TRUE(textLink.IsAtomic());
}

TEST(TextLink, Can_Create_TextLink_With_First_Parameter)
{
	TString string = "safhtrhrgafasf";
	TextLink textLink;

	ASSERT_NO_THROW(TextLink textLink(string));
	EXPECT_EQ(textLink.GetDown(), nullptr);
	EXPECT_EQ(textLink.GetNext(), nullptr);
	EXPECT_TRUE(textLink.IsAtomic());
}

//TODO: make tests for standard constructor in TextLink with 2,3 and all params
TEST(TextLink, DISABLED_Can_Create_TextLink_With_Second_Parameter)
{}

TEST(TextLink, DISABLED_Can_Create_TextLink_With_Third_Parameter)
{}

TEST(TextLink, DISABLED_Can_Create_TextLink_With_All_Parameters)
{}

TEST(TextLink, Can_Initialaze_Memory_System_Without_Parameters)
{
	TextLink textLink;
	ASSERT_NO_THROW(textLink.InitMemorySystem());
}

TEST(TextLink, Throw_When_Initialazing_Memory_System_With_Neagative_Parameter)
{
	TextLink textLink;

	ASSERT_THROW(textLink.InitMemorySystem(-12), logic_error);
}

TEST(TextLink, Can_Initialaze_Memory_System_With_Parameters)
{
	TextLink textLink;

	ASSERT_NO_THROW(textLink.InitMemorySystem(698));
	ASSERT_NO_THROW(textLink.InitMemorySystem(2));
	ASSERT_NO_THROW(textLink.InitMemorySystem(47));
	ASSERT_NO_THROW(textLink.InitMemorySystem(2351));
}

TEST(TextLink, Can_Print_Free_Links_If_There_Are_No_One)
{
	//TString string = "asfgsdgsdg";
	TextLink textLink;
	textLink.InitMemorySystem(4);
	ASSERT_NO_THROW(textLink.PrintFreeLinks());
}

TEST(TextLink, Can_Create_Text_Using_Operator_New)
{
	TextLink *textLink; 
	ASSERT_NO_THROW(textLink = new TextLink[24]);
	textLink = new TextLink[24];
	//textLink->InitMemorySystem(24);
	TString string1 = "sfsdgdgsd", string2 = "hjkhjk";
	TextLink textLink1(string1), textLink2(string2);
	textLink[0] = textLink1;
	textLink[1] = textLink2;
	textLink->PrintFreeLinks();
}

TEST(TextLink, Can_Create_Text_With_One_String_Using_Operator_New)
{
	TextLink *textLink;
	ASSERT_NO_THROW(textLink = new TextLink[0]);
}

/*-------------------------------Testing_TText_class-------------------------------*/

TEST(Text, Can_Create_Empty_Text)
{
    ASSERT_NO_THROW(Text text);
}

TEST(Text, Can_Create_Text_From_Text_Link)
{
    TString string = "qwrprhqwirqwr";
    pTextLink link = new TextLink(string);

    ASSERT_NO_THROW(Text text(link));
    //EXPECT_EQ(text.GetLine(), string);
}

TEST(Text, Can_Read_Text_From_File)
{
    Text text;
    TextLink::InitMemorySystem();

    ASSERT_NO_THROW(text.Read("input.txt"));
    //text.Read("input.txt");
    //text.Print();
}

TEST(Text, Can_Print_Text/*Can_Print_Text_Read_From_File*/)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");

    ASSERT_NO_THROW(text.Print());
}

TEST(Text, Can_Go_To_The_First_Link)
{
    Text text;
    string expectedString = "1";
    
    TextLink::InitMemorySystem();
    text.Read("input.txt");

    ASSERT_NO_THROW(text.GoFirstLink());

    text.GoFirstLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_To_The_First_Link_Returns_0_If_Everything_Is_Correct)
{
    Text text;

    TextLink::InitMemorySystem();
    text.Read("input.txt");

    EXPECT_EQ(text.GoFirstLink(), 0);
}

TEST(Text, Throw_When_Trying_To_Go_To_The_First_Link_In_Empty_Text)
{
    Text text;

    TextLink::InitMemorySystem();

    EXPECT_EQ(text.GoFirstLink(), -1);

}

TEST(Text, Can_Go_Down_Link)
{
    Text text;
    string expectedString = "1.1";
    TextLink::InitMemorySystem();
    
    text.Read("input.txt");
    //text.Reset();
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoDownLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Down_Link_Returns_0_If_Success)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    text.GoFirstLink();

    EXPECT_EQ(text.GoDownLink(), 0);
}


TEST(Text, Throws_If_Go_Down_Link_In_Lowest_Level)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");

    ASSERT_THROW(text.GoDownLink(), logic_error);
}

TEST(Text, Throws_If_Go_Down_Link_With_Empty_Current_Link)
{
    Text text;
    TextLink::InitMemorySystem();

    ASSERT_THROW(text.GoDownLink(), logic_error);
}

TEST(Text, Can_Go_Next_Link)
{
    Text text;
    string expectedString = "2";
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    //text.Reset();
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoNextLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Next_Link_Returns_0_If_Success)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    text.GoFirstLink();

    EXPECT_EQ(text.GoNextLink(), 0);
}

TEST(Text, Throws_If_Go_Next_Link_In_Lowest_Level)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");

    ASSERT_THROW(text.GoNextLink(), logic_error);
}

TEST(Text, Throws_If_Go_Next_Link_With_Empty_Current_Link)
{
    Text text;
    TextLink::InitMemorySystem();

    ASSERT_THROW(text.GoNextLink(), logic_error);
}

TEST(Text, Can_Go_Previous_Link)
{
    Text text;
    string expectedString = "1";
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    //text.Reset();
    text.GoFirstLink();
    text.GoNextLink();

    ASSERT_NO_THROW(text.GoPreviousLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Previous_Link_Returns_0_If_Success)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    text.GoFirstLink();
    text.GoNextLink();

    EXPECT_EQ(text.GoPreviousLink(), 0);
}

TEST(Text, Throws_If_Go_Next_Link_In_Highest_Level)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    text.GoFirstLink();

    ASSERT_THROW(text.GoPreviousLink(), logic_error);
}

TEST(Text, Throws_If_Go_Previous_Link_With_Empty_Current_Link)
{
    Text text;
    TextLink::InitMemorySystem();

    ASSERT_THROW(text.GoNextLink(), logic_error);
}


TEST(Text, Can_Insert_Down_Line_Into_Empty_Text)
{
    Text text;
    TextLink::InitMemorySystem();

    //text.Read("input.txt");

    ASSERT_NO_THROW(text.InsertDownLine("2.2.1"));
    text.GoDownLink();
    EXPECT_EQ(text.GetLine(), "2.2.1");
}

TEST(Text, DISABLED_Throw_When_Insert_Down_Line_With_Empty_Current_Link)
{
    Text text;
    TextLink::InitMemorySystem();

    //text.Read("input.txt");

    ASSERT_ANY_THROW(text.InsertDownLine("2.2.1"));
    //EXPECT_EQ(text.GetLine(), "2.2.1");
}

TEST(Text, Can_Insert_Muptiple_Down_Line)
{
    Text text;
    TextLink::InitMemorySystem();

    text.InsertDownLine("2");
    text.InsertDownLine("2.1");
    text.InsertDownLine("2.1.1");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), "2.1.1");
}

TEST(Text, Can_Insert_Down_Line_Into_Text)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    text.GoFirstLink();
    text.InsertDownLine("1.0");
    text.GoDownLink();
    EXPECT_EQ(text.GetLine(), "1.0");
}

TEST(Text, Can_Insert_Next_Line_Into_Empty_Text)
{
    Text text;
    TextLink::InitMemorySystem();

    //text.Read("input.txt");

    ASSERT_NO_THROW(text.InsertNextLine("A"));
    text.GoNextLink();
    EXPECT_EQ(text.GetLine(), "A");
}

TEST(Text, DISABLED_Throw_When_Insert_Next_Line_With_Empty_Current_Link)
{
    Text text;
    TextLink::InitMemorySystem();

    //text.Read("input.txt");
    
    ASSERT_ANY_THROW(text.InsertNextLine("A"));
    //EXPECT_EQ(text.GetLine(), "2.2.1");
}

TEST(Text, Can_Insert_Muptiple_Next_Line)
{
    Text text;
    TextLink::InitMemorySystem();

    text.InsertNextLine("13");
    text.InsertNextLine("14");
    text.InsertNextLine("15");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), "15");
}

TEST(Text, Can_Insert_Next_Line_Into_Text)
{
    Text text;
    TextLink::InitMemorySystem();

    text.Read("input.txt");
    //text.GoFirstLink();
    text.InsertNextLine("3");
    text.GoNextLink();
    EXPECT_EQ(text.GetLine(), "3");
}

//TODO: Add tests for deletes