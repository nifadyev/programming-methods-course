#ifndef TPROC_H
#define TPROC_H

const float DEFAULT_PRODUCTIVITY = 0.5f; // Стандартная производительность процессора

class TProc
{
private:
	float productivity; // Производительность процессора
	int clocks;         // Количество тактов имитации
public:
	TProc(int clocks = 1000, float productivity = DEFAULT_PRODUCTIVITY); 
	~TProc() {};

	bool TaskIsReady(float factor);

	float GetProductivity() const { return productivity; }
	int GetClocks() const { return clocks; }
};
#endif