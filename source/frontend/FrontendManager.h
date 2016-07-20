// ******************************************************************************
// Filename:    FrontendManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//   A manager class to contain all the common functionality for front-end pages
//   and GUI graphics.
//
// Revision History:
//   Initial Revision - 01/11/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#pragma once

#include "FrontendPage.h"
#include "FrontendScreens.h"
#include "../NPC/NPCManager.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/camera.h"
#include "../gui/icon.h"
#include "../gui/checkbox.h"
#include "../gui/optionbox.h"
#include "../gui/scrollbar.h"
#include "../gui/slider.h"
#include "../gui/pulldownmenu.h"
#include "../gui/button.h"


enum ButtonSize
{
	ButtonSize_85x25 = 0,
	ButtonSize_65x25,
	ButtonSize_110x47,
	ButtonSize_225x75,

	ButtonSize_NUM,
};

typedef std::vector<FrontendPage*> FrontendPageList;

class FrontendManager
{
public:
	/* Public methods */
	FrontendManager(Renderer* pRenderer, OpenGLGUI* pGUI);
	~FrontendManager();

	// Windows dimensions
	void SetWindowDimensions(int width, int height);
	int GetWindowWidth();
	int GetWindowHeight();

	// Camera
	void SetCamera(Camera* pCamera);

	// Skinning the GUI
	void SkinGUI();
	void UnSkinGUI();

	// Frontend screen
	eFrontendScreen GetFrontendScreen();
	void SetFrontendScreen(eFrontendScreen screen);

	// Load the icon graphics based on a theme
	void LoadCommonGraphics(string themeName);

	// Setup icons for components
	void SetCheckboxIcons(CheckBox* pCheckBox);
	void SetOptionboxIcons(OptionBox* pOptionBox);
	void SetScrollbarIcons(ScrollBar* pScrollbar);
	void SetSliderIcons(Slider* pSlider);
	void SetPulldownMenuIcons(PulldownMenu* pPulldownMenu);
	void SetButtonIcons(Button* pButton, ButtonSize size);
	void SetTabIcons(OptionBox* pTab);

	// Fonts
	unsigned int GetFrontendFont_Large() { return m_frontendFont_Large; }
	unsigned int GetFrontendFont_Medium() { return m_frontendFont_Medium; }
	unsigned int GetFrontendFont_Small() { return m_frontendFont_Small; }
	unsigned int GetFrontendFont_14() { return m_frontendFont_14; }
	unsigned int GetFrontendFont_14_Outline() { return m_frontendFont_14_Outline; }
	unsigned int GetFrontendFont_18() { return m_frontendFont_18; }
	unsigned int GetFrontendFont_18_Outline() { return m_frontendFont_18_Outline; }
	unsigned int GetFrontendFont_20() { return m_frontendFont_20; }
	unsigned int GetFrontendFont_20_Outline() { return m_frontendFont_20_Outline; }
	unsigned int GetFrontendFont_22() { return m_frontendFont_22; }
	unsigned int GetFrontendFont_22_Outline() { return m_frontendFont_22_Outline; }
	unsigned int GetFrontendFont_25() { return m_frontendFont_25; }
	unsigned int GetFrontendFont_25_Outline() { return m_frontendFont_25_Outline; }
	unsigned int GetFrontendFont_30() { return m_frontendFont_30; }
	unsigned int GetFrontendFont_30_Outline() { return m_frontendFont_30_Outline; }
	unsigned int GetFrontendFont_35() { return m_frontendFont_35; }
	unsigned int GetFrontendFont_35_Outline() { return m_frontendFont_35_Outline; }
	unsigned int GetFrontendFont_40() { return m_frontendFont_40; }
	unsigned int GetFrontendFont_40_Outline() { return m_frontendFont_40_Outline; }
	unsigned int GetFrontendFont_50() { return m_frontendFont_50; }
	unsigned int GetFrontendFont_50_Outline() { return m_frontendFont_50_Outline; }
	unsigned int GetFrontendFont_80() { return m_frontendFont_80; }
	unsigned int GetFrontendFont_80_Outline() { return m_frontendFont_80_Outline; }

	// Text effects fonts
	unsigned int GetTextEffectFont() { return m_textEffectFontNormal; }
	unsigned int GetTextEffectOutlineFont() { return m_textEffectFontOutline; }

