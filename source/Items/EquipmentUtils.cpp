// ******************************************************************************
// Filename:    EquipmentUtils.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   Utility functionality for equipment, mostly a way to associate equipment
//   enums with data like the friendly names and display strings.
//
// Revision History:
//   Initial Revision - 12/04/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "Item.h"

string GetEquipmentTitleForType(eEquipment type)
{
	switch(type)
	{
		// Weapons
		case eEquipment_None:				{ return ""; } break;
		case eEquipment_NormalPickaxe:		{ return "Normal Pickaxe"; } break;
		case eEquipment_Torch:				{ return "Torch"; } break;
		case eEquipment_Hammer:				{ return "Hammer"; } break;
		case eEquipment_MageStaff:			{ return "Mage Staff"; } break;
		case eEquipment_NecroStaff:			{ return "Necro Staff"; } break;
		case eEquipment_PriestStaff:		{ return "Priest Staff"; } break;
		case eEquipment_DruidStaff:			{ return "Druid Staff"; } break;
		case eEquipment_2HandedSword:		{ return "Two Handed Sword"; } break;
		case eEquipment_Boomerang:			{ return "Boomerang"; } break;
		case eEquipment_Bomb:				{ return "Bomb"; } break;
		case eEquipment_KnifeLeft:			{ return "Knife"; } break;
		case eEquipment_KnifeRight:			{ return "Knife"; } break;
		case eEquipment_FireballHandLeft:	{ return "Fireball Hands"; } break;
		case eEquipment_FireballHandRight:	{ return "Fireball Hands"; } break;
		case eEquipment_Mace:				{ return "Mace"; } break;
		case eEquipment_Sickle:				{ return "Sickle"; } break;
		case eEquipment_DragonBow:			{ return "Dragon Bow"; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return "Blacksmith Gloves"; } break;
		case eEquipment_NormalBoots:		{ return "Normal Boots"; } break;
		case eEquipment_NormalGloves:		{ return "Normal Gloves"; } break;
		case eEquipment_NormalShoulders:	{ return "Normal Shoulders"; } break;
		case eEquipment_RocketBoots:		{ return "Rocket Boots"; } break;
		case eEquipment_RegrowthBoots:		{ return "Regrowth Boots"; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return "Wooden Sword"; } break;
		case eEquipment_WoodenShield:		{ return "Wooden Shield"; } break;
		case eEquipment_WoodenBow:			{ return "Wooden Bow"; } break;
		case eEquipment_WoodenHelm:			{ return "Wooden Helm"; } break;
		case eEquipment_WoodenArmor:		{ return "Wooden Armor"; } break;
		case eEquipment_WoodenPants:		{ return "Wooden Pants"; } break;
		case eEquipment_WoodenGloves:		{ return "Wooden Gloves"; } break;
		case eEquipment_WoodenBoots:		{ return "Wooden Boots"; } break;
		case eEquipment_WoodenShoulders:	{ return "Wooden Shoulders"; } break;
		// Iron
		case eEquipment_IronSword:			{ return "Iron Sword"; } break;
		case eEquipment_IronShield:			{ return "Iron Shield"; } break;
		case eEquipment_IronHelm:			{ return "Iron Helm"; } break;
		case eEquipment_IronArmor:			{ return "Iron Armor"; } break;
		case eEquipment_IronPants:			{ return "Iron Pants"; } break;
		case eEquipment_IronGloves:			{ return "Iron Gloves"; } break;
		case eEquipment_IronBoots:			{ return "Iron Boots"; } break;
		case eEquipment_IronShoulders:		{ return "Iron Shoulders"; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return "Steel Helm"; } break;
		case eEquipment_SteelArmor:			{ return "Steel Armor"; } break;
		case eEquipment_SteelPants:			{ return "Steel Pants"; } break;
		case eEquipment_SteelGloves:		{ return "Steel Gloves"; } break;
		case eEquipment_SteelBoots:			{ return "Steel Boots"; } break;
		case eEquipment_SteelShoulders:		{ return "Steel Shoulders"; } break;
		// Ash
		case eEquipment_AshHelm:			{ return "Ash Helm"; } break;
		case eEquipment_AshSword:			{ return "Ash Sword"; } break;
		case eEquipment_AshArmor:			{ return "Ash Armor"; } break;
		case eEquipment_AshPants:			{ return "Ash Pants"; } break;
		case eEquipment_AshGloves:			{ return "Ash Gloves"; } break;
		case eEquipment_AshBoots:			{ return "Ash Boots"; } break;
		case eEquipment_AshShoulders:		{ return "Ash Shoulders"; } break;
		// Bone
		case eEquipment_BoneSword:			{ return "Bone Edge"; } break;
		case eEquipment_BoneHelm:			{ return "Bone Helm"; } break;
		case eEquipment_BoneArmor:			{ return "Bone Armor"; } break;
		case eEquipment_BonePants:			{ return "Bone Pants"; } break;
		case eEquipment_BoneGloves:			{ return "Bone Gloves"; } break;
		case eEquipment_BoneBoots:			{ return "Bone Boots"; } break;
		case eEquipment_BoneShoulders:		{ return "Bone Shoulders"; } break;
		// Ice
		case eEquipment_IceHelm:			{ return "Ice Helm"; } break;
		case eEquipment_IceArmor:			{ return "Ice Armor"; } break;
		case eEquipment_IcePants:			{ return "Ice Pants"; } break;
		case eEquipment_IceGloves:			{ return "Ice Gloves"; } break;
		case eEquipment_IceBoots:			{ return "Ice Boots"; } break;
		case eEquipment_IceShoulders:		{ return "Ice Shoulders"; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return "Spike Helm"; } break;
		case eEquipment_SpikeArmor:			{ return "Spike Armor"; } break;
		case eEquipment_SpikePants:			{ return "Spike Pants"; } break;
		case eEquipment_SpikeGloves:		{ return "Spike Gloves"; } break;
		case eEquipment_SpikeBoots:			{ return "Spike Boots"; } break;
		case eEquipment_SpikeShoulders:		{ return "Spike Shoulders"; } break;
	}

	cout << "Warning: Reached end of GetEquipmentTitleForType() without finding type - " << type << ".\n";

	return "";
}

