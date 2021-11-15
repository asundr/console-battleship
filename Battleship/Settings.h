#pragma once

class CSettings
{
public:
	static void ToggleDebugMode(bool _enable);
	static void ToggleDebugMode();
	static bool DebugMode();
	static void ToggleDamageFlash();
	static bool DamageFlash();
	static void ToggleAIDifficulty();
	static bool DifficultAI();
	static void ToggleAlternateTiles();
	static bool AlternateTiles();
private:
	static bool s_debugMode;
	static bool s_damageFlash;
	static bool s_advancedAI;
	static bool s_alternateTiles;
};
