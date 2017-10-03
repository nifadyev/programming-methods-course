// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_prime_numbers.cpp - Copyright (c) Гергель В.П. 20.08.2000
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Тестирование битового поля и множества

#include <iomanip>

 //#define USE_SET // Использовать класс TSet,
// закоментировать, чтобы использовать битовое поле

#ifndef USE_SET // Использовать класс TBitField

#include "tbitfield.h"

int main()
{
	int n, m, k, count;
	setlocale(LC_ALL, "Russian");
	cout << "Тестирование программ поддержки битового поля" << endl;
	cout << "             Решето Эратосфена" << endl;
	cout << "Введите верхнюю границу целых значений - ";
	cin >> n;
	TBitField s(n + 1);
	for (m = 2; m <= n; m++) // заполнение множества
		s.SetBit(m);
	for (m = 2; m * m <= n; m++) // проверка до sqrt(n) и удаление кратных	
		if (s.GetBit(m)) // если m в s, удаление кратных
			for (k = 2 * m; k <= n; k += m)
				if (s.GetBit(k))
					s.ClearBit(k);
	// оставшиеся в s элементы - простые числа
	cout << endl << "Печать множества некратных чисел" << endl << s << endl;
	cout << endl << "Печать простых чисел" << endl;
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
	cout << "В первых " << n << " числах " << count << " простых" << endl;
}
#else

#include "tset.h"

int main()
{
	int n, m, k, count;

	setlocale(LC_ALL, "Russian");
	cout << "Тестирование программ поддержки множества" << endl;
	cout << "              Решето Эратосфена" << endl;
	cout << "Введите верхнюю границу целых значений - ";
	cin >> n;
	TSet s(n + 1);
	// заполнение множества
	for (m = 2; m <= n; m++)
		s.InsertElem(m);
	// проверка до sqrt(n) и удаление кратных
	for (m = 2; m * m <= n; m++)
		// если м в s, удаление кратных
		if (s.IsMember(m))
			for (k = 2 * m; k <= n; k += m)
				if (s.IsMember(k))
					s.DeleteElem(k);
	// оставшиеся в s элементы - простые числа
	cout << endl << "Печать множества некратных чисел" << endl << s << endl;
	cout << endl << "Печать простых чисел" << endl;
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
	cout << "В первых " << n << " числах " << count << " простых" << endl;
}

#endif