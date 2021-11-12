#pragma once

class CGrid;

class CController
{
public:
	const static short s_shipTypeCount = 5;
	const static short s_shipSize[];
	CController(CGrid& _grid);
	~CController();
	CGrid& Grid() const;
	void PlaceShipsRandom();
	bool UpdateShips(short _type);
	bool HasLostAllShips() const;
	short CountOfType(short _type) const;
	void Reset();
protected:
	short m_ships[s_shipTypeCount];
	CGrid& m_grid;
	inline short TypeToIndex(short _type) const
	{
		return _type - 2;
	}
	inline short IndexToType(short _index) const
	{
		return _index + 2;
	}
};
