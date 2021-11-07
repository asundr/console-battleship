#include <iostream>
#include <string>
#include <limits>
#include "Main.h"
#include "Grid.h"
#include "Display.h"		// remove Ctextbox form display
#include "Console.h"
//#include "TextWindow.h" DELETE ME AND FILES


#include "conio.h"

int main()
{
	//CPlayer* ptrPlayer, CControllerAI* ptrAI
	InitializeGame();

	CGrid g1({ 5,1 }, 10, 10);
	CGrid g2({ 75,1 });
	CPlayer p1(g1);
	CControllerAI p2(g2);
	CTextbox textbox({ 6,32 }, 128, 8);
	ResetGame(p1, p2);

	textbox.Print("Welcom to BattleShip! Press anything to play.");
	_getch();
	PlayGame(p1, p2, textbox);
	//ResetGame(p1,p2);
	return 0;
}

void PlayGame(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox)
{
	SetupShips(_player, _ai, _textbox);
	while (_player.Grid().GetFreeTiles() > 0)
	{
		if (_player.Turn(_ai))
		{
			_textbox.Print("\nYou win! All of your enemie's ships have been destroyed!");
			break;
		}
		if (_ai.Turn(_player))
		{
			_textbox.Print("\nYou Lose! All of your ships have been destroyed!");
			break;
		}
		//CursorPos(1, 40);
		_player.Grid().Display();
	}
}

void SetupShips(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox)
{
	_ai.PlaceShipsRandom();
	_textbox.Print("\nWould you like to place your ships manually (Y/N)? ");
	char input = _getch();
	bool manualPlacement = input == 'Y' || input == 'y';
	if (manualPlacement)
	{
		_textbox.Print("\nUse WASD to move, E to rotate and SPACE to confirm location.");
		_player.PlaceShips();
	}
	else
	{
		_player.PlaceShipsRandom();
	}
	_player.Grid().Display(); // TODO this is for the last ship, fix later
	_ai.Grid().Display();
}

void InitializeGame()
{
	srand((unsigned int)time(NULL));
	HWND console = GetConsoleWindow();
	MoveWindow(console, 0, 0, 1500, 800, TRUE); // resize cmd window
	ShowCursor(false);

	DrawBorder({ 4, 31, 132, 10 }, 0xD, Border_Tiles_Marquee);
}

void ResetGame(CPlayer& _player, CControllerAI& _ai)
{
	_player.Reset();
	_player.Grid().Reset();
	_ai.Reset();
	_ai.Grid().Reset();

	_player.Grid().Display();
	_ai.Grid().Display();
}

// TODO
// 
// Feedback / text
// Refine AI
// Main menu / credits
// Cleanup
// Playtesting / polish / ship placement
// Cleanup + comments
// Label features

