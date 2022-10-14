const int MaxLen = 255;
enum {OpenBracket, CloseBracket, AddOrSubstract, MultiplicateOrDivide};

class TFormula
{
private:
	char Formula[MaxLen];     // �������� �������
	char PostfixForm[MaxLen]; // ����������� �����

	void ResetOperands(char* operand1, char* operand2); // ��������� ���������
	int ForbiddenSymbolsChecker(); // �������� �� ����������� ������� � ������������ ������������������ ��������

public:
	TFormula(char *form);                            // �����������
	int FormulaChecker(int Brackets[], int size);    // �������� ������������ ������
	int FormulaConverter();                          // �������������� � ����������� �����
	double FormulaCalculator();                      // ���������� �������
	void Print();                                    // ������ ������� � ��������� � ����������� �����
};