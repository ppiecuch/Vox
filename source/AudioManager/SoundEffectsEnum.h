// ******************************************************************************
// Filename:    SoundEffectsEnum.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   An enum list of all of the sound effects in the game.
//
// Revision History:
//   Initial Revision - 13/06/16
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

enum eSoundEffect
{
	eSoundEffect_None = 0,

	eSoundEffect_FootStep01,
	eSoundEffect_FootStep02,
	eSoundEffect_FootStep03,
	eSoundEffect_FootStep04,
	eSoundEffect_JumpLand,

	eSoundEffect_EquipCloth,
	eSoundEffect_EquipSword,
	eSoundEffect_EquipMove,

	eSoundEffect_ChestOpen,

	eSoundEffect_BowDraw,
	eSoundEffect_ArrowRelease,
	eSoundEffect_FireballCast,
	
	eSoundEffect_MimicJump,
	eSoundEffect_MimicDie,

	eSoundEffect_NUM,
};

extern string g_soundEffectFilenames[eSoundEffect_NUM];