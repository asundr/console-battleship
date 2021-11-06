#pragma once

#include "Grid.h"

class CController
{
public:
	CController(const CGrid& _grid);
	~CController();
	CGrid& Grid();
	void PlaceShipsRandom();
protected:
	short m_shipCount = 5;
	short m_ships[5] = { 2, 3, 3, 4, 5 };
	CGrid m_grid;
};

