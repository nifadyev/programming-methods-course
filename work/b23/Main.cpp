#include "Polinom.h"

int main()
{ 
	TPolinom polinom1, polinom2, sum;

	polinom1.Input();
	polinom2.Input();

	cout << "\nFirst polinom: ";
	polinom1.Print();
	cout << "Second polinom: ";
	polinom2.Print();

	sum = polinom1 + polinom2;
	cout << "Sum of polinoms: ";
	sum.Print();

	return 0;
}