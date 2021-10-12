#pragma once
#include "DataClasses.h"

class Unit
{
public:
	Unit(float posX, float PosY, float dirX, float dirY, float fovAngle, float fovRange, uint32 id);
#pragma region GetSet
	inline	void		SetPosition(const FloatPoint& newpos)	{ position = newpos; }
	inline	void		SetPosition(float nx, float ny)			{ position = FloatPoint(nx, ny); }
	inline	void		SetDirection(const FloatPoint& newdir)	{ direction = newdir;}
	inline	void		SetDirection(float nx, float ny)		{ direction = FloatPoint(nx, ny); }

	inline	void		SetFieldOfViewAngle(float fov)			{ fieldOfViewAngle = fov; }
	inline	void		SetFieldOfViewRange(float fov)			{ fieldOfViewRange = fov; }
	inline	void		SetID(uint32 id)						{ unitID = id; }

	inline	FloatPoint	GetPosition()			const			{ return position; }
	inline	FloatPoint	GetDirection()			const			{ return direction; }
	inline	float		GetFieldOfViewAngle()	const			{ return fieldOfViewAngle; }
	inline	float		GetFieldOfViewRange()	const			{ return fieldOfViewRange; }
	inline	uint32		GetID()					const			{ return unitID; }
#pragma endregion GetSet

	bool CanSeeUnit(Unit const& unit)const;
protected:
	FloatPoint position{ 0.f,0.f };
	FloatPoint direction{ 0.f,0.f };
	float fieldOfViewAngle;
	float fieldOfViewRange;
	uint32 unitID;
};

