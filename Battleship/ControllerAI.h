#pragma once

#include "Grid.h"

class CControllerAI
{

public:
	CControllerAI();
	~CControllerAI();
	void Turn(CGrid& oponentGrid) const;
private:
	Point* m_lastHit = nullptr;

	void PickRandom(CGrid& opponentGrid) const;

};

