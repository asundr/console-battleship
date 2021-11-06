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
	PickRandom(_opponent.Grid());
}

void CControllerAI::PickRandom(CGrid& _grid) const
{
	short index = rand() % _grid.GetFreeTiles();
	_grid.HitNthFreeTile(index);
}

