// ******************************************************************************
// Filename:    ItemUtils.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   Utility functionality for items, mostly a way to associate item enums with
//   data like the friendly names and display strings.
//
// Revision History:
//   Initial Revision - 12/04/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "Item.h"

string GetItemTitleForType(eItem type)
{
	switch(type)
	{
		case eItem_None:			{ return "None"; } break;
		// Dropped item in the world
		case eItem_DroppedItem:		{ return "Dropped Item"; } break;
		// Herts and coins dropped from killing enemies
		case eItem_Coin:			{ return "Coin"; } break;
		case eItem_Heart:			{ return "Heart"; } break;
		// Zombie gib
		case eItem_Gib:				{ return "Gib"; } break;
		// Interactable items
		case eItem_Tombstone:		{ return "Tombstone"; } break;
		case eItem_Chest:			{ return "Chest"; } break;
		case eItem_Torch:			{ return "Torch"; } break;
		case eItem_Furnace:			{ return "Furnace"; } break;
		case eItem_Anvil:			{ return "Anvil"; } break;
		case eItem_QuestBoard:		{ return "Quest Board"; } break;
		case eItem_CampFire:		{ return "Camp Fire"; } break;
		case eItem_Mannequin:		{ return "Mannequin"; } break;
		// Ingredients
		case eItem_SlimeJelly:		{ return "Slime Jelly"; } break;
		case eItem_BeeWing:			{ return "Bee Wing"; } break;
		case eItem_Bone:			{ return "Bone"; } break;
		// Ore and mining
		case eItem_CopperVein:		{ return "Copper Vein"; } break;
		case eItem_CopperOre:		{ return "Copper Ore"; } break;
		case eItem_CopperBar:		{ return "Copper Bar"; } break;
		case eItem_IronVein:		{ return "Iron Vein"; } break;
		case eItem_IronOre:			{ return "Iron Ore"; } break;
		case eItem_IronBar:			{ return "Iron Bar"; } break;
		case eItem_SilverVein:		{ return "Silver Vein"; } break;
		case eItem_SilverOre:		{ return "Silver Ore"; } break;
		case eItem_SilverBar:		{ return "Silver Bar"; } break;
		case eItem_GoldVein:		{ return "Gold Vein"; } break;
		case eItem_GoldOre:			{ return "Gold Ore"; } break;
		case eItem_GoldBar:			{ return "Gold Bar"; } break;
		// World blocks
		case eItem_Block_Grass:		{ return "Grass Block"; } break;
		case eItem_Block_Dirt:		{ return "Dirt Block"; } break;
		case eItem_Block_Stone:		{ return "Stone Block"; } break;
		case eItem_Block_Wood:		{ return "Wood Block"; } break;
		case eItem_Block_Leaf:		{ return "Leaf Block"; } break;
		case eItem_Block_Sand:		{ return "Sand Block"; } break;
		case eItem_Block_Cactus:	{ return "Cactus Block"; } break;
		case eItem_Block_Rock:		{ return "Rock Block"; } break;
		case eItem_Block_Snow:		{ return "Snow Block"; } break;
	}

	cout << "Warning: Reached end of GetItemTitleForType() without finding type - " << type << ".\n";

	return "";
}

