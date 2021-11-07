#include <cstdlib>
#include "Controller.h"
#include "Tile.h"

CController::CController(const CGrid& _grid) : m_grid(_grid)
{
	Reset();
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

// Updates ship lives and returns true if all ships have been lost
bool CController::UpdateShips(short _type)
{
	if (_type < 2 || _type > 6)
	{
		return false;
	}
	short& typeCount = m_ships[_type - 2];
	--typeCount;
	std::cout << m_ships[_type - 2];
	if (typeCount == 0)
	{
		std::cout << "Ship " << _type << " destroyed!" << std::endl;
		if (HasLostAllShips())
		{
			//std::cout << "VICOTRY\n";
			return true;
		}
	}
	return false;
}

// Returns true if all ships have been lost
bool CController::HasLostAllShips() const
{
	for (short count : m_ships)
	{
		if (count > 0)
		{
			return false;
		}
	}
	return true;
}

void CController::Reset()
{
	static short ships[] = { 2, 3, 3, 4, 5 };
	for (short i = 0; i < m_shipCount; ++i)
	{
		m_ships[i] = ships[i];
	}
}