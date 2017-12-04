#define _SCL_SECURE_NO_WARNINGS

#include <algorithm>
#include <iostream>
#include <cstring>
#include "tformula.h"
#include "tstack.h"

using namespace std;

TFormula::TFormula(char *form)
{
	int length = strlen(form);
	if (length == 0)
	{
		throw invalid_argument("String is empty");
	}
	if (length > 255)
	{
		throw invalid_argument("Size of expression is too big. Max size is 255");
	}

	strcpy_s(Formula, form);
	for (int i = 0; i < MaxLen; i++)
	{
		PostfixForm[i] = 0;
	}
}

int TFormula::FormulaChecker(int Brackets[], int size)
{
	if (size < 0)
	{
		throw invalid_argument("Size must be positive");
	}
	if (ForbiddenSymbolsChecker() > 0) // ������� �������� ���������� ���� +-, .* ��� �������
	{
		return ForbiddenSymbolsChecker();
	}

	TStack parentheses(size);
	int errors = 0;
	int resultTableIndex = 0; // ���������� �������� � resultTable
	int bracketNumber = 1; // ����� ������ � �������
	int flag = 0; // ������� ��� ���������� ����� �������� � ������ �������/������� �����
	int **resultTable = new int*[2]; // ������ ������� ����������� � ����������� ������
	for (int i = 0; i < 2; i++)
	{
		resultTable[i] = new int[size] {};
	}
	
	//���� �������� ������ � �������
	for (int i = 0; i < size; i++)
	{
		if (flag == 1)
		{ 
			break;
		}

		switch (Brackets[i])
		{
		case (int)'(':
		{
			if (parentheses.IsFull())
			{
				errors++;
				flag = 1;
				break;
			}

			parentheses.Put(bracketNumber++);
			break;
		}

		case (int)')':
		{
			if (parentheses.IsEmpty())
			{
				resultTable[0][resultTableIndex] = 0; // ����������� ������
				resultTable[1][resultTableIndex] = bracketNumber++; // ����������� ������
				errors++;
			}
			else
			{
				resultTable[0][resultTableIndex] = parentheses.Get();
				resultTable[1][resultTableIndex] = bracketNumber++;
			}

			resultTableIndex++;
			break;
		}
		}
	}

	// ���� ���� ����� ������� �� ����, �� ��������� resultTable �������� ��������
	while(!parentheses.IsEmpty())
	{
		resultTable[0][resultTableIndex] = parentheses.Get();
		resultTable[1][resultTableIndex] = 0;
		errors++;
		resultTableIndex++;
	}

	// ������ resultTable
	//for (int i = 0; i < 2; i++) 
	//{
	//	for (int j = 0; j < resultTableIndex; j++)
	//		cout << resultTable[i][j] << " ";
	//	cout << endl;
	//}

	delete[] resultTable;

	return errors;
}

int TFormula::FormulaConverter()
{
	int formulaLength = strlen(Formula);
	int* intFormula = new int[formulaLength]; // ��������� ������������� Formula
	for (int i = 0; i < formulaLength; i++)
	{
		intFormula[i] = (int)Formula[i];
	}

	if (FormulaChecker(intFormula, formulaLength) > 0)
	{
		return 1;
	}

	int flag = 0; // ������� ��� �������� � ��������� �������� ����� �����������, ���� �� ����������� ��������
	int index = 0; // ������ ������� PostfixForm
	int operationPriority = -1;
	int previousOperationPriority = -2;
	TStack operations(formulaLength);
	
	// ���� ����������� ������� � ����������� ���
	for (int i = 0; i < formulaLength; i++)
	{
		flag = 0;

		switch (Formula[i]) // ����������� ����������� ��������
		{
			case '(':
			{
				operationPriority = OpenBracket;
				break;
			}
			case ')':
			{
				operationPriority = CloseBracket;
				break;
			}
			case '+':
			{
				operationPriority = AddOrSubstract;
				break;
			}
			case '-':
			{
				operationPriority = AddOrSubstract;
				break;
			}
			case '*':
			{
				operationPriority = MultiplicateOrDivide;
				break;
			}
			case '/':
			{
				operationPriority = MultiplicateOrDivide;
				break;
			}
			default: // ���� �������� �� �������, �� �������� �����/����� � PostfixForm
			{
				operationPriority = -1;
				PostfixForm[index++] = Formula[i];
				flag = 1;
				break;
			}
			
		}

		if (flag == 1)
		{
			continue;
		}

		if (operationPriority == OpenBracket)
		{
			operations.Put((int)'(');
			previousOperationPriority = operationPriority;
			continue;
		}

		if (operationPriority > previousOperationPriority)
		{
			if (operationPriority == CloseBracket)
			{
				while (!operations.IsEmpty()) // ������������ ���������� � ����� ��������
				{
					int temp = operations.Get();
					if (temp != (int)'(') // ���� �� ���������� ����������� ������
					{
						PostfixForm[index++] = (char)temp;					
					}
				}
			}

			else
			{
				PostfixForm[index++] = ' ';
				operations.Put((int)Formula[i]);
			}
		}

		if (operations.IsEmpty())
		{
			operations.Put((int)Formula[i]);
		}

		else if (operationPriority <= previousOperationPriority)
		{
			while(!operations.IsEmpty())
			{
				int temp = operations.Get();
				if (temp != (int)'(')
				{
					PostfixForm[index++] = (char)temp;
				}
			}
		}

		previousOperationPriority = operationPriority;
	}


	while (!operations.IsEmpty()) // ���� ����� ����� �������� �������� � �����
	{
		PostfixForm[index++] = (char)operations.Get();
	}

	return 0;
}

