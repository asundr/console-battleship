#pragma once

#include "Grid.h"

class CController
{
public:
	CController(const CGrid& _grid);
	~CController();
	CGrid& Grid();
	void PlaceShipsRandom();
	bool UpdateShips(short _type);
	bool HasLostAllShips() const;
	short CountOfType(short _type);
	void Reset();
protected:
	const short m_shipCount = 5;
	short m_ships[5];// = { 2, 3, 3, 4, 5 };
	CGrid m_grid;
};
