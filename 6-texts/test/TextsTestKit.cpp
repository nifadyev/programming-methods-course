#include <gtest/gtest.h>
#include "TTextLink.h"
#include "TText.h"
#include "TTextViewer.h"

/*-------------------------------Testing_TextLink_class-------------------------------*/
TEST(TextLink, Can_Create_TextLink_Without_Parameters)
{
    TextLink::InitMemorySystem();
    TextLink textLink;

    ASSERT_NO_THROW(TextLink textLink);
    EXPECT_EQ(textLink.GetDown(), nullptr);
    EXPECT_EQ(textLink.GetNext(), nullptr);
    EXPECT_TRUE(textLink.IsAtomic());
}

TEST(TextLink, Can_Create_TextLink_With_First_Parameter)
{
    TString string = "qwerty";
    TextLink textLink;

    ASSERT_NO_THROW(TextLink textLink(string));
}

TEST(TextLink, Can_Create_TextLink_With_Second_Parameter)
{
    TString string = "qwerty", emptyString = "";
    pTextLink textLinkNext = new TextLink(string);
    TextLink textLink(emptyString, textLinkNext);

    EXPECT_EQ(textLink.GetDown(), nullptr);
    EXPECT_EQ(textLink.GetNext(), textLinkNext);
}

TEST(TextLink, Can_Create_TextLink_With_Third_Parameter)
{
    TString string = "qwerty", emptyString = "";
    pTextLink textLinkDown = new TextLink(string);
    TextLink textLink(emptyString, nullptr, textLinkDown);

    EXPECT_EQ(textLink.GetNext(), nullptr);
    EXPECT_EQ(textLink.GetDown(), textLinkDown);
}

TEST(TextLink, Can_Create_TextLink_With_All_Parameters)
{
    TString string = "qwerty", emptyString = "";
    pTextLink textLinkNext = new TextLink(string);
    pTextLink textLinkDown = new TextLink(string);
    TextLink textLink(emptyString, textLinkNext, textLinkDown);

    EXPECT_EQ(textLink.GetNext(), textLinkNext);
    EXPECT_EQ(textLink.GetDown(), textLinkDown);
}

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

TEST(TextLink, Can_Create_Text_Link_Using_Operator_New)
{
    TextLink::InitMemorySystem();
    TextLink *textLink;

    ASSERT_NO_THROW(textLink = new TextLink[24]);
}

/*-------------------------------Testing_TText_class-------------------------------*/

TEST(Text, Can_Create_Empty_Text)
{
    ASSERT_NO_THROW(Text text);
}

TEST(Text, Can_Create_Text_From_Text_Link)
{
    TString string = "wasd";
    pTextLink link = new TextLink(string);

    ASSERT_NO_THROW(Text text(link));
}

TEST(Text, Can_Go_To_The_First_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "1";

    text.InsertNextLine("1");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoFirstLink());
}

TEST(Text, Throw_When_Trying_To_Go_To_The_First_Link_In_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    EXPECT_EQ(text.GoFirstLink(), -1);
}

TEST(Text, Can_Go_Down_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "1.1";

    text.InsertDownLine("1.1");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoDownLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Down_Link_Returns_0_If_Success)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertDownLine("1.1");
    text.GoFirstLink();

    EXPECT_EQ(text.GoDownLink(), 0);
}

TEST(Text, Throws_If_Go_Down_Link_With_Empty_Current_Link)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.GoDownLink(), logic_error);
}

TEST(Text, Can_Go_Next_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "2";

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.GoNextLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Next_Link_Returns_0_If_Success)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    text.GoFirstLink();

    EXPECT_EQ(text.GoNextLink(), 0);
}

TEST(Text, Throws_If_Go_Next_Link_With_Empty_Current_Link)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.GoNextLink(), logic_error);
}

TEST(Text, Can_Go_Previous_Link)
{
    TextLink::InitMemorySystem();
    Text text;
    string expectedString = "";

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    text.GoFirstLink();
    text.GoNextLink();

    ASSERT_NO_THROW(text.GoPreviousLink());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Go_Previous_Link_Returns_0_If_Success)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    
    text.GoFirstLink();
    text.GoNextLink();

    EXPECT_EQ(text.GoPreviousLink(), 0);
}

TEST(Text, Throws_If_Go_Next_Link_In_Highest_Level)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.GoFirstLink();

    ASSERT_THROW(text.GoPreviousLink(), logic_error);
}

TEST(Text, Throws_If_Go_Previous_Link_With_Empty_Current_Link)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.GoNextLink(), logic_error);
}

TEST(Text, Can_Insert_Down_Line_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "example";

    ASSERT_NO_THROW(text.InsertDownLine("example"));

    text.GoDownLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Muptiple_Down_Line)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "1.1.1";

    text.InsertDownLine("1");
    text.InsertDownLine("1.1");
    text.InsertDownLine("1.1.1");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Down_Line_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "1.0";

    text.InsertDownLine("1");
    text.GoFirstLink();
    text.InsertDownLine("1.0");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Line_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_NO_THROW(text.InsertNextLine("A"));

    text.GoNextLink();
    EXPECT_EQ(text.GetLine(), "A");
}

