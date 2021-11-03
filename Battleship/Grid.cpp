#include <iostream>

#include "Grid.h"
#include "Console.h"

CGrid::CGrid(const Point& _origin, short _width, short _height) 
		: m_origin(Point(_origin)), m_width(_width), m_height(_height)
{
	m_tiles = new CTile[m_width * m_height];
	const short max = m_width * m_height;
//	for (short i = 0; i < max; ++i)
//	{
//		m_tiles[i] = Tile(); // TODO double check if this is copied
//	}
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
}

void CGrid::Display() const
{
	for (short y = 0; y < m_height; ++y)
	{
		for (short x = 0; x < m_width; ++x)
		{
			short dispX = m_origin.x + x * CTile::s_width;
			short dispY = m_origin.y + y * CTile::s_height;
			m_tiles[Index(x, y)].Draw(dispX, dispY); 
		}
	}
	ResetConsoleText();
}