// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sample_prime_numbers.cpp - Copyright (c) ������� �.�. 20.08.2000
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������������ �������� ���� � ���������

#include <iomanip>

 //#define USE_SET // ������������ ����� TSet,
// ���������������, ����� ������������ ������� ����

#ifndef USE_SET // ������������ ����� TBitField

#include "tBitField.h"

int main()
{
	int n, m, k, count;
	setlocale(LC_ALL, "Russian");
	cout << "������������ �������� ��������� �������� ����" << endl;
	cout << "             ������ ����������" << endl;
	cout << "������� ������� ������� ����� �������� - ";
	cin >> n;
	TBitField s(n + 1);
	for (m = 2; m <= n; m++) // ���������� ���������
		s.SetBit(m);
	for (m = 2; m * m <= n; m++) // �������� �� sqrt(n) � �������� �������	
		if (s.GetBit(m)) // ���� m � s, �������� �������
			for (k = 2 * m; k <= n; k += m)
				if (s.GetBit(k))
					s.ClearBit(k);
	// ���������� � s �������� - ������� �����
	cout << endl << "������ ��������� ��������� �����" << endl << s << endl;
	cout << endl << "������ ������� �����" << endl;
	count = 0;
	k = 1;
	for (m = 2; m <= n; m++)
		if (s.GetBit(m))
		{
			count++;
			cout << setw(3) << m << " ";
			if (k++ % 25 == 0)
				cout << endl;
		}
	cout << endl;
	cout << "� ������ " << n << " ������ " << count << " �������" << endl;
}
#else

#include "tset.h"

int main()
{
	int n, m, k, count;

	setlocale(LC_ALL, "Russian");
	cout << "������������ �������� ��������� ���������" << endl;
	cout << "              ������ ����������" << endl;
	cout << "������� ������� ������� ����� �������� - ";
	cin >> n;
	TSet s(n + 1);
	// ���������� ���������
	for (m = 2; m <= n; m++)
		s.InsertElem(m);
	// �������� �� sqrt(n) � �������� �������
	for (m = 2; m * m <= n; m++)
		// ���� � � s, �������� �������
		if (s.IsMember(m))
			for (k = 2 * m; k <= n; k += m)
				if (s.IsMember(k))
					s.DeleteElem(k);
	// ���������� � s �������� - ������� �����
	cout << endl << "������ ��������� ��������� �����" << endl << s << endl;
	cout << endl << "������ ������� �����" << endl;
	count = 0;
	k = 1;
	for (m = 2; m <= n; m++)
		if (s.IsMember(m))
		{
			count++;
			cout << setw(3) << m << " ";
			if (k++ % 25 == 0)
				cout << endl;
		}
	cout << endl;
	cout << "� ������ " << n << " ������ " << count << " �������" << endl;
}

#endif