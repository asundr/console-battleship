#include <string>
#include <iostream>
#include "Console.h"
#include "Textbox.h"
#include "Display.h"

// Draws a column from a 6x5 pixel letter represented by the last 30 bits of an integer
void PrintLetterColumn(int mask, Point p, int col, int padding)
{
	int dy = 0;
	for (int i = 0; i < padding; ++i, ++dy)
	{
		CursorPos(p.x, p.y + dy);
		std::cout << ' ';
	}
	for (int i = 29; i > 0; i -= 6, ++dy)
	{
		CursorPos(p.x, p.y + dy);
		bool filled = mask & (1 << (i - col));
		std::cout << (filled ? '\u00DB' : ' ');
	}
	for (int i = 0; i < padding; ++i, ++dy)
	{
		CursorPos(p.x, p.y + dy);
		std::cout << ' ';
	}
}

// Draws a row from a 6x5 pixel number represented by the last 30 bits of an integer
void PrintNumberRow(int mask, Point p, int row, int padding, char background)
{
	CursorPos(p.x, p.y);
	for (int i = 0; i < padding; ++i)
	{
		std::cout << background;
	}
	int start = 29 - row * 6;
	for (int i = 0; i < 6; ++i)
	{
		bool filled = mask & (1 << (start - i));
		std::cout << (filled ? '\u00DB' : background);
	}
	for (int i = 0; i < padding; ++i)
	{
		std::cout << background;
	}
}

// Draws a border with 'colour' defining the text and background colour.
// 'tiles' defines eights characters used to draw the top, bottom, left, right,
// top-left, top-right, bottom-left, bottom-right tiles respectively
void DrawBorder(Bounds bounds, int colour, const char tiles[])
{
	SetColour(colour);
	CursorPos(bounds.x + 1, bounds.y);
	for (int i = 1; i < bounds.width; ++i)
	{
		std::cout << tiles[0];
	}
	CursorPos(bounds.x + 1, bounds.y + bounds.height - 1);
	for (int i = 1; i < bounds.width; ++i)
	{
		std::cout << tiles[2];
	}
	for (int i = 1; i < bounds.height; ++i)
	{
		CursorPos(bounds.x, bounds.y + i);
		std::cout << tiles[3];
		CursorPos(bounds.x + bounds.width - 1, bounds.y + i);
		std::cout << tiles[1];
	}
	CursorPos(bounds.x, bounds.y);
	std::cout << tiles[4];
	CursorPos(bounds.x + bounds.width - 1, bounds.y);
	std::cout << tiles[5];
	CursorPos(bounds.x + bounds.width - 1, bounds.y + bounds.height - 1);
	std::cout << tiles[6];
	CursorPos(bounds.x, bounds.y + bounds.height - 1);
	std::cout << tiles[7];
	ResetConsoleText();
}

// Fills the region with the passed backgorund colour
void FillBorder(Bounds bounds, int colour)
{
	SetColour(colour);
	for (int i = 0; i < bounds.width; ++i)
	{
		for (int j = 0; j < bounds.height; ++j)
		{
			CursorPos(bounds.x + i, bounds.y + j);
			std::cout << ' ';
		}
	}
	ResetConsoleText();
}

// Prints the text marquee which can be animated by using a different seen number
void PrintTitle(Bounds& bounds, const std::string& word, short _colour)
{
	Point p = { bounds.x + 1, bounds.y + 1 };
	int wordStart = ((bounds.width - 1) - (7 * word.length())) / 2; // centers the text
	SetColour(_colour);
	for (int i = 0; i < wordStart; ++i)
	{
		PrintLetterColumn(0, p, 0);
		++p.x;
	}
	for (char c : word)
	{
		for (int row = 0; row < 6; ++row)
		{
			PrintLetterColumn(Letter_Masks[c - 'A'], p, row);
			++p.x;
		}
		PrintLetterColumn(0, p, 0);
		++p.x;
	}
	while (p.x < bounds.x + bounds.width - 1)
	{
		PrintLetterColumn(0, p, 0);
		++p.x;
	}
}

void DrawAt(short _x, short _y, char _c, short _colour)
{
	CursorPos(_x, _y);
	if (_colour >= 0)
	{
		SetColour(_colour);
	}
	std::cout << _c;
}

void PrintStringAt(short _x, short _y, std::string _str, short _colour)
{
	CursorPos(_x, _y);
	if (_colour >= 0)
	{
		SetColour(_colour);
	}
	std::cout << _str;
}