	// Label colours
	Colour GetNormalFontColour() { return m_normalColour; }
	Colour GetHoverFontColour() { return m_hoverColour; }
	Colour GetPressedFontColour() { return m_pressedColour; }
	Colour GetDisabledFontColour() { return m_disabledColour; }

	// Checkbox
	Icon* GetCheckboxIcon() { return m_pCheckboxIcon; };
	Icon* GetCheckboxIconHover() { return m_pCheckboxIconHover; };
	Icon* GetCheckboxIconPressed() { return m_pCheckboxIconPressed; };
	Icon* GetCheckboxIconDisabled() { return m_pCheckboxIconDisabled; };
	Icon* GetCheckboxIconToggled() { return m_pCheckboxIconToggled; };
	Icon* GetCheckboxIconToggledHover() { return m_pCheckboxIconToggledHover; };
	Icon* GetCheckboxIconToggledPressed() { return m_pCheckboxIconToggledPressed; };
	Icon* GetCheckboxIconToggledDisabled() { return m_pCheckboxIconToggledDisabled; };

	// Optionbox
	Icon* GetOptionboxIcon() { return m_pOptionboxIcon; };
	Icon* GetOptionboxIconHover() { return m_pOptionboxIconHover; };
	Icon* GetOptionboxIconPressed() { return m_pOptionboxIconPressed; };
	Icon* GetOptionboxIconDisabled() { return m_pOptionboxIconDisabled; };
	Icon* GetOptionboxIconToggled() { return m_pOptionboxIconToggled; };
	Icon* GetOptionboxIconToggledHover() { return m_pOptionboxIconToggledHover; };
	Icon* GetOptionboxIconToggledPressed() { return m_pOptionboxIconToggledPressed; };
	Icon* GetOptionboxIconToggledDisabled() { return m_pOptionboxIconToggledDisabled; };

	// Scrollbar
	Icon* GetScrollbarArrowDownIcon() { return m_pScrollbarArrowDownIcon; };
	Icon* GetScrollbarArrowDownHoverIcon() { return m_pScrollbarArrowDownIconHover; };
	Icon* GetScrollbarArrowDownPressedIcon() { return m_pScrollbarArrowDownIconPressed; };
	Icon* GetScrollbarArrowDownDisabledIcon() { return m_pScrollbarArrowDownIconDisabled; };
	Icon* GetScrollbarArrowUpIcon() { return m_pScrollbarArrowUpIcon; };
	Icon* GetScrollbarArrowUpHoverIcon() { return m_pScrollbarArrowUpIconHover; };
	Icon* GetScrollbarArrowUpPressedIcon() { return m_pScrollbarArrowUpIconPressed; };
	Icon* GetScrollbarArrowUpDisabledIcon() { return m_pScrollbarArrowUpIconDisabled; };
	Icon* GetScrollbarBackgroundIcon() { return m_pScrollbarBackgroundIcon; };
	Icon* GetScrollbarBackgroundIconDisabled() { return m_pScrollbarBackgroundIconDisabled; };
	Icon* GetScrollbarIcon() { return m_pScrollbarIcon; };
	Icon* GetScrollbarHoverIcon() { return m_pScrollbarIconHover; };
	Icon* GetScrollbarPressedIcon() { return m_pScrollbarIconPressed; };
	Icon* GetScrollbarDisabledIcon() { return m_pScrollbarIconDisabled; };

	// Slider
	Icon* GetSliderIconDefault() { return m_pSliderIconDefault; };
	Icon* GetSliderIconHover() { return m_pSliderIconHover; };
	Icon* GetSliderIconDrag() { return m_pSliderIconDrag; };
	Icon* GetSliderIconDefaultBlank() { return m_pSliderIconDefaultBlank; };
	Icon* GetSliderIconHoverBlank() { return m_pSliderIconHoverBlank; };
	Icon* GetSliderIconDragBlank() { return m_pSliderIconDragBlank; };
	Icon* GetSliderIconIncrementButtonDefault() { return m_pSliderIncrementIcon; };
	Icon* GetSliderIconIncrementButtonHover() { return m_pSliderIncrementIconHover; };
	Icon* GetSliderIconIncrementButtonPressed() { return m_pSliderIncrementIconPressed; };
	Icon* GetSliderIconIncrementButtonDisabled() { return m_pSliderIncrementIconDisabled; };
	Icon* GetSliderIconDecrementButtonDefault() { return m_pSliderDecrementIcon; };
	Icon* GetSliderIconDecrementButtonHover() { return m_pSliderDecrementIconHover; };
	Icon* GetSliderIconDecrementButtonPressed() { return m_pSliderDecrementIconPressed; };
	Icon* GetSliderIconDecrementButtonDisabled() { return m_pSliderDecrementIconDisabled; };

