#pragma once

struct Bounds;
struct Point;

namespace Display
{

	// Each bit represents a pixel for a 6x5 number
	const int Digit_Masks[] =
	{
		0b011110110011110011110011011110,	// 0
		0b111100001100001100001100111111,	// 1
		0b011110110011000110001100111111,	// 2
		0b011110110011000110110011011110,	// 3
		0b110011110011111111000011000011,	// 4
		0b111111110000111110000011111110,	// 5
		0b011110110000111110110011011110,	// 6
		0b111111000110001100011000110000,	// 7
		0b011110110011011110110011011110,	// 8
		0b011110110011011111000011011110	// 9
	};

	// Each bit represents a pixel for a 6x5 letter
	const int Letter_Masks[] =
	{
		0b011110110011111111110011110011,	// A
		0b111110110011111111110011111111,	// B
		0b011110110011110000110011011110,	// C
		0b111110110011110011110011111110,	// D
		0b111111110000111111110000111111,	// E
		0,									// F
		0,									// G
		0b110011110011111111110011110011,	// H
		0b111111001100001100001100111111,	// I
		0b111111000110110110110110011110,	// J
		0b110011110110111100110110110011,	// K
		0b110000110000110000110000111111,	// L
		0,									// M
		0b110011111011111111110111110011,	// N
		0b111111110011110011110011111111,	// O
		0b111111110011111111110000110000,	// P
		0,									// Q
		0b111111110001111111110110110011,	// R
		0b111111110000111111000011111111,	// S
		0b111111001100001100001100001100,	// T
		0b110011110011110011110011111111,	// U
		0b110011110011110011110011001100,	// V
		0b110011101101101101101101111111,	// W
		0,									// X
		0b110011110011111111001100001100,	// Y
		0									// Z
	};

	// defines eights characters used to draw the top, bottom, left, right,
	// top-left, top-right, bottom-left, bottom-right tiles respectively
	const char Border_Tiles[] = "\u00CD\u00BA\u00CD\u00BA\u00C9\u00BB\u00BC\u00C8";

	void PrintLetterColumn(int _mask, Point _p, int _col, int _padding = 1);
	void PrintLetterRow(int _mask, Point _p, int _row, int _padding, char _background);
	void DrawBorder(const Bounds& _bounds, int _colour, const char _borderTiles[]);
	void FillBorder(const Bounds& _bounds, int _colour);
	void PrintTitle(const Bounds& _bounds, const std::string& _word, short _colour);
	void DrawAt(short _x, short _y, char _c, short _colour = -1);
	void PrintStringAt(short _x, short _y, std::string _str, short _colour = -1);
}
