#include "ConsoleApp.h"
#include "WinMin.h"


void ConsoleApp::Start()
{

	map.AddUnit(0, 0, 0, 1, 135.5, 2);
	map.AddUnit(0, 1, 0, 1, 135.5, 2);
	map.AddUnit(0, 3, 0, 1, 135.5, 2);
	Unit& unit1 = map.GetUnit(0);
	Unit& unit2 = map.GetUnit(1);
	Unit& unit3 = map.GetUnit(2);

	std::cout << "\nUnit 1 can see unit 2 : " << unit1.CanSeeUnit(unit2);
	std::cout << "\nUnit 1 can see unit 3 : " << unit1.CanSeeUnit(unit3);
	std::cout << "\nUnit 2 can see unit 1 : " << unit2.CanSeeUnit(unit1);
	std::cout << "\nUnit 2 can see unit 3 : " << unit2.CanSeeUnit(unit3);
	std::cout << "\nUnit 3 can see unit 2 : " << unit3.CanSeeUnit(unit2);
	std::cout << "\nUnit 3 can see unit 1 : " << unit3.CanSeeUnit(unit1);
	//std::cout << unit1.CanSeeUnit(unit2);
	

}
