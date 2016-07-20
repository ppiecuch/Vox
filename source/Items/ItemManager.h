// ******************************************************************************
// Filename:    ItemManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   The item manager is in charge of managing and all the items in the game,
//   including creation, destruction, updating and rendering the items.
//   Different rendering modes are also supported for items depending on their
//   state.
//
// Revision History:
//   Initial Revision - 12/04/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include <vector>
#include <string>
using namespace std;

#include "Item.h"
#include "ItemSpawner.h"
#include "../blocks/ChunkManager.h"
#include "../blocks/BlocksEnum.h"
#include "../Particles/BlockParticleManager.h"
#include "../Inventory/InventoryManager.h"
#include "../Player/Player.h"

class LightingManager;

typedef std::vector<ItemSpawner*> ItemSpawnerList;


class ItemSubSpawnData
{
public:
	eItem m_sourceItem;
	BlockType m_sourceBlockType;

	eItem m_spawnedItem;
	string m_spawnedItemFilename;
	string m_spawnedItemTitle;
	bool m_collectible;
	bool m_interactable;
	float m_scale;

	string m_droppedItemFilename;
	string m_droppedItemTextureFilename;
	InventoryType m_droppedItemInventoryType;
	eItem m_droppedItemItem;
	ItemStatus m_droppedItemStatus;
	EquipSlot m_droppedItemEquipSlot;
	ItemQuality m_droppedItemQuality;
	bool m_droppedItemLeft;
	bool m_droppedItemRight;
	string m_droppedItemTitle;
	string m_droppedItemDescription;
	float m_droppedItemPlacementR;
	float m_droppedItemPlacementG;
	float m_droppedItemPlacementB;
	int m_droppedItemQuantity;
};

typedef vector<Item*> ItemList;
typedef vector<ItemSubSpawnData*> ItemSubSpawnDataList;

class ItemManager
{
public:
	/* Public methods */
	ItemManager(Renderer* pRenderer, ChunkManager* pChunkManager, Player* pPlayer);
	~ItemManager();

	void SetLightingManager(LightingManager* pLightingManager);
	void SetBlockParticleManager(BlockParticleManager* pBlockParticleManager);
	void SetQubicleBinaryManager(QubicleBinaryManager* pQubicleBinaryManager);
	void SetInventoryManager(InventoryManager* pInventoryManager);
	void SetNPCManager(NPCManager* pNPCManager);

	// Deletion
	void ClearItems();
	void ClearSubSpawnData();
	void ClearItemSpawners();

	void RemoveItemSpawnerFromItems(ItemSpawner* pSpawner);

	// Item sub spawn data
	ItemSubSpawnData* GetItemSubSpawnData(eItem sourceItem);
	ItemSubSpawnData* GetItemSubSpawnData(BlockType sourceBlockType);

	// Creation
	Item* CreateItem(vec3 position, vec3 velocity, vec3 rotation, const char* objectFilename, eItem itemType, const char* itemTitle, bool interactable, bool collectible, float scale);
	void RemoveItem(const char* itemTitle);
	ItemSpawner* CreateItemSpawner(vec3 position, vec3 direction);

	// Get number of items
	int GetNumItems();
	int GetNumRenderItems();

	// Collision detection
	bool CheckCollisions(vec3 center, vec3 previousCenter, float radius, vec3 *pNormal, vec3 *pMovement);

	// Player item interaction
	Item* CheckItemPlayerInteraction();

	// Rendering Helpers
	void CalculateWorldTransformMatrix();
	void SetWireFrameRender(bool wireframe);

	// Update
	void Update(float dt);
	void UpdateItemLights(float dt);
	void UpdateItemParticleEffects(float dt);
	void UpdateHoverItems();

	// Rendering
	void Render(bool outline, bool reflection, bool silhouette, bool shadow);
	void RenderDebug();

protected:
	/* Protected methods */

private:
	/* Private methods */
	void AddItemSubSpawnData(eItem sourceItem, BlockType sourceBlockType, eItem spawnedItem, string spawnedItemFilename, string spawnedItemTitle, bool interactable, bool collectible,float scale,
		string droppedItemFilename, string droppedItemTextureFilename, InventoryType droppedItemInventoryType, eItem droppedItemItem, ItemStatus droppedItemStatus, EquipSlot droppedItemEquipSlot, ItemQuality droppedItemQuality,
		bool droppedItemLeft, bool droppedItemRight, string droppedItemTitle, string droppedItemDescription, float droppedItemPlacementR, float droppedItemPlacementG, float droppedItemPlacementB, int droppedItemQuantity);

public:
	/* Public members */
	static float ITEM_INTERACTION_DISTANCE;
	static float ITEM_INERACCTION_RADIUS_CHECK;

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;
	ChunkManager* m_pChunkManager;
	LightingManager* m_pLightingManager;
	BlockParticleManager* m_pBlockParticleManager;
	Player* m_pPlayer;
	QubicleBinaryManager* m_pQubicleBinaryManager;
	InventoryManager* m_pInventoryManager;
	NPCManager* m_pNPCManager;

	// Counters
	int m_numRenderItems;

	// Item list
	ItemList m_vpItemList;

	// Item spawner
	ItemSpawnerList m_vpItemSpawnerList;

	// Subspawn data, used to control which items spawn sub items
	ItemSubSpawnDataList m_vpItemSubSpawnDataList;
};
