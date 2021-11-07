#include "ControllerAI.h"

#include <cstdlib>
#include "Tile.h"

CControllerAI::CControllerAI(CGrid& _grid) : CController(_grid)
{
	
}

CControllerAI::~CControllerAI()
{

}

bool CControllerAI::Turn(CController& _opponent)
{
	short type = HitRandom(_opponent);
	return _opponent.UpdateShips(type);
}

short CControllerAI::HitRandom(CController& _opponent) const
{
	short index = rand() % _opponent.Grid().GetFreeTiles();
	return _opponent.Grid().HitNthFreeTile(index);
}

