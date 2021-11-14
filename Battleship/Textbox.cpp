#include <string>
#include "Textbox.h"
#include <iostream>
#include "Console.h"

CTextbox::CTextbox(Bounds _bounds) 
{
	m_bounds = new Bounds(_bounds);
	m_curr = new Point{ _bounds.x, _bounds.y };
}

CTextbox::~CTextbox()
{
}

short CTextbox::Height() const
{
	return m_bounds->height;
}

short CTextbox::Width() const
{
	return m_bounds->width;
}

// Moves the terminal cursor to (x,y) within the terminal's coord system
void CTextbox::MoveTo(short _x, short _y)
{
	m_curr->x = _x;
	m_curr->y = _y;
	CursorPos(_x, _y);
}

// Overload
void CTextbox::MoveTo(Point _p)
{
	MoveTo(_p.x, _p.y);
}

// Removes all text from the window
void CTextbox::Clear()
{
	ResetConsoleText();
	for (short i = 0; i < m_bounds->height; ++i)
	{
		CursorPos(m_bounds->x, m_bounds->y + i);
		for (short j = 0; j < m_bounds->width; ++j)
		{
			std::cout << ' ';
		}
	}
	MoveTo(m_bounds->x, m_bounds->y);
}

// Removes all text from th currnt line;
void CTextbox::ClearLine()
{
	MoveTo(m_bounds->x, m_curr->y);
	for (short i = 0; i < m_bounds->width; ++i)
	{
		std::cout << ' ';
		m_curr->x++;
	}
	MoveTo(*m_curr);
}

// Prints a acharacter at the current cursor position
void CTextbox::Print(char c)
{
	if (c == '\n' || m_curr->x == m_bounds->x + m_bounds->width)
	{
		if (m_curr->y < m_bounds->y + m_bounds->height - 1)
		{
			++m_curr->y;
		}
		else
		{
			ScrollUp(1);
		}
		MoveTo(m_bounds->x, m_curr->y);
		if (c == '\n')
			return;
	}
	MoveTo(*m_curr);
	std::cout << c;
	m_curr->x += c == '\t' ? 4 : 1;
}

// Print a character with the specified text and background colour id
void CTextbox::Print(char c, int colour)
{
	SetColour(colour);
	Print(c);
}

// Prints a string 
void CTextbox::Print(const char str[])
{
	for (short i = 0; str[i] != '\0'; ++i)
	{
		Print(str[i]);
	}
}

// Prints a string
void CTextbox::Print(const std::string str)
{
	Print(str.c_str());
}

// Prints a string with the specified text and background colour id
void CTextbox::Print(const char str[], int colour)
{
	SetColour(colour);
	Print(str);
}

// Prints a string with the specified text and background colour id
void CTextbox::Print(const std::string str, int colour)
{
	Print(str.c_str(), colour);
}

// Shifts every line of text up by n lines
void CTextbox::ScrollUp(int n)
{
	char* line = new char[m_bounds->width + 1];
	line[m_bounds->width] = '\0';
	for (short i = n; i < m_bounds->height; ++i)
	{
		for (short j = 0; j < m_bounds->width; ++j)
		{
			line[j] = GetCharacterAtCursor(m_bounds->x + j, m_bounds->y + i);
		}
		MoveTo(m_bounds->x, m_bounds->y + i - n);
		Print(line);
	}
	delete[] line;
	for (short i = std::max(0, m_bounds->height - n); i < m_bounds->height; ++i)
	{
		MoveTo(m_bounds->x, m_bounds->y + i);
		ClearLine();
	}
	MoveTo(m_bounds->x, m_bounds->y + std::max(0, m_bounds->height - n));
}