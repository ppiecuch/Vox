// ******************************************************************************
// Filename:    Enemy.h
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


#include "../models/modelloader.h"

#include "../blocks/ChunkManager.h"
#include "../Particles/BlockParticleManager.h"
#include "../Projectile/ProjectileManager.h"

class LightingManager;
class EnemyManager;
class BlockParticleManager;
class TextEffectsManager;
class ItemManager;
class NPCManager;
class NPC;
class EnemySpawner;
class HUD;

enum eEnemyType
{
	eEnemyType_None = 0,

	eEnemyType_GreenSlime,
	eEnemyType_RedSlime,
	eEnemyType_BlueSlime,
	eEnemyType_YellowSlime,

	eEnemyType_NormalSkeleton,
	eEnemyType_RangedSkeleton,
	eEnemyType_MeleeSkeleton,
	eEnemyType_MageSkeleton,

	eEnemyType_IronGiant,

	eEnemyType_Mummy,
	eEnemyType_WalkingZombie,
	eEnemyType_CrawlingZombie,

	eEnemyType_Bee,
	eEnemyType_Bat,
	eEnemyType_Ghost,
	eEnemyType_Doppelganger,

	eEnemyType_TargetDummy,

	eEnemyType_Mimic,

	eEnemyType_SnowGolem,
	eEnemyType_MagmaGolem,
};

class Enemy
{
public:
	/* Public methods */
	Enemy(Renderer* pRenderer, ChunkManager* pChunkManager, Player* pPlayer, LightingManager* pLightingManager, BlockParticleManager* pBlockParticleManager, TextEffectsManager* pTextEffectsManager, ItemManager* pItemManager, ProjectileManager* pProjectileManager, HUD* pHUD, EnemyManager* pEnemyManager, NPCManager* pNPCManager, QubicleBinaryManager* pQubicleBinaryManager, eEnemyType enemyType);
	~Enemy();

	// Erase flag
	bool GetErase();
	void SetErase(bool erase);

	// Accessors / Setters
	void SetPosition(vec3 pos);
	vec3 GetPosition();
	void SetVelocity(vec3 vel);
	vec3 GetVelocity();
	void SetRotation(float rot);
	float GetRotation();
	float GetFaceLookingRotation();
	void SetScale(float scale);
	float GetRadius();
	void UpdateRadius();
	vec3 GetCenter();
	vec3 GetAboveHeadPosition();
	vec3 GetForwardVector();
	vec3 GetRightVector();
	vec3 GetUpVector();
	vec3 GetTargetForward();

	// Setup
	void SetupEnemyForType();
	void SetupWeaponsForType();
	void InitEnemyForType();
	void LoadWeapon(bool left, string weaponFile);
	void UnloadWeapon(bool left);

	// Enemy spawner
	void SetEnemySpawner(EnemySpawner* pSpawner);
	void RemoveEnemySpawner(EnemySpawner* pSpawner);

	// Animation
	void SetAnimationSpeed(float speed, bool onlySetOnCompleteAnimation, AnimationSections section);
	float GetAnimationSpeed(AnimationSections section);
	bool AnimationFinished(AnimationSections section);

	// Looking
	void SetTargetForwardToLookAtPoint(vec3 point);
	void LookAtPoint(vec3 point);
	void LookAtRandomDirection();
	void SetRandomLookMode();
	void SetBodyTurnStopThreshold(float threshold);
	void SetBodyTurnSpeedMultiplier(float multiplier);

	// World
	void UpdateGridPosition();
	Chunk* GetCachedGridChunkOrFromPosition(vec3 pos);
	void ClearChunkCacheForChunk(Chunk* pChunk);

	// Collision
	bool CheckCollisions(vec3 positionCheck, vec3 previousPosition, vec3 *pNormal, vec3 *pMovement);
	bool IsBlockInFront();

	// Movement
	void MoveAbsolute(vec3 direction, const float speed, bool shouldChangeForward = true);
	void StopMoving();
	void Jump(bool jumpUpBlock);
	bool CanJump();
	bool IsMoving();
	float GetMovementSpeed();
	bool CanMoveTowardsTarget();

