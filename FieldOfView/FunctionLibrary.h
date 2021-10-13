#pragma once
#include "DataClasses.h"

//Check where the point lies relative to the vector
inline PointToVectorPosition CheckPointToVectorPosition(const FloatPoint& pointLoc, const FloatPoint& vecOrigin, const FloatPoint& vecDirection)
{
	float value =	((pointLoc.GetY() - vecOrigin.GetY()) * (vecDirection.GetX() - vecOrigin.GetX())) -
					((pointLoc.GetX() - vecOrigin.GetX()) * (vecDirection.GetY() - vecOrigin.GetY()));
	if (value > 0) { return PointToVectorPosition::Left; }
	if (value < 0) { return PointToVectorPosition::Right; }
	return PointToVectorPosition::On;
}
