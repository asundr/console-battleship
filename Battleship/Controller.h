#pragma once

enum class TileType;
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
	bool UpdateShips(TileType _type);
	bool HasLostAllShips() const;
	short CountOfType(TileType _type) const;
	void Reset();
protected:
	short m_ships[s_shipTypeCount];
	CGrid& m_grid;
	inline short TypeToIndex(TileType _type) const
	{
		return (short)_type - 2;
	}
	inline TileType IndexToType(short _index) const
	{
		return (TileType)(_index + 2);
	}
};
