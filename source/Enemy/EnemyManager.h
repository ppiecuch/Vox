// ******************************************************************************
// Filename:    EnemyManager.h
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


#include "Enemy.h"
#include "EnemySpawner.h"

#include "../blocks/ChunkManager.h"

class LightingManager;
class BlockParticleManager;
class TextEffectsManager;
class ItemManager;
class ProjectileManager;
class HUD;
class NPCManager;

typedef std::vector<Enemy*> EnemyList;
typedef std::vector<EnemySpawner*> EnemySpawnerList;


class EnemyManager
{
public:
	/* Public methods */
	EnemyManager(Renderer* pRenderer, ChunkManager* pChunkManager, Player* pPlayer);
	~EnemyManager();

	void SetLightingManager(LightingManager* pLightingManager);
	void SetBlockParticleManager(BlockParticleManager* pBlockParticleManager);
	void SetTextEffectsManager(TextEffectsManager* pTextEffectsManager);
	void SetItemManager(ItemManager* pItemManager);
	void SetProjectileManager(ProjectileManager* pProjectileManager);
	void SetHUD(HUD* pHUD);
	void SetQubicleBinaryManager(QubicleBinaryManager* pQubicleBinaryManager);
	void SetNPCManager(NPCManager* pNPCManager);

	// Clearing
	void ClearEnemies();
	void ClearEnemyChunkCacheForChunk(Chunk* pChunk);
	void ClearEnemySpawners();

	void RemoveEnemySpawnerFromEnemies(EnemySpawner* pSpawner);

	// Creation
	Enemy* CreateEnemy(vec3 position, eEnemyType enemyType, float scale);
	void CreateEnemyCamp(vec3 campPosition);
	EnemySpawner* CreateEnemySpawner(vec3 position, vec3 direction);

	// Get number of enemies
	int GetNumEnemies();
	int GetNumRenderEnemies();
	Enemy* GetEnemy(int index);

	// Get enemy based on cursor position
	Enemy* GetCursorEnemy(Camera* pGameCamera, int cursorX, int cursorY);

	// Rendering Helpers
	void SetWireFrameRender(bool wireframe);

	// Gameplay
	void RemoveSappedFromEnemies(Enemy *pEnemyToBeSapped);

	// Collision
	void PushCollisions(Enemy* pPushingEnemy, vec3 position, float radius);

	// Updating
	void UpdateWeaponLights(float dt);
	void UpdateWeaponParticleEffects(float dt);
	void Update(float dt);
	void UpdateEnemyPlayerAttackCheck(float dt);
	void UpdateEnemyProjectileCheck(float dt);
	void CalculateWorldTransformMatrix();

	// Rendering
	void Render(bool outline, bool reflection, bool silhouette, bool shadow);
	void RenderFaces();
	void RenderOutlineEnemies();
	void RenderWeaponTrails();
	void RenderDebug();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	static const int MAX_NUM_ENEMIES = 15;

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;
	ChunkManager* m_pChunkManager;
	LightingManager* m_pLightingManager;
	Player* m_pPlayer;
	BlockParticleManager* m_pBlockParticleManager;
	TextEffectsManager* m_pTextEffectsManager;
	ItemManager* m_pItemManager;
	ProjectileManager* m_pProjectileManager;
	HUD* m_pHUD;
	QubicleBinaryManager* m_pQubicleBinaryManager;
	NPCManager* m_pNPCManager;

	int m_numRenderEnemies;

	// Enemy lists
	tthread::mutex m_enemyMutex;
	EnemyList m_vpEnemyList;
	EnemyList m_vpEnemyCreateList;

	// Enemy spawner
	tthread::mutex m_enemySpawnerMutex;
	EnemySpawnerList m_vpEnemySpawnerList;
};
