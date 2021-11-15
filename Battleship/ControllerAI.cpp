#include "ControllerAI.h"
#include <cstdlib>
#include "Grid.h"
#include "Tile.h"
#include "Settings.h"

CControllerAI::CControllerAI(CGrid& _grid) : CController(_grid)
{
	m_target = new Point{ -1, -1 };
	m_xAxis = new Point[12];
	m_yAxis = new Point[12];
}

CControllerAI::~CControllerAI()
{
	delete m_target;
	delete[] m_xAxis;
	delete[] m_yAxis;
}

// AI will fire randomly unless it has hit an incompletely destroyed ship
TileType CControllerAI::Turn(CController& _opponent)
{
	TileType type;
	if (m_target->x != -1 && CSettings::DifficultAI())
	{
		type = TargetShip(_opponent);
	}
	else
	{
		type = HitRandom(_opponent);
	}
	return type;
}

// Returns AI to a new game state
void CControllerAI::Reset()
{
	CController::Reset();
	m_xLength = 0;
	m_yLength = 0;
	SetTarget(-1, -1);
}

void CControllerAI::SetTarget(short _x, short _y)
{
	m_target->x = _x;
	m_target->y = _y;
}

// Uniformly picks from the remaining tiles that haven't been hit
// Sets target to the selected tile coord if a ship is hit
TileType CControllerAI::HitRandom(CController& _opponent)
{
	short index = rand() % _opponent.Grid().GetFreeTiles();
	TileType type =  _opponent.Grid().HitNthFreeTile(index, *m_target);
	if (type == TileType::EMPTY)
	{
		SetTarget(-1, -1);
	}
	return type;
}

// Makes an educated guess to destroy any ships hit in previous turns
TileType CControllerAI::TargetShip(CController& _opponent)
{
	CGrid& grid = _opponent.Grid();
	static bool xDirection = true;

	if (m_target->x == -1)
	{
		return HitRandom(_opponent);
	}

	if (m_xLength == 0 && m_yLength == 0)	// Initialize search axis
	{
		if (rand() % 2 == 0)
		{
			m_xAxis[m_xLength++] = *m_target;
			xDirection = true;
		}
		else
		{
			m_yAxis[m_yLength++] = *m_target;
			xDirection = false;
		}
	}

	Point pCurr = { -1, -1 };
	if (m_yLength == 0 || m_xLength != 0 && xDirection)		// Search along xAxis
	{
		Point xLast = m_xAxis[m_xLength - 1];
		pCurr = FindAlongAxis(grid, xLast, true);
		if (pCurr.x == -1)
		{
			m_yAxis[m_yLength++] = m_xAxis[--m_xLength]; // check other axis if ship not destroyed
			xDirection = false;
		}
		else if (grid.GetTileType(pCurr.x, pCurr.y) != TileType::EMPTY) 
		{
			m_yAxis[m_yLength++] = pCurr;   // add ship tile to memory if hit
		}
	}
	else  // search along yAxis
	{
		Point yLast = m_yAxis[m_yLength - 1];
		pCurr = FindAlongAxis(grid, yLast, false);
		if (pCurr.x == -1)
		{
			m_xAxis[m_xLength++] = m_yAxis[--m_yLength]; // check other axis if ship not destroyed
			xDirection = true;
		}
		else if (grid.GetTileType(pCurr.x, pCurr.y) != TileType::EMPTY)
		{
			m_xAxis[m_xLength++] = pCurr; // add ship tile to memmory if hit
		}
	}
	if (pCurr.x == -1) // no good choices on axis, retry with other axis or past hit
	{
		return TargetShip(_opponent); 
	}
	
	TileType type = grid.HitTile(pCurr.x, pCurr.y);
	if (_opponent.CountOfType(type) == 1)  // ship about to be destroyed
	{
		// clean memory of all tiles from destroyed ship
		CleanAxisOfType(grid, m_xAxis, m_xLength, type);
		CleanAxisOfType(grid, m_yAxis, m_yLength, type);

		// Target coord of any discoved but un-destroyed ships
		if (m_xLength == 0 && m_yLength == 0)
		{
			SetTarget(-1, -1);
		}
		else
		{
			xDirection = m_yLength == 0 || m_xLength != 0 && m_xLength < m_yLength;
			Point pNext = xDirection ? m_xAxis[m_xLength-1] : m_yAxis[m_yLength-1];
			SetTarget(pNext.x, pNext.y);
		}
	}
	return type;
}

// Returns either point at the end of a continuous line of hit ships, else (-1,-1)
Point CControllerAI::FindAlongAxis(const CGrid& _grid, const Point& _target, bool _isXAxis) const
{
	Point direction = { _isXAxis ? 1 : 0, _isXAxis ? 0 : 1 };
	Point pMax = FindBoatEnd(_grid, _target, direction.x, direction.y);
	Point pMin = FindBoatEnd(_grid, _target, -direction.x, -direction.y);
	
	if (pMax.x != -1 && pMin.x != -1)
	{
		return rand() % 2 == 1 ? pMax : pMin;
	}
	return pMax.x != -1 ? pMax : pMin;
}

// Returns a point at specific end of a continuous line of hit ships, else (-1,-1)
Point CControllerAI::FindBoatEnd(const CGrid& _grid, const Point& _target, short _dx, short _dy) const
{
	short xCurr = _target.x, yCurr = _target.y;
	do
	{
		xCurr += _dx;
		yCurr += _dy;
	} while (
		_grid.IsInBounds(xCurr, yCurr)
		&& !_grid.CanHitTile(xCurr, yCurr)
		&& _grid.GetTileType(xCurr, yCurr) != TileType::MISS
	);

	if (!_grid.IsInBounds(xCurr, yCurr) || !_grid.CanHitTile(xCurr, yCurr))
	{
		return { -1,-1 };
	}
	return { xCurr, yCurr };
}

// Removes all coords from array that match the damaged id of the passed TileType
void CControllerAI::CleanAxisOfType(const CGrid& _grid, Point* _axis, short& _length, TileType _type)
{
	TileType hitType = CTile::DamageType(_type);
	short max = _length;
	_length = 0;
	for (int i = 0; i < max; ++i)
	{
		Point& pCurr = _axis[i];
		if (_grid.GetTileType(pCurr.x, pCurr.y) != hitType)
		{
			_axis[_length++] = pCurr;
		}
	}
}
