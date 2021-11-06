#pragma once

#include "Controller.h"
#include "ControllerAI.h"

class CPlayer : public CController
{
public:
	CPlayer(CGrid& _grid);
	~CPlayer();
	void Turn(CController& _opponent);
	void SetSelectorBounds(CGrid& _grid, short _x, short _y, short _width, short _height);
	void SetSelectorBounds(short _x, short _y, short _width, short _height);
	bool SetSelector(Point& _coord, CGrid& _grid);
	bool SetSelector(Point& _coord);
	bool ShiftSelector(Point& _shift, CGrid& _grid);
	bool ShiftSelector(Point& _shift);
	bool ToggleSelectorRotation(CGrid& _grid);
	bool ToggleSelectorRotation();
	void RevertTiles(CGrid& _grid);
	void DrawSelection(CGrid& _grid) const;
	void PlaceShips();
	bool HandleSelctionInput(short _value);
	bool HandleSelctionInput(short _value, CGrid& _grid);
private:
	Point m_selector = { 0, 0 };
	Point m_selectorBounds = { 0, 0 };
};