string GetItemDescriptionForType(eItem type)
{
	switch(type)
	{
		case eItem_None:			{ return "None"; } break;
		// Dropped item in the world
		case eItem_DroppedItem:		{ return "Dropped Item"; } break;
		// Herts and coins dropped from killing enemies
		case eItem_Coin:			{ return "Coin"; } break;
		case eItem_Heart:			{ return "Heart"; } break;
		// Zombie gib
		case eItem_Gib:				{ return "Gib"; } break;
		// Interactable items
		case eItem_Tombstone:		{ return "Tombstone"; } break;
		case eItem_Chest:			{ return "Chest"; } break;
		case eItem_Torch:			{ return "Torch"; } break;
		case eItem_Furnace:			{ return "Furnace"; } break;
		case eItem_Anvil:			{ return "Anvil"; } break;
		case eItem_QuestBoard:		{ return "Quest Board"; } break;
		case eItem_CampFire:		{ return "Camp Fire"; } break;
		case eItem_Mannequin:		{ return "A wooden mannequin, used for storing armor sets."; } break;
		// Ingredients
		case eItem_SlimeJelly:		{ return "Jelly from a slime monster."; } break;
		case eItem_BeeWing:			{ return "A wing from a bee."; } break;
		case eItem_Bone:			{ return "A raw bone from a skeleton."; } break;
		// Ore and mining
		case eItem_CopperVein:		{ return "Copper Vein"; } break;
		case eItem_CopperOre:		{ return "A nugget of copper ore. Can be smelted down at a furnace to create copper bars."; } break;
		case eItem_CopperBar:		{ return "A solid bar of copper, used for crafting items made out of copper."; } break;
		case eItem_IronVein:		{ return "Iron Vein"; } break;
		case eItem_IronOre:			{ return "A nugget of iron ore. Can be smelted down at a furnace to create iron bars."; } break;
		case eItem_IronBar:			{ return "A solid bar of iron, used for crafting items made out of iron."; } break;
		case eItem_SilverVein:		{ return "Silver Vein"; } break;
		case eItem_SilverOre:		{ return "A nugget of silver ore. Can be smelted down at a furnace to create silver bars."; } break;
		case eItem_SilverBar:		{ return "A solid bar of silver, used for crafting items made out of silver."; } break;
		case eItem_GoldVein:		{ return "Gold Vein"; } break;
		case eItem_GoldOre:			{ return "A nugget of gold ore. Can be smelted down at a furnace to create gold bars."; } break;
		case eItem_GoldBar:			{ return "A solid bar of gold, used for crafting items made out of gold."; } break;
		// World blocks
		case eItem_Block_Grass:		{ return "Grass block for world building."; } break;
		case eItem_Block_Dirt:		{ return "Dirt block for world building."; } break;
		case eItem_Block_Stone:		{ return "Stone block for world building."; } break;
		case eItem_Block_Wood:		{ return "Wood block for world building."; } break;
		case eItem_Block_Leaf:		{ return "Leaf block for world building."; } break;
		case eItem_Block_Sand:		{ return "Sand block for world building."; } break;
		case eItem_Block_Cactus:	{ return "Cactus block for world building."; } break;
		case eItem_Block_Rock:		{ return "Rock block for world building."; } break;
		case eItem_Block_Snow:		{ return "Snow block for world building."; } break;
	}

	cout << "Warning: Reached end of GetItemDescriptionForType() without finding type - " << type << ".\n";

	return "";
}

