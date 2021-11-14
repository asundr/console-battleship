#include "Player.h"
#include "conio.h"
#include "Tile.h"
#include "Grid.h"

CPlayer::CPlayer(CGrid& _grid) : CController(_grid)
{
	m_grid.SetVisible(true);
	m_selector = new Bounds{ 0, 0, 0, 0 };
}

CPlayer::~CPlayer()
{
	delete m_selector;
}

void CPlayer::Reset()
{
	CController::Reset();
	SetSelector(0, 0);
	SetSelectorBounds(0, 0);
}

TileType CPlayer::Turn(CController& _opponent)
{
	UpdateSelectorBounds(m_selector->x, m_selector->y, 1, 1, _opponent.Grid());
	TileType type;
	do
	{
		type = HandleSelctionInput(TileType::NONE, _opponent);
	} while (type == TileType::NONE);
	return type;
}

void CPlayer::UpdateSelectorBounds(short _x, short _y, short _width, short _height, const CGrid& _grid)
{
	RevertTiles(_grid);
	SetSelector(_x, _y);
	SetSelectorBounds(_width, _height);
	DrawSelection(_grid);
}

void CPlayer::UpdateSelectorBounds(short _x, short _y, short _width, short _height)
{
	UpdateSelectorBounds(_x, _y, _width, _height, m_grid);
}

void CPlayer::UpdateSelectorBounds(const Bounds& _bounds, const CGrid& _grid)
{
	UpdateSelectorBounds(_bounds.x, _bounds.y, _bounds.width, _bounds.height, _grid);
}

void CPlayer::UpdateSelectorBounds(const Bounds& _bounds)
{
	UpdateSelectorBounds(_bounds, m_grid);
}

bool CPlayer::UpdateSelector(const Point& _coord, const CGrid& _grid)
{
	Bounds bounds = { _coord.x, _coord.y, m_selector->width, m_selector->height };
	if (!_grid.IsRegionInBounds(bounds))
	{
		return false;
	}
	UpdateSelectorBounds(bounds, _grid);
	return true;
}

bool CPlayer::UpdateSelector(const Point& _coord)
{
	return UpdateSelector(_coord, m_grid);
}

bool CPlayer::ShiftSelector(const Point& _shift, const CGrid& _grid)
{
	Point pNew = { m_selector->x + _shift.x , m_selector->y + _shift.y };
	return UpdateSelector(pNew, _grid);
}

bool CPlayer::ShiftSelector(const Point& _shift)
{
	return ShiftSelector(_shift, m_grid);
}

bool CPlayer::ToggleSelectorRotation(const CGrid& _grid)
{
	Bounds boundsRot = { m_selector->x, m_selector->y, m_selector->height, m_selector->width };
	if (!_grid.IsRegionInBounds(boundsRot))
	{
		return false;
	}
	UpdateSelectorBounds(boundsRot, _grid);
	return true;
}

bool CPlayer::ToggleSelectorRotation()
{
	return ToggleSelectorRotation(m_grid);
}

void CPlayer::RevertTiles(const CGrid& _grid) const
{
	_grid.RevertTiles(*m_selector);
}

void CPlayer::DrawSelection(const CGrid& _grid) const
{
	//Bounds bounds = { m_selector->x, m_selector->y, m_selector->width, m_selector->height };
	if (m_selector->width == m_selector->height) // TODO add better check for ship placement vs firing
	{
		if (_grid.CanHitTile(m_selector->x, m_selector->y))
		{
			_grid.DrawSelection(*m_selector);
		}
		else
		{
			_grid.DrawSelectionError(*m_selector);
		}
	}
	else if (_grid.IsRegionEmpty(*m_selector)) // placing ships 
	{
		_grid.DrawSelection(*m_selector);
	}
	else
	{
		_grid.DrawSelectionError(*m_selector);
	}
}

void CPlayer::PlaceShips()
{
	for (short i = s_shipTypeCount - 1; i >= 0; --i)
	{
		if (m_selector->width < m_selector->height)  // if selector is vertical
		{
			UpdateSelectorBounds(m_selector->x, m_selector->y, 1, m_ships[i]);
		}
		else    // if selector is horizontal
		{
			UpdateSelectorBounds(m_selector->x, m_selector->y, m_ships[i], 1);
		}
		while (HandleSelctionInput(IndexToType(i)) == TileType::NONE);
	}
	RevertTiles(m_grid);
	UpdateSelectorBounds(0, 0, 0, 0);
}

TileType CPlayer::HandleSelctionInput(TileType _type, const CController& _controller)
{	
	CGrid& grid = _controller.Grid();
	int input = _getch();
	if (input == 101) // E
	{
		ToggleSelectorRotation(grid);
	}
	else if (input == 32) // SPACE
	{
		if (_type == TileType::NONE)
		{
			if (grid.CanHitTile(m_selector->x, m_selector->y))
			{
				return grid.HitTile(m_selector->x, m_selector->y);
			}
		}
		else if (grid.TryToPlaceShip(*m_selector, _type, false))
		{
			return _type;
		}
	}
	else
	{
		Point dx;
		switch (input)	// WASD
		{
		case 97:
			dx = { -1, 0 }; break;
		case 100:
			dx = { 1, 0 }; break;
		case 115:
			dx = { 0, 1 }; break;
		case 119:
			dx = { 0, -1 }; break;
		default:
			dx = { 0,0 };
		}
		ShiftSelector(dx, grid);
	}
	return TileType::NONE;
}

TileType CPlayer::HandleSelctionInput(TileType _type)
{
	return HandleSelctionInput(_type, *this);
}

void CPlayer::SetSelector(short _x, short _y)
{
	m_selector->x = _x;
	m_selector->y = _y;
}

void CPlayer::SetSelectorBounds(short _width, short _height)
{
	m_selector->width = _width;
	m_selector->height = _height;
}