string GetEquipmentDescriptionForType(eEquipment type)
{
	switch(type)
	{
		case eEquipment_None:				{ return ""; } break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ return "Used for mining and digging the world."; } break;
		case eEquipment_Torch:				{ return "A torch to light up the darkness."; } break;
		case eEquipment_Hammer:				{ return "A hammer to smite your foes."; } break;
		case eEquipment_MageStaff:			{ return "A staff that contains powerful magic."; } break;
		case eEquipment_NecroStaff:			{ return "A necromancer staff once used by powerful mages of undeath."; } break;
		case eEquipment_PriestStaff:		{ return "A holy staff of pure energy."; } break;
		case eEquipment_DruidStaff:			{ return "A staff that is engraved with nature."; } break;
		case eEquipment_2HandedSword:		{ return "A sword that requires both hands to wield."; } break;
		case eEquipment_Boomerang:			{ return "Once thrown, the boomerang returns to you."; } break;
		case eEquipment_Bomb:				{ return "An explosive bomb, can destroy enemies and the landscape."; } break;
		case eEquipment_KnifeLeft:			{ return "A stabbing knife."; } break;
		case eEquipment_KnifeRight:			{ return "A stabbing knife."; } break;
		case eEquipment_FireballHandLeft:	{ return "Cast powerful spells using only your hands."; } break;
		case eEquipment_FireballHandRight:	{ return "Cast powerful spells using only your hands."; } break;
		case eEquipment_Mace:				{ return "A deadly mace, to smite down your enemies."; } break;
		case eEquipment_Sickle:				{ return "Very sharp and very deadly."; } break;
		case eEquipment_DragonBow:			{ return "Once used by the dragon riders of old Vox."; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return "Blacksmith gloves are used during the crafting of items."; } break;
		case eEquipment_NormalBoots:		{ return "Normal boots."; } break;
		case eEquipment_NormalGloves:		{ return "Normal gloves."; } break;
		case eEquipment_NormalShoulders:	{ return "Normal shoulders."; } break;
		case eEquipment_RocketBoots:		{ return "Rocket boots."; } break;
		case eEquipment_RegrowthBoots:		{ return "Regrowth boots."; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return "A wooden sword, not very good in combat."; } break;
		case eEquipment_WoodenShield:		{ return "A wooden shield, cannnot protect against much."; } break;
		case eEquipment_WoodenBow:			{ return "A wooden bow, made for shooting arrows."; } break;
		case eEquipment_WoodenHelm:			{ return "Wooden helm."; } break;
		case eEquipment_WoodenArmor:		{ return "Wooden armor."; } break;
		case eEquipment_WoodenPants:		{ return "Wooden pants."; } break;
		case eEquipment_WoodenGloves:		{ return "Wooden gloves."; } break;
		case eEquipment_WoodenBoots:		{ return "Wooden boots."; } break;
		case eEquipment_WoodenShoulders:	{ return "Wooden shoulders."; } break;
		// Iron
		case eEquipment_IronSword:			{ return "A sturdy sword made of iron."; } break;
		case eEquipment_IronShield:			{ return "A shield of pure iron."; } break;
		case eEquipment_IronHelm:			{ return "Iron helm."; } break;
		case eEquipment_IronArmor:			{ return "Iron armor."; } break;
		case eEquipment_IronPants:			{ return "Iron pants."; } break;
		case eEquipment_IronGloves:			{ return "Iron gloves."; } break;
		case eEquipment_IronBoots:			{ return "Iron boots."; } break;
		case eEquipment_IronShoulders:		{ return "Iron shoulders."; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return "Steel helm."; } break;
		case eEquipment_SteelArmor:			{ return "Steel armor."; } break;
		case eEquipment_SteelPants:			{ return "Steel pants."; } break;
		case eEquipment_SteelGloves:		{ return "Steel gloves."; } break;
		case eEquipment_SteelBoots:			{ return "Steel boots."; } break;
		case eEquipment_SteelShoulders:		{ return "Steel shoulders."; } break;
		// Ash
		case eEquipment_AshSword:			{ return "Ash sword."; } break;
		case eEquipment_AshHelm:			{ return "Ash helm."; } break;
		case eEquipment_AshArmor:			{ return "Ash armor."; } break;
		case eEquipment_AshPants:			{ return "Ash pants."; } break;
		case eEquipment_AshGloves:			{ return "Ash gloves."; } break;
		case eEquipment_AshBoots:			{ return "Ash boots."; } break;
		case eEquipment_AshShoulders:		{ return "Ash shoulders."; } break;
		// Bone
		case eEquipment_BoneSword:			{ return "A sword made entirely out of bones."; } break;
		case eEquipment_BoneHelm:			{ return "Bone helm."; } break;
		case eEquipment_BoneArmor:			{ return "Bone armor."; } break;
		case eEquipment_BonePants:			{ return "Bone pants."; } break;
		case eEquipment_BoneGloves:			{ return "Bone gloves."; } break;
		case eEquipment_BoneBoots:			{ return "Bone boots."; } break;
		case eEquipment_BoneShoulders:		{ return "Bone shoulders."; } break;
		// Ice
		case eEquipment_IceHelm:			{ return "Ice helm."; } break;
		case eEquipment_IceArmor:			{ return "Ice armor."; } break;
		case eEquipment_IcePants:			{ return "Ice pants."; } break;
		case eEquipment_IceGloves:			{ return "Ice gloves."; } break;
		case eEquipment_IceBoots:			{ return "Ice boots."; } break;
		case eEquipment_IceShoulders:		{ return "Ice shoulders."; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return "Spike helm."; } break;
		case eEquipment_SpikeArmor:			{ return "Spike armor."; } break;
		case eEquipment_SpikePants:			{ return "Spike pants."; } break;
		case eEquipment_SpikeGloves:		{ return "Spike gloves."; } break;
		case eEquipment_SpikeBoots:			{ return "Spike boots."; } break;
		case eEquipment_SpikeShoulders:		{ return "Spike shoulders."; } break;
	}

	cout << "Warning: Reached end of GetEquipmentDescriptionForType() without finding type - " << type << ".\n";

	return "";
}

