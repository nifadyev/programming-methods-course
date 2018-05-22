#ifndef STUDENT_ACHIEVEMENTS_INCLUDE_STUDENT_ACHIEVEMENTS_H
#define STUDENT_ACHIEVEMENTS_INCLUDE_STUDENT_ACHIEVEMENTS_H

#include <fstream>
#include <vector>
#include <string>
#include "StudentInfo.h"
#include "TTable.h"

template <class Table>
class StudentAchievements
{
 private:
    vector<TTable *> tables;
    int groupNumber;

    int GetGroupNumber()
    {
        ifstream file;
        int result = 0;

        for (int i = 1;; i++)
        {
            file.open(GetFileName(i));
            if (file.is_open())
            {
                result++;
                file.close();
            }
            else
            {
                return result;
            }
        }
    }

    void LoadStudentsProgress()
    {
        ifstream file;

        for (int i = 1; i <= groupNumber; i++)
        {
            TTable *tempTable = new Table();
            file.open(GetFileName(i));
            while (!file.eof())
            {
                string name;
                int math, aads, os, english, mno;

                file >> name;
                file >> math >> aads >> os >> english >> mno;
                tempTable->InsertRecord(name, new StudentInfo(math, aads, os, english, mno));
            }

            tempTable->Reset();
            tables.push_back(tempTable);
            file.close();
        }
    }

    string GetFileName(int groupID)
    {
        // TODO: Change when is'll be ready to pull
        string filename = "students/group";
        filename += '0' + groupID;
        filename += ".txt";

        return filename;
    }

 public:
    StudentAchievements()
    {
        groupNumber = GetGroupNumber();
        LoadStudentsProgress();
    }

    // Student marks
    StudentInfo *GetStudentInfo(TKey studentName)
    {
        for (auto /* TTable */ i = tables.begin(); i != tables.end(); i++)
        {
            try
            {
                (*i)->FindRecord(studentName);
                return (StudentInfo*)((*i)->FindRecord(studentName));
            }
            catch (...)
            {
                return 0;
            }
            
        }
    }

    // Student mark
    int GetStudentMark(TKey studentName, int course)
    {
        if (course < 0 || course > NUMBER_OF_MARKS)
        {
            throw invalid_argument("Error! Cannot get mark on unexisting course");
        }

        return GetStudentInfo(studentName)->marks[course];
    }

    // Average student mark on on all courses
    double CalculateStudentAverageMark(TKey studentName)
    {
        if (!GetStudentInfo(studentName))
        {
            throw;
        }

        StudentInfo *info = GetStudentInfo(studentName);
        double result = 0;

        for (int i = 0; i < NUMBER_OF_MARKS; i++)
        {
            result += info->marks[i];
        }

        return result / NUMBER_OF_MARKS;
    }

    // Average student mark among all students of all groups
    double CalculateAverageMark(int course = -1)
    {
        double result = 0;
        double count = 0;

        for (int i = 0; i < groupNumber; i++)
        {
            result += CalculateAverageGroupMark(i, course);
            count++;
        }

        return result / count;
    }

    // Average mark among students of concrete group
    // If course != -1 then calculate on concrete course
    double CalculateAverageGroupMark(int group, int course = -1)
    {
        double result = 0;
        double count = 0;
        TTable *table = tables[group];
        table->Reset();
        
        while (!table->IsTableEnded())
        {
            StudentInfo *info = (StudentInfo *)(table->GetValuePTR());

            if (info)
            {
                for (int i = 0; i < NUMBER_OF_MARKS; i++)
                {
                    if (course == -1 || course == i)
                    {
                        result += info->marks[i];
                        count++;
                    }
                }

                table->GoNext();
            }
        }

        return result / count;
    }

    // Get group ID with best achievements on concrete course or on all courses
    int GetGroupIDWithBestMarks(int course = -1)
    {
        double max = 0;
        int bestGroup = -1;

        for (int i = 0; i < groupNumber; i++)
        {
            double mark = CalculateAverageGroupMark(i, course);
            if (mark > max)
            {
                max = mark;
                bestGroup = 1;
            }
        }

        return ++bestGroup; // Group numeration starts from 1
    }

    // Group numeration starts from 1 that's why if group = 0 =>
    // Calculate number of students with perfect marks in all groups
    int GetExcellentStudentsNumber(int group = 0)
    {
        int result = 0;

        for (int i = 0; i < groupNumber; i++)
        {
            if (group == 0 || group == (i + 1))
            {
                TTable *table = tables[i];
                table->Reset();

                while (!table->IsTableEnded())
                {
                    int markSum = 0;
                    StudentInfo *info = (StudentInfo *)table->GetValuePTR();
                    if (info != 0)
                    {
                        for (int j = 0; j < NUMBER_OF_MARKS; j++)
                        {
                            markSum += info->marks[i];
                        }
                    }

                    // if every mark is five
                    if (markSum == NUMBER_OF_MARKS * 5)
                    {
                        result++;
                    }
                    table->GoNext();
                }
            }
        }

        return result;
    }
};

#endif // STUDENT_ACHIEVEMENTS_INCLUDE_STUDENT_ACHIEVEMENTS_H
