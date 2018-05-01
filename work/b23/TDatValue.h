#ifndef TDATA_VALUE_INCLUDE_TDATA_VALUE_H
#define TDATA_VALUE_INCLUDE_TDATA_VALUE_H


class TDataValue
{
public:
    ~TDataValue() {}
    virtual TDataValue* GetCopy() = 0;
    ~TDataValue() {}
};
typedef TDataValue *pTDataValue;

#endif // TDATA_VALUE_INCLUDE_TDATA_VALUE_H