string GetEquipmentFilenameForType(eEquipment type)
{
	switch(type)
	{
		case eEquipment_None:				{ return ""; } break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ return "media/gamedata/weapons/Pickaxe/Pickaxe.weapon"; } break;
		case eEquipment_Torch:				{ return "media/gamedata/weapons/Torch/Torch.weapon"; } break;
		case eEquipment_Hammer:				{ return "media/gamedata/weapons/Hammer/Hammer.weapon"; } break;
		case eEquipment_MageStaff:			{ return "media/gamedata/weapons/Staff/Staff.weapon"; } break;
		case eEquipment_NecroStaff:			{ return "media/gamedata/weapons/NecroStaff/NecroStaff.weapon"; } break;
		case eEquipment_PriestStaff:		{ return "media/gamedata/weapons/PriestStaff/PriestStaff.weapon"; } break;
		case eEquipment_DruidStaff:			{ return "media/gamedata/weapons/DruidStaff/DruidStaff.weapon"; } break;
		case eEquipment_2HandedSword:		{ return "media/gamedata/weapons/2HandedSword/2HandedSword.weapon"; } break;
		case eEquipment_Boomerang:			{ return "media/gamedata/weapons/Boomerang/Boomerang.weapon"; } break;
		case eEquipment_Bomb:				{ return "media/gamedata/items/Bomb/Bomb.item"; } break;
		case eEquipment_KnifeLeft:			{ return "media/gamedata/weapons/Knife/Knife.weapon"; } break;
		case eEquipment_KnifeRight:			{ return "media/gamedata/weapons/Knife/Knife.weapon"; } break;
		case eEquipment_FireballHandLeft:	{ return "media/gamedata/weapons/FireballHands/FireballHandsLeft.weapon"; } break;
		case eEquipment_FireballHandRight:	{ return "media/gamedata/weapons/FireballHands/FireballHandsRight.weapon"; } break;
		case eEquipment_Mace:				{ return "media/gamedata/weapons/Mace/Mace.weapon"; } break;
		case eEquipment_Sickle:				{ return "media/gamedata/weapons/Sickle/Sickle.weapon"; } break;
		case eEquipment_DragonBow:			{ return "media/gamedata/weapons/DragonBow/DragonBow.weapon"; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return "media/gamedata/equipment/BlacksmithGloves/BlacksmithGloves.equipment"; } break;
		case eEquipment_NormalBoots:		{ return "media/gamedata/equipment/NormalBoots/NormalBoots.equipment"; } break;
		case eEquipment_NormalGloves:		{ return "media/gamedata/equipment/NormalGloves/NormalGloves.equipment"; } break;
		case eEquipment_NormalShoulders:	{ return "media/gamedata/equipment/NormalShoulders/NormalShoulders.equipment"; } break;
		case eEquipment_RocketBoots:		{ return "media/gamedata/equipment/RocketBoots/RocketBoots.equipment"; } break;
		case eEquipment_RegrowthBoots:		{ return "media/gamedata/equipment/RegrowthBoots/RegrowthBoots.equipment"; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return "media/gamedata/weapons/WoodenSword/WoodenSword.weapon"; } break;
		case eEquipment_WoodenShield:		{ return "media/gamedata/weapons/WoodenShield/WoodenShield.weapon"; } break;
		case eEquipment_WoodenBow:			{ return "media/gamedata/weapons/WoodenBow/WoodenBow.weapon"; } break;
		case eEquipment_WoodenHelm:			{ return "media/gamedata/equipment/WoodHelm/WoodHelm.equipment"; } break;
		case eEquipment_WoodenArmor:		{ return "media/gamedata/equipment/WoodBody/WoodBody.equipment"; } break;
		case eEquipment_WoodenPants:		{ return "media/gamedata/equipment/WoodPants/WoodPants.equipment"; } break;
		case eEquipment_WoodenGloves:		{ return "media/gamedata/equipment/WoodGloves/WoodGloves.equipment"; } break;
		case eEquipment_WoodenBoots:		{ return "media/gamedata/equipment/WoodBoots/WoodBoots.equipment"; } break;
		case eEquipment_WoodenShoulders:	{ return "media/gamedata/equipment/WoodShoulders/WoodShoulders.equipment"; } break;
		// Iron
		case eEquipment_IronSword:			{ return "media/gamedata/weapons/IronSword/IronSword.weapon"; } break;
		case eEquipment_IronShield:			{ return "media/gamedata/weapons/IronShield/IronShield.weapon"; } break;
		case eEquipment_IronHelm:			{ return "media/gamedata/equipment/IronHelm/IronHelm.equipment"; } break;
		case eEquipment_IronArmor:			{ return "media/gamedata/equipment/IronBody/IronBody.equipment"; } break;
		case eEquipment_IronPants:			{ return "media/gamedata/equipment/IronPants/IronPants.equipment"; } break;
		case eEquipment_IronGloves:			{ return "media/gamedata/equipment/IronGloves/IronGloves.equipment"; } break;
		case eEquipment_IronBoots:			{ return "media/gamedata/equipment/IronBoots/IronBoots.equipment"; } break;
		case eEquipment_IronShoulders:		{ return "media/gamedata/equipment/IronShoulders/IronShoulders.equipment"; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return "media/gamedata/equipment/SteelHelm/SteelHelm.equipment"; } break;
		case eEquipment_SteelArmor:			{ return "media/gamedata/equipment/SteelBody/SteelBody.equipment"; } break;
		case eEquipment_SteelPants:			{ return "media/gamedata/equipment/SteelPants/SteelPants.equipment"; } break;
		case eEquipment_SteelGloves:		{ return "media/gamedata/equipment/SteelGloves/SteelGloves.equipment"; } break;
		case eEquipment_SteelBoots:			{ return "media/gamedata/equipment/SteelBoots/SteelBoots.equipment"; } break;
		case eEquipment_SteelShoulders:		{ return "media/gamedata/equipment/SteelShoulders/SteelShoulders.equipment"; } break;
		// Ash
		case eEquipment_AshSword:			{ return "media/gamedata/weapons/AshSword/AshSword.weapon"; } break;
		case eEquipment_AshHelm:			{ return "media/gamedata/equipment/AshHelm/AshHelm.equipment"; } break;
		case eEquipment_AshArmor:			{ return "media/gamedata/equipment/AshBody/AshBody.equipment"; } break;
		case eEquipment_AshPants:			{ return "media/gamedata/equipment/AshPants/AshPants.equipment"; } break;
		case eEquipment_AshGloves:			{ return "media/gamedata/equipment/AshGloves/AshGloves.equipment"; } break;
		case eEquipment_AshBoots:			{ return "media/gamedata/equipment/AshBoots/AshBoots.equipment"; } break;
		case eEquipment_AshShoulders:		{ return "media/gamedata/equipment/AshShoulders/AshShoulders.equipment"; } break;
		// Bone
		case eEquipment_BoneSword:			{ return "media/gamedata/weapons/BoneEdge/BoneEdge.weapon"; } break;
		case eEquipment_BoneHelm:			{ return "media/gamedata/equipment/BoneHelm/BoneHelm.equipment"; } break;
		case eEquipment_BoneArmor:			{ return "media/gamedata/equipment/BoneBody/BoneBody.equipment"; } break;
		case eEquipment_BonePants:			{ return "media/gamedata/equipment/BonePants/BonePants.equipment"; } break;
		case eEquipment_BoneGloves:			{ return "media/gamedata/equipment/BoneGloves/BoneGloves.equipment"; } break;
		case eEquipment_BoneBoots:			{ return "media/gamedata/equipment/BoneBoots/BoneBoots.equipment"; } break;
		case eEquipment_BoneShoulders:		{ return "media/gamedata/equipment/BoneShoulders/BoneShoulders.equipment"; } break;
		// Ice
		case eEquipment_IceHelm:			{ return "media/gamedata/equipment/IceHelm/IceHelm.equipment"; } break;
		case eEquipment_IceArmor:			{ return "media/gamedata/equipment/IceBody/IceBody.equipment"; } break;
		case eEquipment_IcePants:			{ return "media/gamedata/equipment/IcePants/IcePants.equipment"; } break;
		case eEquipment_IceGloves:			{ return "media/gamedata/equipment/IceGloves/IceGloves.equipment"; } break;
		case eEquipment_IceBoots:			{ return "media/gamedata/equipment/IceBoots/IceBoots.equipment"; } break;
		case eEquipment_IceShoulders:		{ return "media/gamedata/equipment/IceShoulders/IceShoulders.equipment"; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return "media/gamedata/equipment/SpikeHelm/SpikeHelm.equipment"; } break;
		case eEquipment_SpikeArmor:			{ return "media/gamedata/equipment/SpikeBody/SpikeBody.equipment"; } break;
		case eEquipment_SpikePants:			{ return "media/gamedata/equipment/SpikePants/SpikePants.equipment"; } break;
		case eEquipment_SpikeGloves:		{ return "media/gamedata/equipment/SpikeGloves/SpikeGloves.equipment"; } break;
		case eEquipment_SpikeBoots:			{ return "media/gamedata/equipment/SpikeBoots/SpikeBoots.equipment"; } break;
		case eEquipment_SpikeShoulders:		{ return "media/gamedata/equipment/SpikeShoulders/SpikeShoulders.equipment"; } break;
	}

	cout << "Warning: Reached end of GetEquipmentFilenameForType() without finding type - " << type << ".\n";

	return "";
}

