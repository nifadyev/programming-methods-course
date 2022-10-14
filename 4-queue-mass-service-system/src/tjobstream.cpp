#include "tjobstream.h"

TJobStream::TJobStream(int size, float intensity) : TQueue(size)
{
	if (intensity < 0.0f || intensity > 1.0f)
	{
		throw invalid_argument("Intensity of stream must be more than 0 and less than 1");
	}

	this->streamLength = size;
	this->intensity = intensity;
}