string GetItemFilenameForType(eItem type)
{
	switch(type)
	{
		case eItem_None:			{ return ""; } break;
		// Dropped item in the world
		case eItem_DroppedItem:		{ return ""; } break;
		// Herts and coins dropped from killing enemies
		case eItem_Coin:			{ return "media/gamedata/items/Coin/Coin.item"; } break;
		case eItem_Heart:			{ return "media/gamedata/items/Heart/Heart.item"; } break;
		// Zombie gib
		case eItem_Gib:				{ return "media/gamedata/items/Hand1Gib.item"; } break;
		// Interactable items
		case eItem_Tombstone:		{ return "media/gamedata/items/Tombstone/Tombstone1.item"; } break;
		case eItem_Chest:			{ return "media/gamedata/items/Chest/Chest.item"; } break;
		case eItem_Torch:			{ return "media/gamedata/items/Torch/Torch.item"; } break;
		case eItem_Furnace:			{ return "media/gamedata/items/Furnace/Furnace.item"; } break;
		case eItem_Anvil:			{ return "media/gamedata/items/Anvil/Anvil.item"; } break;
		case eItem_QuestBoard:		{ return "media/gamedata/items/QuestBoard/QuestBoard.item"; } break;
		case eItem_CampFire:		{ return "media/gamedata/items/CampFire/CampFire.item"; } break;
		case eItem_Mannequin:		{ return "media/gamedata/items/Mannequin/Mannequin.item"; } break;
		// Ingredients
		case eItem_SlimeJelly:		{ return "media/gamedata/items/SlimeJelly/SlimeJelly.item"; } break;
		case eItem_BeeWing:			{ return "media/gamedata/items/BeeWing/BeeWing.item"; } break;
		case eItem_Bone:			{ return "media/gamedata/items/Bone/Bone.item"; } break;
		// Ore and mining
		case eItem_CopperVein:		{ return "media/gamedata/items/CopperVein/CopperVein0.item"; } break;
		case eItem_CopperOre:		{ return "media/gamedata/items/CopperOre/CopperOre.item"; } break;
		case eItem_CopperBar:		{ return "media/gamedata/items/CopperBar/CopperBar.item"; } break;
		case eItem_IronVein:		{ return "media/gamedata/items/IronVein/IronVein0.item"; } break;
		case eItem_IronOre:			{ return "media/gamedata/items/IronOre/IronOre.item"; } break;
		case eItem_IronBar:			{ return "media/gamedata/items/IronBar/IronBar.item"; } break;
		case eItem_SilverVein:		{ return "media/gamedata/items/SilverVein/SilverVein0.item"; } break;
		case eItem_SilverOre:		{ return "media/gamedata/items/SilverOre/SilverOre.item"; } break;
		case eItem_SilverBar:		{ return "media/gamedata/items/SilverBar/SilverBar.item"; } break;
		case eItem_GoldVein:		{ return "media/gamedata/items/GoldVein/GoldVein0.item"; } break;
		case eItem_GoldOre:			{ return "media/gamedata/items/GoldOre/GoldOre.item"; } break;
		case eItem_GoldBar:			{ return "media/gamedata/items/GoldBar/GoldBar.item"; } break;
		// World blocks
		case eItem_Block_Grass:		{ return "media/gamedata/items/Block_Grass/Block_Grass.item"; } break;
		case eItem_Block_Dirt:		{ return "media/gamedata/items/Block_Dirt/Block_Dirt.item"; } break;
		case eItem_Block_Stone:		{ return "media/gamedata/items/Block_Stone/Block_Stone.item"; } break;
		case eItem_Block_Wood:		{ return "media/gamedata/items/Block_Wood/Block_Wood.item"; } break;
		case eItem_Block_Leaf:		{ return "media/gamedata/items/Block_Leaf/Block_Leaf.item"; } break;
		case eItem_Block_Sand:		{ return "media/gamedata/items/Block_Sand/Block_Sand.item"; } break;
		case eItem_Block_Cactus:	{ return "media/gamedata/items/Block_Cactus/Block_Cactus.item"; } break;
		case eItem_Block_Rock:		{ return "media/gamedata/items/Block_Rock/Block_Rock.item"; } break;
		case eItem_Block_Snow:		{ return "media/gamedata/items/Block_Snow/Block_Snow.item"; } break;
	}

	cout << "Warning: Reached end of GetItemFilenameForType() without finding type - " << type << ".\n";

	return "";
}

string GetItemTextureForType(eItem type)
{
	switch(type)
	{
		case eItem_None:			{ return ""; } break;
		// Dropped item in the world
		case eItem_DroppedItem:		{ return ""; } break;
		// Herts and coins dropped from killing enemies
		case eItem_Coin:			{ return "media/textures/items/coin.tga"; } break;
		case eItem_Heart:			{ return "media/textures/items/heart.tga"; } break;
		// Zombie gib
		case eItem_Gib:				{ return "media/textures/items/question_mark.tga"; } break;
		// Interactable items
		case eItem_Tombstone:		{ return "media/textures/items/tombstone.tga"; } break;
		case eItem_Chest:			{ return "media/textures/items/chest.tga"; } break;
		case eItem_Torch:			{ return "media/textures/items/torch.tga"; } break;
		case eItem_Furnace:			{ return "media/textures/items/furnace.tga"; } break;
		case eItem_Anvil:			{ return "media/textures/items/anvil.tga"; } break;
		case eItem_QuestBoard:		{ return "media/textures/items/quest_board.tga"; } break;
		case eItem_CampFire:		{ return "media/textures/items/camp_fire.tga"; } break;
		case eItem_Mannequin:		{ return "media/textures/items/mannequin.tga"; } break;
		// Ingredients
		case eItem_SlimeJelly:		{ return "media/textures/items/slime_jelly.tga"; } break;
		case eItem_BeeWing:			{ return "media/textures/items/bee_wing.tga"; } break;
		case eItem_Bone:			{ return "media/textures/items/bone.tga"; } break;
		// Ore and mining
		case eItem_CopperVein:		{ return "media/textures/items/question_mark.tga"; } break;
		case eItem_CopperOre:		{ return "media/textures/items/copper_ore.tga"; } break;
		case eItem_CopperBar:		{ return "media/textures/items/copper_bar.tga"; } break;
		case eItem_IronVein:		{ return "media/textures/items/question_mark.tga"; } break;
		case eItem_IronOre:			{ return "media/textures/items/iron_ore.tga"; } break;
		case eItem_IronBar:			{ return "media/textures/items/iron_bar.tga"; } break;
		case eItem_SilverVein:		{ return "media/textures/items/question_mark.tga"; } break;
		case eItem_SilverOre:		{ return "media/textures/items/silver_ore.tga"; } break;
		case eItem_SilverBar:		{ return "media/textures/items/silver_bar.tga"; } break;
		case eItem_GoldVein:		{ return "media/textures/items/question_mark.tga"; } break;
		case eItem_GoldOre:			{ return "media/textures/items/gold_ore.tga"; } break;
		case eItem_GoldBar:			{ return "media/textures/items/gold_bar.tga"; } break;
		// World blocks
		case eItem_Block_Grass:		{ return "media/textures/items/block_grass.tga"; } break;
		case eItem_Block_Dirt:		{ return "media/textures/items/block_dirt.tga"; } break;
		case eItem_Block_Stone:		{ return "media/textures/items/block_stone.tga"; } break;
		case eItem_Block_Wood:		{ return "media/textures/items/block_wood.tga"; } break;
		case eItem_Block_Leaf:		{ return "media/textures/items/block_leaf.tga"; } break;
		case eItem_Block_Sand:		{ return "media/textures/items/block_sand.tga"; } break;
		case eItem_Block_Cactus:	{ return "media/textures/items/block_cactus.tga"; } break;
		case eItem_Block_Rock:		{ return "media/textures/items/block_rock.tga"; } break;
		case eItem_Block_Snow:		{ return "media/textures/items/block_snow.tga"; } break;
	}

	cout << "Warning: Reached end of GetItemTextureForType() without finding type - " << type << ".\n";

	return "";
}

