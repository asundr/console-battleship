#include <iostream>
#include <string>
#include <limits>
#include "Main.h"
#include "Grid.h"
#include "Player.h"
#include "Console.h"

#include "conio.h"

int main()
{
	srand((unsigned int)time(NULL));
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, 1500, 800, TRUE); // resize cmd window
	ShowCursor(false);

	CGrid g1({ 5,1 }, 10, 10);
	CGrid g2({ 75,1 });
	CTile a(2);
	//p1.SetTile(3, 8, a);



	CPlayer p1(g1);
	p1.PlaceShipsRandom();

	g1.Display();
	g2.Display();

	p1.SetSelectorBounds(0, 0, 1, 5);

	//CursorPos(1, 40);
	//int out = _getch();
	//std::cout << out;

	CGrid& grid = g2;
	
	while (true)
	{
		int out = _getch();
		if (out == 101)
		{
			p1.ToggleSelectorRotation(grid);
		}
		else if (out == 13)
		{

		}
		else
		{
			Point dx;
			switch (out)
			{
			case 97:
				dx = { -1, 0 }; break;
			case 100:
				dx = { 1, 0 }; break;
			case 115:
				dx = { 0, 1 }; break;
			case 119:
				dx = { 0, -1 }; break;
			default:
				dx = { 0,0 };
			}
			p1.ShiftSelector(dx, grid);
		}
	}


	return 0;
}

// TODO
// 
// Player Inputs ( mouse input? )
// Player ship placement
// Ship damage
// Game loop
// Refine AI
// Feedback
// Main menu
// Cleanup
// Playtesting / polish
// Cleanup
//