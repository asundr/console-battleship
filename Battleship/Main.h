#pragma once

enum class TileType;
class CPlayer;
class CControllerAI;
class CTextbox;

void InitializeDisplay();
void PlayGame(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox);
void SetupShips(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox);
void DisplayTitle(CTextbox& _textbox, std::string _title, std::string _subtitle, short _colour);
void ResetGame(CPlayer& _player, CControllerAI& _ai);
bool PromptBool(CTextbox& _textbox, std::string message);
short PromptDigit();
void ShowMainMenu(CTextbox& _textbox);
void ShowOptions(CTextbox& _textbox);
void ShowCredits(CTextbox& _textbox);
void ShowInstructions(CTextbox& _textbox);

const std::string Credit_List[] =
{
	"Programmer:",
	"Arun Sundaram",
	"", 
	"ASCII Art Numbers:",
	"https://gist.github.com/yuanqing/ffa2244bd134f911d365",
	"",
	"Thanks for playing!", "Press any key to Exit."
};

const short Tile_Icons_ID[] = { 1, -1, 2, -2, 8, 7 };
const std::string Tile_Icon_Name[] =
{
	" Ocean", " Miss", " Ship", " Hit", " Valid", " Invalid"
};
