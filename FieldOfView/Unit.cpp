#include "Unit.h"
#include "WinMin.h"

Unit::Unit(float posX, float PosY, float dirX, float dirY, float fovAngle, float fovRange, uint32 id):
	position{posX,PosY},
	direction{dirX,dirY},
	fieldOfViewAngle{fovAngle},
	fieldOfViewRange{fovRange},
	unitID{id}
{
}

bool Unit::CanSeeUnit(Unit const& unit)const
{
	FloatPoint distance = (position - unit.GetPosition()).Abs();
	if (fieldOfViewRange >= distance.Length().GetX())
	{
		// <...................>	//Vec Directions
		// ..|.......P.......|..	//Point
		// ....|...........|....
		// ......|.......|......
		// ........|...|........
		//. .........U..........	//Vec Origins

		//check left view vector 
		//Point should be right to vector
		FloatPoint leftvec = direction.GetNewRotated(-fieldOfViewAngle / 2);
		PointToVectorPosition lvpos = CheckPointToVectorPosition(unit.GetPosition(), position,leftvec);
		if (lvpos == PointToVectorPosition::Left) { return false; }

		//check right view vector 
		//Point should be left to vector
		FloatPoint rightvec = direction.GetNewRotated(fieldOfViewAngle / 2);
		PointToVectorPosition rvpos = CheckPointToVectorPosition(unit.GetPosition(), position, rightvec);
		if (rvpos == PointToVectorPosition::Right) { return false; }
		
		return true;
	}
	

	return false; 
}