	// Button
	Icon* GetButtonIcon(ButtonSize size) { return m_pButtonIcon[size]; };
	Icon* GetButtonIconHover(ButtonSize size) { return m_pButtonIconHover[size]; };
	Icon* GetButtonIconPressed(ButtonSize size) { return m_pButtonIconPressed[size]; };
	Icon* GetButtonIconDisabled(ButtonSize size) { return m_pButtonIconDisabled[size]; };

	// Close button
	Icon* GetCloseExitButtonIcon() { return m_pCloseExitButtonIcon; }
	Icon* GetCloseExitButtonIcon_Hover() { return m_pCloseExitButtonIcon_Hover; }
	Icon* GetCloseExitButtonIcon_Pressed() { return m_pCloseExitButtonIcon_Pressed; }

	// Rotate buttons
	Icon* GetRightRotateArrow() { return m_pArrowRight_Icon; }
	Icon* GetRightRotateArrow_Hover() { return m_pArrowRight_Icon_Hover; }
	Icon* GetRightRotateArrow_Pressed() { return m_pArrowRight_Icon_Pressed; }
	Icon* GetLeftRotateArrow() { return m_pArrowLeft_Icon; }
	Icon* GetLeftRotateArrow_Hover() { return m_pArrowLeft_Icon_Hover; }
	Icon* GetLeftRotateArrow_Pressed() { return m_pArrowLeft_Icon_Pressed; }

	// Tab Options
	Icon* GetTab75OptionIcon() { return m_pTab75OptionIcon; }
	Icon* GetTab75OptionIcon_Hover() { return m_pTab75OptionIcon_Hover; }
	Icon* GetTab75OptionIcon_Pressed() { return m_pTab75OptionIcon_Pressed; }
	Icon* GetTab75OptionIcon_Toggled() { return m_pTab75OptionIcon_Toggled; }
	Icon* GetTab75OptionIcon_Toggled_Hover() { return m_pTab75OptionIcon_Toggled_Hover; }
	Icon* GetTab75OptionIcon_Toggled_Pressed() { return m_pTab75OptionIcon_Toggled_Pressed; }

	// Common, shared frontend page params
	float GetCameraOrbitTimer();
	void SetCameraOrbitTimer(float orbit);

	// Frontend functionality
	void SetOptionsReturnToMainMenu(bool mainMenu);
	void SetModsMenuReturnToMainMenu(bool mainMenu);
	void SetHoverNPC(NPC* pHoverNPC);
	void SetSelectedNPC(NPC* pSelectedNPC);
	void SetCharacterSubSelection(string subSelection);
	void GotoNextCreditScreen();
	void DisableShadowOption();

	// Constants
	float GetToolTipAppearDelay();

	// Updating
	void Update(float dt);
	void UpdateFrontEndCamera(float dt);

	// Rendering
	void Render();
	void Render2D();
	void RenderDebug();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	Renderer* m_pRenderer;
	OpenGLGUI* m_pGUI;

	// Window params
	int m_windowWidth;
	int m_windowHeight;

	// Camera
	Camera* m_pCamera;

	// Current frontend screen
	eFrontendScreen m_currentScreen;
	FrontendPage* m_currentPage;

	// Pages
	FrontendPageList m_vpFrontendPages;

	// Fonts
	unsigned int m_frontendFont_Large;
	unsigned int m_frontendFont_Medium;
	unsigned int m_frontendFont_Small;
	unsigned int m_frontendFont_14;
	unsigned int m_frontendFont_14_Outline;
	unsigned int m_frontendFont_18;
	unsigned int m_frontendFont_18_Outline;
	unsigned int m_frontendFont_20;
	unsigned int m_frontendFont_20_Outline;
	unsigned int m_frontendFont_22;
	unsigned int m_frontendFont_22_Outline;
	unsigned int m_frontendFont_25;
	unsigned int m_frontendFont_25_Outline;
	unsigned int m_frontendFont_30;
	unsigned int m_frontendFont_30_Outline;
	unsigned int m_frontendFont_35;
	unsigned int m_frontendFont_35_Outline;
	unsigned int m_frontendFont_40;
	unsigned int m_frontendFont_40_Outline;
	unsigned int m_frontendFont_50;
	unsigned int m_frontendFont_50_Outline;
	unsigned int m_frontendFont_80;
	unsigned int m_frontendFont_80_Outline;

