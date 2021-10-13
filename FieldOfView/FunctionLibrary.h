#pragma once
#include "DataClasses.h"
#include "TreeAgent.h"

//Check where the point lies relative to the vector
PointToVectorPosition CheckPointToVectorPosition(const FloatPoint& pointLoc, const FloatPoint& vecOrigin, const FloatPoint& vecDirection);

class TreeAgent; class Box;
//Check in which quad agent located, or not at all
TreeDirection GetQuadrant(TreeAgent* agent, Box* treebounds);

bool IntersectBounds(TreeAgent* agentPtr, Box& bounds);