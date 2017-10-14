// ����, ���, ���� "������ ����������������-2", �++, ���
//
// utmatrix.h - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (21.04.2015)
//
// ����������������� ������� - ���������� �� ������ ������� �������

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // ������ �������
	int StartIndex; // ������ ������� �������� �������
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // ����������� �����������
	~TVector();
	int GetSize() { return Size; } // ������ �������
	int GetStartIndex() { return StartIndex; } // ������ ������� ��������
	ValType& operator[](int pos);             // ������
	bool operator==(const TVector &v) const;  // ���������
	bool operator!=(const TVector &v) const;  // ���������
	TVector& operator=(const TVector &v);     // ������������

	// ��������� ��������
	TVector  operator+(const ValType &val);   // ��������� ������
	TVector  operator-(const ValType &val);   // ������� ������
	TVector  operator*(const ValType &val);   // �������� �� ������

	// ��������� ��������
	TVector  operator+(const TVector &v);     // ��������
	TVector  operator-(const TVector &v);     // ���������
	ValType  operator*(const TVector &v);     // ��������� ������������

	// ����-�����
	friend istream& operator>>(istream &in, TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}

	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s < 0) || (s > MAX_VECTOR_SIZE - 1) || (si < 0))
	{
		throw "OutOfRangeException";
	}
	this->Size = s;
	this->StartIndex = si;
	this->pVector = new ValType[Size];
	for (int i = 0; i < Size; i++) // for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] = 0;
	}
}

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	this->Size = v.Size;
	this->StartIndex = v.StartIndex;
	this->pVector = new ValType[Size];
	for (int i = StartIndex; i < Size; i++) 
	{
		pVector[i] = v.pVector[i];
	}
}

template <class ValType>
TVector<ValType>::~TVector()
{
	// TODO:
	delete[] pVector;
} 

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < 0) || (pos > Size - 1) || (pos < StartIndex))
	{
		throw "OutOfRangeException";
	}
	return pVector[pos];
} 

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector &v) const
{
	// TODO: need to know should sizes and start indexes be equal or not
	if ((Size != v.Size) || (StartIndex != v.StartIndex))
	{
		return false;
	}
	for (int i = StartIndex; i < Size; i++)
	{
		if (pVector[i] != v.pVector[i])
		{
			return false;
		}
	}
	return true;
} 

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return (*this == v) ? false : true;
} 

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++) // StartIndex
	{
		if (i < StartIndex) // ������ ����� ����� ��������� ���������
		{
			pVector[i] = 0;
			continue;
		}
		pVector[i] = v.pVector[i];
	}
	return *this;
} 

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] += val;
	}
	return *this;
} 

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] -= val;
	}
	return *this;
} 

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] *= val;
	}
	return *this;
} 

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size)
	{
		throw "Sizes are not equal";
	}
	TVector result(*this);
	for (int i = StartIndex; i < Size; i++)
	{
		result.pVector[i] = pVector[i] + v.pVector[i];
	}
	return result;
} 

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size)
	{
		throw "Sizes are not equal";
	}
	TVector result(*this);
	for (int i = StartIndex; i < Size; i++)
	{
		result.pVector[i] = pVector[i] - v.pVector[i];
	}
	return result;
} 

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	int sum = 0;
	if (Size != v.Size)
	{
		throw "Sizes are not equal";
	}
	TVector result(*this);
	for (int i = StartIndex; i < Size; i++)
	{
		sum += pVector[i] * v.pVector[i];
	}
	return sum;
} 


  // ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt);                    // �����������
	TMatrix(const TVector<TVector<ValType> > &mt); // �������������� ����
	bool operator==(const TMatrix &mt) const;      // ���������
	bool operator!=(const TMatrix &mt) const;      // ���������
	TMatrix& operator= (const TMatrix &mt);        // ������������
	TMatrix  operator+ (const TMatrix &mt);        // ��������
	TMatrix  operator- (const TMatrix &mt);        // ���������

												   // ���� / �����
	friend istream& operator>>(istream &in, TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			in >> mt.pVector[i];
		return in;
	}
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
			out << mt.pVector[i] << endl;
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	// TODO:
} 

template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	// TODO:
	return true;
} 

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	// TODO:
	return true;
} 

template <class ValType> // ������������
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	// TODO:
	TMatrix<int> a(1);
	return a;
} 

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	// TODO:
	TMatrix<int> a(1);
	return a;
} 

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	// TODO:
	TMatrix<int> a(1);
	return a;
} 

  // TVector �3 �2 �4 �6
  // TMatrix �2 �2 �3 �3
#endif