string GetEquipmentTextureForType(eEquipment type)
{
	switch(type)
	{
		case eEquipment_None:				{ return ""; } break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ return "media/textures/items/pickaxe.tga"; } break;
		case eEquipment_Torch:				{ return "media/textures/items/torch.tga"; } break;
		case eEquipment_Hammer:				{ return "media/textures/items/hammer.tga"; } break;
		case eEquipment_MageStaff:			{ return "media/textures/items/staff_mage.tga"; } break;
		case eEquipment_NecroStaff:			{ return "media/textures/items/staff_necro.tga"; } break;
		case eEquipment_PriestStaff:		{ return "media/textures/items/staff_priest.tga"; } break;
		case eEquipment_DruidStaff:			{ return "media/textures/items/staff_druid.tga"; } break;
		case eEquipment_2HandedSword:		{ return "media/textures/items/2handed_sword.tga"; } break;
		case eEquipment_Boomerang:			{ return "media/textures/items/boomerang.tga"; } break;
		case eEquipment_Bomb:				{ return "media/textures/items/bomb.tga"; } break;
		case eEquipment_KnifeLeft:			{ return "media/textures/items/knife.tga"; } break;
		case eEquipment_KnifeRight:			{ return "media/textures/items/knife.tga"; } break;
		case eEquipment_FireballHandLeft:	{ return "media/textures/items/fireball_hand.tga"; } break;
		case eEquipment_FireballHandRight:	{ return "media/textures/items/fireball_hand.tga"; } break;
		case eEquipment_Mace:				{ return "media/textures/items/mace.tga"; } break;
		case eEquipment_Sickle:				{ return "media/textures/items/sickle.tga"; } break;
		case eEquipment_DragonBow:			{ return "media/textures/items/dragon_bow.tga"; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return "media/textures/items/blacksmith_gloves.tga"; } break;
		case eEquipment_NormalBoots:		{ return "media/textures/items/normal_boots.tga"; } break;
		case eEquipment_NormalGloves:		{ return "media/textures/items/normal_gloves.tga"; } break;
		case eEquipment_NormalShoulders:	{ return "media/textures/items/normal_shoulders.tga"; } break;
		case eEquipment_RocketBoots:		{ return "media/textures/items/rocket_boots.tga"; } break;
		case eEquipment_RegrowthBoots:		{ return "media/textures/items/regrowth_boots.tga"; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return "media/textures/items/wood_sword.tga"; } break;
		case eEquipment_WoodenShield:		{ return "media/textures/items/wood_shield.tga"; } break;
		case eEquipment_WoodenBow:			{ return "media/textures/items/wood_bow.tga"; } break;
		case eEquipment_WoodenHelm:			{ return "media/textures/items/wood_helm.tga"; } break;
		case eEquipment_WoodenArmor:		{ return "media/textures/items/wood_armor.tga"; } break;
		case eEquipment_WoodenPants:		{ return "media/textures/items/wood_pants.tga"; } break;
		case eEquipment_WoodenGloves:		{ return "media/textures/items/wood_gloves.tga"; } break;
		case eEquipment_WoodenBoots:		{ return "media/textures/items/wood_boots.tga"; } break;
		case eEquipment_WoodenShoulders:	{ return "media/textures/items/wood_shoulders.tga"; } break;
		// Iron
		case eEquipment_IronSword:			{ return "media/textures/items/iron_sword.tga"; } break;
		case eEquipment_IronShield:			{ return "media/textures/items/iron_shield.tga"; } break;
		case eEquipment_IronHelm:			{ return "media/textures/items/iron_helm.tga"; } break;
		case eEquipment_IronArmor:			{ return "media/textures/items/iron_armor.tga"; } break;
		case eEquipment_IronPants:			{ return "media/textures/items/iron_pants.tga"; } break;
		case eEquipment_IronGloves:			{ return "media/textures/items/iron_gloves.tga"; } break;
		case eEquipment_IronBoots:			{ return "media/textures/items/iron_boots.tga"; } break;
		case eEquipment_IronShoulders:		{ return "media/textures/items/iron_shoulders.tga"; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return "media/textures/items/steel_helm.tga"; } break;
		case eEquipment_SteelArmor:			{ return "media/textures/items/steel_armor.tga"; } break;
		case eEquipment_SteelPants:			{ return "media/textures/items/steel_pants.tga"; } break;
		case eEquipment_SteelGloves:		{ return "media/textures/items/steel_gloves.tga"; } break;
		case eEquipment_SteelBoots:			{ return "media/textures/items/steel_boots.tga"; } break;
		case eEquipment_SteelShoulders:		{ return "media/textures/items/steel_shoulders.tga"; } break;
		// Ash
		case eEquipment_AshSword:			{ return "media/textures/items/ash_sword.tga"; } break;
		case eEquipment_AshHelm:			{ return "media/textures/items/ash_helm.tga"; } break;
		case eEquipment_AshArmor:			{ return "media/textures/items/ash_armor.tga"; } break;
		case eEquipment_AshPants:			{ return "media/textures/items/ash_pants.tga"; } break;
		case eEquipment_AshGloves:			{ return "media/textures/items/ash_gloves.tga"; } break;
		case eEquipment_AshBoots:			{ return "media/textures/items/ash_boots.tga"; } break;
		case eEquipment_AshShoulders:		{ return "media/textures/items/ash_shoulders.tga"; } break;
		// Bone
		case eEquipment_BoneSword:			{ return "media/textures/items/bone_edge.tga"; } break;
		case eEquipment_BoneHelm:			{ return "media/textures/items/bone_helm.tga"; } break;
		case eEquipment_BoneArmor:			{ return "media/textures/items/bone_armor.tga"; } break;
		case eEquipment_BonePants:			{ return "media/textures/items/bone_pants.tga"; } break;
		case eEquipment_BoneGloves:			{ return "media/textures/items/bone_gloves.tga"; } break;
		case eEquipment_BoneBoots:			{ return "media/textures/items/bone_boots.tga"; } break;
		case eEquipment_BoneShoulders:		{ return "media/textures/items/bone_shoulders.tga"; } break;
		// Ice
		case eEquipment_IceHelm:			{ return "media/textures/items/ice_helm.tga"; } break;
		case eEquipment_IceArmor:			{ return "media/textures/items/ice_armor.tga"; } break;
		case eEquipment_IcePants:			{ return "media/textures/items/ice_pants.tga"; } break;
		case eEquipment_IceGloves:			{ return "media/textures/items/ice_gloves.tga"; } break;
		case eEquipment_IceBoots:			{ return "media/textures/items/ice_boots.tga"; } break;
		case eEquipment_IceShoulders:		{ return "media/textures/items/ice_shoulders.tga"; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return "media/textures/items/spike_helm.tga"; } break;
		case eEquipment_SpikeArmor:			{ return "media/textures/items/spike_armor.tga"; } break;
		case eEquipment_SpikePants:			{ return "media/textures/items/spike_pants.tga"; } break;
		case eEquipment_SpikeGloves:		{ return "media/textures/items/spike_gloves.tga"; } break;
		case eEquipment_SpikeBoots:			{ return "media/textures/items/spike_boots.tga"; } break;
		case eEquipment_SpikeShoulders:		{ return "media/textures/items/spike_shoulders.tga"; } break;
	}

	cout << "Warning: Reached end of GetEquipmentTextureForType() without finding type - " << type << ".\n";

	return "";
}

