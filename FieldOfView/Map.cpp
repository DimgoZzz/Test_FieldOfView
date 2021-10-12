#include "Map.h"
#include "WinMin.h"

int32 Map::AddUnit(float posX, float posY, float dirX, float dirY, float fovAngle, float fovRange)
{
	//Возможно можно улучшить?
	unitArr.push_back(Unit{ posX,posY,dirX,dirY,fovAngle,fovRange,static_cast<uint32>(unitArr.size())});
	return 0;
}

Unit& Map::GetUnit(int32 id)
{
	if(id < 0 || (int)unitArr.size() < id)
	{
		CritErr("Error:\n Cant Find Unit ID");
	}
	return unitArr[id];
}

void Map::DeleteUnit(int32 id)
{
}
