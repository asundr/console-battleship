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

short  CTile::GetColour(bool _isVisible) const
{
	if (!_isVisible && m_type > 0)
	{
		return 0x13;//0x37; //0x87;
	}
	if (m_type == 1)
	{
		return 0x13; //0x38; //0x18
	}
	else if (m_type == -1)
	{
		return 0x17;
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
		return 0xC6;//0xC0;
	}
	else
	{
		return 0x7F; //0x80;
	}
}

char CTile::GetCharacter(bool _isVisible) const
{
	if (!_isVisible && m_type > 0)
	{
		return '\u00EF';
	}
	if (abs(m_type) == 1)
	{
		return '\u00EF';
	}
	else if (abs(m_type) > 1 && abs(m_type) < 7)
	{
		return CanHit() ? '\u00E9' : '#';
	}
	else
	{
		return ' ';
	}
}

void CTile::Draw(short _x, short _y, bool _isVisible) const	// TODO add visibility param
{
	SetColour(GetColour(_isVisible));
	char c = GetCharacter(_isVisible);
	for (short dy = 0; dy < s_height; ++dy)
	{
		CursorPos(_x, _y + dy);
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