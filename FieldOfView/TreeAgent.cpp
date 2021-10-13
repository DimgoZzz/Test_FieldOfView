#include "TreeAgent.h"

bool TreeAgent::CanSeeUnit(TreeAgent* unit) const
{
	FloatPoint distance = (agentLocation - unit->agentLocation).Abs();
	if (pow(AppSettings::AgentSightRadius,2) >= distance.LengthPow2())
	{
		// <...................>	//Vec Directions
		// ..|.......P.......|..	//Point
		// ....|...........|....
		// ......|.......|......
		// ........|...|........
		//. .........U..........	//Vec Origins

		//check left view vector 
		//Point should be right to vector
		FloatPoint leftvec = agentDirection.GetNewRotated(-AppSettings::AgentSightHalfAngle);
		PointToVectorPosition lvpos = CheckPointToVectorPosition(unit->agentLocation, agentLocation, leftvec);
		if (lvpos == PointToVectorPosition::Left) { return false; }

		//check right view vector 
		//Point should be left to vector
		FloatPoint rightvec = agentDirection.GetNewRotated(AppSettings::AgentSightHalfAngle);
		PointToVectorPosition rvpos = CheckPointToVectorPosition(unit->agentLocation, agentLocation, rightvec);
		if (rvpos == PointToVectorPosition::Right) { return false; }

		return true;
	}


	return false;
}
