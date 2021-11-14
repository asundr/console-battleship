#pragma once

#ifndef __Point__
#define __Point__
struct Point
{
	short x, y;
};
#endif

#ifndef __BOUNDS__
#define __BOUNDS__
struct Bounds
{
	short x = 0, y = 0, width = 1, height = 1;
};
#endif

namespace Display
{
	void SetWindowBounds(short _x, short _y, short _width, short _height);
	void ShowCursor(bool _visible);
	void CursorPos(short _x, short _y);
	char GetCharacterAtCursor(short _x, short _y);
	short GetColourAtCursor(short _x, short _y);
	void SetColour(int _colour);
	void ResetConsoleText();
}
