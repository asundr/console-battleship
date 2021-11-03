#pragma once

#include "Tile.h"

#ifndef __Point__
#define __Point__
struct Point
{
	short x, y;
};
#endif


//class CTile
//{
////private:
//public:
//	short value = 1;
//};


class CGrid
{
public:
	CGrid(const Point& _origin, short _width = 10, short _height = 10);
	~CGrid();
	short Width() const;
	short Height() const;
	const Point& Origin() const;
	CTile& GetTile(short _x, short _y) const;
	void SetTile(short _x, short _y, const CTile& _tile); // TODO delete?
	void HitTile(short _x, short _y);
	bool CanHitTile(short _x, short _y) const;
	short GetFreeTiles() const;
	CTile& GetNthFreeTile(short num) const;
	void Display() const;
private:
	short m_width, m_height;
	Point m_origin;
	bool m_visible = false;
	CTile* m_tiles;
	short m_hitCount = 0;
	inline short Index(short _x, short _y) const 
	{
		return _y * m_width + _x;
	}
};
