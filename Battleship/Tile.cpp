#include <iostream>

#include "Tile.h"
#include "Console.h"

CTile::CTile(short _type) : m_type(_type)
{
}

CTile::~CTile()
{

}

short CTile::Type() const
{
	return m_type;
}

void CTile::Hit()
{
	m_type = - m_type;
}

bool CTile::CanHit() const
{
	return m_type > 0;
}

short  CTile::GetColour() const
{
	if (m_type == 1)
	{
		return 0x18;
	}
	else
	{
		return 0x88;
	}
}

void CTile::Draw(short x, short y) const
{
	SetColour(GetColour());
	for (short dy = 0; dy < s_height; ++dy)
	{
		CursorPos(x, y + dy);
		for (short dx = 0; dx < s_width; ++dx)
		{
			std::cout << ' ';
		}
	}
}