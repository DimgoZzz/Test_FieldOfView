#pragma once
#include "DataClasses.h"


class TreeAgent
{
public:
	TreeAgent(FloatPoint& loc, FloatPoint& dir) :agentLocation(loc),agentDirection(dir) {};
	TreeAgent(float x, float y,float dx,float dy):agentLocation(FloatPoint(x, y)), agentDirection(FloatPoint(dx, dy)) {};

	void SetID(uint32 id) { ID = id; }

	inline float GetLeftBound() { return agentLocation.GetX() - AppSettings::AgentSightRadius; }
	inline float GetRightBound(){ return agentLocation.GetX() + AppSettings::AgentSightRadius; }
	inline float GetUpBound()	{ return agentLocation.GetX() - AppSettings::AgentSightRadius; }
	inline float GetDownBound() { return agentLocation.GetX() + AppSettings::AgentSightRadius; }

	bool CanSeeUnit(TreeAgent* unit)const;
	//TO DO Allocator 
	FloatPoint agentLocation;
	FloatPoint agentDirection;

	int32 seeCount = 0;
	uint32 ID = 0;
	void* agentClassData = nullptr;
};

