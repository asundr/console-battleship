#include <iostream>

#include "Grid.h"
#include "Console.h"

CGrid::CGrid(const Point& _origin, short _width, short _height) 
		: m_origin(Point(_origin)), m_width(_width), m_height(_height)
{
	m_tiles = new CTile[m_width * m_height];
	const short max = m_width * m_height;
	Reset();
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

void CGrid::SetVisible(bool _isVisible)
{
	m_visible = _isVisible;
}

CTile& CGrid::GetTile(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)];
}

void CGrid::SetTile(short _x, short _y, const CTile& _tile)
{
	m_tiles[Index(_x, _y)] = _tile;;
}

short CGrid::HitTile(short _x, short _y)
{
	++m_hitCount;
	CTile& tile = m_tiles[Index(_x, _y)];
	short type = tile.Type();
	tile.Hit();
	DrawTileAt(_x, _y, tile, m_visible);
	return type;
}

bool CGrid::CanHitTile(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)].CanHit();
}

short CGrid::GetFreeTiles() const
{
	return m_width * m_height - m_hitCount;
}

short CGrid::HitNthFreeTile(short n, Point& _hitCoords)
{
	for (short r = 0; r < m_height; ++r)
	{
		for (short c = 0; c < m_width; ++c)
		{
			CTile& tile = m_tiles[Index(c, r)];
			if (!tile.CanHit())
			{
				continue;
			}
			else if (n == 0)
			{
				_hitCoords.x = c;
				_hitCoords.y = r;
				return HitTile(c, r);
			}
			else
			{
				--n;
			}
		}
	}
	return 0;
}

void CGrid::ActionOverRegion(void (*action)(CGrid&, CTile&,short,short,bool), short _x, short _y, short _width, short _height)
{
	for (short r = 0; r < _height; ++r)
	{
		for (short c = 0; c < _width; ++c)
		{
			short i = _x + c;
			short j = _y + r;
			action(*this, m_tiles[Index(i, j)], i, j, m_visible);
		}
	}
}

void CGrid::RevertTiles(short _x, short _y, short _width, short _height) 
{
	ActionOverRegion([](CGrid& _grid, CTile& tile, short x, short y, bool visible) -> void { _grid.DrawTileAt(x, y, tile, visible); },
		_x, _y, _width, _height);
}

void CGrid::DrawSelection(short _x, short _y, short _width, short _height)
{
	ActionOverRegion([](CGrid& _grid, CTile& tile, short x, short y, bool visible) -> void { _grid.DrawTileAt(x, y, CTile::s_selectorTile); },
		_x, _y, _width, _height);
}

void CGrid::DrawSelectionError(short _x, short _y, short _width, short _height)
{
	ActionOverRegion([](CGrid& _grid, CTile& tile, short x, short y, bool visible) -> void { _grid.DrawTileAt(x, y, CTile::s_errorTile); },
		_x, _y, _width, _height);
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

bool CGrid::TryToPlaceShip(short _x, short _y, short _width, short _height, short _type, bool _randomOrientation)
{
	if (!_randomOrientation)
	{
		return IsRegionEmpty(_x, _y, _width, _height) && FillRegion(_x, _y, _width, _height, _type);
	}
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
			DrawTileAt(x, y, m_tiles[Index(x, y)], m_visible);
		}
	}
	ResetConsoleText();
}

void CGrid::DrawTileAt(short _x, short _y, CTile& _tile, bool _isVisible) const
{
	short dispX = m_origin.x + _x * CTile::s_width;
	short dispY = m_origin.y + _y * CTile::s_height;
	_tile.Draw(dispX, dispY, _isVisible);
	ResetConsoleText();
}

void CGrid::Reset()
{
	selector = nullptr;
	m_hitCount = 0;
	for (int i = m_width * m_height - 1; i >= 0; --i)
	{
		m_tiles[i] = CTile();
	}
}