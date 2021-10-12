#include "HighResClock.h"
#include "WinMin.h"

using namespace DogFW;


DogFW::HighResClock::HighResClock():mLastTime(0)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;
}

__int64 HighResClock::CurrentCount()
{
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	return currTime;
}

void DogFW::HighResClock::Measure()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&mLastTime);
}

double DogFW::HighResClock::StopMeasure()
{
	__int64 temp;
	QueryPerformanceCounter((LARGE_INTEGER*)&temp);
	return (temp - mLastTime) * mSecondsPerCount;
}
