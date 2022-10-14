#include <iostream>
#include <ctime>
#include <iomanip>
#include "tjobstream.h"
#include "tproc.h"

using namespace std;

void Work(TJobStream& stream, TProc& proccessor); // Имитация работы

int main()
{
	srand(time(0));
	int clocks = 50000;
	int streamSize = 10;
	TJobStream jobStream(streamSize, DEFAULT_INTENSITY);
	TProc proccessor(clocks, DEFAULT_PRODUCTIVITY);

	Work(jobStream, proccessor);

	return 0;
}

void Work(TJobStream& stream, TProc& proccessor)
{
	int rejectedTasks = 0;
	int acceptedTasks = 0;
	int downtime = 0; // Количество тактов простоя процессора

	float streamIntensity;
	float proccessorProductivity;

	for (int i = 0; i < proccessor.GetClocks(); i++)
	{
		streamIntensity = (float)rand() / RAND_MAX;
		proccessorProductivity = (float)rand() / RAND_MAX;

		if (streamIntensity < DEFAULT_INTENSITY)
		{
			if (!stream.IsFull())
			{
				stream.Put(++acceptedTasks);
			}
			else
			{
				rejectedTasks++;
			}
		}

		if (proccessorProductivity < DEFAULT_PRODUCTIVITY)
		{
			if (!stream.IsEmpty())
			{
				proccessor.TaskIsReady(proccessorProductivity);
				stream.Get();
			}
			else
			{
				downtime++;
			}
		}
	}

	cout << fixed << setprecision(2); // Фиксация макс количества цифр после запятой
	cout << "Results of job imitation------------------------" << endl;
	cout << "Clocks: " << proccessor.GetClocks() << endl;
	cout << "Size of JobStream: " << stream.GetStreamLength() << endl;
	cout << "Stream intensity " << stream.GetIntensity() << endl;
	cout << "Proccessor productivity " << proccessor.GetProductivity() << endl;
	cout << "Task is generated every " << (float)proccessor.GetClocks() / (float)acceptedTasks << " clock" << endl;
	cout << "Task is completed every " << (float)(proccessor.GetClocks() - downtime) / (float)acceptedTasks << " clock" << endl;

	cout << "\nTasks accepted: " << acceptedTasks << endl;
	cout << "Tasks rejected: " << rejectedTasks << endl;
	cout << "Percent of rejection: " << ((float)rejectedTasks / (float)proccessor.GetClocks()) * 100.0f << "%" << endl;
	cout << "Percent of downtime: " << ((float)downtime / (float)proccessor.GetClocks()) *  100.0f << "%" << endl;
}