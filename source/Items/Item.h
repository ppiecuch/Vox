// ******************************************************************************
// Filename:    Item.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   An item object contains all the data and functionality associated with
//   the items that are used in the game, this includes items that are stored
//   and equipped by the player, as well as items that are dropped in the world.
//   Items are interactable by the players and also have physics and collisions.
//
// Revision History:
//   Initial Revision - 12/04/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "../blocks/ChunkManager.h"
#include "../models/VoxelWeapon.h"
#include "../Particles/BlockParticleManager.h"
#include "../Inventory/InventoryManager.h"
#include "../Maths/BoundingRegion.h"
#include "ItemsEnum.h"
#include "EquipmentEnum.h"

class LightingManager;
class ItemManager;
class ItemSpawner;

// Item helper functionality
string GetItemTitleForType(eItem type);
string GetItemDescriptionForType(eItem type);
float GetItemRadiusForType(eItem type);
string GetItemFilenameForType(eItem type);
string GetItemTextureForType(eItem type);

// Equipment helper functionality
string GetEquipmentTitleForType(eEquipment type);
string GetEquipmentDescriptionForType(eEquipment type);
string GetEquipmentFilenameForType(eEquipment type);
string GetEquipmentTextureForType(eEquipment type);
InventoryType GetInventoryTypeForEquipment(eEquipment type);
EquipSlot GetEquipSlotForEquipment(eEquipment type);
ItemQuality GetItemQualityForEquipment(eEquipment type);
void GetItemSidesForEquipment(eEquipment type, bool *left, bool *right);
void AddStatsModifiersForType(eEquipment type, InventoryItem* pItem);


class Item
{
public:
	/* Public methods */
	Item(Renderer* pRenderer, ChunkManager* pChunkManager, QubicleBinaryManager* pQubicleBinaryManager, string itemTitle, eItem itemType, float scale);
	~Item();

	// Unloading
	void UnloadEffectsAndLights();

	void SetLightingManager(LightingManager* pLightingManager);
	void SetBlockParticleManager(BlockParticleManager* pBlockParticleManager);
	void SetPlayer(Player* pPlayer);
	void SetItemManager(ItemManager* pItemManager);
	void SetInventoryManager(InventoryManager* pInventoryManager);

	void SetErase(bool erase);
	bool NeedsErasing();

	string GetFileName();

	void SetChunk(Chunk* pChunk);
	Chunk* GetChunk();

	VoxelWeapon* GetVoxelItem();

	// Setup
	void LoadItem(const char* objectFilename);

	// Item spawner
	void SetItemSpawner(ItemSpawner* pSpawner);
	void RemoveItemSpawner(ItemSpawner* pSpawner);

	// Accessors / Setters
	void SetPosition(vec3 pos);
	vec3 GetPosition();
	void SetVelocity(vec3 vel);
	vec3 GetVelocity();
	void SetRotation(vec3 rot);
	vec3 GetRotation();
	void SetAngularVelocity(vec3 angvel);
	vec3 GetAngularVelocity();
	void SetGravityDirection(vec3 dir);
	vec3 GetGravityDirection();
	float GetScale();
	float GetRadius();
	vec3 GetCenter();

	// Inventory item params
	void SetDroppedItem(const char* filename, const char* iconFilename, InventoryType itemType, eItem item, ItemStatus status, EquipSlot equipSlot, ItemQuality itemQuality, bool left, bool right, const char* title, const char* description, float r, float g, float b, int quantity);
	void SetDroppedItem(InventoryItem* pItem);
	InventoryItem* GetDroppedInventoryItem();

	// Collectible
	bool IsCollectible();
	void SetIsCollectible(bool collect);
	void SetCollectionDelay(float delay);
	bool IsItemPickedUp();
	void SetPickupGotoPosition(vec3 pickupPos);

	// Auto disappear
	void SetAutoDisappear(float disappearTime);

	// Animation
	bool IsStillAnimating();

	// Rendering helpers
	void SetOutlineRender(bool outline);
	bool IsOutlineRender();
	void SetWireFrameRender(bool wireframe);
	void CalculateWorldTransformMatrix();

	// Loot items
	int GetNumLootItems();
	InventoryItem* GetLootItem(int index);
	InventoryItem* AddLootItem(InventoryItem* pItem, int slotX, int slotY);
	InventoryItem* AddLootItem(const char* filename, const char* iconFilename, InventoryType itemType, eItem item, ItemStatus status, EquipSlot equipSlot, ItemQuality itemQuality, const char* title, const char* description, bool left, bool right, float r, float g, float b, int quantity, int slotX, int slotY);
	void RemoveLootItem(InventoryItem* pInventoryItem);
	void ClearLootItems();
	InventoryItemList GetLootItemList();

	// Item type
	eItem GetItemType();

	// Item title
	const char* GetItemTitle();

	// Should we create dying lights when we unload
	void SetCreateDyingLights(bool dyingLights);