	// Combat
	void DoDamage(float amount, Colour textColour, vec3 knockbackDirection, float knockbackAmount, bool createParticleHit, bool shouldUpdateGUI);
	void CheckPlayerDamageRadius();
	void CheckNPCDamageRadius();
	void CheckProjectileDamageRadius(Projectile* pProjectile);
	void Explode();
	void ConvertIntoOtherEnemyType(eEnemyType newEnemyType, float scale);
	void Respawn();
	bool CanCheckAggroRange();

	void SetNPCDied(NPC* pNPC);
	void SetTargetNPC(NPC* pTargetNPC);

	// Gameplay
	void SetSapped(bool sapped);
	bool IsSapped();

	// Spawning
	void SetSpawningParams(vec3 start, vec3 end, float time);

	// Wander / Random target
	void SetRandomTargetMode(bool randomTargetMode);
	void GetNewRandomTargetPosition();
	void ResetRandomTargetPosition();
	void SetLeashParameters(vec3 leashPosition, float leashRadius);

	// Attacking
	void Attack();
	void ReleaseAttack();
	bool CanAttack();
	bool GetAttackEnabled();
	float GetAttackRadius();
	float GetAttackRotation();
	float GetAttackSegmentAngle();

	// Projectile hitbox
	eProjectileHitboxType GetProjectileHitboxType();
	float GetProjectileHitboxRadius();
	float GetProjectileHitboxXLength();
	float GetProjectileHitboxYLength();
	float GetProjectileHitboxZLength();
	vec3 GetProjectileHitboxCenter();

	// Spawn loot items
	void SpawnLootItems();
	void SpawnGibs();

	// Rendering Helpers
	void CalculateWorldTransformMatrix();
	void SetOutlineRender(bool outline);
	bool GetOutlineRender();
	void SetWireFrameRender(bool wireframe);

	// Updating
	void UpdateWeaponLights(float dt);
	void UpdateWeaponParticleEffects(float dt);
	void Update(float dt);
	void UpdatePhysics(float dt);
	void UpdateLookingAndForwardTarget(float dt);
	void UpdateCombat(float dt);
	void UpdateGameplay(float dt);
	void UpdateMeleeCombat(float dt);
	void UpdateRangedCombat(float dt);
	void UpdateTouchCombat(float dt);
	void UpdateMovement(float dt);
	void UpdateSpawning(float dt);
	void UpdateTimers(float dt);

	// Rendering
	void Render(bool outline, bool reflection, bool silhouette);
	void RenderFace();
	void RenderWeaponTrails();
	void RenderDebug();
	void RenderForwardDebug();
	void RenderRandomPositionDebug();
	void RenderChargingAttackDebug();
	void RenderLookingAreaDebug();
	void RenderProjectileHitboxDebug();

protected:
	/* Protected methods */
	static void _AttackEnabledTimerFinished(void *apData);
	void AttackEnabledTimerFinished();

	static void _AttackEnabledDelayTimerFinished(void *apData);
	void AttackEnabledDelayTimerFinished();

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
	Player* m_pPlayer;
	EnemyManager* m_pEnemyManager;
	BlockParticleManager* m_pBlockParticleManager;
	TextEffectsManager* m_pTextEffectsManager;
	ItemManager* m_pItemManager;
	ProjectileManager* m_pProjectileManager;
	HUD* m_pHUD;
	QubicleBinaryManager* m_pQubicleBinaryManager;
	NPCManager* m_pNPCManager;

	// Erase flag
	bool m_erase;

	// Enemy radius
	float m_radius;

	// Enemy position and movement variables
	vec3 m_position;
	vec3 m_previousPosition;
	vec3 m_velocity;
	vec3 m_gravityDirection;

	// Forward vector
	vec3 m_forward;

	// Target forward / looking vector
	vec3 m_targetForward;

	// Scale
	float m_renderScale;

