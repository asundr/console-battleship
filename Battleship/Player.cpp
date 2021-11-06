#include "Player.h"

CPlayer::CPlayer(CGrid& _grid) : CController(_grid)
{
}

CPlayer::~CPlayer()
{

}

void CPlayer::SetSelectorBounds(short _x, short _y, short _width, short _height)
{
	RevertTiles(m_grid);
	m_selector = { _x, _y };
	m_selectorBounds = { _width, _height };
	DrawSelection(m_grid);
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
	_grid.ActionOverRegion(
		[](CGrid& _grid, CTile& tile, short x, short y) -> void { _grid.DrawTileAt(x,y,tile);}, //{ tile.Draw(x,y); },
		m_selector.x,
		m_selector.y,
		m_selectorBounds.x,
		m_selectorBounds.y
	);
}

void CPlayer::DrawSelection(CGrid& _grid) const
{
	_grid.ActionOverRegion(
		[](CGrid& _grid, CTile& tile, short x, short y) -> void { _grid.DrawTileAt(x, y, selectorTile); }, //{ DrawSelectorTile(_grid, x, y); },
		m_selector.x,
		m_selector.y,
		m_selectorBounds.x,
		m_selectorBounds.y
	);
}

void CPlayer::ResetSelector(CGrid& _grid)
{
	RevertTiles(_grid);
	m_selector = { 0,0 };
	m_selectorBounds = { 0,0 };
}

CTile CPlayer::selectorTile = CTile(9);

//oid CPlayer::DrawSelectorTile(CGrid& _grid, short _x, short _y) // TODO delete?
//
//	_grid.DrawTileAt(_x, _y, selectorTile);
//