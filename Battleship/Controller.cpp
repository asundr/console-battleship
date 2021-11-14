#include "Controller.h"
#include <cstdlib>
#include "Tile.h"
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
	//short x, y;
	Bounds bounds = { 0, 0, 0, 1 };
	for (short i = s_shipTypeCount - 1; i >= 0; --i)
	{
		bounds.width = m_ships[i];
		do
		{
			bounds.x = rand() % m_grid.Width();
			bounds.y = rand() % m_grid.Height();
		} while ( !m_grid.TryToPlaceShip(bounds, IndexToType(i)) );
	}
}

// Updates ship lives and returns true if hit
bool CController::UpdateShips(TileType _type)
{
	if (!CTile::CanHit(_type) || !CTile::IsShip(_type))
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
short CController::CountOfType(TileType _type) const
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