double TFormula::FormulaCalculator()
{
	const int defaultOperandLength = 16;
	int formulaLength = strlen(PostfixForm); 
	int index = 0; // ������ charOperand1 � charOperand2
	int operandNumber = 1; // ����� ��������
	Stack<double> operands(formulaLength); // ���� ��� ������������ �����
	char charOperand1[defaultOperandLength]; // ���������� ������������� ������� ��������
	char charOperand2[defaultOperandLength]; // ���������� ������������� ������� ��������	
	for (int i = 0; i < defaultOperandLength; i++) 
	{
		charOperand1[i] = 0;
		charOperand2[i] = 0;
 	}

	//���������� ������� ������������ ����
	for (int i = 0; i < formulaLength; i++)
	{

		switch (PostfixForm[i])
		{
		case ' ':
		{
			// ���� ����������� ��� ��������
			if (strlen(charOperand1) > 0 && strlen(charOperand2) > 0) 
			{
				// ������ ������ ������� � ����
				operands.Put(atof(charOperand1));
				// ������ �������� �������
				copy(charOperand2, charOperand2 + strlen(charOperand2), charOperand1); 
				// �������� ������ �������
				for (unsigned int i = 0; i < strlen(charOperand2); i++) 
					charOperand2[i] = 0;
			}

			// ���� ���� ������ �������
			if (charOperand1 != "") 
			{
				operandNumber = 2;
			}

			// ��� �������� �����������
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0) 
			{
				operandNumber = 1;
			}

			index = 0;
			break;
		}

		case '+':
		{
			// ���� ��� �������� �����������
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0) 
			{
				operands.Put((operands.Get() + operands.Get())); 
			}

			// ����� � ���� ���������� ������������ � int ����� ���������
			else
			{
				operands.Put(atof(charOperand1) + atof(charOperand2));
			}
			
			ResetOperands(charOperand1, charOperand2); // ��������� ���������
			operandNumber = 1;
			break;
		}

		case '-':
		{
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0)
			{
				double substractor = operands.Get(); // ����������
				operands.Put(operands.Get() - substractor);
			}

			else
			{
				operands.Put(atof(charOperand1) - atof(charOperand2));
			}

			ResetOperands(charOperand1, charOperand2);
			operandNumber = 1;
			break;
		}

		case '*':
		{
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0)
			{
				operands.Put(operands.Get() * operands.Get());
			}

			else
			{
				operands.Put(atof(charOperand1) * atof(charOperand2));
			}

			ResetOperands(charOperand1, charOperand2);
			operandNumber = 1;
			break;
		}

		case '/':
		{
			if (strlen(charOperand1) == 0 && strlen(charOperand2) == 0)
			{
				double divider = operands.Get(); // ��������
				operands.Put(operands.Get() / divider);
			}

			else
			{
				operands.Put(atof(charOperand1) / atof(charOperand2));
			}

			ResetOperands(charOperand1, charOperand2);
			operandNumber = 1;
			break;
		}

		// �� ����������� ��������
		default:
		{
			if (operandNumber == 1)
			{
				charOperand1[index++] = PostfixForm[i];
			}

			else
			{
				charOperand2[index++] = PostfixForm[i];
			}

			break;
		}
		}
	}

	return operands.Get();
}

void TFormula::Print()
{
	cout << "Infix formula: " << Formula << endl;
	cout << "Postfix formula: " << PostfixForm << endl;
}

void TFormula::ResetOperands(char * operand1, char * operand2) // ��������� ���������
{
	for (unsigned int i = 0; i < strlen(operand1); i++)
	{
		operand1[i] = 0;
	}
	for (unsigned int i = 0; i < strlen(operand2); i++)
	{
		operand2[i] = 0;
	}
}


int TFormula::ForbiddenSymbolsChecker() // �������� �� ����������� ������� � ������������ ������������������ ��������
{
	int errors = 0;

	for (unsigned int i = 0; i < strlen(Formula); i++)
	{
		char symbol = Formula[i];
		char nextSymbol = Formula[i + 1];

		// �������� �� ����������� �������
		if ((symbol < '0' || symbol > '9') && symbol != '.' &&
			symbol != '(' && symbol != ')' &&
			symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/')
		{
			errors++;
		}

		// �������� �� ������������ ������������������ ��������
		if ((symbol == nextSymbol) && (symbol == '.' || symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'))
		{
			errors++;
		}
	}

	return errors;
}
