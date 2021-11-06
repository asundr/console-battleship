#include <cstdlib>
#include "Controller.h"
#include "Tile.h"

CController::CController(const CGrid& _grid) : m_grid(_grid)
{

}

CController::~CController()
{

}

CGrid& CController::Grid()
{
	return m_grid;
}

void CController::PlaceShipsRandom()
{
	for (short i = m_shipCount - 1; i >= 0; --i)	// TODO WIP
	{
		short x = rand() % (m_grid.Width() - 1);
		short y = rand() % (m_grid.Height() - 1);
		while (!m_grid.TryToPlaceShip(x, y, m_ships[i], 1, i + 2))
		{
			x = rand() % (m_grid.Width() - 1);
			y = rand() % (m_grid.Height() - 1);
		}
	}
}

