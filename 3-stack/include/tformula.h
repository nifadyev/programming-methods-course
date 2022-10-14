const int MaxLen = 255;
enum {OpenBracket, CloseBracket, AddOrSubstract, MultiplicateOrDivide};

class TFormula
{
private:
	char Formula[MaxLen];     // Исходная формула
	char PostfixForm[MaxLen]; // Постфиксная форма

	void ResetOperands(char* operand1, char* operand2); // Обнуление операндов
	int ForbiddenSymbolsChecker(); // Проверка на посторонние символы и недопустимую последовательность операций

public:
	TFormula(char *form);                            // Конструктор
	int FormulaChecker(int Brackets[], int size);    // Проверка корректности скобок
	int FormulaConverter();                          // Преобразование в постфиксную форму
	double FormulaCalculator();                      // Вычисление формулы
	void Print();                                    // Печать формулы в инфиксной и постфиксной видах
};