TEST(Text, Can_Insert_Muptiple_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "15";

    text.InsertNextLine("13");
    text.InsertNextLine("14");
    text.InsertNextLine("15");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Line_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "A";

    text.InsertNextLine("A");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Down_Section_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "0.1";

    ASSERT_NO_THROW(text.InsertDownSection("0.1"));

    text.GoDownLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Muptiple_Down_Sections)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "0.1.1";

    text.InsertDownSection("0");
    text.InsertDownSection("0.1");
    text.InsertDownSection("0.1.1");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Down_Section_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "0.0";

    text.InsertNextLine("0");
    text.GoFirstLink();
    text.InsertDownSection("0.0");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Section_Into_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "A";

    ASSERT_NO_THROW(text.InsertNextSection("A"));

    text.GoNextLink();
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Muptiple_Next_Sections)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "15";

    text.InsertNextSection("13");
    text.InsertNextSection("14");
    text.InsertNextSection("15");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Insert_Next_Section_Into_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "3";

    text.InsertNextLine("2");
    text.InsertNextSection("3");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Throw_When_Delete_Down_Line_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteDownLine(), logic_error);
}

TEST(Text, Throw_When_Delete_Down_Line_Text_Without_Down_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("A");

    ASSERT_ANY_THROW(text.DeleteDownLine());
}

TEST(Text, Can_Delete_Down_Line_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertDownLine("1.1");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.DeleteDownLine());
}

TEST(Text, Throw_When_Delete_Next_Line_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextLine(), logic_error);
}

TEST(Text, Throw_When_Delete_Next_Line_From_Text_Without_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextLine(), logic_error);
}

TEST(Text, Can_Delete_Next_Line_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextLine("QWERTY");

    ASSERT_NO_THROW(text.DeleteNextLine());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Delete_Muptiple_Next_Lines)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextLine("Q");
    text.InsertNextLine("W");
    text.InsertNextLine("E");

    ASSERT_NO_THROW(text.DeleteNextLine());
    ASSERT_NO_THROW(text.DeleteNextLine());
    ASSERT_NO_THROW(text.DeleteNextLine());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Throw_When_Delete_Down_Section_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteDownSection(), logic_error);
}

TEST(Text, Throw_When_Delete_Down_Section_Text_Without_Down_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("A");

    ASSERT_ANY_THROW(text.DeleteDownSection());
}

TEST(Text, Can_Delete_Down_Section_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertDownSection("1.1");
    text.GoFirstLink();

    ASSERT_NO_THROW(text.DeleteDownSection());
}

TEST(Text, Throw_When_Delete_Next_Sections_From_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextSection(), logic_error);
}

TEST(Text, Throw_When_Delete_Next_Section_From_Text_Without_Next_Line)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.DeleteNextSection(), logic_error);
}

TEST(Text, Can_Delete_Next_Section_From_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextSection("QWERTY");

    ASSERT_NO_THROW(text.DeleteNextSection());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Delete_Muptiple_Next_Sections)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    text.InsertNextSection("Q");
    text.InsertNextSection("W");
    text.InsertNextSection("E");

    ASSERT_NO_THROW(text.DeleteNextSection());
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Can_Reset_Text)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    text.InsertNextLine("3");

    ASSERT_NO_THROW(text.Reset());
    EXPECT_EQ(text.Reset(), 0);
}

TEST(Text, Can_Reset_Empty_Text)
{
    TextLink::InitMemorySystem();
    Text text;
    TString expectedString = "";

    ASSERT_NO_THROW(text.Reset());
    EXPECT_EQ(text.Reset(), 0);
    EXPECT_EQ(text.GetLine(), expectedString);
}

TEST(Text, Is_Text_Ended_Returns_True)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.GoNext();

    ASSERT_NO_THROW(text.IsTextEnded());
    EXPECT_TRUE(text.IsTextEnded());
}

TEST(Text, Is_Text_Ended_Returns_False)
{
    TextLink::InitMemorySystem();
    Text text;

    text.InsertNextLine("1");
    text.InsertNextLine("2");
    text.Reset();

    ASSERT_NO_THROW(text.IsTextEnded());
    EXPECT_FALSE(text.IsTextEnded());
}

TEST(Text, Can_Go_Next)
{
    TextLink::InitMemorySystem();
    TString a = "1", expectedString = "2";
    Text txt(new TextLink(a));

    txt.GoFirstLink();
    txt.InsertNextLine("2");
    txt.GoNextLink();
    txt.InsertNextLine("3");
    txt.GoNextLink();
    txt.Reset();
    txt.GoNext();

    EXPECT_EQ(txt.GetLine(), expectedString);
}

TEST(Text, Throw_If_Trying_To_Read_From_Non_Existing_File)
{
    TextLink::InitMemorySystem();
    Text text;

    ASSERT_THROW(text.Read("nput.txt"), invalid_argument);
}

TEST(Text, Can_Write_Text_To_File)
{
    TextLink::InitMemorySystem();
    Text text;

    text.SetLine("A");
    text.InsertDownLine("a");

    ASSERT_NO_THROW(text.Write("output.txt"));
}

TEST(Text, Can_Get_Copy)
{
    TextLink::InitMemorySystem();
    Text text;
    pText copiedText = nullptr;

    text.SetLine("A");
    text.InsertDownLine("a");
    text.InsertDownLine("b");
    text.InsertDownLine("c");
    text.InsertNextLine("B");

    ASSERT_NO_THROW(copiedText = text.GetCopy());
}
