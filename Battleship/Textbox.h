#pragma once

struct Point;
struct Bounds;

class CTextbox
{
public:
	CTextbox(Bounds _bounds);
	~CTextbox();
	short Height() const;
	short Width() const;
	void MoveTo(short _x, short _y);
	void MoveTo(Point _p);
	void Clear();
	void ClearLine();
	void Print(char _chr);
	void Print(char _c, int _colour);
	void Print(const char _str[]);
	void Print(const std::string _str);
	void Print(const char _str[], int _colour);
	void Print(const std::string _str, int _colour);
	void PrintLineCentre(const std::string _str, int _colour = -1);
	void ScrollUp(int _count);
private:
	Bounds* m_bounds;
	Point* m_curr;
};
