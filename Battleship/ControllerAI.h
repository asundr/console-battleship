#pragma once

#include "Controller.h"
#include "Grid.h"

class CControllerAI : public CController
{

public:
	CControllerAI(CGrid& _grid);
	~CControllerAI();
	void Turn(CController& _opponent);
private:
	Point* m_lastHit = nullptr;
	void PickRandom(CGrid& opponentGrid) const;
};

