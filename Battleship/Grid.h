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
	CTile& GetTile(short _x, short _y) const;
	void SetTile(short _x, short _y, const CTile& _tile);
	short HitTile(short _x, short _y);
	bool CanHitTile(short _x, short _y) const;
	short GetFreeTiles() const;
	short HitNthFreeTile(short num);
	//bool ActionOverTiles(bool (*action)(CTile&), short x, short y, short dx, short dy, short steps); // TODO delete?
	void ActionOverRegion(void (*action)(CGrid&, CTile&, short, short), short _x, short _y, short _width, short _height);
	void RevertTiles(short _x, short _y, short _width, short _height);
	void DrawSelection(short _x, short _y, short _width, short _height);
	void DrawSelectionError(short _x, short _y, short _width, short _height);
	bool IsRegionEmpty(short x, short y, short width, short length) const;
	bool FillRegion(short _x, short _y, short _width, short _length, short type);
	bool TryToPlaceShip(short _x, short _y, short _width, short _height, short _type, bool _randomOrientation = false);
	bool IsInBounds(short x, short y) const;
	bool IsRegionInBounds(short _x, short _y, short _width, short _height) const;
	void Display() const;
	void DrawTileAt(short _x, short _y, CTile& _tile) const;
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
