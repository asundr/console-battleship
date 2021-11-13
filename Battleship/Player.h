#pragma once

#include "Controller.h"

enum class TileType;
struct Point;
class CControllerAI;

class CPlayer : public CController
{
public:
	CPlayer(CGrid& _grid);
	~CPlayer();
	void Reset();
	TileType Turn(CController& _opponent);
	void UpdateSelectorBounds(short _x, short _y, short _width, short _height, const CGrid& _grid);
	void UpdateSelectorBounds(short _x, short _y, short _width, short _height);
	bool UpdateSelector(const Point& _coord, const CGrid& _grid);
	bool UpdateSelector(const Point& _coord);
	bool ShiftSelector(const Point& _shift, const CGrid& _grid);
	bool ShiftSelector(const Point& _shift);
	bool ToggleSelectorRotation(const CGrid& _grid);
	bool ToggleSelectorRotation();
	void RevertTiles(const CGrid& _grid) const;
	void DrawSelection(const CGrid& _grid) const;
	void PlaceShips();
	TileType HandleSelctionInput(TileType _type);
	TileType HandleSelctionInput(TileType _type, const CController& _opponent);
protected:
	Point* m_selector;
	Point* m_selectorBounds;
	void SetSelector(short _x, short _y);
	void SetSelectorBounds(short _x, short _y);
};
