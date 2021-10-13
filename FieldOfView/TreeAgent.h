#pragma once
#include "DataClasses.h"


class TreeAgent
{
public:
	TreeAgent(FloatPoint& loc) :agentLocation(FloatPoint(loc)) {};
	TreeAgent(float x, float y):agentLocation(FloatPoint(x, y)){};

	void SetID(uint32 id) { ID = id; }

	//TO DO Allocator 
	FloatPoint agentLocation;

	uint32 ID = 0;
	void* agentClassData = nullptr;
};