InventoryType GetInventoryTypeForEquipment(eEquipment type)
{
	switch(type)
	{
		case eEquipment_None:				{ return InventoryType_Nothing; } break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ return InventoryType_Weapon_Pickaxe; } break;
		case eEquipment_Torch:				{ return InventoryType_Weapon_Torch; } break;
		case eEquipment_Hammer:				{ return InventoryType_Weapon_Hammer; } break;
		case eEquipment_MageStaff:			{ return InventoryType_Weapon_Staff; } break;
		case eEquipment_NecroStaff:			{ return InventoryType_Weapon_Staff; } break;
		case eEquipment_PriestStaff:		{ return InventoryType_Weapon_Staff; } break;
		case eEquipment_DruidStaff:			{ return InventoryType_Weapon_Staff; } break;
		case eEquipment_2HandedSword:		{ return InventoryType_Weapon_2HandedSword; } break;
		case eEquipment_Boomerang:			{ return InventoryType_Weapon_Boomerang; } break;
		case eEquipment_Bomb:				{ return InventoryType_Weapon_Bomb; } break;
		case eEquipment_KnifeLeft:			{ return InventoryType_Weapon_Dagger; } break;
		case eEquipment_KnifeRight:			{ return InventoryType_Weapon_Dagger; } break;
		case eEquipment_FireballHandLeft:	{ return InventoryType_Weapon_SpellHands; } break;
		case eEquipment_FireballHandRight:	{ return InventoryType_Weapon_SpellHands; } break;
		case eEquipment_Mace:				{ return InventoryType_Weapon_Mace; } break;
		case eEquipment_Sickle:				{ return InventoryType_Weapon_Sickle; } break;
		case eEquipment_DragonBow:			{ return InventoryType_Weapon_Bow; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return InventoryType_Clothing; } break;
		case eEquipment_NormalBoots:		{ return InventoryType_Clothing; } break;
		case eEquipment_NormalGloves:		{ return InventoryType_Clothing; } break;
		case eEquipment_NormalShoulders:	{ return InventoryType_Clothing; } break;
		case eEquipment_RocketBoots:		{ return InventoryType_Clothing; } break;
		case eEquipment_RegrowthBoots:		{ return InventoryType_Clothing; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return InventoryType_Weapon_Sword; } break;
		case eEquipment_WoodenShield:		{ return InventoryType_Weapon_Shield; } break;
		case eEquipment_WoodenBow:			{ return InventoryType_Weapon_Bow; } break;
		case eEquipment_WoodenHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_WoodenArmor:		{ return InventoryType_Clothing; } break;
		case eEquipment_WoodenPants:		{ return InventoryType_Clothing; } break;
		case eEquipment_WoodenGloves:		{ return InventoryType_Clothing; } break;
		case eEquipment_WoodenBoots:		{ return InventoryType_Clothing; } break;
		case eEquipment_WoodenShoulders:	{ return InventoryType_Clothing; } break;
		// Iron
		case eEquipment_IronSword:			{ return InventoryType_Weapon_Sword; } break;
		case eEquipment_IronShield:			{ return InventoryType_Weapon_Shield; } break;
		case eEquipment_IronHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_IronArmor:			{ return InventoryType_Clothing; } break;
		case eEquipment_IronPants:			{ return InventoryType_Clothing; } break;
		case eEquipment_IronGloves:			{ return InventoryType_Clothing; } break;
		case eEquipment_IronBoots:			{ return InventoryType_Clothing; } break;
		case eEquipment_IronShoulders:		{ return InventoryType_Clothing; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_SteelArmor:			{ return InventoryType_Clothing; } break;
		case eEquipment_SteelPants:			{ return InventoryType_Clothing; } break;
		case eEquipment_SteelGloves:		{ return InventoryType_Clothing; } break;
		case eEquipment_SteelBoots:			{ return InventoryType_Clothing; } break;
		case eEquipment_SteelShoulders:		{ return InventoryType_Clothing; } break;
		// Ash
		case eEquipment_AshSword:			{ return InventoryType_Weapon_Sword; } break;
		case eEquipment_AshHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_AshArmor:			{ return InventoryType_Clothing; } break;
		case eEquipment_AshPants:			{ return InventoryType_Clothing; } break;
		case eEquipment_AshGloves:			{ return InventoryType_Clothing; } break;
		case eEquipment_AshBoots:			{ return InventoryType_Clothing; } break;
		case eEquipment_AshShoulders:		{ return InventoryType_Clothing; } break;
		// Bone
		case eEquipment_BoneSword:			{ return InventoryType_Weapon_Sword; } break;
		case eEquipment_BoneHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_BoneArmor:			{ return InventoryType_Clothing; } break;
		case eEquipment_BonePants:			{ return InventoryType_Clothing; } break;
		case eEquipment_BoneGloves:			{ return InventoryType_Clothing; } break;
		case eEquipment_BoneBoots:			{ return InventoryType_Clothing; } break;
		case eEquipment_BoneShoulders:		{ return InventoryType_Clothing; } break;
		// Ice
		case eEquipment_IceHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_IceArmor:			{ return InventoryType_Clothing; } break;
		case eEquipment_IcePants:			{ return InventoryType_Clothing; } break;
		case eEquipment_IceGloves:			{ return InventoryType_Clothing; } break;
		case eEquipment_IceBoots:			{ return InventoryType_Clothing; } break;
		case eEquipment_IceShoulders:		{ return InventoryType_Clothing; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return InventoryType_Clothing; } break;
		case eEquipment_SpikeArmor:			{ return InventoryType_Clothing; } break;
		case eEquipment_SpikePants:			{ return InventoryType_Clothing; } break;
		case eEquipment_SpikeGloves:		{ return InventoryType_Clothing; } break;
		case eEquipment_SpikeBoots:			{ return InventoryType_Clothing; } break;
		case eEquipment_SpikeShoulders:		{ return InventoryType_Clothing; } break;
	}

	cout << "Warning: Reached end of GetInventoryTypeForEquipment() without finding type - " << type << ".\n";

	return InventoryType_Nothing;
}

