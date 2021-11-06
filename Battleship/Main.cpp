#include <iostream>
#include <string>
#include <limits>
#include "Main.h"
#include "Grid.h"
#include "Player.h"
#include "ControllerAI.h"
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
	CPlayer p1(g1);
	CControllerAI p2(g2);

	p2.PlaceShipsRandom();

	g1.Display();
	g2.Display();

	CGrid& grid = g2;
	
	p1.PlaceShips();
	g1.Display();

	while (g2.GetFreeTiles() > 0)
	{
		p1.Turn(p2);
		p2.Turn(p1);
		CursorPos(1, 40);
		std::cout << p1.Grid().GetFreeTiles();
		g1.Display();
	}

	return 0;
}

// TODO
// 
// Ship damage
// Game loop
// Refine AI
// Feedback / text
// Main menu
// Cleanup
// Playtesting / polish
// Cleanup
//