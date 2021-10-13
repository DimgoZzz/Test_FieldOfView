#include "TreeAgent.h"

bool TreeAgent::CanSeeAgent(TreeAgent* agent) const
{
	FloatPoint distance = (agentLocation - agent->agentLocation).Abs();

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
		PointToVectorPosition lvpos = CheckPointToVectorPosition(agent->agentLocation, agentLocation, leftvec);
		if (lvpos == PointToVectorPosition::Left) { return false; }

		//check right view vector 
		//Point should be left to vector
		FloatPoint rightvec = agentDirection.GetNewRotated(AppSettings::AgentSightHalfAngle);
		PointToVectorPosition rvpos = CheckPointToVectorPosition(agent->agentLocation, agentLocation, rightvec);
		if (rvpos == PointToVectorPosition::Right) { return false; }

		return true;
	}

	return false;
}

int GetQuadrant(const TreeAgent* agent, const Box* treebounds)
{
	auto center = treebounds->GetCenter();
	// West
	//if (agent->GetRightBound() < center.GetX())
	//{
	//	// North West
	//	if (valueBox.GetBottom() < center.GetY())
	//		return 0;
	//	// South West
	//	else if (valueBox.top >= center.GetY())
	//		return 2;
	//	// Not contained in any quadrant
	//	else
	//		return -1;
	//}
	//// East
	//else if (valueBox.left >= center.GetX())
	//{
	//	// North East
	//	if (valueBox.GetBottom() < center.GetY())
	//		return 1;
	//	// South East
	//	else if (valueBox.top >= center.GetY())
	//		return 3;
	//	// Not contained in any quadrant
	//	else
	//		return -1;
	//}
	//// Not contained in any quadrant
	//else
	//	return -1;
}
