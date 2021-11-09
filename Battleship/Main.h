#pragma once

#include "Player.h"
#include "ControllerAI.h"
#include "Textbox.h"

void InitializeDisplay();
void PlayGame(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox);
void SetupShips(CPlayer& _player, CControllerAI& _ai, CTextbox& _textbox);
void ResetGame(CPlayer& _player, CControllerAI& _ai);
bool PromptBool(CTextbox& _textbox, std::string message);

const std::string Credit_List[] =
{
	"\t\t\t\tCredits",
	"\n", "\n",
	"\n\t\t\t  Programmer:",
	"\n\t\t\t Arun Sundaram",
	"\n", "\n",
	"\n\t\t  ASCII Art Numbers:",
	"\n   https://gist.github.com/yuanqing/", "\n\t\t ffa2244bd134f911d365",
	"\n", "\n",	"\n", "\n",
	"\n\t\t  Thanks for playing!",
	"\n\t\tPress Enter to return.",
	"\n", "\n",	"\n", "\n"
};

