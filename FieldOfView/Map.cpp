#include "Map.h"
#include "WinMin.h"

int32 Map::AddUnit(float posX, float posY, float dirX, float dirY, float fovAngle, float fovRange)
{
	//Возможно можно улучшить?
	unitArr.push_back(Unit{ posX,posY,dirX,dirY,fovAngle,fovRange,static_cast<uint32>(unitArr.size())});
	++UnitCount;
	return 0;
}

Unit& Map::GetUnit(uint32 id)
{
	if(id < 0 || UnitCount < id)
	{
		CritErr("Error:\n Cant Find Unit ID");
	}
	return unitArr[id];
}

void Map::DeleteUnit(uint32 id)
{
	//to do
}
