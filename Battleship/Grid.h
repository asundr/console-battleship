#pragma once

#include "Tile.h"

#ifndef __Point__
#define __Point__
struct Point
{
	short x, y;
};
#endif

class CGrid
{
public:
	CGrid(const Point& _origin, short _width = 10, short _height = 10);
	~CGrid();
	short Width() const;
	short Height() const;
	const Point& Origin() const;
	void SetVisible(bool _isVisible);
	CTile& GetTile(short _x, short _y) const;
	void SetTile(short _x, short _y, const CTile& _tile);
	short HitTile(short _x, short _y);
	bool CanHitTile(short _x, short _y) const;
	short GetFreeTiles() const;
	short HitNthFreeTile(short _num, Point& _hitCoords);
	void ActionOverRegion(void (*action)(const CGrid&, CTile&, short, short, bool), short _x, short _y, short _width, short _height) const;
	void RevertTiles(short _x, short _y, short _width, short _height) const;
	void DrawSelection(short _x, short _y, short _width, short _height) const;
	void DrawSelectionError(short _x, short _y, short _width, short _height) const;
	bool IsRegionEmpty(short x, short y, short width, short length) const;
	bool FillRegion(short _x, short _y, short _width, short _length, short type);
	bool TryToPlaceShip(short _x, short _y, short _width, short _height, short _type, bool _randomOrientation = false);
	bool IsInBounds(short x, short y) const;
	bool IsRegionInBounds(short _x, short _y, short _width, short _height) const;
	void Display() const;
	void DrawTileAt(short _x, short _y, CTile& _tile, bool _isVisible = true) const;
	void Reset();
private:
	short m_width, m_height;
	Point m_origin;
	bool m_visible = false;
	CTile* m_tiles;
	short m_hitCount = 0;
	Point* selector = nullptr;
	inline short Index(short _x, short _y) const 
	{
		return _y * m_width + _x;
	}
};
