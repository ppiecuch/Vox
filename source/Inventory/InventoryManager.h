// ******************************************************************************
// Filename:    InventoryManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   The inventory manager is linked to the player and holds the information
//   about what items the player has inside their inventory and also what
//   items the player has equipped. The internal state of the inventory and
//   equipped items gets changed when the player modifies the InventoryGUI
//   and characterGUI.
//
// Revision History:
//   Initial Revision - 30/07/12
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include <vector>
#include <string>
using namespace std;

#include "../Items/StatAttribute.h"
#include "../Items/ItemsEnum.h"
#include "../Items/EquipmentEnum.h"
#include "../Player/PlayerClass.h"

class Player;
class InventoryGUI;
class LootGUI;
class ActionBar;

typedef vector<StatAttribute*> StatAttributeList;

// Item types
enum InventoryType
{
	InventoryType_Nothing = 0,

	InventoryType_Item,
	InventoryType_Scenery,
	InventoryType_Block,

	InventoryType_Clothing,

	InventoryType_Weapon_Sword,
	InventoryType_Weapon_Axe,
	InventoryType_Weapon_Hammer,
	InventoryType_Weapon_Mace,
	InventoryType_Weapon_Dagger,
	InventoryType_Weapon_Sickle,
	InventoryType_Weapon_2HandedSword,
	InventoryType_Weapon_Shield,
	InventoryType_Weapon_Boomerang,
	InventoryType_Weapon_Bomb,
	InventoryType_Weapon_Bow,
	InventoryType_Weapon_Staff,
	InventoryType_Weapon_Wand,
	InventoryType_Weapon_Pickaxe,
	InventoryType_Weapon_Torch,
	InventoryType_Weapon_SpellHands,

	InventoryType_Consumable,
};

// Equipment slots
enum EquipSlot
{
	EquipSlot_NoSlot = 0,

	EquipSlot_LeftHand,
	EquipSlot_RightHand,

	EquipSlot_Head,
	EquipSlot_Shoulders,
	EquipSlot_Body,
	EquipSlot_Legs,
	EquipSlot_Hand,
	EquipSlot_Feet,
	EquipSlot_Accessory1,
	EquipSlot_Accessory2,

	EquipSlot_NumSlots,
};

// Quality
enum ItemQuality
{
	ItemQuality_Common = 0,
	ItemQuality_Uncommon,
	ItemQuality_Magical,
	ItemQuality_Rare,
	ItemQuality_Epic,
};

// Status effects
enum ItemStatus
{
	ItemStatus_None = 0,
	ItemStatus_Fire,
	ItemStatus_Ice,
	ItemStatus_Poison,
	ItemStatus_Exploding,
};

struct ItemTextData
{
	eItem m_item;
	string m_filename;
	string m_title;
	string m_description;
};


class InventoryItem
{
public:
	InventoryItem() { }
	~InventoryItem() 
	{
		ClearAttributes();
	}

	void ClearAttributes()
	{
		for(unsigned int i = 0; i < m_vpStatAttributes.size(); i++)
		{
			delete m_vpStatAttributes[i];
			m_vpStatAttributes[i] = 0;
		}
		m_vpStatAttributes.clear();
	}

	void AddStatAttribute(AttributeType type, int amount)
	{
		StatAttribute *pAttribute = new StatAttribute(type, amount);

		m_vpStatAttributes.push_back(pAttribute);
	}

	string GetStatsAttributeString()
	{
		string returnString = "";

		if(m_vpStatAttributes.size() > 0)
		{
			returnString += "\n";
		}

		for(unsigned int i = 0; i < m_vpStatAttributes.size(); i++)
		{
			string statAttribute = m_vpStatAttributes[i]->GetString();

			returnString += statAttribute;

			if(i < m_vpStatAttributes.size()-1)
			{
				returnString += "\n";
			}
		}

		return returnString;
	}

	// Filename
    string m_filename;

	// Icon filename for GUI
    string m_Iconfilename;

	// Title
    string m_title;

	// Description
    string m_description;

	// Item type
    InventoryType m_itemType;

	// Item
    eItem m_item;

	// Status effects
	ItemStatus m_status;

	// Equip slot
	EquipSlot m_equipSlot;

	// Quality
	ItemQuality m_itemQuality;
	
	// Display left or right sprites
	bool m_left;
	bool m_right;

	// Placement block colour
	float m_placementR;
	float m_placementG;
	float m_placementB;

	// Loot GUI placement
	int m_lootSlotX;
	int m_lootSlotY;

	// Is the item equipped or not
	bool m_equipped;

	// Scale and offset
	float m_scale;
	float m_offsetX;
	float m_offsetY;
	float m_offsetZ;

	// Quantity
    int m_quantity;

	// Stat modifiers
	StatAttributeList m_vpStatAttributes;

	// Erase flag
    bool m_remove;
};


typedef vector<InventoryItem*> InventoryItemList;


class InventoryManager
{
public:
	/* Public methods */
	InventoryManager();
	~InventoryManager();

	// Linkage
	void SetPlayer(Player* pPlayer);
	void SetInventoryGUI(InventoryGUI* pInventoryGUI);
	void SetLootGUI(LootGUI* pLootGUI);
	void SetActionBar(ActionBar* pActionBar);