EquipSlot GetEquipSlotForEquipment(eEquipment type)
{
	switch (type)
	{
		case eEquipment_None:				{ return EquipSlot_NoSlot; } break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ return EquipSlot_RightHand; } break;
		case eEquipment_Torch:				{ return EquipSlot_LeftHand; } break;
		case eEquipment_Hammer:				{ return EquipSlot_RightHand; } break;
		case eEquipment_MageStaff:			{ return EquipSlot_RightHand; } break;
		case eEquipment_NecroStaff:			{ return EquipSlot_RightHand; } break;
		case eEquipment_PriestStaff:		{ return EquipSlot_RightHand; } break;
		case eEquipment_DruidStaff:			{ return EquipSlot_RightHand; } break;
		case eEquipment_2HandedSword:		{ return EquipSlot_RightHand; } break;
		case eEquipment_Boomerang:			{ return EquipSlot_RightHand; } break;
		case eEquipment_Bomb:				{ return EquipSlot_RightHand; } break;
		case eEquipment_KnifeLeft:			{ return EquipSlot_LeftHand; } break;
		case eEquipment_KnifeRight:			{ return EquipSlot_RightHand; } break;
		case eEquipment_FireballHandLeft:	{ return EquipSlot_LeftHand; } break;
		case eEquipment_FireballHandRight:	{ return EquipSlot_RightHand; } break;
		case eEquipment_Mace:				{ return EquipSlot_RightHand; } break;
		case eEquipment_Sickle:				{ return EquipSlot_RightHand; } break;
		case eEquipment_DragonBow:			{ return EquipSlot_LeftHand; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return EquipSlot_Hand; } break;
		case eEquipment_NormalBoots:		{ return EquipSlot_Feet; } break;
		case eEquipment_NormalGloves:		{ return EquipSlot_Hand; } break;
		case eEquipment_NormalShoulders:	{ return EquipSlot_Shoulders; } break;
		case eEquipment_RocketBoots:		{ return EquipSlot_Feet; } break;
		case eEquipment_RegrowthBoots:		{ return EquipSlot_Feet; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return EquipSlot_RightHand; } break;
		case eEquipment_WoodenShield:		{ return EquipSlot_LeftHand; } break;
		case eEquipment_WoodenBow:			{ return EquipSlot_LeftHand; } break;
		case eEquipment_WoodenHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_WoodenArmor:		{ return EquipSlot_Body; } break;
		case eEquipment_WoodenPants:		{ return EquipSlot_Legs; } break;
		case eEquipment_WoodenGloves:		{ return EquipSlot_Hand; } break;
		case eEquipment_WoodenBoots:		{ return EquipSlot_Feet; } break;
		case eEquipment_WoodenShoulders:	{ return EquipSlot_Shoulders; } break;
		// Iron
		case eEquipment_IronSword:			{ return EquipSlot_RightHand; } break;
		case eEquipment_IronShield:			{ return EquipSlot_LeftHand; } break;
		case eEquipment_IronHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_IronArmor:			{ return EquipSlot_Body; } break;
		case eEquipment_IronPants:			{ return EquipSlot_Legs; } break;
		case eEquipment_IronGloves:			{ return EquipSlot_Hand; } break;
		case eEquipment_IronBoots:			{ return EquipSlot_Feet; } break;
		case eEquipment_IronShoulders:		{ return EquipSlot_Shoulders; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_SteelArmor:			{ return EquipSlot_Body; } break;
		case eEquipment_SteelPants:			{ return EquipSlot_Legs; } break;
		case eEquipment_SteelGloves:		{ return EquipSlot_Hand; } break;
		case eEquipment_SteelBoots:			{ return EquipSlot_Feet; } break;
		case eEquipment_SteelShoulders:		{ return EquipSlot_Shoulders; } break;
		// Ash
		case eEquipment_AshSword:			{ return EquipSlot_RightHand; } break;
		case eEquipment_AshHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_AshArmor:			{ return EquipSlot_Body; } break;
		case eEquipment_AshPants:			{ return EquipSlot_Legs; } break;
		case eEquipment_AshGloves:			{ return EquipSlot_Hand; } break;
		case eEquipment_AshBoots:			{ return EquipSlot_Feet; } break;
		case eEquipment_AshShoulders:		{ return EquipSlot_Shoulders; } break;
		// Bone
		case eEquipment_BoneSword:			{ return EquipSlot_RightHand; } break;
		case eEquipment_BoneHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_BoneArmor:			{ return EquipSlot_Body; } break;
		case eEquipment_BonePants:			{ return EquipSlot_Legs; } break;
		case eEquipment_BoneGloves:			{ return EquipSlot_Hand; } break;
		case eEquipment_BoneBoots:			{ return EquipSlot_Feet; } break;
		case eEquipment_BoneShoulders:		{ return EquipSlot_Shoulders; } break;
		// Ice
		case eEquipment_IceHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_IceArmor:			{ return EquipSlot_Body; } break;
		case eEquipment_IcePants:			{ return EquipSlot_Legs; } break;
		case eEquipment_IceGloves:			{ return EquipSlot_Hand; } break;
		case eEquipment_IceBoots:			{ return EquipSlot_Feet; } break;
		case eEquipment_IceShoulders:		{ return EquipSlot_Shoulders; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return EquipSlot_Head; } break;
		case eEquipment_SpikeArmor:			{ return EquipSlot_Body; } break;
		case eEquipment_SpikePants:			{ return EquipSlot_Legs; } break;
		case eEquipment_SpikeGloves:		{ return EquipSlot_Hand; } break;
		case eEquipment_SpikeBoots:			{ return EquipSlot_Feet; } break;
		case eEquipment_SpikeShoulders:		{ return EquipSlot_Shoulders; } break;
	}

	cout << "Warning: Reached end of GetEquipSlotForEquipment() without finding type - " << type << ".\n";

	return EquipSlot_NoSlot;
}

