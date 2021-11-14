#pragma once

#ifndef __TILETYPE__
#define __TILETYPE__
enum class TileType
{
	TYPE5_D = -6,
	TYPE4_D,
	TYPE3_D,
	TYPE2_D,
	TYPE1_D,
	MISS,
	NONE,
	EMPTY,
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4,
	TYPE5,
	SELECTION_BAD,
	SELECITON_GOOD
};
#endif

class CTile
{
public:
	static const short s_height = 3;
	static const short s_width = 2 * s_height;
	CTile(TileType _type = TileType::EMPTY);
	~CTile();
	TileType Type() const;
	void Hit();
	bool CanHit() const;
	bool IsShip() const;
	void Draw(short _x, short _y, bool _isVisible = true) const;
	static TileType DamageType(TileType _type);
	static bool IsShip(TileType _type);
	static bool CanHit(TileType _type);
private:
	TileType m_type = TileType::EMPTY;
	short GetColour(bool _isVisible = true) const;
	char GetCharacter(bool _isVisible = true) const;
};
