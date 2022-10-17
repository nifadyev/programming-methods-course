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

int main()
{
    StudentAchievements<TScanTable> table;
    cout << "-----------------------Group 1-----------------------\n"; 
    cout << "Number of students with excellent marks in group 1: " << table.GetExcellentStudentsNumber(0) << endl;
    cout << "Average group mark: " << table.CalculateAverageGroupMark(0) << endl;

cout << "/n-----------------------Group 2-----------------------\n"; 
    cout << "Number of students with excellent marks in group: " << table.GetExcellentStudentsNumber(1) << endl;
    cout << "Average group mark: " << table.CalculateAverageGroupMark(1) << endl;
    
    cout << "/n-----------------------Additional information-----------------------\n"; 
    cout << "Average mark on Math: " << table.CalculateAverageMark(0) << endl;
    cout << "Average mark on AaDS: " << table.CalculateAverageMark(1) << endl;
    cout << "Average mark on OS: " << table.CalculateAverageMark(2) << endl;
    cout << "Average mark on English: " << table.CalculateAverageMark(3) << endl;
    cout << "Average mark on MNO: " << table.CalculateAverageMark(4) << endl;
    
    cout << "\nBest group (based on average mark among students): " << table.GetGroupIDWithBestMarks(0) << endl;
    
    return 0;
}
