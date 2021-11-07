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
	for (short i = m_shipCount - 1; i >= 0; --i)
	{
		short x = rand() % m_grid.Width();
		short y = rand() % m_grid.Height();
		while (!m_grid.TryToPlaceShip(x, y, m_ships[i], 1, i + 2))
		{
			x = rand() % m_grid.Width();
			y = rand() % m_grid.Height();
		}
	}
}

#include <iostream> // TODO remove

void CController::UpdateShips(short _type)
{
	if (_type < 2 || _type > 6)
	{
		return;
	}
	short& typeCount = m_ships[_type - 2];
	--typeCount;
	std::cout << m_ships[_type - 2];
	if (typeCount == 0)
	{
		// output "destroyed ship"
	}
	//check if all ships destroyed -> loss/win
}
