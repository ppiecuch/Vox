// ******************************************************************************
// Filename:    ItemsEnum.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   An enum list of all of the items in the game, used for item tracking
//   and item specific functionality.
//
// Revision History:
//   Initial Revision - 12/04/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

enum eItem
{
	eItem_None = 0,

	// Dropped item in the world
	eItem_DroppedItem,

	// Herts and coins dropped from killing enemies
	eItem_Coin,
	eItem_Heart,

	// Zombie gib
	eItem_Gib,

	// Interactable items
	eItem_Tombstone,
	eItem_Chest,
	eItem_Torch,
	eItem_Furnace,
	eItem_Anvil,
	eItem_QuestBoard,
	eItem_CampFire,
	eItem_Mannequin,
	
	// Ingredients
	eItem_SlimeJelly,
	eItem_BeeWing,
	eItem_Bone,

	// Ore and mining
	eItem_CopperVein,
	eItem_CopperOre,
	eItem_CopperBar,
	eItem_IronVein,
	eItem_IronOre,
	eItem_IronBar,
	eItem_SilverVein,
	eItem_SilverOre,
	eItem_SilverBar,
	eItem_GoldVein,
	eItem_GoldOre,
	eItem_GoldBar,

	// World blocks
	eItem_Block_Grass,
	eItem_Block_Dirt,
	eItem_Block_Stone,
	eItem_Block_Wood,
	eItem_Block_Leaf,
	eItem_Block_Sand,
	eItem_Block_Cactus,
	eItem_Block_Rock,
	eItem_Block_Snow,

	eItem_NUM_ITEMS,
};