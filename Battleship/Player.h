#pragma once

#include "Controller.h"

class CPlayer : public CController
{
public:
	CPlayer(CGrid& _grid);
	~CPlayer();
	void SetSelectorBounds(short _x, short _y, short _width, short _height);
	bool SetSelector(Point& _coord, CGrid& _grid);
	bool SetSelector(Point& _coord);
	bool ShiftSelector(Point& _shift, CGrid& _grid);
	bool ShiftSelector(Point& _shift);
	bool ToggleSelectorRotation(CGrid& _grid);
	bool ToggleSelectorRotation();
	void RevertTiles(CGrid& _grid);
	void DrawSelection(CGrid& _grid) const;
	void ResetSelector(CGrid& _grid);
	static void DrawSelectorTile(CGrid& _grid, short _x, short _y);
private:
	Point m_selector = { 0, 0 };
	Point m_selectorBounds = { 0, 0 };
	static CTile selectorTile;
};

