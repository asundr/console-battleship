#pragma once

#include "Controller.h"

struct Point;
class CControllerAI;

class CPlayer : public CController
{
public:
	CPlayer(CGrid& _grid);
	~CPlayer();
	void Reset();
	short Turn(CController& _opponent);
	void UpdateSelectorBounds(short _x, short _y, short _width, short _height, CGrid& _grid);
	void UpdateSelectorBounds(short _x, short _y, short _width, short _height);
	bool UpdateSelector(const Point& _coord, CGrid& _grid);
	bool UpdateSelector(const Point& _coord);
	bool ShiftSelector(const Point& _shift, CGrid& _grid);
	bool ShiftSelector(const Point& _shift);
	bool ToggleSelectorRotation(CGrid& _grid);
	bool ToggleSelectorRotation();
	void RevertTiles(CGrid& _grid) const;
	void DrawSelection(CGrid& _grid) const;
	void PlaceShips();
	short HandleSelctionInput(short _value);
	short HandleSelctionInput(short _value, CController& _opponent);
protected:
	Point* m_selector;
	Point* m_selectorBounds;
	void SetSelector(short _x, short _y);
	void SetSelectorBounds(short _x, short _y);
};