ItemQuality GetItemQualityForEquipment(eEquipment type)
{
	switch (type)
	{
		case eEquipment_None:				{ return ItemQuality_Common; } break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ return ItemQuality_Common; } break;
		case eEquipment_Torch:				{ return ItemQuality_Common; } break;
		case eEquipment_Hammer:				{ return ItemQuality_Common; } break;
		case eEquipment_MageStaff:			{ return ItemQuality_Common; } break;
		case eEquipment_NecroStaff:			{ return ItemQuality_Common; } break;
		case eEquipment_PriestStaff:		{ return ItemQuality_Common; } break;
		case eEquipment_DruidStaff:			{ return ItemQuality_Common; } break;
		case eEquipment_2HandedSword:		{ return ItemQuality_Common; } break;
		case eEquipment_Boomerang:			{ return ItemQuality_Common; } break;
		case eEquipment_Bomb:				{ return ItemQuality_Common; } break;
		case eEquipment_KnifeLeft:			{ return ItemQuality_Common; } break;
		case eEquipment_KnifeRight:			{ return ItemQuality_Common; } break;
		case eEquipment_FireballHandLeft:	{ return ItemQuality_Common; } break;
		case eEquipment_FireballHandRight:	{ return ItemQuality_Common; } break;
		case eEquipment_Mace:				{ return ItemQuality_Magical; } break;
		case eEquipment_Sickle:				{ return ItemQuality_Magical; } break;
		case eEquipment_DragonBow:			{ return ItemQuality_Rare; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ return ItemQuality_Uncommon; } break;
		case eEquipment_NormalBoots:		{ return ItemQuality_Uncommon; } break;
		case eEquipment_NormalGloves:		{ return ItemQuality_Uncommon; } break;
		case eEquipment_NormalShoulders:	{ return ItemQuality_Uncommon; } break;
		case eEquipment_RocketBoots:		{ return ItemQuality_Uncommon; } break;
		case eEquipment_RegrowthBoots:		{ return ItemQuality_Uncommon; } break;
		// Wood
		case eEquipment_WoodenSword:		{ return ItemQuality_Common; } break;
		case eEquipment_WoodenShield:		{ return ItemQuality_Common; } break;
		case eEquipment_WoodenBow:			{ return ItemQuality_Common; } break;
		case eEquipment_WoodenHelm:			{ return ItemQuality_Common; } break;
		case eEquipment_WoodenArmor:		{ return ItemQuality_Common; } break;
		case eEquipment_WoodenPants:		{ return ItemQuality_Common; } break;
		case eEquipment_WoodenGloves:		{ return ItemQuality_Common; } break;
		case eEquipment_WoodenBoots:		{ return ItemQuality_Common; } break;
		case eEquipment_WoodenShoulders:	{ return ItemQuality_Common; } break;
		// Iron
		case eEquipment_IronSword:			{ return ItemQuality_Common; } break;
		case eEquipment_IronShield:			{ return ItemQuality_Common; } break;
		case eEquipment_IronHelm:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_IronArmor:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_IronPants:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_IronGloves:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_IronBoots:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_IronShoulders:		{ return ItemQuality_Uncommon; } break;
		// Steel
		case eEquipment_SteelHelm:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_SteelArmor:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_SteelPants:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_SteelGloves:		{ return ItemQuality_Uncommon; } break;
		case eEquipment_SteelBoots:			{ return ItemQuality_Uncommon; } break;
		case eEquipment_SteelShoulders:		{ return ItemQuality_Uncommon; } break;
		// Ash
		case eEquipment_AshSword:			{ return ItemQuality_Epic; } break;
		case eEquipment_AshHelm:			{ return ItemQuality_Rare; } break;
		case eEquipment_AshArmor:			{ return ItemQuality_Rare; } break;
		case eEquipment_AshPants:			{ return ItemQuality_Rare; } break;
		case eEquipment_AshGloves:			{ return ItemQuality_Rare; } break;
		case eEquipment_AshBoots:			{ return ItemQuality_Rare; } break;
		case eEquipment_AshShoulders:		{ return ItemQuality_Rare; } break;
		// Bone
		case eEquipment_BoneSword:			{ return ItemQuality_Rare; } break;
		case eEquipment_BoneHelm:			{ return ItemQuality_Rare; } break;
		case eEquipment_BoneArmor:			{ return ItemQuality_Rare; } break;
		case eEquipment_BonePants:			{ return ItemQuality_Rare; } break;
		case eEquipment_BoneGloves:			{ return ItemQuality_Rare; } break;
		case eEquipment_BoneBoots:			{ return ItemQuality_Rare; } break;
		case eEquipment_BoneShoulders:		{ return ItemQuality_Rare; } break;
		// Ice
		case eEquipment_IceHelm:			{ return ItemQuality_Rare; } break;
		case eEquipment_IceArmor:			{ return ItemQuality_Rare; } break;
		case eEquipment_IcePants:			{ return ItemQuality_Rare; } break;
		case eEquipment_IceGloves:			{ return ItemQuality_Rare; } break;
		case eEquipment_IceBoots:			{ return ItemQuality_Rare; } break;
		case eEquipment_IceShoulders:		{ return ItemQuality_Rare; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ return ItemQuality_Epic; } break;
		case eEquipment_SpikeArmor:			{ return ItemQuality_Epic; } break;
		case eEquipment_SpikePants:			{ return ItemQuality_Epic; } break;
		case eEquipment_SpikeGloves:		{ return ItemQuality_Epic; } break;
		case eEquipment_SpikeBoots:			{ return ItemQuality_Epic; } break;
		case eEquipment_SpikeShoulders:		{ return ItemQuality_Epic; } break;
	}

	cout << "Warning: Reached end of GetItemQualityForEquipment() without finding type - " << type << ".\n";

	return ItemQuality_Common;
}

