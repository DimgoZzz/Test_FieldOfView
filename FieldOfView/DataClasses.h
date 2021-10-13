#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include "SSEVector.h"

#pragma region BaseTypes
using	int8 = int8_t;
using	int16 = int16_t;
using	int32 = int32_t;
using	int64 = int64_t;
using	uint8 = uint8_t;
using	uint16 = uint16_t;
using	uint32 = uint32_t;
using	uint64 = uint64_t;

struct IntPoint
{
	int32 x{ 0 };
	int32 y{ 0 };
};

using FloatPoint = DogFW::SSEVector2;
#pragma endregion BaseTypes

enum class PointToVectorPosition : int8
{
	On = 0,
	Left = 1,
	Right = 2
};

class AppSettings
{
public:
	static int32 MaxUnits;
	static float AgentSightRadius;
	static float AgentSightHalfAngle;
	static float WorldSize;
};