	// Text effects fonts
	unsigned int m_textEffectFontNormal;
	unsigned int m_textEffectFontOutline;

	// Label colours
	Colour m_normalColour;
	Colour m_hoverColour;
	Colour m_pressedColour;
	Colour m_disabledColour;

	// Checkbox
	Icon* m_pCheckboxIcon;
	Icon* m_pCheckboxIconHover;
	Icon* m_pCheckboxIconPressed;
	Icon* m_pCheckboxIconDisabled;
	Icon* m_pCheckboxIconToggled;
	Icon* m_pCheckboxIconToggledHover;
	Icon* m_pCheckboxIconToggledPressed;
	Icon* m_pCheckboxIconToggledDisabled;

	// Optionbox
	Icon* m_pOptionboxIcon;
	Icon* m_pOptionboxIconHover;
	Icon* m_pOptionboxIconPressed;
	Icon* m_pOptionboxIconDisabled;
	Icon* m_pOptionboxIconToggled;
	Icon* m_pOptionboxIconToggledHover;
	Icon* m_pOptionboxIconToggledPressed;
	Icon* m_pOptionboxIconToggledDisabled;

	// Scrollbar
	Icon* m_pScrollbarArrowDownIcon;
	Icon* m_pScrollbarArrowDownIconHover;
	Icon* m_pScrollbarArrowDownIconPressed;
	Icon* m_pScrollbarArrowDownIconDisabled;
	Icon* m_pScrollbarArrowUpIcon;
	Icon* m_pScrollbarArrowUpIconHover;
	Icon* m_pScrollbarArrowUpIconPressed;
	Icon* m_pScrollbarArrowUpIconDisabled;
	Icon* m_pScrollbarBackgroundIcon;
	Icon* m_pScrollbarBackgroundIconDisabled;
	Icon* m_pScrollbarIcon;
	Icon* m_pScrollbarIconHover;
	Icon* m_pScrollbarIconPressed;
	Icon* m_pScrollbarIconDisabled;

	// Slider
	Icon* m_pSliderIconDefault;
	Icon* m_pSliderIconHover;
	Icon* m_pSliderIconDrag;
	Icon* m_pSliderIconDefaultBlank;
	Icon* m_pSliderIconHoverBlank;
	Icon* m_pSliderIconDragBlank;
	Icon* m_pSliderIncrementIcon;
	Icon* m_pSliderIncrementIconHover;
	Icon* m_pSliderIncrementIconPressed;
	Icon* m_pSliderIncrementIconDisabled;
	Icon* m_pSliderDecrementIcon;
	Icon* m_pSliderDecrementIconHover;
	Icon* m_pSliderDecrementIconPressed;
	Icon* m_pSliderDecrementIconDisabled;

	// Buttons
	Icon** m_pButtonIcon;
	Icon** m_pButtonIconHover;
	Icon** m_pButtonIconPressed;
	Icon** m_pButtonIconDisabled;

	// Close button
	Icon* m_pCloseExitButtonIcon;
	Icon* m_pCloseExitButtonIcon_Hover;
	Icon* m_pCloseExitButtonIcon_Pressed;

	// Rotate buttons
	Icon* m_pArrowLeft_Icon;
	Icon* m_pArrowLeft_Icon_Hover;
	Icon* m_pArrowLeft_Icon_Pressed;
	Icon* m_pArrowRight_Icon;
	Icon* m_pArrowRight_Icon_Hover;
	Icon* m_pArrowRight_Icon_Pressed;

	// Tab Options
	Icon* m_pTab75OptionIcon;
	Icon* m_pTab75OptionIcon_Hover;
	Icon* m_pTab75OptionIcon_Pressed;
	Icon* m_pTab75OptionIcon_Toggled;
	Icon* m_pTab75OptionIcon_Toggled_Hover;
	Icon* m_pTab75OptionIcon_Toggled_Pressed;

	// Common, shared frontend page params
	float m_cameraOrbitTimer;

	// Constants
	float m_tooltipAppearDelay;
};
