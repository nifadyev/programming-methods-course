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
	TString string = "asfgsdgsdg";
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
