// ******************************************************************************
// Filename:    PlayerStats.cpp
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

#include "PlayerStats.h"
#include "Player.h"
#include "../VoxGame.h"

#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
using namespace std;


PlayerStats::PlayerStats(Player* pPlayer)
{
	m_pPlayer = pPlayer;	

	m_class = PlayerClass_Debug;

	m_supressExport = false;

	ResetStats();
}

PlayerStats::~PlayerStats()
{
}

// Reset
void PlayerStats::ResetStats()
{
	m_level = 1;

	m_experience = 0;
	m_maxExperience = 100;

	m_numPointsAvailable = 0;

	m_strengthStat = 1;
	m_dexterityStat = 1;
	m_intelligenceStat = 1;
	m_vitalityStat = 1;
	m_armorStat = 1;
	m_luckStat = 1;
}

// Supress export
void PlayerStats::SetSupressExport(bool supress)
{
	m_supressExport = supress;
}

// Loading / Saving
void PlayerStats::ImportStats(string playerName)
{
	m_name = playerName;

	ifstream importFile;
	char lfilename[128];
	sprintf(lfilename, "saves/characters/%s/%s.stats", playerName.c_str(), playerName.c_str());
	importFile.open(lfilename, ios_base::binary);

    if(importFile.is_open())
    {
		string tempString;

		string name;
		importFile >> tempString >> name;

		int playerClass;
		importFile >> tempString >> playerClass;
		m_class = (PlayerClass)playerClass;

		importFile >> tempString >> m_level;
		importFile >> tempString >> m_experience;
		importFile >> tempString >> m_maxExperience;
		importFile >> tempString >> m_numPointsAvailable;
		importFile >> tempString >> m_strengthStat;
		importFile >> tempString >> m_dexterityStat;
		importFile >> tempString >> m_intelligenceStat;
		importFile >> tempString >> m_vitalityStat;
		importFile >> tempString >> m_armorStat;
		importFile >> tempString >> m_luckStat;

		// Import the file signature
		string signature;
		importFile >> tempString >> signature;

		importFile.close();
	}
}

void PlayerStats::ExportStats(string playerName)
{
	if (m_supressExport)
	{
		return;
	}

	if(playerName == "")
	{
		return;
	}

	ofstream exportFile;
	char lfilename[128];
	sprintf(lfilename, "saves/characters/%s/%s.stats", playerName.c_str(), playerName.c_str());
	exportFile.open(lfilename, ios_base::binary);

	if(exportFile.is_open())
	{
		exportFile << "name: " << playerName << "\n";
		exportFile << "class: " << m_class << "\n";
		exportFile << "level: " << m_level << "\n";
		exportFile << "experience: " << m_experience << "\n";
		exportFile << "maxExperience: " << m_maxExperience << "\n";
		exportFile << "numStatsPoints: " << m_numPointsAvailable << "\n";
		exportFile << "strength: " << m_strengthStat << "\n";
		exportFile << "dexterity: " << m_dexterityStat << "\n";
		exportFile << "intelligence: " << m_intelligenceStat << "\n";
		exportFile << "vitality: " << m_vitalityStat << "\n";
		exportFile << "armor: " << m_armorStat << "\n";
		exportFile << "luck: " << m_luckStat << "\n\n";

		// Export the file signature
		exportFile << "signature: " << "\n";

		exportFile.close();
	}
}

// Accessors
PlayerClass PlayerStats::GetClass()
{
	return m_class;
}

int PlayerStats::GetLevel()
{
	return m_level;
}

int PlayerStats::GetExperience()
{
	return m_experience;
}

int PlayerStats::GetMaxExperience()
{
	return m_maxExperience;
}

int PlayerStats::GetNumPointsAvailable()
{
	return m_numPointsAvailable;
}

int PlayerStats::GetStrengthStat()
{
	return m_strengthStat;
}

int PlayerStats::GetDexterityStat()
{
	return m_dexterityStat;
}

int PlayerStats::GetIntelligenceStat()
{
	return m_intelligenceStat;
}

int PlayerStats::GetVitalityStat()
{
	return m_vitalityStat;
}

int PlayerStats::GetArmorStat()
{
	return m_armorStat;
}

int PlayerStats::GetLuckStat()
{
	return m_luckStat;
}

// Setters
void PlayerStats::SetClass(PlayerClass playerClass)
{
	m_class = playerClass;
}

void PlayerStats::GiveExperience(int amount)
{
	m_experience += amount;

	if(m_experience >= m_maxExperience)
	{
		m_pPlayer->LevelUp();

		m_maxExperience = (int)(m_maxExperience * 1.5f);
		m_experience = 0;
		m_level++;

		m_numPointsAvailable += 5;

		VoxGame::GetInstance()->GetCharacterGUI()->UpdatePlayerStats();
	}

	VoxGame::GetInstance()->GetHUD()->UpdatePlayerData();

	ExportStats(m_name);
}

void PlayerStats::SetNumPointsAvailable(int numPoints)
{
	m_numPointsAvailable = numPoints;

	ExportStats(m_name);
}

void PlayerStats::SetStrengthStat(int stat)
{
	m_strengthStat = stat;

	ExportStats(m_name);
}

void PlayerStats::SetDexterityStat(int stat)
{
	m_dexterityStat = stat;

	ExportStats(m_name);
}

void PlayerStats::SetIntelligenceStat(int stat)
{
	m_intelligenceStat = stat;

	ExportStats(m_name);
}

void PlayerStats::SetVitalityStat(int stat)
{
	m_vitalityStat = stat;

	ExportStats(m_name);
}

void PlayerStats::SetArmorStat(int stat)
{
	m_armorStat = stat;

	ExportStats(m_name);
}

void PlayerStats::SetLuckStat(int stat)
{
	m_luckStat = stat;

	ExportStats(m_name);
}
