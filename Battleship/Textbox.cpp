#include <string>
#include "Textbox.h"
#include <iostream>
#include "Console.h"

using namespace Display;

CTextbox::CTextbox(Bounds _bounds) 
{
	m_bounds = new Bounds(_bounds);
	m_curr = new Point{ _bounds.x, _bounds.y };
}

CTextbox::~CTextbox()
{
}

const Bounds& CTextbox::Bound() const
{
	return *m_bounds;
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

// Prints a character at the current cursor position
void CTextbox::Print(char _chr)
{
	if (_chr == '\n' || m_curr->x == m_bounds->x + m_bounds->width)
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
		if (_chr == '\n')
		{
			return;
		}
	}
	MoveTo(*m_curr);
	std::cout << _chr;
	m_curr->x += _chr == '\t' ? 4 : 1;
}

// Print a character with the specified text and background colour id
void CTextbox::Print(char _c, int _colour)
{
	SetColour(_colour);
	Print(_c);
}

// Prints a string 
void CTextbox::Print(const char _str[])
{
	for (short i = 0; _str[i] != '\0'; ++i)
	{
		Print(_str[i]);
	}
}

// Prints a string
void CTextbox::Print(const std::string _str)
{
	Print(_str.c_str());
}

// Prints a string with the specified text and background colour id
void CTextbox::Print(const char _str[], int _colour)
{
	SetColour(_colour);
	Print(_str);
}

// Prints a string with the specified text and background colour id
void CTextbox::Print(const std::string _str, int _colour)
{
	Print(_str.c_str(), _colour);
}

// Prints a string centered on the current line (assumes x=0)
void CTextbox::PrintLineCentre(const std::string _str, int _colour)
{
	if (_colour >= 0)
	{
		SetColour(_colour);
	}
	short padding = (m_bounds->width - (short)_str.length()) / 2;
	MoveTo(m_bounds->x + padding, m_curr->y);
	Print(_str);
}

// Shifts every line of text up by n lines
void CTextbox::ScrollUp(int _count)
{
	char* line = new char[m_bounds->width + 1];
	line[m_bounds->width] = '\0';
	for (short i = _count; i < m_bounds->height; ++i)
	{
		for (short j = 0; j < m_bounds->width; ++j)
		{
			line[j] = GetCharacterAtCursor(m_bounds->x + j, m_bounds->y + i);
		}
		MoveTo(m_bounds->x, m_bounds->y + i - _count);
		Print(line);
	}
	delete[] line;
	for (short i = std::max(0, m_bounds->height - _count); i < m_bounds->height; ++i)
	{
		MoveTo(m_bounds->x, m_bounds->y + i);
		ClearLine();
	}
	MoveTo(m_bounds->x, m_bounds->y + std::max(0, m_bounds->height - _count));
}
