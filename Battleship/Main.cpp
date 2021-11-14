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

	CGrid g1(Point{ 3, 1 });
	CGrid g2(Point{ 66, 1 });
	CPlayer p1(g1);
	CControllerAI p2(g2);
	CTextbox textbox({ 4, 32, 121, 8 });
	ResetGame(p1, p2);

	DisplayTitle(textbox, "BATTLESHIP", "\b", 0x0E);
	ShowInstructions(textbox);

	do
	{
		ResetGame(p1, p2);
		PlayGame(p1, p2, textbox);
	} while (PromptBool(textbox, "\nPlay again (Y/N)? "));
	
	ShowCredits(textbox);
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
	_player.Grid().Draw();
	_ai.Grid().Draw();

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
	_player.Grid().Draw();
	_ai.Grid().Draw();
}

void InitializeDisplay()
{
	using namespace Display;
	srand((unsigned int)time(NULL));
	SetWindowBounds(0, 0, 960, 700);
	ShowCursor(false);

	short borderColour = 0x6;
	DrawBorder({ 1, 0 , 64, 32 }, borderColour, Border_Tiles);
	DrawBorder({ 64, 0 , 64, 32 }, borderColour, Border_Tiles);
	DrawBorder({ 1, 31, 127, 10 }, borderColour, Border_Tiles);

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
	Bounds textBounds = Bounds(_textbox.Bound());
	textBounds.y--;
	for (int i = 0; i < textBounds.height; ++i)
	{
		_textbox.ScrollUp(1);
	}
	Display::PrintTitle(textBounds, _title, 0x0E);
	_textbox.PrintLineCentre(_subtitle.append(" Press E to continue."));
	while (tolower(_getch()) != 'e');
	for (int i = 0; i < textBounds.height; ++i)
	{
		_textbox.ScrollUp(1);
	}
	Display::ResetConsoleText();
}

void ResetGame(CPlayer& _player, CControllerAI& _ai)
{
	_player.Reset();
	_player.Grid().Reset();
	_ai.Reset();
	_ai.Grid().Reset();
	_ai.Grid().SetVisible(false);
	_player.Grid().Draw();
	_ai.Grid().Draw();
}

bool PromptBool(CTextbox& _textbox, std::string message)
{
	_textbox.Print(message);
	char input = tolower(_getch());
	while (input != 'y' && input != 'n')
	{
		input = tolower(_getch());
	}
	_textbox.Print(input);
	return input == 'y';
}

void ShowCredits(CTextbox& _textbox)
{
	Display::SetColour(0xE);
	_textbox.Clear();
	for (const std::string& str : Credit_List)
	{
		_textbox.Print('\n');
		_textbox.PrintLineCentre(str);
	}
	char input = _getch();
	for (short i = 0; i < _textbox.Height(); ++i)
	{
		_textbox.ScrollUp(1);
	}
}

void ShowInstructions(CTextbox& _textbox)
{
	short padding = 7;
	_textbox.PrintLineCentre("Tile Types\n\n\n\n\n\n", 0xE);
	_textbox.PrintLineCentre("Goal: Destroy your opponent's ships before they can destroy your own.\n");
	_textbox.PrintLineCentre("Press any key to continue.");
	for (int i = 0; i < 6; ++i)
	{
		short dx = i * _textbox.Width();
		CTile(TileType(Tile_Icons_ID[i])).Draw(padding + dx / 6, 34);
		const std::string& name = Tile_Icon_Name[i];
		Display::PrintStringAt(padding + 6 + dx, 36, name, 0x7);
	}
	char input = _getch();
	for (short i = 0; i < _textbox.Height(); ++i)
	{
		_textbox.ScrollUp(1);
	}
}

// TODO
// 
// check requirement
// Label features

