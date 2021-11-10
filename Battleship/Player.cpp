#include "conio.h"
#include "Player.h"

CPlayer::CPlayer(CGrid& _grid) : CController(_grid)
{
	m_grid.SetVisible(true);
}

CPlayer::~CPlayer()
{

}

short CPlayer::Turn(CController& _opponent)
{
	//CGrid& oGrid = _opponent.Grid();
	SetSelectorBounds(_opponent.Grid(), m_selector.x, m_selector.y, 1, 1);
	short type;
	do
	{
		type = HandleSelctionInput(0, _opponent);
	} while (!type);
	return type;
}

void CPlayer::Reset()
{
	CController::Reset();
	m_selector = { 0, 0 };
	m_selectorBounds = { 0, 0 };
}

void CPlayer::SetSelectorBounds(CGrid& _grid, short _x, short _y, short _width, short _height)
{
	RevertTiles(_grid);
	m_selector = { _x, _y };
	m_selectorBounds = { _width, _height };
	DrawSelection(_grid);
}

void CPlayer::SetSelectorBounds(short _x, short _y, short _width, short _height)
{
	SetSelectorBounds(m_grid, _x, _y, _width, _height);
}

bool CPlayer::SetSelector(Point& _coord, CGrid& _grid)
{
	if (!_grid.IsRegionInBounds(_coord.x, _coord.y, m_selectorBounds.x, m_selectorBounds.y))
	{
		return false;
	}
	RevertTiles(_grid); //SetSelecotrBounds(_grid, ...)
	m_selector = _coord;
	DrawSelection(_grid);
	return true;
}

bool CPlayer::SetSelector(Point& _coord)
{
	return SetSelector(_coord, m_grid);
}

bool CPlayer::ShiftSelector(Point& _shift, CGrid& _grid)
{
	Point pNew = { m_selector.x + _shift.x , m_selector.y + _shift.y };
	return SetSelector(pNew, _grid);
}

bool CPlayer::ShiftSelector(Point& _shift)
{
	return ShiftSelector(_shift, m_grid);
}

bool CPlayer::ToggleSelectorRotation(CGrid& _grid)
{
	if (!_grid.IsRegionInBounds(m_selector.x, m_selector.y, m_selectorBounds.y, m_selectorBounds.x))
	{
		return false;
	}
	RevertTiles(_grid);
	m_selectorBounds = { m_selectorBounds.y, m_selectorBounds.x };
	DrawSelection(_grid);
	return true;
}

bool CPlayer::ToggleSelectorRotation()
{
	return ToggleSelectorRotation(m_grid);
}

void CPlayer::RevertTiles(CGrid& _grid)
{
	_grid.RevertTiles(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y);
}

void CPlayer::DrawSelection(CGrid& _grid) const
{
	if (m_selectorBounds.x == m_selectorBounds.y) // TODO add better check for ship placement vs firing
	{
		if (_grid.GetTile(m_selector.x, m_selector.y).CanHit())
		{
			_grid.DrawSelection(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y);
		}
		else
		{
			_grid.DrawSelectionError(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y);
		}
	}
	else if (_grid.IsRegionEmpty(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y))
	{
		_grid.DrawSelection(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y);
	}
	else
	{
		_grid.DrawSelectionError(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y);
	}
}


void CPlayer::PlaceShips()
{
	for (short i = m_shipCount - 1; i >= 0; --i)
	{
		if (m_selectorBounds.x < m_selectorBounds.y)
		{
			SetSelectorBounds(m_selector.x, m_selector.y, 1, m_ships[i]);
		}
		else
		{
			SetSelectorBounds(m_selector.x, m_selector.y, m_ships[i], 1);
		}
		while (! HandleSelctionInput(i + 2));
	}
	SetSelectorBounds(0, 0, 0, 0);
}

short CPlayer::HandleSelctionInput(short _value, CController& _controller)
{	
	CGrid& grid = _controller.Grid();
	int input = _getch();
	if (input == 101)
	{
		ToggleSelectorRotation(grid);
	}
	else if (input == 32)
	{
		if (_value == 0)
		{
			if (grid.CanHitTile(m_selector.x, m_selector.y))
			{
				return grid.HitTile(m_selector.x, m_selector.y);
			}
		}
		else if (grid.TryToPlaceShip(m_selector.x, m_selector.y, m_selectorBounds.x, m_selectorBounds.y, _value, false))
		{
			return _value;
		}
	}
	else
	{
		Point dx;
		switch (input)
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
	return 0;
}

short CPlayer::HandleSelctionInput(short _value)
{
	return HandleSelctionInput(_value, *this);
}