float GetItemRadiusForType(eItem type)
{
	switch (type)
	{
		case eItem_None:			{ return 1.00f; } break;
		// Dropped item in the world
		case eItem_DroppedItem:		{ return 0.50f; } break;
		// Herts and coins dropped from killing enemies
		case eItem_Coin:			{ return 0.25f; } break;
		case eItem_Heart:			{ return 0.25f; } break;
		// Zombie gib
		case eItem_Gib:				{ return 0.125f; } break;
		// Interactable items
		case eItem_Tombstone:		{ return 0.50f; } break;
		case eItem_Chest:			{ return 0.50f; } break;
		case eItem_Torch:			{ return 1.00f; } break;
		case eItem_Furnace:			{ return 0.50f; } break;
		case eItem_Anvil:			{ return 0.50f; } break;
		case eItem_QuestBoard:		{ return 1.00f; } break;
		case eItem_CampFire:		{ return 0.50f; } break;
		case eItem_Mannequin:		{ return 1.00f; } break;
		// Ingredients
		case eItem_SlimeJelly:		{ return 0.25f; } break;
		case eItem_BeeWing:			{ return 0.25f; } break;
		case eItem_Bone:			{ return 0.25f; } break;
		// Ore and mining
		case eItem_CopperVein:		{ return 0.50f; } break;
		case eItem_CopperOre:		{ return 0.25f; } break;
		case eItem_CopperBar:		{ return 0.25f; } break;
		case eItem_IronVein:		{ return 0.50f; } break;
		case eItem_IronOre:			{ return 0.25f; } break;
		case eItem_IronBar:			{ return 0.25f; } break;
		case eItem_SilverVein:		{ return 0.50f; } break;
		case eItem_SilverOre:		{ return 0.25f; } break;
		case eItem_SilverBar:		{ return 0.25f; } break;
		case eItem_GoldVein:		{ return 0.5f; } break;
		case eItem_GoldOre:			{ return 0.25f; } break;
		case eItem_GoldBar:			{ return 0.25f; } break;
		// World blocks
		case eItem_Block_Grass:		{ return 0.25f; } break;
		case eItem_Block_Dirt:		{ return 0.25f; } break;
		case eItem_Block_Stone:		{ return 0.25f; } break;
		case eItem_Block_Wood:		{ return 0.25f; } break;
		case eItem_Block_Leaf:		{ return 0.25f; } break;
		case eItem_Block_Sand:		{ return 0.25f; } break;
		case eItem_Block_Cactus:	{ return 0.25f; } break;
		case eItem_Block_Rock:		{ return 0.25f; } break;
		case eItem_Block_Snow:		{ return 0.25f; } break;
	}

	cout << "Warning: Reached end of GetItemRadiusForType() without finding type - " << type << ".\n";

	return 1.0f;
}