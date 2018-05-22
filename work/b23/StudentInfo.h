#ifndef STUDENT_INFO_INCLUDE_STUDENT_INFO_H
#define STUDENT_INFO_INCLUDE_STUDENT_INFO_H

#include "DatValue.h"
static const int NUMBER_OF_MARKS = 5;

class StudentInfo : public TDataValue
{
 private:
    enum
    {
        MATH,
        AaDS,
        OS,
        ENGLISH,
        MNO
    };

 public:
    int marks[NUMBER_OF_MARKS];

    StudentInfo(int math = 4, int aads = 4, int os = 4, int english = 4, int mno = 4)
    {
        if (math < 0 || math > 5 || aads < 0 || aads > 5 || os < 0 || os > 5 || english < 0 || english > 5 || mno < 0 || mno > 5)
        {
            throw invalid_argument("Error! Marks should be more than 0 and less than 6");
        }

        marks[MATH] = math;
        marks[AaDS] = aads;
        marks[OS] = os;
        marks[ENGLISH] = english;
        marks[MNO] = mno;
    }

    TDataValue *GetCopy()
    {
        return new StudentInfo(marks[MATH], marks[AaDS], marks[OS], marks[ENGLISH], marks[MNO]);
    }

    int GetMark(int course)
    {
        return marks[course];
    }
};

#endif // STUDENT_INFO_INCLUDE_STUDENT_INFO_H
