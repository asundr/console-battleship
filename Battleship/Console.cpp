#include "Console.h"
#include <windows.h>

namespace Display
{
	// Returns a reference to the console handler
	HANDLE& GetHandle()
	{
		static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		return hConsole;
	}

	// Sets position and dimensions of console window
	void SetWindowBounds(short _x, short _y, short _width, short _height)
	{
		HWND console = GetConsoleWindow();
		MoveWindow(console, _x, _y, _width, _height, TRUE);
	}

	// Toggles the visibility of the console cursor
	void ShowCursor(bool _visible)
	{
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(GetHandle(), &cursorInfo);
		cursorInfo.bVisible = _visible;
		SetConsoleCursorInfo(GetHandle(), &cursorInfo);
	}

	// Moves the cursor to the position (x, y)
	void CursorPos(short _x, short _y)
	{
		CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
		GetConsoleScreenBufferInfo(GetHandle(), &screenBufferInfo);
		screenBufferInfo.dwCursorPosition = { _x, _y };
		SetConsoleCursorPosition(GetHandle(), screenBufferInfo.dwCursorPosition);
	}

	// Returns general information about the character at (x,y)
	CHAR_INFO GetCharInfo(short _x, short _y)
	{
		CHAR_INFO charInfo;
		SMALL_RECT copyBounds = { _x, _y, _x, _y };
		return ReadConsoleOutput(GetHandle(), &charInfo, { 1,1 }, { 0, 0 }, &copyBounds)
			? charInfo
			: CHAR_INFO();
	}

	// Returns the character at the position (x,y)
	char GetCharacterAtCursor(short _x, short _y)
	{
		return GetCharInfo(_x, _y).Char.AsciiChar;
	}

	// Returns color information at the position (x,y)
	short GetColourAtCursor(short _x, short _y)
	{
		return GetCharInfo(_x, _y).Attributes;
	}

	// Sets the text and background colour to print next
	void SetColour(int _colour)
	{
		SetConsoleTextAttribute(GetHandle(), _colour);
	}

	// Returns the colour scheme back to white text on a black 
	void ResetConsoleText()
	{
		SetColour(0x0F);
	}

}
