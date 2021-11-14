#include "Grid.h"
#include <cstdlib>
#include "Tile.h"
#include "Console.h"

CGrid::CGrid(const Bounds& _bounds)
{
	m_bounds = new Bounds(_bounds);
	m_tiles = new CTile[_bounds.width * _bounds.height];
	Reset();
}

CGrid::CGrid(const Point& _origin) : CGrid(Bounds{_origin.x, _origin.y, 10,10})
{
}

CGrid::~CGrid()
{
	delete[] m_tiles;
}

short CGrid::Width() const
{
	return m_bounds->width;
}

short CGrid::Height() const
{
	return m_bounds->height;
}

void CGrid::SetVisible(bool _isVisible)
{
	m_visible = _isVisible;
}

CTile& CGrid::GetTile(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)];
}

void CGrid::SetTile(short _x, short _y, const CTile& _tile) const
{
	m_tiles[Index(_x, _y)] = _tile;;
}

TileType CGrid::HitTile(short _x, short _y)
{
	++m_hitCount;
	CTile& tile = m_tiles[Index(_x, _y)];
	TileType type = tile.Type();
	tile.Hit();
	DrawTileAt(_x, _y, tile, m_visible);
	return type;
}

bool CGrid::CanHitTile(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)].CanHit();
}

TileType CGrid::GetTileType(short _x, short _y) const
{
	return m_tiles[Index(_x, _y)].Type();
}

short CGrid::GetFreeTiles() const
{
	return m_bounds->width * m_bounds->height - m_hitCount;
}

// Iterates though tiles hitting n-th tiles that has not been hit
TileType CGrid::HitNthFreeTile(short _count, Point& _hitCoords)
{
	for (short r = 0; r < m_bounds->height; ++r)
	{
		for (short c = 0; c < m_bounds->width; ++c)
		{
			CTile& tile = m_tiles[Index(c, r)];
			if (!tile.CanHit())
			{
				continue;
			}
			else if (_count == 0)
			{
				_hitCoords.x = c;
				_hitCoords.y = r;
				return HitTile(c, r);
			}
			else
			{
				--_count;
			}
		}
	}
	return TileType::NONE;
}

// Iterates over a 2D region, performing the passed action for each tile
void CGrid::ActionOverRegion(void (*_action)(const CGrid&, const CTile&,short,short,bool), const Bounds& _bounds) const
{
	for (short r = 0; r < _bounds.height; ++r)
	{
		for (short c = 0; c < _bounds.width; ++c)
		{
			short i = _bounds.x + c;
			short j = _bounds.y + r;
			_action(*this, m_tiles[Index(i, j)], i, j, m_visible);
		}
	}
}

// Redraws the tiles within the bounds to their default display
void CGrid::RevertTiles(const Bounds& _bounds) const
{
	ActionOverRegion([](const CGrid& _grid, const CTile& tile, short x, short y, bool visible) -> 
		void { _grid.DrawTileAt(x, y, tile, visible); }, _bounds);
}

// Draws tiles over a region to indicate a valid selection
void CGrid::DrawSelection(const Bounds& _bounds) const
{
	ActionOverRegion([](const CGrid& _grid, const CTile& tile, short x, short y, bool visible) ->
		void { _grid.DrawTileAt(x, y, CTile(TileType::SELECITON_GOOD)); }, _bounds);
}

// Draws tiles over a region to indicate an invalid selection
void CGrid::DrawSelectionError(const Bounds& _bounds) const
{
	ActionOverRegion([](const CGrid& _grid, const CTile& tile, short x, short y, bool visible) ->
		void { _grid.DrawTileAt(x, y, CTile(TileType::SELECTION_BAD)); }, _bounds);
}

// Returns true if bounds contain only unhit, empty tiles
bool CGrid::IsRegionEmpty(const Bounds& _bounds) const
{
	if (!IsRegionInBounds(_bounds))
	{
		return false;
	}
	for (short i = 0; i < _bounds.width; ++i)
	{
		for (short j = 0; j < _bounds.height; ++j)
		{
			if (m_tiles[Index(_bounds.x + i, _bounds.y + j)].Type() != TileType::EMPTY)
			{
				return false;
			}
		}
	}
	return true;
}

// Attempts to add a ship with the passed bounds to an empty region of the grid, true if successful
bool CGrid::TryToPlaceShip(const Bounds& _bounds, TileType _type, bool _randomOrientation) const
{
	if (!_randomOrientation)
	{
		return IsRegionEmpty(_bounds) && FillRegion(_bounds, _type);
	}
	bool swap = rand() % 2 == 1;
	short width = swap ? _bounds.height : _bounds.width;
	short height = swap ? _bounds.width : _bounds.height;
	Bounds b1 = { _bounds.x, _bounds.y, width, height };
	Bounds b2 = { _bounds.x, _bounds.y, height, width };
	return IsRegionEmpty(b1) && FillRegion(b1, _type)
		|| IsRegionEmpty(b2) && FillRegion(b2, _type);
}

// Attempts to fill a region with a type of tile, returns true if successful
bool CGrid::FillRegion(const Bounds& _bounds, TileType _type) const
{
	if (!IsRegionInBounds(_bounds))
	{
		return false;
	}
	for (short i = 0; i < _bounds.width; ++i)
	{
		for (short j = 0; j < _bounds.height; ++j)
		{
			SetTile(_bounds.x + i, _bounds.y + j, CTile(_type));
		}
	}
	return true;
}

// Returns true if the coordinate exists in the grid
bool CGrid::IsInBounds(short _x, short _y) const
{
	return _x >= 0 && _x < m_bounds->width && _y >= 0 && _y < m_bounds->height;
}

// Returns true if every tile in thee bounds exists in the grid
bool CGrid::IsRegionInBounds(const Bounds& _bounds) const
{
	return IsInBounds(_bounds.x, _bounds.y) 
		&& IsInBounds(_bounds.x + _bounds.width - 1, _bounds.y + _bounds.height - 1);
}

// Redraws the entire grid
void CGrid::Draw() const
{
	for (short y = 0; y < m_bounds->height; ++y)
	{
		for (short x = 0; x < m_bounds->width; ++x)
		{
			DrawTileAt(x, y, m_tiles[Index(x, y)], m_visible);
		}
	}
	Display::ResetConsoleText();
}

void CGrid::DamageFlash() const
{
	for (short y = 0; y < m_bounds->height; ++y)
	{
		for (short x = 0; x < m_bounds->width; ++x)
		{
			DrawTileAt(x, y, CTile(TileType::SELECTION_BAD), true);
		}
	}
	//Display::ResetConsoleText();
	Draw();
}

// Draws the passed tile at the passed coordinate
void CGrid::DrawTileAt(short _x, short _y, const CTile& _tile, bool _isVisible) const
{
	short dispX = m_bounds->x + _x * CTile::s_width;
	short dispY = m_bounds->y + _y * CTile::s_height;
	_tile.Draw(dispX, dispY, _isVisible);
	Display::ResetConsoleText();
}

// Returns the grid to a new games state
void CGrid::Reset()
{
	selector = nullptr;
	m_hitCount = 0;
	for (int i = m_bounds->width * m_bounds->height - 1; i >= 0; --i)
	{
		m_tiles[i] = CTile();
	}
}
