#include <iostream>
#include "UserComm.h"
#include "Polinom.h"


int main()
{ 
	// This is draft of Input Monom
	smatch result;
	string input;
	regex monom("(\\+?-?\\d+)x\\^?([0-9]{1})y\\^?([0-9]{1})z\\^?([0-9]{1})");

	cout << "Enter polinom: ";
	getline(cin, input);
	auto begin = input.cbegin();
	auto end = input.cend();

	for (; regex_search(begin, end, result, monom); begin = result.suffix().first)
	{
		// res[0] is monom
		// res[1] is coeff
		// res[2] is x_exp
		// res[3] is y_exp
		// res[4] is z_exp
		//TODO: add check for wrong arguments
		int index = atoi(result[2].str().c_str()) * 100 + atoi(result[3].str().c_str()) * 10 + atoi(result[4].str().c_str());
		cout << index << endl;
		cout << result[0] << endl;
		cout << result[1] << endl;
		//v.push_back(std::make_pair(toInt(res[1].str()), index));
	}
	return 0;
}