#include "ConsoleApp.h"
#include "WinMin.h"


void ConsoleApp::Start()
{
	DogFW::HighResClock clock;
	std::vector<FloatPoint> dirs;
	dirs.push_back(FloatPoint(1.f, 0.f));
	dirs.push_back(FloatPoint(0.f, 1.f));
	dirs.push_back(FloatPoint(-1.f, 0.f));
	dirs.push_back(FloatPoint(0.f, -1.f));
	dirs.push_back(FloatPoint(0.707f, 0.707f));
	dirs.push_back(FloatPoint(-0.707f, -0.707f));
	dirs.push_back(FloatPoint(-0.707f, 0.707f));
	dirs.push_back(FloatPoint(0.707f, -0.707f));

	for (int i = 0; i < 10000; ++i)
	{
		map.AddUnit((i%100)/10.f, (i % 100)/10.f, dirs[i%8].GetX(), dirs[i % 8].GetY(), 135.5, 2);
	}

	int64 result = 0;
	clock.Measure();
	for (int i = 0; i < 10000; ++i)
	{
		Unit& u = map.GetUnit(i);
		for (int j = 0; j < 10000; ++j)
		{
			result+=u.CanSeeUnit(map.GetUnit(j));
		}
	}
	double time = clock.StopMeasure();

	std::cout << "Total time : " << time << std::endl;
	std::cout << "Total intersections : " << result << std::endl;

}
