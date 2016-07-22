// ******************************************************************************
// Filename:    ProjectileManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 15/02/15
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "Projectile.h"

#include "../blocks/ChunkManager.h"
#include "../Particles/BlockParticleManager.h"

class LightingManager;
class GameWindow;

typedef std::vector<Projectile*> ProjectileList;

class ProjectileManager
{
public:
	/* Public methods */
	ProjectileManager(Renderer* pRenderer, ChunkManager* pChunkManager);
	~ProjectileManager();

	void SetLightingManager(LightingManager* pLightingManager);
	void SetBlockParticleManager(BlockParticleManager* pBlockParticleManager);
	void SetPlayer(Player* pPlayer);
	void SetQubicleBinaryManager(QubicleBinaryManager* pQubicleBinaryManager);

	// Clearing
	void ClearProjectiles();
	void ClearProjectileOwnerForEnemy(Enemy* pEnemy);
	void ClearProjectileOwnerForNPC(NPC* pNPC);

	// Creating
	Projectile* CreateProjectile(vec3 position, vec3 velocity, float rotation, const char* objectFilename, float scale);

	// Get projectile
	Projectile* GetProjectile(int index);

	// Get number of projectiles
	int GetNumProjectiles();
	int GetNumRenderProjectiles();

	// Rendering helpers
	void CalculateWorldTransformMatrix();

	// Updating
	void Update(float dt);
	void UpdateProjectileLights(float dt);
	void UpdateProjectileParticleEffects(float dt);

	// Rendering
	void Render();
	void RenderWeaponTrails();
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
	LightingManager* m_pLightingManager;
	GameWindow* m_pGameWindow;
	BlockParticleManager* m_pBlockParticleManager;
	Player* m_pPlayer;
	QubicleBinaryManager* m_pQubicleBinaryManager;

	int m_numRenderProjectiles;

	// Enemy lists
	tthread::mutex m_projectileMutex;
	ProjectileList m_vpProjectileList;
	tthread::mutex m_projectileCreateMutex;
	ProjectileList m_vpProjectileCreateList;
};