	// Grid
	void UpdateGridPosition();
	Chunk* GetCachedGridChunkOrFromPosition(vec3 pos);

	// Interaction position
	void SetInteractionPositionOffset(vec3 offset);
	vec3 GetInteractionPosition();

	// World collision
	void SetWorldCollide(bool collide);
	bool CheckCollisions(vec3 positionCheck, vec3 previousPosition, vec3 *pNormal, vec3 *pMovement);

	// Bounding collision region
	void CreateBoundingRegion(vec3 origin, BoundingRegionType boundingType, float radius, float xWidth, float yWidth, float zWidth, float scale);
	void UpdateBoundingRegion(int index, vec3 origin, BoundingRegionType boundingType, float radius, float xWidth, float yWidth, float zWidth, float scale);
	void AddBoundingRegion(vec3 origin, BoundingRegionType boundingType, float radius, float xWidth, float yWidth, float zWidth, float scale);
	BoundingRegionList GetBoundingRegionList();
	bool IsColliding(vec3 center, vec3 previousCenter, float radius, vec3 *pNormal, vec3 *pMovement);
	void SetCollisionEnabled(bool set);
	bool IsCollisionEnabled();
	void UpdateCollisionRadius();
	float GetCollisionRadius();

	// Explode
	void Explode();

	// Interaction
	void SetInteractable(bool interactable);
	bool IsInteractable();
	bool IsInteracting();
	void Interact();
	void SpawnSubItems();
	void SetCurrentInteractCount(int currentInteract);
	int GetCurrentInteractCount();
	void SetMaxtInteractCount(int maxInteract);
	int GetMaxInteractCount();

	// Update
	void Update(float dt);
	void UpdatePhysics(float dt);
	void UpdateTimers(float dt);
	void UpdatePlayerMagnet(float dt);
	void UpdateItemLights(float dt);
	void UpdateItemParticleEffects(float dt);

	// Rendering
	void Render(bool outline, bool reflection, bool silhouette);
	void RenderDebug();
	void RenderCollisionRegions();

protected:
	/* Protected methods */
	static void _PickupAnimationFinished(void *apData);
	void PickupAnimationFinished();

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
	BlockParticleManager* m_pBlockParticleManager;
	Player* m_pPlayer;
	ItemManager* m_pItemManager;
	QubicleBinaryManager* m_pQubicleBinaryManager;
	InventoryManager* m_pInventoryManager;

	// Erase flag
	bool m_erase;

	// Item title
	string m_itemTitle;

	// Filename
	string m_fileName;

	// Forward vector
	vec3 m_forward;

	// Position
	vec3 m_position;

	// Previous position
	vec3 m_previousPosition;

	// Velocity
	vec3 m_velocity;

	// Rotation
	vec3 m_rotation;

	// Angular velocity
	vec3 m_angularVelocity;

	// Gravity
	vec3 m_gravityDirection;

	// Item world matrix
	Matrix4x4 m_worldMatrix;

	// The item's qubicle class
	VoxelWeapon* m_pVoxelItem;

	// The items that are stored in this item if it is a chest
	InventoryItemList m_vpInventoryItemList;

	// For when an item is pickup up from the floor, this contains the params to make it into an inventory item
	InventoryItem* m_droppedInventoryItem;

	// Item type
	eItem m_itemType;

	// 	Scale
	float m_renderScale;

	// Are we rendering outline for this item
	bool m_outlineRender;

	// Radius
	float m_radius;

	// Should we collide with the world
	bool m_worldCollide;

	// Interaction position
	vec3 m_interactionPositionOffset;

	// Pickup animation variables
	bool m_itemPickup;
	vec3 m_pickupPos;

	// Disappear animation, used when we pickup items
	bool m_disappear;
	float m_disappearDelay;
	float m_disappearTimer;
	bool m_disappearAnimationStarted;
	float m_disappearScale;

	// Auto dissapear;
	bool m_autoDisappear;
	float m_autoDisappearTimer;

	// Is this item collectible by the player
	bool m_isCollectible;

	// The time delay before this item is collectible by the player
	float m_collectionDelay;

	// Are we able to be interactable?
	bool m_interactable;

	// Are we currently interacting with this item
	bool m_itemInteracting;

	// Interact counting... i.e. mining takes more than one hit to destroy.
	int m_interactCount;
	int m_maxInteractCount;

	// Should we create dying lights when we unload the item?
	bool m_bCreateDyingLights;

	// Were we created from an item spawner
	ItemSpawner* m_pParentItemSpawner;

	// Grid position
	int m_gridPositionX;
	int m_gridPositionY;
	int m_gridPositionZ;

	// Cached grid chunk
	Chunk* m_pCachedGridChunk;

	// Owning chunk
	Chunk* m_pOwningChunk;

	// Bounding region list
	BoundingRegionList m_vpBoundingRegionList;
	bool m_collisionEnabled;
	float m_collisionRadius;
};
