#pragma once

#include "Controller.h"

struct Point;

class CControllerAI : public CController
{
public:
	CControllerAI(CGrid& _grid);
	~CControllerAI();
	short Turn(CController& _opponent);
	void Reset();
private:
	Point* m_lastHit;
	Point* m_xAxis;
	Point* m_yAxis;
	short m_xLength = 0;
	short m_yLength = 0;

	void SetLastHit(short _x, short _y);
	short HitRandom(CController& _opponent);
	short TargetShip(CController& _opponent);
	Point FindAlongAxis(const CGrid& _grid, const Point& _lastHit, bool _isXAxis) const;
	Point FindBoatEnd(const CGrid& _grid, const Point& _lastHit, short _dx, short _dy) const;
	void CleanAxisOfType(const CGrid& _grid, Point* _axis, short& _length, short _type);
};