	// Animation params
	float m_animationSpeed[AnimationSections_NUMSECTIONS];
	bool m_animationSpeedonlySetOnCompleteAnimation[AnimationSections_NUMSECTIONS];
	bool m_animationFinished[AnimationSections_NUMSECTIONS];

	// Enemy name
	string m_enemyName;

	// Enemy type
	eEnemyType m_eEnemyType;
	string m_typeString;
	string m_modelNameString;
	int m_modelVariation;

	// Idle flag
	bool m_bIsIdle;
	float m_waitBeforeStopMovingAnimationTimer;
	bool m_hasSetIdleAnimation;

	// Movement params
	float m_movementSpeed;
	float m_movementFreezeTimer;

	// Jumping params
	bool m_bCanJump;
	float m_jumpTime;
	float m_jumpTimer;
	float m_jumpHeight;

	// Look at point
	bool m_bLookAtPoint;
	vec3 m_lookPoint;
	bool m_bIsLookingAtPoint;

	// Turn speed multiplier
	float m_bodyTurnSpeedMultiplier;

	// Turn stop threshold
	float m_bodyTurnStopThreshold;

	// Rendering modes
	bool m_outlineRender;

	// Enemy game properties
	float m_maxHealth;
	float m_health;

	// Damage and knockback timers
	float m_damageTime;
	float m_damageTimer;
	float m_knockbackTime;
	float m_knockbackTimer;

	// Combat
	bool m_bCanAttack;
	float m_attackDelayTime;
	float m_attackDelayTimer;
	bool m_bCanInteruptCombatAnim;
	bool m_attackEnabled;
	bool m_insideAttackRadius;
	float m_attackEnabledTimer;
	float m_attackEnabledDelayTimer;
	float m_attackSegmentAngle;
	float m_attackRadius;
	float m_attackRotation;
	float m_movementWaitAfterAttackTimer;

	// Gameplay
	bool m_sapped;
	float m_sappedTimer;
	unsigned int m_sappedParticleEffectId;
	BlockParticleEffect* m_pSappedParticleEffect;

	// Charging attacks
	bool m_bIsChargingAttack;
	float m_chargeAmount;
	float m_chargeTime;
	vec3 m_chargeSpawnVelocity;
	vec3 m_chargeSpawnPosition;

	// Projectile hitbox
	eProjectileHitboxType m_eProjectileHitboxType;
	float m_projectileHitboxRadius;
	float m_projectileHitboxXLength;
	float m_projectileHitboxYLength;
	float m_projectileHitboxZLength;
	vec3 m_projectileHitboxCenterOffset;

	// Aggro
	bool m_aggro;
	float m_aggroLookSegmentAngle;
	float m_aggroLookRadius;
	float m_aggroResetTime;
	float m_aggroResetTimer;

	// Spawning
	bool m_spawning;
	vec3 m_spawnStartPosition;
	vec3 m_spawnEndPosition;
	float m_spawnTime;
	float m_spawningTimer;
	float m_spawningT;

	// Wander / random target
	bool m_bRandomTargetPositionMode;
	float m_getRamdomTargetPositionTimer;
	vec3 m_randomTargetPosition;
	float m_leashRadius;
	vec3 m_leashPosition;

	// Stuck
	bool m_bUpdateStuckTimer;
	bool m_bStuck;
	float m_stuckTimer;

	// Enemy light
	unsigned int m_enemyLightId;

	// Enemy particle effect
	unsigned int m_enemyParticleEffectId;
	BlockParticleEffect* m_pEnemyParticleEffect;

	// Grid position
	int m_gridPositionX;
	int m_gridPositionY;
	int m_gridPositionZ;

	// Cached chunk from grid position
	Chunk* m_pCachedGridChunk;

	// Enemy's world matrix
	Matrix4x4 m_worldMatrix;

	// Target NPC
	NPC* m_pTargetNPC;

	// Were we created from an enemy spawner
	EnemySpawner* m_pParentEnemySpawner;

	// Voxel character
	VoxelCharacter* m_pVoxelCharacter;
};
