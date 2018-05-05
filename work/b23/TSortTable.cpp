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
            QuickSort(pRecords, dataCount);
            break;
        default:
            throw runtime_error("Error! Sort method is not mentioned");
    }
}

void TSortTable::InsertSort(pTTabRecord *pMemory, int dataCount)
{
    for (int i = 0; i < dataCount; i++)
    {
        //TODO: try using for instead of while
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

void TSortTable::MergeSorter(pTTabRecord *& pData, int left, int right)
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

void TSortTable::MergeData(pTTabRecord *& pData,int left,int middle, int right)
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

void TSortTable::QuickSort(pTTabRecord * pMemory, int left, int right)
{
    if (left < right)
    {
        int temp = QuickSplit(pRecords, left, right);
        QuickSort(pRecords, left, temp - 1);
        QuickSort(pRecords, temp, right);
    }
}

int TSortTable::QuickSplit(pTTabRecord * pData, int left, int right)
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
        // Could be incorrect
        pRecords[i] = new TTabRecord(table.pRecords[i]->GetKey(), table.pRecords[i]->GetValuePTR());
    }
    sortMethod = INSERT_SORT;
    SortData();
    Reset();
}

TSortTable & TSortTable::operator=(const TScanTable & table)
{
    // TODO: �������� ����� �������� return
}

TSortMethod TSortTable::GetSortMethod(void)
{
    return TSortMethod();
}

void TSortTable::SetSortMethod(TSortMethod srtMethod)
{
}

pTDataValue TSortTable::FindRecord(TKey key)
{
    return pTDataValue();
}

void TSortTable::InsertRecord(TKey key, pTDataValue value)
{
}

void TSortTable::DeleteRecord(TKey key)
{
}
