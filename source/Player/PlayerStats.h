// ******************************************************************************
// Filename:    PlayerStats.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 15/04/15
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "PlayerClass.h"

class Player;

#include <string>
using namespace std;


class PlayerStats
{
public:
	/* Public methods */
	PlayerStats(Player* pPlayer);
	~PlayerStats();

	// Reset
	void ResetStats();

	// Supress export
	void SetSupressExport(bool supress);

	// Loading / Saving
	void ImportStats(string playerName);
	void ExportStats(string playerName);
	
	// Accessors
	PlayerClass GetClass();
	int GetLevel();
	int GetExperience();
	int GetMaxExperience();
	int GetNumPointsAvailable();
	int GetStrengthStat();
	int GetDexterityStat();
	int GetIntelligenceStat();
	int GetVitalityStat();
	int GetArmorStat();
	int GetLuckStat();

	// Setters
	void SetClass(PlayerClass playerClass);
	void GiveExperience(int amount);
	void SetNumPointsAvailable(int numPoints);
	void SetStrengthStat(int stat);
	void SetDexterityStat(int stat);
	void SetIntelligenceStat(int stat);
	void SetVitalityStat(int stat);
	void SetArmorStat(int stat);
	void SetLuckStat(int stat);

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Player* m_pPlayer;

	// Player name
	string m_name;

	// Player class
	PlayerClass m_class;

	// Level
	int m_level;

	// Experience
	int m_experience;
	int m_maxExperience;

	// Num points to allocate to stats
	int m_numPointsAvailable;

	// Stats
	int m_strengthStat;
	int m_dexterityStat;
	int m_intelligenceStat;
	int m_vitalityStat;
	int m_armorStat;
	int m_luckStat;

	// Force to stop export player stats
	bool m_supressExport;
};
