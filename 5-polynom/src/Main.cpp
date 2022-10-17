#include "Polinom.h"

int main()
{ 
	TPolinom polinom1, polinom2, sum;
	const int x = 3, y = -6, z = 2;

	polinom1.Input();
	polinom2.Input();

	cout << "\nFirst polinom: ";
	polinom1.Print();
	cout << "Second polinom: ";
	polinom2.Print();

	sum = polinom1 + polinom2;
	cout << "Sum of polinoms: ";
	sum.Print();

	cout << "Sum of polinoms(if x = " << x << ", y = " << y << " and z = " << z << "): " << sum.Calculate(x, y, z) << endl;

	return 0;
}