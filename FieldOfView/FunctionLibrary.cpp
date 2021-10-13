#include "FunctionLibrary.h"


//Check where the point lies relative to the vector
PointToVectorPosition CheckPointToVectorPosition(const FloatPoint& pointLoc, const FloatPoint& vecOrigin, const FloatPoint& vecDirection)
{
	float value = ((pointLoc.GetY() - vecOrigin.GetY()) * (vecDirection.GetX() - vecOrigin.GetX())) -
		((pointLoc.GetX() - vecOrigin.GetX()) * (vecDirection.GetY() - vecOrigin.GetY()));
	if (value > 0) { return PointToVectorPosition::Left; }
	if (value < 0) { return PointToVectorPosition::Right; }
	return PointToVectorPosition::On;
}

TreeDirection GetQuadrant(TreeAgent* agent, Box* treebounds)
{
	auto center = treebounds->GetCenter();
	// West
	if (agent->GetRightBound() < center.GetX())
	{
		// North West
		if (agent->GetDownBound() < center.GetY())
			return TreeDirection::NorthWest;
		// South West
		else if (agent->GetUpBound() >= center.GetY())
			return TreeDirection::SouthWest;
		// Not contained in any quadrant
		else
			return TreeDirection::None;
	}
	// East
	else if (agent->GetLeftBound() >= center.GetX())
	{
		// North East
		if (agent->GetDownBound() < center.GetY())
			return TreeDirection::NorthEast;
		// South East
		else if (agent->GetUpBound() >= center.GetY())
			return TreeDirection::SouthEast;
		// Not contained in any quadrant
		else
			return TreeDirection::None;
	}
	// Not contained in any quadrant
	else
	{
		return TreeDirection::None;
	}

}

bool IntersectBounds(TreeAgent* agentPtr, Box& bounds)
{

	return ((((agentPtr->GetLeftBound() - bounds.left) < AppSettings::AgentSightRadius) && ((agentPtr->GetLeftBound() - bounds.left) > -AppSettings::AgentSightRadius))
			||
			(((agentPtr->GetRightBound() - bounds.GetRight()) < AppSettings::AgentSightRadius) && ((agentPtr->GetRightBound() - bounds.GetRight()) > -AppSettings::AgentSightRadius))
			||
			(((agentPtr->GetUpBound() - bounds.top) < AppSettings::AgentSightRadius) && ((agentPtr->GetUpBound() - bounds.top) > -AppSettings::AgentSightRadius))
			||
			(((agentPtr->GetDownBound() - bounds.GetBottom()) < AppSettings::AgentSightRadius) && ((agentPtr->GetDownBound() - bounds.GetBottom() > -AppSettings::AgentSightRadius))));
}

