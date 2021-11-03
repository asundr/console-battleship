#pragma once

enum class TileType
{
	EMPTY = 1,
	MISS = -1,

};

class CTile
{
public:
	static const short s_height = 3;
	static const short s_width = 2 * s_height;
	CTile(short _type = 1);
	~CTile();
	short Type() const;
	void Hit();
	bool CanHit() const;
	void Draw(short x, short y) const;
private:
	short m_type = 1;
	short GetColour() const;
};

