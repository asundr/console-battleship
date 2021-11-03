#include <iostream>
#include <string>
#include <limits>
#include "Main.h"
#include "Grid.h"
#include "Console.h"

int main()
{
	srand((unsigned int)time(NULL));
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, 1500, 800, TRUE); // resize cmd window
	ShowCursor(false);

	CGrid p1({ 5,1 }, 10, 10);
	CGrid p2({ 75,1 });
	CTile a(2);
	p1.SetTile(3, 8, a);

	p1.Display();
	p2.Display();

	return 0;
}

