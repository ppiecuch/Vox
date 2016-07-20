// ******************************************************************************
// Filename:    RandomLootManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 01/04/16
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "Item.h"
#include "ItemsEnum.h"
#include "../Enemy/Enemy.h"
#include "../Inventory/InventoryManager.h"

#include <vector>
#include <string>
using namespace std;


class EnemyIngredientsSpawnData
{
public:
	eEnemyType m_sourceEnemy;
	eItem m_spawnedItem;
	int m_minSpawn;
	int m_maxSpawn;
};

class RandomLootItem
{
public:
	InventoryItem* m_pLootItem;
	eEquipment m_equipmentType;
	int m_repickValue;
};

typedef vector<EnemyIngredientsSpawnData*> EnemyIngredientsSpawnDataList;
typedef vector<RandomLootItem*> RandomLootItemList;

class RandomLootManager
{
public:
	/* Public methods */
	RandomLootManager();
	~RandomLootManager();

	// Deletion
	void ClearEnemyIngredientsSpawnData();
	void ClearRandomLootList();

	// Enemy dropping ingredients
	void AddEnemyIngredientSpawnData(eEnemyType sourceEnemy, eItem spawnedItem, int minSpawn, int maxSpawn);
	void GetSpawnedIngredientItemForEnemy(eEnemyType sourceEnemy, eItem *item, int *quantity);

	// Random loot
	void AddRandomLoot(eEquipment equipment);
	InventoryItem* GetRandomLootItem(eEquipment *equipment);

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

	// Enemy ingredients
	EnemyIngredientsSpawnDataList m_vpEnemyIngredientsSpawnDataList;

	// Random loot
	RandomLootItemList m_vpRandomLootItemList;
};
