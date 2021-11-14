#include <string>
#include "Display.h"
#include <iostream>
#include "Console.h"

namespace Display
{
	// Draws a column from a 6x5 pixel letter represented by the last 30 bits of an integer
	void PrintLetterColumn(int _mask, Point _p, int _col, int _padding)
	{
		int dy = 0;
		for (int i = 0; i < _padding; ++i, ++dy)
		{
			CursorPos(_p.x, _p.y + dy);
			std::cout << ' ';
		}
		for (int i = 29; i > 0; i -= 6, ++dy)
		{
			CursorPos(_p.x, _p.y + dy);
			bool filled = _mask & (1 << (i - _col));
			std::cout << (filled ? '\u00DB' : ' ');
		}
		for (int i = 0; i < _padding; ++i, ++dy)
		{
			CursorPos(_p.x, _p.y + dy);
			std::cout << ' ';
		}
	}

	// Draws a row from a 6x5 pixel number represented by the last 30 bits of an integer
	void PrintLetterRow(int _mask, Point _p, int _row, int _padding, char _background)
	{
		CursorPos(_p.x, _p.y);
		for (int i = 0; i < _padding; ++i)
		{
			std::cout << _background;
		}
		int start = 29 - _row * 6;
		for (int i = 0; i < 6; ++i)
		{
			bool filled = _mask & (1 << (start - i));
			std::cout << (filled ? '\u00DB' : _background);
		}
		for (int i = 0; i < _padding; ++i)
		{
			std::cout << _background;
		}
	}

	// Draws a border with 'colour' defining the text and background colour.
	// 'tiles' defines eights characters used to draw the top, bottom, left, right,
	// top-left, top-right, bottom-left, bottom-right tiles respectively
	void DrawBorder(const Bounds& _bounds, int _colour, const char _borderTiles[])
	{
		SetColour(_colour);
		CursorPos(_bounds.x + 1, _bounds.y);
		for (int i = 1; i < _bounds.width; ++i)
		{
			std::cout << _borderTiles[0];
		}
		CursorPos(_bounds.x + 1, _bounds.y + _bounds.height - 1);
		for (int i = 1; i < _bounds.width; ++i)
		{
			std::cout << _borderTiles[2];
		}
		for (int i = 1; i < _bounds.height; ++i)
		{
			CursorPos(_bounds.x, _bounds.y + i);
			std::cout << _borderTiles[3];
			CursorPos(_bounds.x + _bounds.width - 1, _bounds.y + i);
			std::cout << _borderTiles[1];
		}
		CursorPos(_bounds.x, _bounds.y);
		std::cout << _borderTiles[4];
		CursorPos(_bounds.x + _bounds.width - 1, _bounds.y);
		std::cout << _borderTiles[5];
		CursorPos(_bounds.x + _bounds.width - 1, _bounds.y + _bounds.height - 1);
		std::cout << _borderTiles[6];
		CursorPos(_bounds.x, _bounds.y + _bounds.height - 1);
		std::cout << _borderTiles[7];
		ResetConsoleText();
	}

	// Fills the region with the passed backgorund colour
	void FillBorder(const Bounds& _bounds, int _colour)
	{
		SetColour(_colour);
		for (int i = 0; i < _bounds.width; ++i)
		{
			for (int j = 0; j < _bounds.height; ++j)
			{
				CursorPos(_bounds.x + i, _bounds.y + j);
				std::cout << ' ';
			}
		}
		ResetConsoleText();
	}

	// Prints the text marquee which can be animated by using a different seen number
	void PrintTitle(const Bounds& _bounds, const std::string& _word, short _colour)
	{
		Point p = { _bounds.x + 1, _bounds.y + 1 };
		int wordStart = ((_bounds.width - 1) - (7 * _word.length())) / 2; // centers the text
		SetColour(_colour);
		for (int i = 0; i < wordStart; ++i)
		{
			PrintLetterColumn(0, p, 0);
			++p.x;
		}
		for (char c : _word)
		{
			for (int row = 0; row < 6; ++row)
			{
				PrintLetterColumn(Letter_Masks[c - 'A'], p, row);
				++p.x;
			}
			PrintLetterColumn(0, p, 0);
			++p.x;
		}
		while (p.x < _bounds.x + _bounds.width - 1)
		{
			PrintLetterColumn(0, p, 0);
			++p.x;
		}
	}

	// Prints a character at (x,y) with a given colour
	void DrawAt(short _x, short _y, char _c, short _colour)
	{
		CursorPos(_x, _y);
		if (_colour >= 0)
		{
			SetColour(_colour);
		}
		std::cout << _c;
	}

	// Prints a string starting at (x,y) with a given colour
	void PrintStringAt(short _x, short _y, std::string _str, short _colour)
	{
		CursorPos(_x, _y);
		if (_colour >= 0)
		{
			SetColour(_colour);
		}
		std::cout << _str;
	}

}
