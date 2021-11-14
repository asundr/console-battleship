#pragma once

#include "Controller.h"

enum class TileType;
struct Point;

class CControllerAI : public CController
{
public:
	CControllerAI(CGrid& _grid);
	~CControllerAI();
	TileType Turn(CController& _opponent);
	void Reset();
private:
	Point* m_target;
	Point* m_xAxis;
	Point* m_yAxis;
	short m_xLength = 0;
	short m_yLength = 0;

	void SetTarget(short _x, short _y);
	TileType HitRandom(CController& _opponent);
	TileType TargetShip(CController& _opponent);
	Point FindAlongAxis(const CGrid& _grid, const Point& _lastHit, bool _isXAxis) const;
	Point FindBoatEnd(const CGrid& _grid, const Point& _lastHit, short _dx, short _dy) const;
	void CleanAxisOfType(const CGrid& _grid, Point* _axis, short& _length, TileType _type);
};
