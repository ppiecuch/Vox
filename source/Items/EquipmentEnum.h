// ******************************************************************************
// Filename:    EquipmentEnum.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   An enum list of all of the equipment in the game, used for equipment
//   tracking and equipment specific functionality.
//
// Revision History:
//   Initial Revision - 12/04/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

enum eEquipment
{
	eEquipment_None = 0,

	// Weapons
	eEquipment_NormalPickaxe,
	eEquipment_Torch,
	eEquipment_Hammer,
	eEquipment_MageStaff,
	eEquipment_NecroStaff,
	eEquipment_PriestStaff,
	eEquipment_DruidStaff,
	eEquipment_2HandedSword,
	eEquipment_Boomerang,
	eEquipment_Bomb,
	eEquipment_KnifeLeft,
	eEquipment_KnifeRight,
	eEquipment_FireballHandLeft,
	eEquipment_FireballHandRight,
	eEquipment_Mace,
	eEquipment_Sickle,
	eEquipment_DragonBow,

	// Equipment
	eEquipment_BlacksmithGloves,
	eEquipment_NormalBoots,
	eEquipment_NormalGloves,
	eEquipment_NormalShoulders,
	eEquipment_RocketBoots,
	eEquipment_RegrowthBoots,

	// Wooden
	eEquipment_WoodenSword,
	eEquipment_WoodenShield,
	eEquipment_WoodenBow,
	eEquipment_WoodenHelm,
	eEquipment_WoodenArmor,
	eEquipment_WoodenPants,
	eEquipment_WoodenGloves,
	eEquipment_WoodenBoots,
	eEquipment_WoodenShoulders,

	// Copper

	// Iron
	eEquipment_IronSword,
	eEquipment_IronShield,
	eEquipment_IronHelm,
	eEquipment_IronArmor,
	eEquipment_IronPants,
	eEquipment_IronGloves,
	eEquipment_IronBoots,
	eEquipment_IronShoulders,

	// Steel
	eEquipment_SteelHelm,
	eEquipment_SteelArmor,
	eEquipment_SteelPants,
	eEquipment_SteelGloves,
	eEquipment_SteelBoots,
	eEquipment_SteelShoulders,

	// Silver

	// Gold

	// Ash
	eEquipment_AshSword,
	eEquipment_AshHelm,
	eEquipment_AshArmor,
	eEquipment_AshPants,
	eEquipment_AshGloves,
	eEquipment_AshBoots,
	eEquipment_AshShoulders,

	// Bone
	eEquipment_BoneSword,
	eEquipment_BoneHelm,
	eEquipment_BoneArmor,
	eEquipment_BonePants,
	eEquipment_BoneGloves,
	eEquipment_BoneBoots,
	eEquipment_BoneShoulders,

	// Ice
	eEquipment_IceHelm,
	eEquipment_IceArmor,
	eEquipment_IcePants,
	eEquipment_IceGloves,
	eEquipment_IceBoots,
	eEquipment_IceShoulders,

	// Spike
	eEquipment_SpikeHelm,
	eEquipment_SpikeArmor,
	eEquipment_SpikePants,
	eEquipment_SpikeGloves,
	eEquipment_SpikeBoots,
	eEquipment_SpikeShoulders,

	eEquipment_NUM_EQUIPMENT,
};