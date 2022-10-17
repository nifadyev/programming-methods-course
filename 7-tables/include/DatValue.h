#ifndef TDAT_VALUE_INCLUDE_TDAT_VALUE_H
#define TDAT_VALUE_INCLUDE_TDAT_VALUE_H

class TDataValue
{
 public:
    ~TDataValue() {}
    virtual TDataValue* GetCopy() = 0;
};
typedef TDataValue *pTDataValue;

#endif  // TDAT_VALUE_INCLUDE_TDAT_VALUE_H
