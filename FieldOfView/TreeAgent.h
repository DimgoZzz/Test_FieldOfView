#pragma once
#include "DataClasses.h"
#include "FunctionLibrary.h"
#include "Box.h"


class TreeAgent
{
public:
	TreeAgent(FloatPoint& loc, FloatPoint& dir) :agentLocation(loc),agentDirection(dir) {};
	TreeAgent(float x, float y,float dx,float dy):agentLocation(FloatPoint(x, y)), agentDirection(FloatPoint(dx, dy)) {};

	float GetLeftBound()	const { return agentLocation.GetX() - AppSettings::AgentSightRadius; }
	float GetRightBound()	const { return agentLocation.GetX() + AppSettings::AgentSightRadius; }
	float GetUpBound()		const { return agentLocation.GetY() - AppSettings::AgentSightRadius; }
	float GetDownBound()	const { return agentLocation.GetY() + AppSettings::AgentSightRadius; }

	void SetID(uint32 id) { ID = id; }

	bool CanSeeAgent(TreeAgent* agent)const;
public:
	//TO DO Allocator 
	FloatPoint agentLocation;
	FloatPoint agentDirection;

	int32 seeCount = 0;
	uint32 ID = 0;
};
