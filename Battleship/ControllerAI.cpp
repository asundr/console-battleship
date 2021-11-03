#include "ControllerAI.h"

#include <cstdlib>
#include "Tile.h"

CControllerAI::CControllerAI()
{

}

CControllerAI::~CControllerAI()
{

}

void CControllerAI::Turn(CGrid& oponentGrid) const
{

}

void CControllerAI::PickRandom(CGrid& opponentGrid) const
{
	short index = rand() % (opponentGrid.GetFreeTiles() - 1);
	CTile tile = opponentGrid.GetNthFreeTile(index);
	tile.Hit();
}