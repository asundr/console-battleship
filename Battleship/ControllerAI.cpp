#include "ControllerAI.h"

#include <cstdlib>
//#include "Tile.h"

CControllerAI::CControllerAI(CGrid& _grid) : CController(_grid)
{
	m_xAxis = new Point[12];
	m_yAxis = new Point[12];
}

CControllerAI::~CControllerAI()
{
	delete[] m_xAxis;
	delete[] m_yAxis;
}

short CControllerAI::Turn(CController& _opponent)
{
	short type;
	if (m_lastHit.x != -1)
	{
		type = TargetShip(_opponent);
	}
	else
	{
		type = HitRandom(_opponent);
	}
	return type;
}

void CControllerAI::Reset()
{
	CController::Reset();
	m_xLength = 0;
	m_yLength = 0;
	m_lastHit = { -1, -1 };
}

short CControllerAI::HitRandom(CController& _opponent)
{
	short index = rand() % _opponent.Grid().GetFreeTiles();
	short type =  _opponent.Grid().HitNthFreeTile(index, m_lastHit);
	if (type == 1)
	{
		m_lastHit = { -1, -1 };
	}
	return type;
}

short CControllerAI::TargetShip(CController& _opponent)
{
	CGrid& grid = _opponent.Grid();
	static bool xDirection = true;

	if (m_lastHit.x == -1)
	{
		return HitRandom(_opponent);
	}

	if (m_xLength == 0 && m_yLength == 0)	// Initialize search axis
	{
		if (rand() % 2 == 0)
		{
			m_xAxis[m_xLength++] = m_lastHit;
			xDirection = true;
		}
		else
		{
			m_yAxis[m_yLength++] = m_lastHit;
			xDirection = false;
		}
	}

	Point pCurr = { -1, -1 };
	if (m_yLength == 0 || m_xLength != 0 && xDirection)		// Pick axis to search
	{
		Point xLast = m_xAxis[m_xLength - 1];
		pCurr = HitAlongAxis(grid, xLast, true);
		if (pCurr.x == -1)
		{
			m_yAxis[m_yLength++] = m_xAxis[--m_xLength]; // check other axis if ship not destroyed
			xDirection = false;
		}
		else if (grid.GetTile(pCurr.x, pCurr.y).Type() != 1)
		{
			m_yAxis[m_yLength++] = pCurr;
		}
	}
	else
	{
		Point yLast = m_yAxis[m_yLength - 1];
		pCurr = HitAlongAxis(grid, yLast, false);
		if (pCurr.x == -1)
		{
			m_xAxis[m_xLength++] = m_yAxis[--m_yLength]; // check other axis if ship not destroyed
			xDirection = true;
		}
		else if (grid.GetTile(pCurr.x, pCurr.y).Type() != 1)
		{
			m_xAxis[m_xLength++] = pCurr;
		}
	}
	if (pCurr.x == -1)
	{
		return TargetShip(_opponent); // retry with other axis or Point
	}
	
	short type = grid.HitTile(pCurr.x, pCurr.y);
	if (_opponent.CountOfType(type) == 1)  // ship about to be destroyed
	{
		CleanAxisOfType(grid, m_xAxis, m_xLength, type);
		CleanAxisOfType(grid, m_yAxis, m_yLength, type);

		if (m_xLength == 0 && m_yLength == 0)
		{
			m_lastHit = { -1, -1 };
		}
		else
		{
			xDirection = m_yLength == 0 || m_xLength != 0 && m_xLength < m_yLength;
			m_lastHit = xDirection ? m_xAxis[m_xLength-1] : m_yAxis[m_yLength-1];

		}
	}
	return type;
}

// Returns a point at the end of a continuous line of hit ships, else nullptr
Point CControllerAI::HitAlongAxis(CGrid& _grid, Point& _lastHit, bool _xAxis)
{
	Point direction = { _xAxis ? 1 : 0, _xAxis ? 0 : 1 };
	Point pMax = TryToFindBoatEnd(_grid, _lastHit, direction.x, direction.y);
	Point pMin = TryToFindBoatEnd(_grid, _lastHit, -direction.x, -direction.y);
	
	if (pMax.x != -1 && pMin.x != -1)
	{
		return rand() % 2 == 1 ? pMax : pMin;
	}
	return pMax.x != -1 ? pMax : pMin;
}

Point CControllerAI::TryToFindBoatEnd(CGrid& _grid, Point& _lastHit, short _dx, short _dy)
{
	short xCurr = _lastHit.x, yCurr = _lastHit.y;
	do
	{
		xCurr += _dx;
		yCurr += _dy;
	} while (
		_grid.IsInBounds(xCurr, yCurr)
		&& !_grid.CanHitTile(xCurr, yCurr)
		&& _grid.GetTile(xCurr, yCurr).Type() != -1
	);

	if (!_grid.IsInBounds(xCurr, yCurr) || !_grid.CanHitTile(xCurr, yCurr))
	{
		return { -1,-1 };
	}
	Point out = { xCurr, yCurr };
	return out;
}

void CControllerAI::CleanAxisOfType(CGrid& _grid, Point* _axis, short& _length, short _type)
{
	short max = _length;
	_length = 0;
	for (int i = 0; i < max; ++i)
	{
		Point& pCurr = _axis[i];
		if (_grid.GetTile(pCurr.x, pCurr.y).Type() != -_type)
		{
			_axis[_length++] = pCurr;
		}
	}
}
