#pragma once

enum class TileType // TODO
{
	EMPTY = 1,
	MISS = -1
};

class CTile
{
public:
	static const short s_height = 3;
	static const short s_width = 2 * s_height;
	static const CTile Null;
	CTile(short _type = 1);
	~CTile();
	short Type() const;
	void Hit();
	bool CanHit() const;
	void Draw(short _x, short _y, bool _isVisible = true) const;
	static CTile s_selectorTile;
	static CTile s_errorTile;
private:
	short m_type = 1;
	short GetColour(bool _isVisible = true) const;
	char GetCharacter(bool _isVisible = true) const;
};

