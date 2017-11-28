// ������������ ��������� ������ - ������������ �����

#include <iostream>
#include "tstack.h"

using namespace std;

void main()
{
	TStack st(35);
	int temp;

	setlocale(LC_ALL, "Russian");
	cout << "������������ �������� ��������� ��������� ���� �����" << endl;

	for (int i = 0; i < 35; i++)
	{
		st.Put(i);
		cout << "�������� �������� " << i << " ��� " << st.GetRetCode() << endl;
	}

	while (!st.IsEmpty())
	{
		temp = st.Get();
		cout << "����� �������� " << temp << " ��� " << st.GetRetCode() << endl;
	}
}
