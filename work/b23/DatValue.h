#ifndef TDATAVALUE
#define TDATAVALUE
class TDataValue
{
public:
	virtual TDataValue* GetCopy() const = 0;
	~TDataValue() {}
};

typedef TDataValue *pTDataValue;
#endif