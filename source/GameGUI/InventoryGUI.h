// ******************************************************************************
// Filename:    InventoryGUI.h
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

#include "../blocks/ChunkManager.h"
#include "../Player/Player.h"
#include "../Inventory/InventoryManager.h"
#include "../gui/draggablerenderrectangle.h"
#include "../gui/formattedlabel.h"
#include "../gui/guiwindow.h"
#include "../gui/openglgui.h"

class FrontendManager;
class InventoryGUI;
class CharacterGUI;
class LootGUI;
class ActionBar;
class LootSlotItem;
class ItemManager;

class InventorySlotItem
{
public:
	InventoryGUI* m_pInventoryGUI;
	InventoryItem* m_pInventoryItem;
	DraggableRenderRectangle* m_pInventoryIcon;	

	int m_slotX;
	int m_slotY;

	bool m_dropshadowAdded;
	bool m_erase;
};

class InventoryGUI
{
public:
	/* Public methods */
	InventoryGUI(Renderer* pRenderer, OpenGLGUI* pGUI, FrontendManager* pFrontendManager, ChunkManager* pChunkManager, Player* pPlayer, InventoryManager* pInventoryManager, int windowWidth, int windowHeight);
	~InventoryGUI();

	void SetCharacterGUI(CharacterGUI* pCharacterGUI);
	void SetLootGUI(LootGUI* pLootGUI);
	void SetActionBar(ActionBar* pActionBar);
	void SetItemManager(ItemManager *pItemManager);

	// Skinning the GUI
	void SkinGUI();
	void UnSkinGUI();

	// Loading
	void Load(bool loadDelay = false, float loadDelayTime = 0.0f);
	void Unload();
	bool IsLoadDelayed();
	bool IsLoaded();

	void SetWindowDimensions(int windowWidth, int windowHeight);

	void GetInventoryDimensions(int indexX, int indexY, int* x, int* y, int* width, int *height);
	void GetDestroySlotDimensions(int* x, int* y, int* width, int* height);
	void GetDropSlotDimensions(int* x, int* y, int* width, int* height);

	GUIWindow* GetInventoryWindow();

	void CreateInventoryItems();
	void DeleteInventoryItems();

	void UpdateActionBar();

	// Tooltips
	void UpdateToolTipAppear(float dt);
	void ShowTooltip(InventorySlotItem* pInventoryItem);
	void HideTooltip();

	// Popup
	void OpenPopup(string popupTitle, string popupText);
	void ClosePopup();

	InventorySlotItem* GetInventorySlotItem(int x, int y);
	InventorySlotItem* GetInventorySlotItemEquipped(EquipSlot equipSlot);

	void SetEquippedItem(EquipSlot equipSlot, string title);

	void EquipItem(InventoryItem* pInventoryItem, int inventoryX, int inventoryY);
	void EquipItem(LootSlotItem* pLootItem);
	void EquipItem(InventorySlotItem* pInventoryItem);
	void UnequipItem(EquipSlot equipSlot, bool left, bool right);

	void Update(float dt);

protected:
	/* Protected methods */
	static void _InventoryItemPressed(void *apData);
	void InventoryItemPressed(InventorySlotItem* pInventoryItem);

	static void _InventoryItemReleased(void *apData);
	void InventoryItemReleased(InventorySlotItem* pInventoryItem);

	static void _InventoryItemEntered(void *apData);
	void InventoryItemEntered(InventorySlotItem* pInventoryItem);

	static void _InventoryItemExited(void *apData);
	void InventoryItemExited(InventorySlotItem* pInventoryItem);

	static void _CloseExitPressed(void *pData);
	void CloseExitPressed();

	static void _PopupConfirmPressed(void *apData);
	void PopupConfirmPressed();

	static void _PopupCancelPressed(void *apData);
	void PopupCancelPressed();

private:
	/* Private methods */

public:
	/* Public members */
	static const int MAX_NUM_SLOTS_HORIZONTAL = 6;
	static const int MAX_NUM_SLOTS_VERTICAL = 3;

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;
	OpenGLGUI* m_pGUI;
	FrontendManager* m_pFrontendManager;
	ChunkManager* m_pChunkManager;
	Player* m_pPlayer;
	InventoryManager* m_pInventoryManager;
	CharacterGUI* m_pCharacterGUI;
	LootGUI* m_pLootGUI;
	ActionBar* m_pActionBar;
	ItemManager* m_pItemManager;

	bool m_loaded;

	int m_windowWidth;
	int m_windowHeight;

	int m_inventoryWindowWidth;
	int m_inventoryWindowHeight;
	int m_titlebarWidth;
	int m_titlebarHeight;

	// Load delay
	bool m_loadDelay;
	float m_loadDelayTime;

	// GUI components
	GUIWindow* m_pInventoryWindow;
	Icon* m_pTitleBarIcon;
	Icon* m_pTitleBarBackgroundIcon;
	Icon* m_pInventoryWindowBackgroundIcon;
	Button* m_pCloseExitButton;
	Icon* m_pDestroyIcon;
	Label* m_pDestroyLabel;
	Icon* m_pDropIcon;
	Label* m_pDropLabel;

	Icon* m_pInventoryBackgroundSlotBorder_Common;
	Icon* m_pInventoryBackgroundSlotBorder_Uncommon;
	Icon* m_pInventoryBackgroundSlotBorder_Magical;
	Icon* m_pInventoryBackgroundSlotBorder_Rare;
	Icon* m_pInventoryBackgroundSlotBorder_Epic;

	// Pressed icons
	std::vector<InventorySlotItem*> m_vpInventorySlotItems;
	string m_pEquippedItems[EquipSlot_NumSlots];

	int m_pressedX;
	int m_pressedY;
	InventorySlotItem* m_pPressedInventoryItem;

	InventorySlotItem* m_pInventoryItemToDelete;

	// Tooltip
	Icon* m_pTooltipBackground_Common;
	Icon* m_pTooltipBackground_Uncommon;
	Icon* m_pTooltipBackground_Magical;
	Icon* m_pTooltipBackground_Rare;
	Icon* m_pTooltipBackground_Epic;
	Label* m_pTooltipNameLabel;
	FormattedLabel* m_pTooltipDescriptionLabel;
	Label* m_pTooltipSlotLabel;
	Label* m_pTooltipQualityLabel;
	bool m_toolTipVisible;
	int m_tooltipWidth;
	int m_tooltipHeight;
	int m_tooltipDescBorder;
	ItemQuality m_tooltipQuality;
	float m_tooltipAppearDelayTimer;
	bool m_toolTipComponentsAdded;

	// Popup
	int m_popupWidth;
	int m_popupHeight;
	int m_popupBorderSpacer;
	int m_popupTitleSpacer;
	int m_popupIconSize;
	int m_popupIconSpacer;
	Label* m_popupTitle;
	FormattedLabel* m_popupText;
	Button* m_pPopupConfirmButton;
	Button* m_pPopupCancelButton;
	Icon* m_pPopupBackgroundIcon;
};
