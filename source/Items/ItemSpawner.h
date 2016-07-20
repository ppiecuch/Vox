// ******************************************************************************
// Filename:    ItemSpawner.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 18/11/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "Item.h"
#include "../blocks/ChunkManager.h"
#include "../blocks/BiomeManager.h"
#include "../Particles/BlockParticleManager.h"


class LightingManager;
class GameWindow;
class BlockParticleManager;
class TextEffectsManager;
class ItemManager;
class ProjectileManager;
class Projectile;
class NPCManager;
class NPC;

class ItemSpawner
{
public:
	/* Public methods */
	ItemSpawner(Renderer* pRenderer, ChunkManager* pChunkManager, Player* pPlayer, ItemManager* pItemManager, NPCManager* pNPCManager);
	~ItemSpawner();

	// Accessors
	void SetPosition(vec3 pos);
	vec3 GetPosition();
	void SetInitialPosition(vec3 pos);
	vec3 GetInitialPosition();
	void SetFacingDirection(vec3 dir);
	vec3 GetFacingDirection();
	bool ShouldFollowPlayer();

	// Spawning params
	void SetSpawningParams(float initialSpawnDelay, float spawnTimer, int maxNumItemsActive, vec3 spawnRandomOffset, bool shouldSpawnOnGround, vec3 groundSpawnOffset, bool followPlayerIntheWorld, bool spawnFullLoaderRange, float minDistanceFromPlayer, Biome biomeSpawn, float spawnScale);
	void AddItemTypeToSpawn(eItem item);

	// Items removed
	void RemoveItemFromThisSpawner();

	// Spawning
	void StartSpawning(float initialDelay);
	void StopSpawning();
	eItem GetItemTypeToSpawn();
	bool GetSpawnPosition(vec3* pSpawnPosition);

	// Updating
	void Update(float dt);
	void UpdateTimers(float dt);

	// Rendering
	void Render();
	void RenderDebug();

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
	Renderer* m_pRenderer;
	ChunkManager* m_pChunkManager;
	Player* m_pPlayer;
	ItemManager* m_pItemManager;
	NPCManager* m_pNPCManager;

	// Are we spawning?
	bool m_spawning;

	// Can we spawn?
	bool m_canSpawn;

	// What biome do we spawn items in?
	Biome m_biomeSpawn;

	// Spawn time delay
	float m_spawnTime;

	// Number of spawned items from this spawner
	int m_numSpawnedItems;

	// Max number of items to have active at once
	int m_maxNumItemsToHaveActive;

	// Should we follow the player as he moves in the world? i.e So that we can constantly spawn items around the player
	bool m_followPlayerIntheWorld;

	// Can we spawn in the full loader range?
	bool m_spawnFullLoaderRange;

	// Spawn scale for the item
	float m_spawnScale;

	// Random spawn offset
	vec3 m_spawnRandomOffset;

	// What is the minimum distance that we have to be from the player when spawning.
	float m_minDistanceFromPlayer;

	// Should we spawn on the ground?
	bool m_shouldSpawnOnGround;

	// Should we spawn an offset from the ground?
	vec3 m_groundSpawnOffset;

	// Item types to spawn
	std::vector<eItem> m_vpItemTypeList;

	// Spawner position
	vec3 m_position;
	vec3 m_initialiPosition;

	// Facing direction
	vec3 m_spawnFacingDirection;

	// Spawning params
	float m_spawnCountdownTimer;
};
