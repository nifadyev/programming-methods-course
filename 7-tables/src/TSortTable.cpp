#include "TSortTable.h"

void TSortTable::SortData(void)
{
    switch (sortMethod)
    {
    case INSERT_SORT:
        InsertSort(pRecords, dataCount);
        break;
    case MERGE_SORT:
        MergeSort(pRecords, dataCount);
        break;
    case QUICK_SORT:
        QuickSort(pRecords, 0, dataCount - 1);
        break;
    default:
        throw runtime_error("Error! Sort method is not mentioned");
    }
}

void TSortTable::InsertSort(pTTabRecord *pMemory, int dataCount)
{
    for (int i = 0; i < dataCount; i++)
    {
        int j = i;
        pTTabRecord temp = pRecords[i];

        while (j > 0 && (temp->GetKey() < pRecords[i]->GetKey()))
        {
            pRecords[i] = pRecords[i - 1];
            j--;
        }
        pRecords[j] = temp;
    }
}

void TSortTable::MergeSort(pTTabRecord *pMemory, int dataCount)
{
    MergeSorter(pRecords, 0, dataCount - 1);
}

void TSortTable::MergeSorter(pTTabRecord *&pData, int left, int right)
{
    if (left == right)
    {
        return;
    }

    int middle = (right + left) / 2;
    MergeSorter(pData, left, middle);
    MergeSorter(pData, middle + 1, right);
    MergeData(pData, left, middle, right);
}

void TSortTable::MergeData(pTTabRecord *&pData, int left, int middle, int right)
{
    pTTabRecord *pBuffer = new pTTabRecord[right - left + 1];
    int i = left, j = middle + 1, k = 0;

    while (i <= middle && j <= right)
    {
        if (pData[i]->GetKey() < pData[j]->GetKey())
        {
            pBuffer[k++] = pData[i++];
        }
        else
        {
            pBuffer[k++] = pData[j++];
        }
    }

    if (i > middle)
    {
        while (j <= right)
        {
            pBuffer[k++] = pData[j++];
        }
    }
    else
    {
        while (i <= middle)
        {
            pBuffer[k++] = pData[i++];
        }
    }

    k = 0;
    for (i = left; i <= right; i++)
    {
        pData[i] = pBuffer[k++];
    }

    delete[] pBuffer;
}

void TSortTable::QuickSort(pTTabRecord *pMemory, int left, int right)
{
    if (left < right)
    {
        int temp = QuickSplit(pRecords, left, right);
        QuickSort(pRecords, left, temp - 1);
        QuickSort(pRecords, temp, right);
    }
}

int TSortTable::QuickSplit(pTTabRecord *pData, int left, int right)
{
    TKey pivot = pRecords[(left + right) / 2]->GetKey();
    int i = left, j = right;

    while (i <= j)
    {
        while (pRecords[i]->GetKey() < pivot)
        {
            i++;
        }
        while (pRecords[i]->GetKey() > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            pTTabRecord temp = pRecords[i];
            pRecords[i] = pRecords[j];
            pRecords[j] = temp;
            i++;
            j--;
        }
    }

    return i;
}

TSortTable::TSortTable(const TScanTable &table) : TScanTable(table.GetTableSize())
{
    dataCount = table.dataCount;
    for (int i = 0; i < dataCount; i++)
    {
        pRecords[i] = new TTabRecord(table.pRecords[i]->GetKey(), table.pRecords[i]->GetValuePTR());
    }

    sortMethod = INSERT_SORT;
    SortData();
    Reset();
}

TSortTable &TSortTable::operator=(const TScanTable &table)
{
    if (this != &table)
    {
        if (pRecords != nullptr)
        {
            for (int i = 0; i < maxTableSize; ++i)
            {
                if (pRecords[i] != nullptr)
                {
                    if (pRecords[i]->pValue != nullptr)
                    {
                        delete pRecords[i]->pValue;
                    }
                    delete pRecords[i];
                }
            }

            delete[] pRecords;
        }

        maxTableSize = table.maxTableSize;
        dataCount = table.dataCount;
        pRecords = new pTTabRecord[maxTableSize];
        for (int i = 0; i < maxTableSize; ++i)
        {
            if (table.pRecords[i] != nullptr)
            {
                pRecords[i] = new TTabRecord(table.pRecords[i]->GetKey(), table.pRecords[i]->GetValuePTR());
            }
            else
            {
                pRecords[i] = nullptr;
            }
        }

        SortData();
        Reset();
    }

    return *this;
}

TSortMethod TSortTable::GetSortMethod(void)
{
    return sortMethod;
}

void TSortTable::SetSortMethod(TSortMethod srtMethod)
{
    if (srtMethod != INSERT_SORT && srtMethod != MERGE_SORT && srtMethod != QUICK_SORT)
    {
        throw invalid_argument("Error! Chosed sort method is not supported");
    }

    sortMethod = srtMethod;
}

pTDataValue TSortTable::FindRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot find record in empty table");
    }

    Reset();
    efficiency = 0;
    int left = 0, right = dataCount;

    while ((right - left) > 0)
    {
        efficiency++;
        int middle = left + (right - left) / 2;
        if (pRecords[middle]->GetKey() == key)
        {
            currentPosition = middle;
            return pRecords[middle]->GetValuePTR();
        }

        if (pRecords[middle]->GetKey() > key)
        {
            right = middle;
        }
        else
        {
            left = middle + 1;
        }
    }

    currentPosition = right;

    throw runtime_error("Error! There is no record with such key");
}

void TSortTable::InsertRecord(TKey key, pTDataValue value)
{
    if (IsFull())
    {
        throw logic_error("Error! Cannot insert record into full table");
    }

    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        for (int i = dataCount; i > currentPosition; --i)
        {
            pRecords[i] = pRecords[i - 1];
        }
        pRecords[currentPosition] = new TTabRecord(key, value);
        dataCount++;
        return;
    }

    throw runtime_error("Error! Record with such data has already existed");
}

void TSortTable::DeleteRecord(TKey key)
{
    if (IsEmpty())
    {
        throw logic_error("Error! Cannot delete record from empty table");
    }

    // Nonexistent key
    try
    {
        FindRecord(key);
    }
    catch (...)
    {
        throw runtime_error("Error! Record with requested key is not found");
    }

    if (pRecords[currentPosition]->pValue != nullptr)
    {
        delete pRecords[currentPosition]->pValue;
    }
    delete pRecords[currentPosition];
    pRecords[currentPosition] = nullptr;

    for (int i = currentPosition; i < dataCount - 1; ++i)
    {
        pRecords[i] = pRecords[i + 1];
    }
    
    pRecords[dataCount - 1] = nullptr;
    dataCount--;
    Reset();
}
