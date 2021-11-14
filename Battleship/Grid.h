#pragma once

enum class TileType;
class CTile;

#ifndef __Point__
#define __Point__
struct Point
{
	short x, y;
};
#endif

#ifndef __BOUNDS__
#define __BOUNDS__
struct Bounds
{
	short x = 0, y = 0, width = 1, height = 1;
};
#endif

class CGrid
{
public:
	CGrid(const Bounds& _bounds);
	CGrid(const Point& _origin);
	~CGrid();
	short Width() const;
	short Height() const;
	void SetVisible(bool _isVisible);
	CTile& GetTile(short _x, short _y) const;
	void SetTile(short _x, short _y, const CTile& _tile) const;
	TileType HitTile(short _x, short _y);
	bool CanHitTile(short _x, short _y) const;
	TileType GetTileType(short _x, short _y) const;
	short GetFreeTiles() const;
	TileType HitNthFreeTile(short _num, Point& _hitCoords);
	void ActionOverRegion(void (*action)(const CGrid&, const CTile&, short, short, bool), const Bounds& _bounds) const;
	void RevertTiles(const Bounds& _bounds) const;
	void DrawSelection(const Bounds& _bounds) const;
	void DrawSelectionError(const Bounds& _bounds) const;
	bool IsRegionEmpty(const Bounds& _bounds) const;
	bool TryToPlaceShip(const Bounds& _bounds, TileType _type, bool _randomOrientation = false) const;
	bool FillRegion(const Bounds& _bounds, TileType _type) const;
	bool IsInBounds(short _x, short _y) const;
	bool IsRegionInBounds(const Bounds& _bounds) const;
	void Display() const;
	void DrawTileAt(short _x, short _y, const CTile& _tile, bool _isVisible = true) const;
	void Reset();
private:
	Bounds* m_bounds;
	bool m_visible = false;
	CTile* m_tiles;
	short m_hitCount = 0;
	Point* selector = nullptr;
	inline short Index(short _x, short _y) const 
	{
		return _y * m_bounds->width + _x;
	}
};
