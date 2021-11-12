#pragma once

enum class TileType
{
	TYPE5_D = -6,
	TYPE4_D,
	TYPE3_D,
	TYPE2_D,
	TYPE1_D,
	MISS,
	NULL,
	EMPTY,
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4,
	TYPE5,
	SELECTION_BAD = 8,
	SELECITON_GOOD
};

class CTile
{
public:
	static const short s_height = 3;
	static const short s_width = 2 * s_height;
	static const CTile Null;
	static const CTile s_selectorTile;
	static const CTile s_errorTile;
	CTile(short _type = 1);
	~CTile();
	short Type() const;
	void Hit();
	bool CanHit() const;
	void Draw(short _x, short _y, bool _isVisible = true) const;
private:
	short m_type = 1;
	short GetColour(bool _isVisible = true) const;
	char GetCharacter(bool _isVisible = true) const;
};

