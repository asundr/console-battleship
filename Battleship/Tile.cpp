#include "Tile.h"
#include <iostream>
#include "Console.h"

CTile::CTile(TileType _type) : m_type(_type)
{
}

CTile::~CTile()
{
}

TileType CTile::Type() const
{
	return m_type;
}

void CTile::Hit()
{
	m_type = DamageType(m_type);
}

bool CTile::CanHit() const
{
	return CanHit(m_type);
}

bool CTile::IsShip() const
{
	return IsShip(m_type);
}

short  CTile::GetColour(bool _isVisible) const
{
	if (!_isVisible && CanHit())
	{
		return 0x13;//0x37; //0x87;
	}
	if (m_type == TileType::EMPTY)
	{
		return 0x13; //0x38; //0x18
	}
	else if (m_type == TileType::MISS)
	{
		return 0x17;
	}
	else if (m_type == TileType::SELECITON_GOOD)
	{
		return 0x20;
	}
	else if (m_type == TileType::SELECTION_BAD)
	{
		return 0xC0;
	}
	else if ((short)m_type < 0)
	{
		return 0x40; //0xCE;//0xC0;
	}
	else
	{
		return 0x7F; //0x80;
	}
}

char CTile::GetCharacter(bool _isVisible) const
{
	if (!_isVisible && CanHit())
	{
		return '.';//'\u00EF';
	}
	if (m_type == TileType::EMPTY || m_type == TileType::MISS)
	{
		//return '.'; //'\u00EF';
		return CanHit() ? '.' : '\u00B0'; //'\u00EF';
	}
	else if (IsShip())
	{
		return CanHit() ? ' ' : ' '; ///*'\u00E9'*/ : '\u00EB';
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

TileType CTile::DamageType(TileType _type)
{
	return TileType(-abs((short)_type));
}

bool CTile::IsShip(TileType _type)
{
	short id = abs((short)_type);
	return id > 1 && id < 7;
}

bool CTile::CanHit(TileType _type)
{
	return (short)_type > 0;
}