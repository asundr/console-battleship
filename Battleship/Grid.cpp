#include <iostream>

#include "Grid.h"
#include "Console.h"

CGrid::CGrid(const Point& _origin, short _width, short _height) 
		: m_origin(Point(_origin)), m_width(_width), m_height(_height)
{
	m_tiles = new CTile[m_width * m_height];
	const short max = m_width * m_height;
}

CGrid::~CGrid()
{
	delete[] m_tiles;
}

short CGrid::Width() const
{
	return m_width;
}

short CGrid::Height() const
{
	return m_height;
}

const Point& CGrid::Origin() const
{
	return m_origin;
}

CTile& CGrid::GetTile(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)];
}

void CGrid::SetTile(short _x, short _y, const CTile& _tile)
{
	m_tiles[Index(_x, _y)] = _tile;;
}

void CGrid::HitTile(short _x, short _y)
{
	++ m_hitCount;
	m_tiles[Index(_x, _y)].Hit();
}

bool CGrid::CanHitTile(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)].CanHit();
}

short CGrid::GetFreeTiles() const
{
	return m_width * m_height - m_hitCount;
}

CTile& CGrid::GetNthFreeTile(short n) const
{
	for (short i = 0; i < m_width * m_height; ++i)
	{
		if (!m_tiles[i].CanHit())
		{
			continue;
		}
		else if (n == 0)
		{
			return m_tiles[i];
		}
		else
		{
			--n;
		}
	}
	return m_tiles[0];//CTile::Null; // TDOD fix w/ equivalent of null
}

// Attemps to perform an repeated action over a line of tiles, returns true if every action successful
bool CGrid::ActionOverTiles(bool (*action)(CTile&), short x, short y, short dx, short dy, short steps) // TODO delete?
{
	if (!IsInBounds(x, y) || !IsInBounds(x + dx * steps, y + dy * steps))
	{
		return false;
	}

	bool valid = true;
	for (short i = 0; valid && i < steps; ++i, x += dx, y += dy)
	{
		valid = action(GetTile(x, y));
	}
	return valid;
}

void CGrid::ActionOverRegion(void (*action)(CGrid&, CTile&,short,short), short _x, short _y, short _width, short _height)
{
	for (short r = 0; r < _height; ++r)
	{
		for (short c = 0; c < _width; ++c)
		{
			short i = _x + c;
			short j = _y + r;
			action(*this, m_tiles[Index(i, j)], i, j);
		}
	}
}

bool CGrid::IsRegionEmpty(short _x, short _y, short _width, short _height) const
{
	if (!IsRegionInBounds(_x, _y, _width, _height))
	{
		return false;
	}
	for (short i = 0; i < _width; ++i)
	{
		for (short j = 0; j < _height; ++j)
		{
			if (m_tiles[Index(_x + i, _y + j)].Type() != 1)
			{
				return false;
			}
		}
	}
	return true;
}

bool CGrid::TryToPlaceShip(short _x, short _y, short _width, short _height, short _type)
{
	bool swap = rand() % 2 == 1;
	short width = swap ? _height : _width;
	short height = swap ? _width : _height;
	return IsRegionEmpty(_x, _y, width, height) && FillRegion(_x, _y, width, height, _type)
		|| IsRegionEmpty(_x, _y, height, width) && FillRegion(_x, _y, height, width, _type);
}

bool CGrid::FillRegion(short _x, short _y, short _width, short _height, short _type)
{
	if (!IsRegionInBounds(_x, _y, _width, _height))
	{
		return false;
	}
	for (short i = 0; i < _width; ++i)
	{
		for (short j = 0; j < _height; ++j)
		{
			SetTile(_x + i, _y + j, _type);
		}
	}
	return true;
}

bool CGrid::IsInBounds(short x, short y) const
{
	return x >= 0 && x < m_width&& y >= 0 && y < m_height;
}

bool CGrid::IsRegionInBounds(short _x, short _y, short _width, short _height) const
{
	return IsInBounds(_x, _y) && IsInBounds(_x + _width - 1, _y + _height - 1);
}

void CGrid::Display() const
{
	for (short y = 0; y < m_height; ++y)
	{
		for (short x = 0; x < m_width; ++x)
		{
			//short dispX = m_origin.x + x * CTile::s_width;
			//short dispY = m_origin.y + y * CTile::s_height;
			//m_tiles[Index(x, y)].Draw(dispX, dispY); 
			DrawTileAt(x, y, m_tiles[Index(x, y)]);
		}
	}
	ResetConsoleText();
}

void CGrid::DrawTileAt(short _x, short _y, CTile& _tile) const
{
	short dispX = m_origin.x + _x * CTile::s_width;
	short dispY = m_origin.y + _y * CTile::s_height;
	_tile.Draw(dispX, dispY);
}
