#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType *pVector;
	int Size;       // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // конструктор копирования
	~TVector();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector &v) const;  // сравнение
	bool operator!=(const TVector &v) const;  // сравнение
	TVector& operator=(const TVector &v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType &val);   // прибавить скаляр
	TVector  operator-(const ValType &val);   // вычесть скаляр
	TVector  operator*(const ValType &val);   // умножить на скаляр

	// векторные операции
	TVector  operator+(const TVector &v);     // сложение
	TVector  operator-(const TVector &v);     // вычитание
	ValType  operator*(const TVector &v);     // скалярное произведение

	// ввод
	friend istream& operator>>(istream &in, TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}

	//вывод
	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.Size; i++)
		{
			out << v.pVector[i] << ' ';
		}
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
	if (s < 0)
	{
		throw length_error("Vector's length must be positive");
	}
	if (s > MAX_VECTOR_SIZE)
	{
		throw length_error("Vector's length must be less than 100 000 000");
	}
	if (si < 0)
	{
		throw invalid_argument("Start index must be positive");
	}
	//this->Size = s;
	//this->StartIndex = si;
	this->pVector = new ValType[Size];
	for (int i = 0; i < this->Size; i++)
	{
		this->pVector[i] = 0;
	}
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v) : Size(v.Size), StartIndex(v.StartIndex)
{

	this->pVector = new ValType[Size];
	for (int i = 0; i < this->Size; i++)
	{
		this->pVector[i] = v.pVector[i];
	}
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] this->pVector;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < this->StartIndex) || (pos > this->Size + this->StartIndex))
	{
		throw range_error("Index of the element is out of vector's range");
	}
	return pVector[pos - this->StartIndex];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if ((this->Size != v.Size) || (this->StartIndex != v.StartIndex))
	{
		return false;
	}
	for (int i = 0; i < this->Size; i++)
	{
		if (this->pVector[i] != v.pVector[i])
		{
			return false;
		}
	}
	return true;
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return (*this == v) ? false : true;
} 

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		if (this->Size != v.Size)
		{
			this->Size = v.Size;
			delete[] pVector;
			this->pVector = new ValType[Size];
		}
		this->StartIndex = v.StartIndex;
		for (int i = 0; i < this->Size; i++)
		{
			this->pVector[i] = v.pVector[i];
		}
	}
	return *this;
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> result(*this);
	if (val != 0)
	{
		for (int i = 0; i < result.Size; i++)
		{
			result.pVector[i] += val;
		}
	}
	return result;
} 

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> result(*this);
	if (val != 0)
	{
		for (int i = 0; i < result.Size; i++)
		{
			result.pVector[i] -= val;
		}
	}
	return result;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> result(*this);
	if (val != 0)
	{
		for (int i = 0; i < result.Size; i++)
		{
			result.pVector[i] *= val;
		}
	}
	return result;
} 

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (this->Size != v.Size)
	{
		throw length_error("Sizes of vectors are not equal");
	}
	TVector<ValType> result(Size, StartIndex);
	for (int i = 0; i < result.Size; i++)
	{
		result.pVector[i] = this->pVector[i] + v.pVector[i];
	}
	return result;
} 

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (this->Size != v.Size)
	{
		throw length_error("Sizes of vectors are not equal");
	}
	TVector<ValType> result(Size, StartIndex);
	for (int i = 0; i < result.Size; i++)
	{
		result.pVector[i] = this->pVector[i] - v.pVector[i];
	}
	return result;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (this->Size != v.Size)
	{
		throw length_error("Sizes of vectors are not equal");
	}
	ValType sum = 0;
	for (int i = 0; i < this->Size; i++)
	{
		sum += this->pVector[i] * v.pVector[i];
	}
	return sum;
} 


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix &mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
	bool operator==(const TMatrix &mt) const;      // сравнение
	bool operator!=(const TMatrix &mt) const;      // сравнение
	TMatrix& operator= (const TMatrix &mt);        // присваивание
	TMatrix  operator+ (const TMatrix &mt);        // сложение
	TMatrix  operator- (const TMatrix &mt);        // вычитание

	// ввод
	friend istream& operator>>(istream &in, TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
		{
			in >> mt.pVector[i];
		}
		return in;
	}

	//вывод
	friend ostream & operator<<(ostream &out, const TMatrix &mt)
	{
		for (int i = 0; i < mt.Size; i++)
		{
			out << mt.pVector[i] << endl;
		}			
		return out;
	}
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
	if (s < 0)
	{
		throw range_error("Cannot create matrix. Size of matrix must be positive");
	}
	if (s > MAX_MATRIX_SIZE)
	{
		throw range_error("Cannot create matrix. Size of matrix must be less than 10 000");
	}
	for (int i = 0; i < this->Size; ++i)
	{
		this->pVector[i] = TVector<ValType>(s - i, i);
	}
} 

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this->Size != mt.Size)
	{
		return false;
	}
	for (int i = 0; i < this->Size; ++i)
	{
		if (this->pVector[i] != mt.pVector[i])
		{
			return false;
		}
	}
	return true;
} 

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return (*this == mt) ? false : true;
} 

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt)
	{
		if (this->Size != mt.Size)
		{
			this->Size = mt.Size;
			delete[] pVector;
			this->pVector = new TVector<ValType>[Size];
		}
		this->StartIndex = mt.StartIndex;
		for (int i = 0; i < this->Size; ++i)
			this->pVector[i] = mt.pVector[i];
	}
	return *this;
} 

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (this->Size != mt.Size)
	{
		throw length_error("Sizes of matrices are not equal");
	}
	TMatrix<ValType> result(*this);
	for (int i = 0; i < this->Size; i++)
	{
		result.pVector[i] = this->pVector[i] + mt.pVector[i];
	}
	return result;
} 

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (this->Size != mt.Size)
	{
		throw length_error("Sizes of matrices are not equal");
	}
	TMatrix<ValType> result(*this);
	for (int i = 0; i < this->Size; i++)
	{
		result.pVector[i] = this->pVector[i] - mt.pVector[i];
	}
	return result;
} 
#endif