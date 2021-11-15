#include "Settings.h"

bool CSettings::s_debugMode = false;
bool CSettings::s_damageFlash = true;
bool CSettings::s_advancedAI = true;
bool CSettings::s_alternateTiles = false;

void CSettings::ToggleDebugMode(bool _enable)
{
	s_debugMode = _enable;
}

void CSettings::ToggleDebugMode()
{
	s_debugMode = !s_debugMode;
}

bool CSettings::DebugMode()
{
	return s_debugMode;
}

void CSettings::ToggleDamageFlash()
{
	s_damageFlash = !s_damageFlash;
}

bool CSettings::DamageFlash()
{
	return s_damageFlash;
}

void CSettings::ToggleAIDifficulty()
{
	s_advancedAI = !s_advancedAI;
}

bool CSettings::DifficultAI()
{
	return s_advancedAI;
}

void CSettings::ToggleAlternateTiles()
{
	s_alternateTiles = !s_alternateTiles;
}

bool CSettings::AlternateTiles()
{
	return s_alternateTiles;
}
