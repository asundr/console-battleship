#include "Controller.h"
#include <cstdlib>
#include "Grid.h"

const short CController::s_shipSize[] = { 2, 3, 3, 4, 5 };

CController::CController(CGrid& _grid) : m_grid(_grid)
{
	Reset();
}

CController::~CController()
{
}

CGrid& CController::Grid() const
{
	return m_grid;
}

void CController::PlaceShipsRandom()
{
	short x, y;
	for (short i = s_shipTypeCount - 1; i >= 0; --i)
	{
		do
		{
			x = rand() % m_grid.Width();
			y = rand() % m_grid.Height();
		} while ( !m_grid.TryToPlaceShip(x, y, m_ships[i], 1, IndexToType(i)) );
	}
}

// Updates ship lives and returns true if hit
bool CController::UpdateShips(short _type)
{
	if (_type < 2 || _type > 6)
	{
		return false;
	}
	short& typeCount = m_ships[TypeToIndex(_type)];
	--typeCount;
	return typeCount == 0;
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

// Returns number of not hit sections of the passed type of ship
short CController::CountOfType(short _type) const
{
	return m_ships[TypeToIndex(_type)];
}

void CController::Reset()
{
	for (short i = 0; i < s_shipTypeCount; ++i)
	{
		m_ships[i] = s_shipSize[i];
	}
}
