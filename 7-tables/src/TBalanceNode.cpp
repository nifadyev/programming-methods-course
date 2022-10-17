#include "TBalanceNode.h"

TDataValue* TBalanceNode::GetCopy()
{
    if (pValue != nullptr)
    {
        return (pTDataValue)(new TBalanceNode(key, pValue->GetCopy(), nullptr, nullptr, balanceIndex));
    }
    else
    {
        return (pTDataValue)(new TBalanceNode(key, nullptr, nullptr, nullptr, balanceIndex));
    }
}

int TBalanceNode::GetBalance(void) const
{
    return balanceIndex;
}

void TBalanceNode::SetBalance(const int& balance)
{
    if (balance != BALANCE_LEFT && balance != BALANCE_OK && balance != BALANCE_RIGHT)
    {
        throw invalid_argument("Error! The balance value must be -1, 0 or 1");
    }

    balanceIndex = balance;
}