void GetItemSidesForEquipment(eEquipment type, bool *left, bool *right)
{
	switch (type)
	{
		case eEquipment_None:				{ *left = false; *right = false; return;} break;
		// Weapons
		case eEquipment_NormalPickaxe:		{ *left = false; *right = true; return; } break;
		case eEquipment_Torch:				{ *left = true; *right = false; return; } break;
		case eEquipment_Hammer:				{ *left = false; *right = true; return; } break;
		case eEquipment_MageStaff:			{ *left = true; *right = true; return; } break;
		case eEquipment_NecroStaff:			{ *left = true; *right = true; return; } break;
		case eEquipment_PriestStaff:		{ *left = true; *right = true; return; } break;
		case eEquipment_DruidStaff:			{ *left = true; *right = true; return; } break;
		case eEquipment_2HandedSword:		{ *left = true; *right = true; return; } break;
		case eEquipment_Boomerang:			{ *left = false; *right = true; return; } break;
		case eEquipment_Bomb:				{ *left = false; *right = true; return; } break;
		case eEquipment_KnifeLeft:			{ *left = true; *right = false; return; } break;
		case eEquipment_KnifeRight:			{ *left = false; *right = true; return; } break;
		case eEquipment_FireballHandLeft:	{ *left = true; *right = false; return; } break;
		case eEquipment_FireballHandRight:	{ *left = false; *right = true; return; } break;
		case eEquipment_Mace:				{ *left = false; *right = true; return; } break;
		case eEquipment_Sickle:				{ *left = false; *right = true; return; } break;
		case eEquipment_DragonBow:			{ *left = true; *right = true; return; } break;
		// Equipment
		case eEquipment_BlacksmithGloves:	{ *left = true; *right = true; return; } break;
		case eEquipment_NormalBoots:		{ *left = true; *right = true; return; } break;
		case eEquipment_NormalGloves:		{ *left = true; *right = true; return; } break;
		case eEquipment_NormalShoulders:	{ *left = true; *right = true; return; } break;
		case eEquipment_RocketBoots:		{ *left = true; *right = true; return; } break;
		case eEquipment_RegrowthBoots:		{ *left = true; *right = true; return; } break;
		// Wood
		case eEquipment_WoodenSword:		{ *left = false; *right = true; return; } break;
		case eEquipment_WoodenShield:		{ *left = true; *right = false; return; } break;
		case eEquipment_WoodenBow:			{ *left = true; *right = true; return; } break;
		case eEquipment_WoodenHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_WoodenArmor:		{ *left = false; *right = false; return; } break;
		case eEquipment_WoodenPants:		{ *left = false; *right = false; return; } break;
		case eEquipment_WoodenGloves:		{ *left = true; *right = true; return; } break;
		case eEquipment_WoodenBoots:		{ *left = true; *right = true; return; } break;
		case eEquipment_WoodenShoulders:	{ *left = true; *right = true; return; } break;
		// Iron
		case eEquipment_IronSword:			{ *left = false; *right = true; return; } break;
		case eEquipment_IronShield:			{ *left = true; *right = false; return; } break;
		case eEquipment_IronHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_IronArmor:			{ *left = false; *right = false; return; } break;
		case eEquipment_IronPants:			{ *left = false; *right = false; return; } break;
		case eEquipment_IronGloves:			{ *left = true; *right = true; return; } break;
		case eEquipment_IronBoots:			{ *left = true; *right = true; return; } break;
		case eEquipment_IronShoulders:		{ *left = true; *right = true; return; } break;
		// Steel
		case eEquipment_SteelHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_SteelArmor:			{ *left = false; *right = false; return; } break;
		case eEquipment_SteelPants:			{ *left = false; *right = false; return; } break;
		case eEquipment_SteelGloves:		{ *left = true; *right = true; return; } break;
		case eEquipment_SteelBoots:			{ *left = true; *right = true; return; } break;
		case eEquipment_SteelShoulders:		{ *left = true; *right = true; return; } break;
		// Ash
		case eEquipment_AshSword:			{ *left = false; *right = true; return; } break;
		case eEquipment_AshHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_AshArmor:			{ *left = false; *right = false; return; } break;
		case eEquipment_AshPants:			{ *left = false; *right = false; return; } break;
		case eEquipment_AshGloves:			{ *left = true; *right = true; return; } break;
		case eEquipment_AshBoots:			{ *left = true; *right = true; return; } break;
		case eEquipment_AshShoulders:		{ *left = true; *right = true; return; } break;
		// Bone
		case eEquipment_BoneSword:			{ *left = false; *right = true; return; } break;
		case eEquipment_BoneHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_BoneArmor:			{ *left = false; *right = false; return; } break;
		case eEquipment_BonePants:			{ *left = false; *right = false; return; } break;
		case eEquipment_BoneGloves:			{ *left = true; *right = true; return; } break;
		case eEquipment_BoneBoots:			{ *left = true; *right = true; return; } break;
		case eEquipment_BoneShoulders:		{ *left = true; *right = true; return; } break;
		// Ice
		case eEquipment_IceHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_IceArmor:			{ *left = false; *right = false; return; } break;
		case eEquipment_IcePants:			{ *left = false; *right = false; return; } break;
		case eEquipment_IceGloves:			{ *left = true; *right = true; return; } break;
		case eEquipment_IceBoots:			{ *left = true; *right = true; return; } break;
		case eEquipment_IceShoulders:		{ *left = true; *right = true; return; } break;
		// Spike
		case eEquipment_SpikeHelm:			{ *left = false; *right = false; return; } break;
		case eEquipment_SpikeArmor:			{ *left = false; *right = false; return; } break;
		case eEquipment_SpikePants:			{ *left = false; *right = false; return; } break;
		case eEquipment_SpikeGloves:		{ *left = true; *right = true; return; } break;
		case eEquipment_SpikeBoots:			{ *left = true; *right = true; return; } break;
		case eEquipment_SpikeShoulders:		{ *left = true; *right = true; return; } break;
	}

	cout << "Warning: Reached end of GetItemSidesForEquipment() without finding type - " << type << ".\n";
	*left = false;
	*right = false;
}

void AddStatsModifiersForType(eEquipment type, InventoryItem* pItem)
{
	if (type == eEquipment_MageStaff) { pItem->AddStatAttribute(AttributeType_Intelligence, 5); }
	if (type == eEquipment_NecroStaff) { pItem->AddStatAttribute(AttributeType_Intelligence, 4); }
	if (type == eEquipment_PriestStaff) { pItem->AddStatAttribute(AttributeType_Intelligence, 6); }
	if (type == eEquipment_DruidStaff) { pItem->AddStatAttribute(AttributeType_Intelligence, 3); }

	if (type == eEquipment_WoodenSword) { pItem->AddStatAttribute(AttributeType_Strength, 2); }
	if (type == eEquipment_WoodenShield) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_WoodenBow) { pItem->AddStatAttribute(AttributeType_Dexterity, 1); }
	if (type == eEquipment_WoodenHelm) { pItem->AddStatAttribute(AttributeType_Armor, 1); }
	if (type == eEquipment_WoodenArmor) { pItem->AddStatAttribute(AttributeType_Armor, 1); }
	if (type == eEquipment_WoodenPants) { pItem->AddStatAttribute(AttributeType_Armor, 1); }
	if (type == eEquipment_WoodenGloves) { pItem->AddStatAttribute(AttributeType_Armor, 1); }
	if (type == eEquipment_WoodenBoots) { pItem->AddStatAttribute(AttributeType_Armor, 1); }
	if (type == eEquipment_WoodenShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 1); }

	if (type == eEquipment_IronSword) { pItem->AddStatAttribute(AttributeType_Strength, 2); }
	if (type == eEquipment_IronShield) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_IronHelm) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_IronArmor) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_IronPants) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_IronGloves) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_IronBoots) { pItem->AddStatAttribute(AttributeType_Armor, 2); }
	if (type == eEquipment_IronShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 2); }

	if (type == eEquipment_SteelHelm) { pItem->AddStatAttribute(AttributeType_Armor, 3); }
	if (type == eEquipment_SteelArmor) { pItem->AddStatAttribute(AttributeType_Armor, 3); }
	if (type == eEquipment_SteelPants) { pItem->AddStatAttribute(AttributeType_Armor, 3); }
	if (type == eEquipment_SteelGloves) { pItem->AddStatAttribute(AttributeType_Armor, 3); }
	if (type == eEquipment_SteelBoots) { pItem->AddStatAttribute(AttributeType_Armor, 3); }
	if (type == eEquipment_SteelShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 3); }

	if (type == eEquipment_AshHelm) { pItem->AddStatAttribute(AttributeType_Armor, 4); }
	if (type == eEquipment_AshArmor) { pItem->AddStatAttribute(AttributeType_Armor, 4); }
	if (type == eEquipment_AshPants) { pItem->AddStatAttribute(AttributeType_Armor, 4); }
	if (type == eEquipment_AshGloves) { pItem->AddStatAttribute(AttributeType_Armor, 4); }
	if (type == eEquipment_AshBoots) { pItem->AddStatAttribute(AttributeType_Armor, 4); }
	if (type == eEquipment_AshShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 4); }

	if (type == eEquipment_BoneHelm) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_BoneArmor) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_BonePants) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_BoneGloves) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_BoneBoots) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_BoneShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 5); }

	if (type == eEquipment_IceHelm) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_IceArmor) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_IcePants) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_IceGloves) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_IceBoots) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_IceShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 5); }

	if (type == eEquipment_SpikeHelm) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_SpikeArmor) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_SpikePants) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_SpikeGloves) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_SpikeBoots) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
	if (type == eEquipment_SpikeShoulders) { pItem->AddStatAttribute(AttributeType_Armor, 5); }
}