	void Reset();

	void ClearInventory();
	void ClearEquipped();
	void ClearOtherCreatedItems();
	void LoadInventory(string playerName, PlayerClass ePlayerClass, bool exportInventoryFile);
	void LoadDefaultInventory();
	void LoadInventoryForClass(PlayerClass ePlayerClass);

	void SetInventoryGUINeedsUpdate(bool update);
	bool InventoryGUINeedsUpdate();

	void SetCharacterGUINeedsUpdate(bool update);
	bool CharacterGUINeedsUpdate();

	// Supress export
	void SetSupressExport(bool supress);

	// Import / Export inventory
	void ExportInventory(string playerName);
	void ImportInventory(string playerName);

	bool IsInventoryFull();

	ItemTextData* GetItemTextData(eItem item);
	bool CanDestroyItemWithHammer(eItem item);

	bool CanAddInventoryItem(const char* title, eItem item, int quantity);

	InventoryItem* CreateInventoryItem(InventoryItem* pItem);
	InventoryItem* CreateInventoryItem(const char* filename, const char* iconFilename, InventoryType itemType, eItem item, ItemStatus status, EquipSlot equipSlot, ItemQuality itemQuality, bool left, bool right, const char* title, const char* description, float r, float g, float b, int quantity, int lootSlotX, int lootSlotY, int setInventorySlotX, int setInventorySlotY);
	InventoryItem* CreateInventoryItemForCrafting(eItem item, int quantity, ItemQuality itemQuality);
	InventoryItem* CreateEquipmentItemFromType(eEquipment equipment);

	InventoryItem* AddInventoryItem(const char* filename, const char* iconFilename, InventoryType itemType, eItem item, ItemStatus status, EquipSlot equipSlot, ItemQuality itemQuality, bool left, bool right, const char* title, const char* description, float r, float g, float b, int quantity, int lootSlotX, int lootSlotY, int setInventorySlotX, int setInventorySlotY);
	InventoryItem* AddInventoryItem(InventoryItem* pInventoryItem, int inventoryX, int inventoryY);
	
	void RemoveInventoryItem(const char* title, eItem item, int quantity);
	void RemoveInventoryItem(EquipSlot equipSlot);
	void RemoveInventoryItem(int slotIndex);
	void RemoveInventoryItem(int xPos, int yPos);

	InventoryItem* GetInventoryItemForSlot(int slotIndex);
	InventoryItem* GetInventoryItemForSlot(int xPos, int yPos);
	InventoryItem* GetInventoryItemWithTitle(string title);

	void SwitchInventoryItems(int slot1, int slot2);
    void SwitchInventoryItems(int x1, int y1, int x2, int y2);

	void SwitchEquippedSlots(EquipSlot equipSlotSrc, EquipSlot equipSlotDst);

	void EquipInventoryItem(int slotIndex, EquipSlot equipSlot);
	void EquipInventoryItem(int xPos, int yPos, EquipSlot equipSlot);

	void EquipLootItem(int xPos, int yPos, InventoryItem* pInventoryItem, EquipSlot equipSlot);

	void UnequipItem(int xPos, int yPos, EquipSlot equipSlot);
	void UnequipItemToLootGUI(EquipSlot equipSlot);
	bool UnequipItemToFreeInventorySlot(EquipSlot equipSlot, int *newSlotX, int *newSlotY);

	InventoryItem* GetInventoryItemForEquipSlot(EquipSlot equipSlot);

	bool IsEquippedStatus(ItemStatus status);

	// Coins
    	int GetNumCoins();
    	void GiveCoins(int numCoins);
    	void TakeCoins(int numCoins);
	bool CoinsUpdated();
	void SetCoinsUpdated(bool set);

	void Update(float dt);

protected:
	/* Protected methods */
	int ConvertSlotsToIndex(int x, int y);

private:
	/* Private methods */

public:
	/* Public members */
	static const int MAX_NUM_SLOTS_HORIZONTAL = 6;
	static const int MAX_NUM_SLOTS_VERTICAL = 3;
	static const int MAX_NUM_INVENTORY_SLOTS = MAX_NUM_SLOTS_HORIZONTAL * MAX_NUM_SLOTS_VERTICAL;

protected:
	/* Protected members */

private:
	/* Private members */
	bool m_InventoryGUINeedsUpdate;
	bool m_CharacterGUINeedsUpdate;

	// Player name
	string m_playerName;

	// List of inventory items in the GUI and equipped
	InventoryItemList m_vpInventoryItemList;

	// Slot mapping for inventory
    InventoryItem* m_ItemSlotMapping[MAX_NUM_INVENTORY_SLOTS];

	// SLot mapping for equipped items
	InventoryItem* m_equippedSlots[EquipSlot_NumSlots];

	// List for deletion purposes, since inventory items get created for random loot and crafting and are stored in this manager.
	InventoryItemList m_vpOtherInventoryItemList;

	// Coins
    int m_numCoins;
	bool m_coinsUpdated;

	// Force to stop export inventory file
	bool m_supressExport;

	Player* m_pPlayer;
	InventoryGUI* m_pInventoryGUI;
	LootGUI* m_pLootGUI;
	ActionBar* m_pActionBar;
};
