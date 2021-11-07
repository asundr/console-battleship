#pragma once

#include "Controller.h"
#include "Grid.h"

class CControllerAI : public CController
{

public:
	CControllerAI(CGrid& _grid);
	~CControllerAI();
	bool Turn(CController& _opponent);
private:
	Point* m_lastHit = nullptr;
	short HitRandom(CController& _opponent) const;
};

