#include "ControllerAI.h"

#include <cstdlib>
#include "Tile.h"

CControllerAI::CControllerAI(CGrid& _grid) : CController(_grid)
{
	
}

CControllerAI::~CControllerAI()
{

}

void CControllerAI::Turn(CController& _opponent)
{
	HitRandom(_opponent);
}

void CControllerAI::HitRandom(CController& _opponent) const
{
	short index = rand() % _opponent.Grid().GetFreeTiles();
	_opponent.Grid().HitNthFreeTile(index);
}

