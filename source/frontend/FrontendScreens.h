// ******************************************************************************
// Filename:    FrontendScreens.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   An enum list of all the different front-end screens, these correspond to
//   the front-end page classes.
//
// Revision History:
//   Initial Revision - 01/11/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#pragma once

enum eFrontendScreen
{
	FrontendScreen_None = 0,

	FrontendScreen_Intro,

	FrontendScreen_MainMenu,
	FrontendScreen_SelectCharacter,
	FrontendScreen_CreateCharacter,
	FrontendScreen_SelectWorld,
	FrontendScreen_CreateWorld,
	FrontendScreen_Credits,

	FrontendScreen_PauseMenu,
	FrontendScreen_OptionsMenu,
	FrontendScreen_ModMenu,

	FrontendScreen_QuitPopup,
};
