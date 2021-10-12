#pragma once

namespace DogFW
{
	class HighResClock
	{
	public:
		HighResClock();
		__int64 CurrentCount();
		void Measure();
		double StopMeasure();
		
	private:
		double mSecondsPerCount;
		__int64 mLastTime;
	};
}
