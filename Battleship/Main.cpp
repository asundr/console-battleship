#include <string>
#include "Main.h"
#include <ctime>
#include "conio.h"
#include "Tile.h"
#include "Grid.h"
#include "Player.h"
#include "ControllerAI.h"
#include "Console.h"
#include "Textbox.h"
#include "Display.h"

int main()
{
	InitializeDisplay();

	CGrid g1({ 3,1 }, 10, 10);
	CGrid g2({ 66,1 });
	CPlayer p1(g1);
	CControllerAI p2(g2);
	CTextbox textbox({ 4, 32, 121, 8 });
	ResetGame(p1, p2);

	DisplayTitle(textbox, "BATTLESHIP", "Press any key to play.", 0x0E);

	do
	{
		ResetGame(p1, p2);
		PlayGame(p1, p2, textbox);
	} while (PromptBool(textbox, "\nPlay again (Y/N)? "));
	
	return 0;
}

void PlayGame(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox)
{
	bool victory = false;
	SetupShips(_player, _ai, _textbox);
	while (_player.Grid().GetFreeTiles() > 0 && _ai.Grid().GetFreeTiles() > 0)
	{
		TileType type = _player.Turn(_ai);
		_textbox.Print("\n\nYou fire... ");
		if (CTile::IsShip(type) && CTile::CanHit(type))
		{
			_textbox.Print("and HIT!");
		}
		else
		{
			_textbox.Print("and miss!");
		}
		if (_ai.UpdateShips(type))
		{
			if (_ai.HasLostAllShips())
			{
				victory = true;
				break;
			}
			else
			{
				_textbox.Print("\nYou destroyed one of your opponent's ships!");
			}
		}
		
 		type = _ai.Turn(_player);
		_textbox.Print("\nYour opponent fires... ");
		if (CTile::IsShip(type) && CTile::CanHit(type))  
		{
			_textbox.Print("and HITS!");
		}
		else
		{
			_textbox.Print("and misses!");
		}
		if (_player.UpdateShips(type))
		{
			if (_player.HasLostAllShips())
			{
				victory = false;
				break;
			}
			else
			{
				_textbox.Print("\nOne of your ships has been destroyed!");
			}
		}
	}
	_ai.Grid().SetVisible(true);
	_player.Grid().Display();
	_ai.Grid().Display();

	if (victory)
	{
		DisplayTitle(_textbox, "YOU WIN", "You destroyed all of your enemy's ships!", 0x0E);
	}
	else
	{
		DisplayTitle(_textbox, "YOU LOSE", "All of your ships have been destroyed!", 0x0E);
	}
}

void SetupShips(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox)
{
	_ai.PlaceShipsRandom();
	bool manualPlacement = PromptBool(_textbox, "\n\nWould you like to place your ships manually (Y/N)? ");
	_textbox.Print("\nUse WASD to move, E to rotate and SPACE to confirm location.");
	if (manualPlacement)
	{
		_player.PlaceShips();
	}
	else
	{
		_player.PlaceShipsRandom();
	}
	_player.Grid().Display();
	_ai.Grid().Display();
}

void InitializeDisplay()
{
	srand((unsigned int)time(NULL));
	SetWindowBounds(0, 0, 960, 700);
	ShowCursor(false);

	short borderColour = 0x6;
	DrawBorder({ 1, 0 , 64, 32 }, borderColour, Border_Tiles);
	DrawBorder({ 64, 0 , 64, 32 }, borderColour, Border_Tiles);
	DrawBorder({ 1, 31, 127, 10 }, borderColour, Border_Tiles); // TODO finish borders

	// connecting borders
	DrawAt(1, 31, '\u00CC', borderColour);
	DrawAt(127, 31, '\u00B9', borderColour);
	DrawAt(64, 0, '\u00CB', borderColour);
	DrawAt(64, 31, '\u00CA', borderColour);
	
	PrintStringAt(29, 0, " PLAYER ", 0xE);
	PrintStringAt(91, 0, " OPPONENT ", 0xE);
	ResetConsoleText();
}

void DisplayTitle(CTextbox& _textbox, std::string _title, std::string _subtitle, short _colour)
{
	Bounds textBounds = { 4, 31, 121, 8 };  // TODO generalize
	for (int i = 0; i < textBounds.height; ++i)
	{
		_textbox.ScrollUp(1);
	}
	PrintTitle(textBounds, _title, 0x0E);
	_textbox.Print("\t\t\t\t\t\t\t\t\t\t\t\t"); // TODO generalize
	_textbox.Print(_subtitle);
	while (_getch() != 'e');		// TODO pick key or add options
	for (int i = 0; i < textBounds.height; ++i)
	{
		_textbox.ScrollUp(1);
	}
}

void ResetGame(CPlayer& _player, CControllerAI& _ai)
{
	_player.Reset();
	_player.Grid().Reset();
	_ai.Reset();
	_ai.Grid().Reset();
	_ai.Grid().SetVisible(false);

	_player.Grid().Display();
	_ai.Grid().Display();
}

bool PromptBool(CTextbox& _textbox, std::string message)
{
	_textbox.Print(message);
	char input = _getch();
	while (input != 'Y' && input != 'y' && input != 'n' && input != 'N')
	{
		input = _getch();
	}
	_textbox.Print(input);
	return input == 'Y' || input == 'y';
}

// TODO
// 
// check requirement
// credits
// Cleanup / check resets
// Playtesting / polish
// Cleanup + comments
// Label features

