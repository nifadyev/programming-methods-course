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
	textLink.InitMemorySystem(47);
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
	textLink[2] = textLink1;
	textLink[1] = textLink2;
	textLink->PrintFreeLinks();
}

TEST(TextLink, Can_Create_Text_With_One_String_Using_Operator_New)
{
	TextLink *textLink;
	ASSERT_NO_THROW(textLink = new TextLink[0]);
}
