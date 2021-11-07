#include <iostream>

#include "Tile.h"
#include "Console.h"

const CTile CTile::Null = CTile(0);

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
		return 0x38; //0x18
	}
	else if (m_type == -1)
	{
		return 0x13;
	}
	else if (m_type == 9)
	{
		return 0x20;
	}
	else if (m_type == 8)
	{
		return 0x40;
	}
	else if (m_type < 0)
	{
		return 0xC0;
	}
	else
	{
		return 0x80;
	}
}

char CTile::GetCharacter() const
{
	if (abs(m_type) == 1)
	{
		return (rand()%2==1) ? '~' : '\u00F7';//'\u00B1';
	}
	else if (abs(m_type) > 1 && abs(m_type) < 7)
	{
		return CanHit() ? '\u00F0' : '*';
	}
	else
	{
		return ' ';
	}
}

void CTile::Draw(short x, short y) const	// TODO add visibility param
{
	SetColour(GetColour());
	char c = GetCharacter();
	for (short dy = 0; dy < s_height; ++dy)
	{
		CursorPos(x, y + dy);
		for (short dx = 0; dx < s_width; ++dx)
		{
			//std::cout << ' ';
			//std::cout <<  abs((int)m_type);
			std::cout << c;
		}
	}
}

CTile CTile::s_selectorTile = CTile(9);
CTile CTile::s_errorTile = CTile(8);