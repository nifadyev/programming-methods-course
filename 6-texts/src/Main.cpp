#include <iostream>
#include "TText.h"
using namespace std;

int main()
{
    TextLink::InitMemorySystem();
    Text text;
    pText pCopiedText = nullptr;

    text.SetLine("A");
    text.InsertDownLine("c");
    text.InsertDownLine("b");
    text.InsertDownLine("a");
    text.InsertDownSection("a");
    text.GoFirstLink(); 
    text.InsertNextLine("B");
    text.GoNextLink();
    text.InsertDownLine("c");
    text.InsertDownLine("b");
    text.InsertDownLine("a");
    text.InsertNextLine("D");
    text.InsertNextLine("C");

    pCopiedText = text.GetCopy();

    text.Reset();
    text.GoNextLink();
    text.DeleteDownSection();
    text.DeleteNextLine();

    text.Write("output.txt");


    text.Print();

    return 0;
}