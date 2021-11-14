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
private:
	Bounds* m_bounds;
	Point* m_curr;
};
