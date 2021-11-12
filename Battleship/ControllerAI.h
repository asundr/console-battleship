#pragma once

#include "Controller.h"
#include "Grid.h"

class CControllerAI : public CController
{
public:
	CControllerAI(CGrid& _grid);
	~CControllerAI();
	short Turn(CController& _opponent);
	void Reset();
private:
	Point m_lastHit = { -1,-1 };
	Point* m_xAxis;
	Point* m_yAxis;
	short m_xLength = 0;
	short m_yLength = 0;

	short HitRandom(CController& _opponent);
	short TargetShip(CController& _opponent);
	Point HitAlongAxis(CGrid& _grid, Point& _lastHit, bool _xAxis);
	Point TryToFindBoatEnd(CGrid& _grid, Point& _lastHit, short _dx, short _dy);
	void CleanAxisOfType(CGrid& _grid, Point* _axis, short& _length, short _type);
};
