// ******************************************************************************
// Filename:    NPCManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   Manager class to control all of the NPC creation, updating, rendering and
//   general management of NPC characters.
//
// Revision History:
//   Initial Revision - 27/09/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "NPC.h"

typedef std::vector<NPC*> NPCList;

class BlockParticleManager;
class TextEffectsManager;
class ItemManager;
class ProjectileManager;
class EnemyManager;

class NPCManager
{
public:
	/* Public methods */
	NPCManager(Renderer* pRenderer, ChunkManager* pChunkManager);
	~NPCManager();

	void SetPlayer(Player* pPlayer);
	void SetLightingManager(LightingManager* pLightingManager);
	void SetBlockParticleManager(BlockParticleManager* pBlockParticleManager);
	void SetTextEffectsManager(TextEffectsManager* pTextEffectsManager);
	void SetItemManager(ItemManager* pItemManager);
	void SetProjectileManager(ProjectileManager* pProjectileManager);
	void SetEnemyManager(EnemyManager* pEnemyManager);
	void SetQubicleBinaryManager(QubicleBinaryManager* pQubicleBinaryManager);

	// Clearing
	void ClearNPCs();
	void ClearNPCChunkCacheForChunk(Chunk* pChunk);

	// Creation
	NPC* CreateNPC(const char* name, string typeName, string modelName, vec3 position, float scale, bool characterSelectScreen, bool useQubicleManager);
	void DeleteNPC(string name);

	// Get NPCs
	NPC* GetNPC(int index);
	NPC* GetNPCByName(string name);
	int GetNumNPCs();
	int GetNumRenderNPCs();
	void ResetNumRenderNPCs();

	// Enemy Died
	void SetEnemyDied(Enemy* pEnemy);

	// Collision
	void PushCollisions(NPC* pPushingNPC, vec3 position, float radius);

	// Interaction
	NPC* CheckNPCPlayerInteraction();

	// Rendering Helpers
	void SetWireFrameRender(bool wireframe);

	// Updating
	void UpdateNamePickingSelection(int pickingId);
	void UpdateHoverNamePickingSelection(int pickingId);
	void UpdateWeaponLights(float dt);
	void UpdateWeaponParticleEffects(float dt);
	void Update(float dt);
	void UpdateScreenCoordinates2d(Camera* pCamera);
	void UpdateHoverNPCs();
	void UpdateNPCProjectileCheck(float dt);
	void CalculateWorldTransformMatrix();

	// Rendering
	void Render(bool outline, bool reflection, bool silhouette, bool renderOnlyOutline, bool renderOnlyNormal, bool shadow);
	void RenderFaces();
	void RenderWeaponTrails();
	void RenderNamePicking();
	void RenderOutlineNPCs();
	void RenderSubSelectionNPCs();
	void RenderSubSelectionNormalNPCs();
	void RenderSubSelectionOverlayNPCs();
	void RenderDebug();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	static float NPC_INTERACTION_DISTANCE;
	static float NPC_INERACCTION_RADIUS_CHECK;

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
	QubicleBinaryManager* m_pQubicleBinaryManager;
	EnemyManager* m_pEnemyManager;

	int m_numRenderNPCs;

	// NPC List
	tthread::mutex m_NPCMutex;
	NPCList m_vpNPCList;
};
