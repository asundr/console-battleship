#pragma once

#include "Controller.h"
#include "Grid.h"

class CControllerAI : public CController
{
public:
	CControllerAI(CGrid& _grid);
	~CControllerAI();
	short Turn(CController& _opponent);
private:
	Point m_lastHit = { -1,-1 };
	Point* xAxis;
	Point* yAxis;
	short xLength = 0;
	short yLength = 0;

	short HitRandom(CController& _opponent);
	short TargetShip(CController& _opponent);
	Point HitAlongAxis(CGrid& _grid, Point& _lastHit, bool xAxis);
	Point TryToFindBoatEnd(CGrid& _grid, Point& _lastHit, short _dx, short _dy);
	void CleanAxisOfType(CGrid& _grid, Point* _axis, short& _length, short _type);

	Point* GetAdjacentCoords(Point& _point);
	Point& RotateDirection90(Point& _direciton);
	Point& RandomDirection(Point& _direction);
	void ReverseHistory(Point** _history, short _length);
};
