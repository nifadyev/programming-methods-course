// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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