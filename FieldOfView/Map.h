#pragma once
#include "DataClasses.h"
#include "Unit.h"

class Map
{
public:
#pragma region GetSet
	inline void		SetMapSize(const IntPoint& newsize)	{ mapSize = newsize; }
	inline IntPoint GetMapSize()						{ return mapSize; }

	int		AddUnit(float posX, float posY, float dirX, float dirY, float fovAngle, float fovRange);
	Unit&	GetUnit(uint32 id);
	void	DeleteUnit(uint32 id);
	inline	uint32	GetUnitCount() { return UnitCount; }
#pragma endregion GetSet
protected:
	IntPoint mapSize{ 10,10 };

	uint32 UnitCount = 0;
	std::vector<Unit> unitArr;
};

