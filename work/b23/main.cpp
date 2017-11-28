// Динамические структуры данных - тестирование стека

#include <iostream>
#include "tstack.h"

using namespace std;

void main()
{
	TStack st(35);
	int temp;

	setlocale(LC_ALL, "Russian");
	cout << "Тестирование программ поддержки структуры типа стека" << endl;

	for (int i = 0; i < 35; i++)
	{
		st.Put(i);
		cout << "Положили значение " << i << " Код " << st.GetRetCode() << endl;
	}

	while (!st.IsEmpty())
	{
		temp = st.Get();
		cout << "Взяли значение " << temp << " Код " << st.GetRetCode() << endl;
	}
}
