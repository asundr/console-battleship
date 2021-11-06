#pragma once

#include "Controller.h"
#include "Grid.h"

class CControllerAI : public CController
{

public:
	CControllerAI(CGrid _grid);
	~CControllerAI();
	void Turn(CGrid& oponentGrid) const;
private:
	Point* m_lastHit = nullptr;

	void PickRandom(CGrid& opponentGrid) const;

};

