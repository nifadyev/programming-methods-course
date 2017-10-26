#include <gtest/gtest.h>

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

/*	friend ostream& operator<<(ostream &out, const TVector &v)
	{
		for (int i = 0; i < v.StartIndex; ++i)
			out << left << setw(5) << setfill(' ') << 0;
		for (int i = 0; i < v.Size; i++)
			out << left << setw(5) << setfill(' ') << v.pVector[i];
		return out;
	}

template <class ValType>
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
	if (Size < 0 || Size > MAX_VECTOR_SIZE)
		throw length_error("EXCEPTION: Vector's length has to be a positive value that is less than 100'000'000");
	if (StartIndex < 0)
		throw invalid_argument("EXCEPTION: Start index has to be a positive value");
	pVector = new ValType[Size]();
}

template <class ValType> //конструктор копировани€
TVector<ValType>::TVector(const TVector<ValType> &v) : Size(v.Size), StartIndex(v.StartIndex)
{
	pVector = new ValType[Size];
	for (int i = 0; i < Size; ++i)
		pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
	if (pVector != nullptr)
		delete[] pVector;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < StartIndex || pos >= Size + StartIndex)
		throw out_of_range("EXCEPTION: index is ous of range");
	return pVector[pos - StartIndex];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector<ValType> &v) const
{
	if (Size != v.Size || StartIndex != v.StartIndex) return false;
	for (int i = 0; i < Size; ++i)
		if (pVector[i] != v.pVector[i]) return false;
	return true;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector<ValType> &v) const
{
	return !(*this == v);
}

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector<ValType> &v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			Size = v.Size;
			if (pVector != nullptr) delete[] pVector;
			pVector = new ValType[Size];
		}
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; ++i)
			pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class ValType> // прибавить скал€р
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> tmp(*this);
	for (int i = 0; i < Size; ++i)
		tmp.pVector[i] += val;
	return tmp;
}

template <class ValType> // вычесть скал€р
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> tmp(*this);
	for (int i = 0; i < Size; ++i)
		tmp.pVector[i] -= val;
	return tmp;
}

template <class ValType> // умножить на скал€р
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> tmp(*this);
	for (int i = 0; i < Size; ++i)
		tmp.pVector[i] *= val;
	return tmp;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size) throw length_error("EXCEPTION: Vectors lengths aren't equal");
	TVector<ValType> tmp(Size, StartIndex);
	for (int i = 0; i < Size; ++i)
		tmp.pVector[i] = pVector[i] + v.pVector[i];
	return tmp;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size) throw length_error("EXCEPTION: Vectors lengths aren't equal");
	TVector<ValType> tmp(Size, StartIndex);
	for (int i = 0; i < Size; ++i)
		tmp.pVector[i] = pVector[i] - v.pVector[i];
	return tmp;
}

template <class ValType> // скал€рное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size != v.Size) throw length_error("EXCEPTION: Vectors lengths aren't equal");
	ValType res = 0;
	for (int i = 0; i < Size; ++i)
		res += pVector[i] * v.pVector[i];
	return res;
}


// ¬ерхнетреугольна€ матрица
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

												   // ввод / вывод
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
	if (s > MAX_MATRIX_SIZE) throw invalid_argument("Matrix size is too large");
	for (int i = 0; i < s; ++i)
		pVector[i] = TVector<ValType>(s - i, i);
}

template <class ValType> // конструктор копировани€
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразовани€ типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	return TVector<TVector<ValType> >::operator==(mt);
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
}

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt)
	{
		if (Size != mt.Size)
		{
			Size = mt.Size;
			if (pVector != nullptr) delete[] pVector;
			pVector = new TVector<ValType>[Size];
		}
		StartIndex = mt.StartIndex;
		for (int i = 0; i < Size; ++i)
			pVector[i] = mt.pVector[i];
	}
	return *this;
}

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType> >::operator+(mt);
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType> >::operator-(mt);
}

// TVector ќ3 Ћ2 ѕ4 —6
// TMatrix ќ2 Ћ2 ѕ3 —3
#endif*/