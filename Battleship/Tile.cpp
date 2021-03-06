#include "Tile.h"
#include <iostream>
#include "Console.h"
#include "Settings.h"

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
	if (!CSettings::DebugMode() && !_isVisible && CanHit())
	{
		return CSettings::AlternateTiles() ? 0x33 : 0x17;
	}
	if (m_type == TileType::EMPTY)
	{
		return CSettings::AlternateTiles() ? 0x33 : 0x17;
	}
	else if (m_type == TileType::MISS)
	{
		return CSettings::AlternateTiles() ? 0x11 : 0x10;
	}
	else if (m_type == TileType::SELECITON_GOOD)
	{
		return 0x20;
	}
	else if (m_type == TileType::SELECTION_BAD)
	{
		return 0xC0;
	}
	else if (IsShip() && !CanHit())
	{
		return 0x40;
	}
	else
	{
		return 0x7F;
	}
}

char CTile::GetCharacter(bool _isVisible) const
{
	if (!CSettings::DebugMode() && !_isVisible && CanHit())
	{
		return '.';
	}
	if (m_type == TileType::EMPTY || m_type == TileType::MISS)
	{
		return CanHit() ? '.' : ':';
	}
	else if (IsShip())
	{
		return ' ';
	}
	else if (m_type == TileType::SELECITON_GOOD || m_type == TileType::SELECTION_BAD)
	{
		return ' ';
	}
	else
	{
		return '?';
	}
}

void CTile::Draw(short _x, short _y, bool _isVisible) const
{
	Display::SetColour(GetColour(_isVisible));
	char c = GetCharacter(_isVisible);
	for (short dy = 0; dy < s_height; ++dy)
	{
		Display::CursorPos(_x, _y + dy);
		for (short dx = 0; dx < s_width; ++dx)
		{
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
