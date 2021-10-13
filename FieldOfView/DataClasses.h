#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include "SSEVector.h"

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


//Used SSEVector Instead

//struct FPoint
//{
//
//	float x{ 0 };
//	float y{ 0 };
//
//	FPoint() {};
//	FPoint(float nx, float ny) : x(nx), y(ny) {};
//	//Конструктор копирования
//	FPoint(const FPoint& in) noexcept : x(in.x),y(in.y) {};
//	//Конструктор присваивания
//	FPoint(FPoint&& in) noexcept : x(in.x), y(in.y) {};
//
//#pragma region Operators
//	//================================================================
//	//Присваивание копированием
//	inline FPoint& operator=(FPoint const& in) noexcept
//	{
//		if (&in != this)
//		{
//			x = in.x;
//			y = in.y;
//		}
//		return *this;
//	}
//	//Присваивание перемещением
//	inline FPoint& operator=(FPoint const&& in) noexcept
//	{
//		if (&in != this)
//		{
//			x = in.x;
//			y = in.y;
//		}
//		return *this;
//	}
//	//================================================================
//	//Returns Negative(Vector)
//	inline FPoint operator-() const
//	{
//		return FPoint(-x,-y);
//	}
//
//	inline FPoint& operator+=(FPoint const& in)
//	{
//		x += in.x;
//		y += in.y;
//		return *this;
//	}
//	inline FPoint& operator-=(FPoint const& in)
//	{
//		x -= in.x;
//		y -= in.y;
//		return *this;
//	}
//	//================================================================
//	inline FPoint operator+ (FPoint const& rin)const 
//	{
//		return FPoint(x+rin.x,y+rin.y);
//	}
//	inline FPoint operator- (FPoint const& rin)const 
//	{
//		return FPoint(x - rin.x, y - rin.y);
//	}
//	//================================================================
//#pragma endregion Operators
//	inline FPoint Abs() const
//	{
//		return FPoint(abs(x), abs(y));
//	};
//	inline float Length() const
//	{
//		return sqrtf(x*x + y*y);
//	};
//};

using FloatPoint = DogFW::SSEVector2;


enum class PointToVectorPosition : int8
{
	On = 0,
	Left = 1,
	Right = 2
};

//Check where the point lies relative to the vector
inline PointToVectorPosition CheckPointToVectorPosition(const FloatPoint &  pointLoc, const FloatPoint & vecOrigin, const FloatPoint & vecDirection)
{
	float value =	((pointLoc.GetY() - vecOrigin.GetY())*(vecDirection.GetX() - vecOrigin.GetX())) - 
					((pointLoc.GetX() - vecOrigin.GetX())*(vecDirection.GetY() - vecOrigin.GetY()));
	if (value > 0) { return PointToVectorPosition::Left; }
	if (value < 0) { return PointToVectorPosition::Right; }
	return PointToVectorPosition::On;
}

class AppSettings
{
public:
	static int32 MaxUnits;
	static float AgentSightRadius;
	static float AgentSightHalfAngle;
	static float WorldSize;
};