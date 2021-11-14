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

class CTextbox
{
	const Point m_origin; // TODO convert to bounds
	Point m_curr;
	const short m_width, m_height;
public:
	CTextbox(Point _origin, short _width, short _height);
	~CTextbox();
	Point Origin() const;
	short Height() const;
	short Width() const;
	void MoveTo(short x, short y);
	void MoveTo(Point p);
	void Clear();
	void ClearLine();
	void Print(char c);
	void Print(char c, int colour);
	void Print(const char str[]);
	void Print(const std::string str);
	void Print(const char str[], int colour);
	void Print(const std::string str, int colour);
	void ScrollUp(int n);
};
