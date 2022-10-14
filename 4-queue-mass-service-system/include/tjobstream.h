#ifndef TJOBSTREAM_H
#define TJOBSTREAM_H

#include "tqueue.h"

const float DEFAULT_INTENSITY = 0.5f; // ����������� ������������� ������

class TJobStream : public TQueue
{
private:
	float intensity;  // ������������� ������ 
	int streamLength;
public:
	TJobStream(int size = DefMemSize, float intensity = DEFAULT_INTENSITY);
	~TJobStream() {};

	float GetIntensity() const { return intensity; }
	int GetStreamLength() const { return streamLength; }
};
#endif