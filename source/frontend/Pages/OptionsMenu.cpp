// ******************************************************************************
// Filename:    OptionsMenu.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 12/10/14
//
// Copyright (c) 2005-2011, Steven Ball
// ******************************************************************************

#include "OptionsMenu.h"
#include "../../VoxGame.h"
#include "../FrontendManager.h"
#include "../../gui/openglgui.h"


OptionsMenu::OptionsMenu(Renderer* pRenderer, OpenGLGUI* pGUI, FrontendManager* pFrontPageManager, int windowWidth, int windowHeight)
	: FrontendPage(pRenderer, pGUI, pFrontPageManager, FrontendScreen_OptionsMenu, windowWidth, windowHeight)
{
	// Options Window
	m_pOptionsWindow = new GUIWindow(m_pRenderer, m_pFrontendManager->GetFrontendFont_Medium(), "Options");
	m_pOptionsWindow->AllowMoving(true);
	m_pOptionsWindow->AllowClosing(false);
	m_pOptionsWindow->AllowMinimizing(false);
	m_pOptionsWindow->AllowScrolling(false);
	m_pOptionsWindow->SetRenderTitleBar(true);
	m_pOptionsWindow->SetRenderWindowBackground(true);
	m_pOptionsWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
	m_pOptionsWindow->Hide();

	m_pTitleBarIcon = new Icon(m_pRenderer, "", 44, 44);
	m_pTitleBarIcon->SetDepth(4.0f);

	m_pOptionsWindowBackgroundIcon = new Icon(m_pRenderer, "", 600, 475);
	m_pOptionsWindowBackgroundIcon->SetDepth(1.0f);

	m_pTitleBarBackgroundIcon = new Icon(m_pRenderer, "", 86, 35);
	m_pTitleBarBackgroundIcon->SetDepth(1.0f);

	m_pCloseExitButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_30(), m_pFrontendManager->GetFrontendFont_30_Outline(), "", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pCloseExitButton->SetLabelOffset(0, 5);
	m_pCloseExitButton->SetCallBackFunction(_CloseExitPressed);
	m_pCloseExitButton->SetCallBackData(this);

	m_pOptionsWindow->SetBackgroundIcon(m_pOptionsWindowBackgroundIcon);
	m_pOptionsWindow->SetTitlebarBackgroundIcon(m_pTitleBarBackgroundIcon);

	m_pOptionsWindow->AddComponent(m_pTitleBarIcon);
	m_pOptionsWindow->AddComponent(m_pCloseExitButton);

	// Tabs
	m_pOptionsModeController = new OptionController(m_pRenderer, m_pFrontendManager->GetFrontendFont_25(), "Mode");
	m_pOptionsModeController->SetDisplayLabel(false);
	m_pOptionsModeController->SetDisplayBorder(false);

	m_pGameplayMode = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_18(), m_pFrontendManager->GetFrontendFont_18_Outline(), "Gameplay", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pGameplayMode->SetCallBackFunction(_GameplayTabPressed);
	m_pGameplayMode->SetCallBackData(this);
	m_pGameplayMode->SetDepth(2.0f);
	m_pGameplayMode->SetPressedOffset(0, -2);

	m_pGraphicsMode = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_18(), m_pFrontendManager->GetFrontendFont_18_Outline(), "Graphics", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pGraphicsMode->SetCallBackFunction(_GraphicsTabPressed);
	m_pGraphicsMode->SetCallBackData(this);
	m_pGraphicsMode->SetDepth(2.1f);
	m_pGraphicsMode->SetPressedOffset(0, -2);

	m_pSoundMode = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_18(), m_pFrontendManager->GetFrontendFont_18_Outline(), "Sound", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pSoundMode->SetCallBackFunction(_SoundTabPressed);
	m_pSoundMode->SetCallBackData(this);
	m_pSoundMode->SetDepth(2.2f);
	m_pSoundMode->SetPressedOffset(0, -2);

	m_pControlsMode = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_18(), m_pFrontendManager->GetFrontendFont_18_Outline(), "Controls", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pControlsMode->SetCallBackFunction(_ControlsTabPressed);
	m_pControlsMode->SetCallBackData(this);
	m_pControlsMode->SetDepth(2.3f);
	m_pControlsMode->SetPressedOffset(0, -2);

	m_pInterfaceMode = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_18(), m_pFrontendManager->GetFrontendFont_18_Outline(), "Interface", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pInterfaceMode->SetCallBackFunction(_InterfaceTabPressed);
	m_pInterfaceMode->SetCallBackData(this);
	m_pInterfaceMode->SetDepth(2.4f);
	m_pInterfaceMode->SetPressedOffset(0, -2);

	m_pOptionsModeController->Add(m_pGameplayMode);
	m_pOptionsModeController->Add(m_pGraphicsMode);
	m_pOptionsModeController->Add(m_pSoundMode);
	m_pOptionsModeController->Add(m_pControlsMode);
	m_pOptionsModeController->Add(m_pInterfaceMode);	
	m_pGameplayMode->SetToggled(true);

	m_pOptionsWindow->AddComponent(m_pOptionsModeController);

	// Gameplay
	m_pInvertedMouseMode = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Inverted Mouse", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pInvertedMouseMode->SetDisplayLabel(true);
	m_pInvertedMouseMode->SetDepth(2.0f);
	m_pInvertedMouseMode->SetPressedOffset(0, -2);

	m_pNormalCamOption = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Normal Cam", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pNormalCamOption->SetCallBackFunction(_SwitchToNormalCam);
	//m_pNormalCamOption->SetCallBackData(this);
	m_pNormalCamOption->SetDisplayLabel(true);
	m_pNormalCamOption->SetPressedOffset(0, -2);
	m_pFollowCamOption = new OptionBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Follow Cam", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pFollowCamOption->SetCallBackFunction(_SwitchToFollowCam);
	//m_pFollowCamOption->SetCallBackData(this);
	m_pFollowCamOption->SetDisplayLabel(true);
	m_pFollowCamOption->SetPressedOffset(0, -2);
	m_pCameraSelector = new OptionController(m_pRenderer, m_pFrontendManager->GetFrontendFont_25(), m_pFrontendManager->GetFrontendFont_25_Outline(), "Camera Mode", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pCameraSelector->SetDisplayLabel(true);
	m_pCameraSelector->SetDisplayBorder(true);
	m_pCameraSelector->SetDepth(2.0f);
	m_pCameraSelector->Add(m_pNormalCamOption);
	m_pCameraSelector->Add(m_pFollowCamOption);
	m_pNormalCamOption->SetToggled(true);

	m_pMouseSensativitySlider = new Slider(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Mouse Sensitivity", 5.0f, 100.0f, 45.0f, Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pMouseSensativitySlider->SetSliderParams(5, 10, ESliderDirection_Horizontal);
	m_pMouseSensativitySlider->SetLabelPositionOffset(0, 14);
	m_pMouseSensativitySlider->SetValuePrecision(0);
	m_pMouseSensativitySlider->SetRenderBackgroundBar(false);
	m_pMouseSensativitySlider->SetDepth(2.0f);

	m_pGamepadSensativitySlider = new Slider(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Gamepad Sensitivity", 5.0f, 100.0f, 20.0f, Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pGamepadSensativitySlider->SetSliderParams(5, 10, ESliderDirection_Horizontal);
	m_pGamepadSensativitySlider->SetLabelPositionOffset(0, 14);
	m_pGamepadSensativitySlider->SetValuePrecision(0);
	m_pGamepadSensativitySlider->SetRenderBackgroundBar(false);
	m_pGamepadSensativitySlider->SetDepth(2.0f);

	m_pSliderBackgroundIcon_MouseSensativity = new Icon(m_pRenderer, "", 207, 31);
	m_pSliderBackgroundIcon_MouseSensativity->SetDepth(1.5f);
	m_pSliderBackgroundIcon_GamepadSensativity = new Icon(m_pRenderer, "", 207, 31);
	m_pSliderBackgroundIcon_GamepadSensativity->SetDepth(1.5f);

	m_vpGameplayComponents.push_back(m_pInvertedMouseMode);
	m_vpGameplayComponents.push_back(m_pCameraSelector);
	m_vpGameplayComponents.push_back(m_pMouseSensativitySlider);
	m_vpGameplayComponents.push_back(m_pGamepadSensativitySlider);
	m_vpGameplayComponents.push_back(m_pSliderBackgroundIcon_MouseSensativity);
	m_vpGameplayComponents.push_back(m_pSliderBackgroundIcon_GamepadSensativity);

	// Graphics
	m_pShadowsCheckBox = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Shadows", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pShadowsCheckBox->SetDisplayLabel(true);
	m_pShadowsCheckBox->SetDepth(2.0f);
	m_pShadowsCheckBox->SetPressedOffset(0, -2);
	m_pFogRenderCheckBox = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Fog Rendering", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pFogRenderCheckBox->SetDisplayLabel(true);
	m_pFogRenderCheckBox->SetDepth(2.0f);
	m_pFogRenderCheckBox->SetPressedOffset(0, -2);
	m_pWaterRenderCheckBox = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Warter Rendering", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pWaterRenderCheckBox->SetDisplayLabel(true);
	m_pWaterRenderCheckBox->SetDepth(2.0f);
	m_pWaterRenderCheckBox->SetPressedOffset(0, -2);

	m_pFullscreenButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_25(), m_pFrontendManager->GetFrontendFont_25_Outline(), "Fullscreen", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pFullscreenButton->SetCallBackFunction(_ToggleFullScreenPressed);
	m_pFullscreenButton->SetCallBackData(this);
	m_pFullscreenButton->SetPressedOffset(0, -2);

	m_vpGraphicsComponents.push_back(m_pShadowsCheckBox);
	m_vpGraphicsComponents.push_back(m_pFogRenderCheckBox);
	m_vpGraphicsComponents.push_back(m_pWaterRenderCheckBox);
	m_vpGraphicsComponents.push_back(m_pFullscreenButton);

	// Sound
	m_pSoundEffects = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Sound", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pSoundEffects->SetCallBackFunction(_SoundEffectsPressed);
	//m_pSoundEffects->SetCallBackData(this);
	m_pSoundEffects->SetDisplayLabel(true);
	m_pSoundEffects->SetDepth(2.0f);
	m_pSoundEffects->SetPressedOffset(0, -2);

	m_pSoundEffectsVolume = new Slider(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "", 0.0f, 1.0f, 0.5f, Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pSoundEffectsVolume->SetSliderParams(5, 10, ESliderDirection_Horizontal);
	//m_pSoundEffectsVolume->SetVaueChangedCallBackFunction(_SoundEffectsChanged);
	//m_pSoundEffectsVolume->SetVaueChangedCallBackData(this);
	m_pSoundEffectsVolume->SetRenderBackgroundBar(false);
	m_pSoundEffectsVolume->SetDepth(2.0f);

	m_pMusic = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Music", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pMusic->SetCallBackFunction(_MusicPressed);
	//m_pMusic->SetCallBackData(this);
	m_pMusic->SetDisplayLabel(true);
	m_pMusic->SetDepth(2.0f);
	m_pMusic->SetPressedOffset(0, -2);

	m_pMusicVolume = new Slider(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "", 0.0f, 1.0f, 0.5f, Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pMusicVolume->SetSliderParams(5, 10, ESliderDirection_Horizontal);
	//m_pMusicVolume->SetVaueChangedCallBackFunction(_MusicVolumeChanged);
	//m_pMusicVolume->SetVaueChangedCallBackData(this);
	m_pMusicVolume->SetRenderBackgroundBar(false);
	m_pMusicVolume->SetDepth(2.0f);

	m_pSliderBackgroundIcon_Sound = new Icon(m_pRenderer, "", 207, 31);
	m_pSliderBackgroundIcon_Sound->SetDepth(1.5f);
	m_pSliderBackgroundIcon_Music = new Icon(m_pRenderer, "", 207, 31);
	m_pSliderBackgroundIcon_Music->SetDepth(1.5f);

	m_vpSoundComponents.push_back(m_pSoundEffects);
	m_vpSoundComponents.push_back(m_pSoundEffectsVolume);
	m_vpSoundComponents.push_back(m_pMusic);
	m_vpSoundComponents.push_back(m_pMusicVolume);
	m_vpSoundComponents.push_back(m_pSliderBackgroundIcon_Sound);
	m_vpSoundComponents.push_back(m_pSliderBackgroundIcon_Music);

	// Interface
	m_pRenderGUI = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Render HUD", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pRenderGUI->SetCallBackFunction(_RenderHUDTogglePressed);
	m_pRenderGUI->SetCallBackData(this);
	m_pRenderGUI->SetDisplayLabel(true);
	m_pRenderGUI->SetDepth(2.0f);
	m_pRenderGUI->SetPressedOffset(0, -2);

	m_pRenderCrosshair = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Render Crosshair", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pRenderCrosshair->SetCallBackFunction(_RenderCrosshairPressed);
	//m_pRenderCrosshair->SetCallBackData(this);
	m_pRenderCrosshair->SetDisplayLabel(true);
	m_pRenderCrosshair->SetDepth(2.0f);
	m_pRenderCrosshair->SetPressedOffset(0, -2);

	m_pHUDAnimations = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "HUD Animations", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pHUDAnimations->SetCallBackFunction(_HUDAnimationsPressed);
	//m_pHUDAnimations->SetCallBackData(this);
	m_pHUDAnimations->SetDisplayLabel(true);
	m_pHUDAnimations->SetDepth(2.0f);
	m_pHUDAnimations->SetPressedOffset(0, -2);

	m_pCustomCursors = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Custom Cursors", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pCustomCursors->SetCallBackFunction(_CustomCursorsTogglePressed);
	m_pCustomCursors->SetCallBackData(this);
	m_pCustomCursors->SetDisplayLabel(true);
	m_pCustomCursors->SetDepth(2.0f);
	m_pCustomCursors->SetPressedOffset(0, -2);

	m_pEquipHoverIcon = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Equip Helper Cursor", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pEquipHoverIcon->SetCallBackFunction(_HUDAnimationsPressed);
	//m_pEquipHoverIcon->SetCallBackData(this);
	m_pEquipHoverIcon->SetDisplayLabel(true);
	m_pEquipHoverIcon->SetDepth(2.0f);
	m_pEquipHoverIcon->SetPressedOffset(0, -2);

	m_pToolTipAppearDelay = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Tooltip Delay", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pToolTipAppearDelay->SetCallBackFunction(_HUDAnimationsPressed);
	//m_pToolTipAppearDelay->SetCallBackData(this);
	m_pToolTipAppearDelay->SetDisplayLabel(true);
	m_pToolTipAppearDelay->SetDepth(2.0f);
	m_pToolTipAppearDelay->SetPressedOffset(0, -2);

	m_pConfirmDeleteItem = new CheckBox(m_pRenderer, m_pFrontendManager->GetFrontendFont_20(), m_pFrontendManager->GetFrontendFont_20_Outline(), "Confirm Item Deletion", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pConfirmDeleteItem->SetCallBackFunction(_HUDAnimationsPressed);
	//m_pConfirmDeleteItem->SetCallBackData(this);
	m_pConfirmDeleteItem->SetDisplayLabel(true);
	m_pConfirmDeleteItem->SetDepth(2.0f);
	m_pConfirmDeleteItem->SetPressedOffset(0, -2);

	m_pResetGUIToDefault = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_25(), m_pFrontendManager->GetFrontendFont_25_Outline(), "Reset GUI", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pResetGUIToDefault->SetLabelOffset(0, 3);
	//m_pResetGUIToDefault->SetCallBackFunction(_ResetGUIPressed);
	//m_pResetGUIToDefault->SetCallBackData(this);
	m_pResetGUIToDefault->SetPressedOffset(0, -2);

	m_vpInterfaceComponents.push_back(m_pRenderGUI);
	m_vpInterfaceComponents.push_back(m_pRenderCrosshair);
	m_vpInterfaceComponents.push_back(m_pHUDAnimations);
	m_vpInterfaceComponents.push_back(m_pCustomCursors);
	m_vpInterfaceComponents.push_back(m_pEquipHoverIcon);
	m_vpInterfaceComponents.push_back(m_pToolTipAppearDelay);
	m_vpInterfaceComponents.push_back(m_pConfirmDeleteItem);
	m_vpInterfaceComponents.push_back(m_pResetGUIToDefault);

	// Controls

	SetWindowDimensions(m_windowWidth, m_windowHeight);

	m_initiallyUsingCustomCursors = false;

	m_returnToMainMenu = false;
}

OptionsMenu::~OptionsMenu()
{
	// Window
	delete m_pOptionsWindow;
	delete m_pTitleBarIcon;
	delete m_pTitleBarBackgroundIcon;
	delete m_pOptionsWindowBackgroundIcon;
	delete m_pCloseExitButton;

	// Tabs
	delete m_pOptionsModeController;
	delete m_pGameplayMode;
	delete m_pGraphicsMode;
	delete m_pSoundMode;
	delete m_pInterfaceMode;
	delete m_pControlsMode;

	// Gameplay
	delete m_pInvertedMouseMode;
	delete m_pNormalCamOption;
	delete m_pFollowCamOption;
	delete m_pCameraSelector;
	delete m_pMouseSensativitySlider;
	delete m_pGamepadSensativitySlider;
	delete m_pSliderBackgroundIcon_MouseSensativity;
	delete m_pSliderBackgroundIcon_GamepadSensativity;

	// Graphics
	delete m_pShadowsCheckBox;
	delete m_pFogRenderCheckBox;
	delete m_pWaterRenderCheckBox;
	delete m_pFullscreenButton;

	// Sound
	delete m_pSoundEffects;
	delete m_pSoundEffectsVolume;
	delete m_pMusic;
	delete m_pMusicVolume;
	delete m_pSliderBackgroundIcon_Sound;
	delete m_pSliderBackgroundIcon_Music;

	// Interface
	delete m_pRenderGUI;
	delete m_pRenderCrosshair;
	delete m_pHUDAnimations;
	delete m_pCustomCursors;
	delete m_pEquipHoverIcon;
	delete m_pToolTipAppearDelay;
	delete m_pConfirmDeleteItem;
	delete m_pResetGUIToDefault;

	// Controls
}

void OptionsMenu::Reset()
{
}

void OptionsMenu::SetWindowDimensions(int windowWidth, int windowHeight)
{
	FrontendPage::SetWindowDimensions(windowWidth, windowHeight);

	m_optionsWindowWidth = 600;
	m_optionsWindowHeight = 475;
	m_titlebarWidth = 135;
	m_titlebarHeight = 35;

	// Window
	m_pOptionsWindow->SetDimensions((int)((m_windowWidth*0.5f) - (m_optionsWindowWidth*0.5f)), (int)((m_windowHeight*0.5f) - (m_optionsWindowHeight*0.5f)), m_optionsWindowWidth, m_optionsWindowHeight);
	m_pOptionsWindow->SetTitleBarDimensions(0, 0, m_titlebarWidth, m_titlebarHeight);
	m_pOptionsWindow->SetTitleOffset(50, 5);
	m_pOptionsWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
	m_pOptionsWindow->SetApplicationBorder(25, 15, 10, 10);

	m_pTitleBarIcon->SetDimensions(0, m_optionsWindowHeight, 44, 44);
	m_pCloseExitButton->SetDimensions(m_optionsWindowWidth-32, m_optionsWindowHeight, 32, 32);

	// Tabs
	m_pOptionsModeController->SetDimensions(0, m_optionsWindowHeight, m_optionsWindowWidth, 32);
	m_pGameplayMode->SetDisplayLabel(false);
	m_pGameplayMode->SetDimensions(m_optionsWindowWidth-32-375, 0, 75, 32);
	m_pGameplayMode->SetDisplayLabel(true);
	int textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pGameplayMode->GetLabel().GetText().c_str());
	m_pGameplayMode->SetLabelPosition((int)(75*0.5f-textWidth*0.5f), 8);

	m_pGraphicsMode->SetDisplayLabel(false);
	m_pGraphicsMode->SetDimensions(m_optionsWindowWidth-32-300, 0, 75, 32);
	m_pGraphicsMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pGraphicsMode->GetLabel().GetText().c_str());
	m_pGraphicsMode->SetLabelPosition((int)(75*0.5f-textWidth*0.5f), 8);

	m_pSoundMode->SetDisplayLabel(false);
	m_pSoundMode->SetDimensions(m_optionsWindowWidth-32-225, 0, 75, 32);
	m_pSoundMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pSoundMode->GetLabel().GetText().c_str());
	m_pSoundMode->SetLabelPosition((int)(75*0.5f-textWidth*0.5f), 8);

	m_pInterfaceMode->SetDisplayLabel(false);
	m_pInterfaceMode->SetDimensions(m_optionsWindowWidth-32-150, 0, 75, 32);
	m_pInterfaceMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pInterfaceMode->GetLabel().GetText().c_str());
	m_pInterfaceMode->SetLabelPosition((int)(75*0.5f-textWidth*0.5f), 8);

	m_pControlsMode->SetDisplayLabel(false);
	m_pControlsMode->SetDimensions(m_optionsWindowWidth-32-75, 0, 75, 32);
	m_pControlsMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pControlsMode->GetLabel().GetText().c_str());
	m_pControlsMode->SetLabelPosition((int)(75*0.5f-textWidth*0.5f), 8);

	// Gameplay
	m_pInvertedMouseMode->SetDimensions(25, m_optionsWindowHeight-65, 20, 20);

	m_pNormalCamOption->SetDimensions(5, 43, 20, 20);
	m_pFollowCamOption->SetDimensions(5, 7, 20, 20);
	m_pCameraSelector->SetDimensions(25, m_optionsWindowHeight-190, 140, 80);

	m_pMouseSensativitySlider->SetDimensions(135, m_optionsWindowHeight-265, 171, 24);
	m_pMouseSensativitySlider->SetCurrentValue(m_pMouseSensativitySlider->GetCurrentValue(), true);
	m_pMouseSensativitySlider->SetLabelPositionOffset(0, 30);

	m_pGamepadSensativitySlider->SetDimensions(135, m_optionsWindowHeight-300, 171, 24);
	m_pGamepadSensativitySlider->SetCurrentValue(m_pGamepadSensativitySlider->GetCurrentValue(), true);
	m_pGamepadSensativitySlider->SetLabelPositionOffset(0, 30);

	m_pSliderBackgroundIcon_MouseSensativity->SetDimensions(131, m_optionsWindowHeight-268, 207, 31);
	m_pSliderBackgroundIcon_GamepadSensativity->SetDimensions(131, m_optionsWindowHeight-303, 207, 31);

	// Graphics
	m_pShadowsCheckBox->SetDimensions(25, m_optionsWindowHeight - 65, 20, 20);
	m_pFogRenderCheckBox->SetDimensions(25, m_optionsWindowHeight - 90, 20, 20);
	m_pWaterRenderCheckBox->SetDimensions(25, m_optionsWindowHeight - 115, 20, 20);
	m_pFullscreenButton->SetDimensions(230, 10, 110, 47);

	// Sound
	m_pSoundEffects->SetDimensions(25, m_optionsWindowHeight-65, 20, 20);
	m_pSoundEffectsVolume->SetDimensions(115, m_optionsWindowHeight-65, 171, 24);
	m_pSoundEffectsVolume->SetCurrentValue(m_pSoundEffectsVolume->GetCurrentValue(), true);

	m_pMusic->SetDimensions(25, m_optionsWindowHeight-105, 20, 20);
	m_pMusicVolume->SetDimensions(115, m_optionsWindowHeight-105, 171, 24);
	m_pMusicVolume->SetCurrentValue(m_pMusicVolume->GetCurrentValue(), true);

	m_pSliderBackgroundIcon_Sound->SetDimensions(111, m_optionsWindowHeight-68, 207, 31);
	m_pSliderBackgroundIcon_Music->SetDimensions(111, m_optionsWindowHeight-108, 207, 31);

	// Interface
	m_pRenderGUI->SetDimensions(25, m_optionsWindowHeight-65, 20, 20);
	m_pRenderCrosshair->SetDimensions(25, m_optionsWindowHeight-105, 20, 20);
	m_pHUDAnimations->SetDimensions(25, m_optionsWindowHeight-145, 20, 20);
	m_pCustomCursors->SetDimensions(25, m_optionsWindowHeight-185, 20, 20);
	m_pEquipHoverIcon->SetDimensions(25, m_optionsWindowHeight-225, 20, 20);
	m_pToolTipAppearDelay->SetDimensions(25, m_optionsWindowHeight-265, 20, 20);
	m_pConfirmDeleteItem->SetDimensions(25, m_optionsWindowHeight-305, 20, 20);
	m_pResetGUIToDefault->SetDimensions(25, m_optionsWindowHeight-375, 110, 47);

	// Controls
}

// Are we returning to the main menu, or are we in the game?
void OptionsMenu::SetReturnToMainMenu(bool mainMenu)
{
	m_returnToMainMenu = mainMenu;
}

// Skinning
void OptionsMenu::SkinGUI()
{
	string themeName = VoxGame::GetInstance()->GetModsManager()->GetHUDTextureTheme();

	string iconName = "media/textures/gui/" + themeName + "/OptionsMenu/slider_background.tga";
	m_pSliderBackgroundIcon_MouseSensativity->SetIcon(iconName);
	m_pSliderBackgroundIcon_GamepadSensativity->SetIcon(iconName);
	m_pSliderBackgroundIcon_Sound->SetIcon(iconName);
	m_pSliderBackgroundIcon_Music->SetIcon(iconName);

	iconName = "media/textures/gui/" + themeName + "/OptionsMenu/options_title_icon.tga";
	m_pTitleBarIcon->SetIcon(iconName);
	iconName = "media/textures/gui/" + themeName + "/OptionsMenu/options_window_background.tga";
	m_pOptionsWindowBackgroundIcon->SetIcon(iconName);
	iconName = "media/textures/gui/" + themeName + "/OptionsMenu/titlebar_background.tga";
	m_pTitleBarBackgroundIcon->SetIcon(iconName);

	m_pOptionsWindow->SetBackgroundIcon(m_pOptionsWindowBackgroundIcon);
	m_pOptionsWindow->SetTitlebarBackgroundIcon(m_pTitleBarBackgroundIcon);

	Point location = m_pOptionsWindow->GetLocation();
	m_pOptionsWindow->SetDimensions(location.m_x, location.m_y, m_optionsWindowWidth, m_optionsWindowHeight);
	m_pOptionsWindow->SetTitleBarDimensions(0, 0, m_titlebarWidth, m_titlebarHeight);

	m_pCloseExitButton->SetDefaultIcon(m_pFrontendManager->GetCloseExitButtonIcon());
	m_pCloseExitButton->SetHoverIcon(m_pFrontendManager->GetCloseExitButtonIcon_Hover());
	m_pCloseExitButton->SetSelectedIcon(m_pFrontendManager->GetCloseExitButtonIcon_Pressed());
	m_pCloseExitButton->SetDisabledIcon(m_pFrontendManager->GetCloseExitButtonIcon());

	m_pFrontendManager->SetTabIcons(m_pGameplayMode);
	m_pFrontendManager->SetTabIcons(m_pGraphicsMode);
	m_pFrontendManager->SetTabIcons(m_pSoundMode);
	m_pFrontendManager->SetTabIcons(m_pControlsMode);
	m_pFrontendManager->SetTabIcons(m_pInterfaceMode);

	m_pGameplayMode->SetDisplayLabel(false);
	m_pGameplayMode->SetDimensions(m_optionsWindowWidth - 32 - 375, 0, 75, 32);
	m_pGameplayMode->SetDisplayLabel(true);
	int textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pGameplayMode->GetLabel().GetText().c_str());
	m_pGameplayMode->SetLabelPosition((int)(75 * 0.5f - textWidth*0.5f), 8);

	m_pGraphicsMode->SetDisplayLabel(false);
	m_pGraphicsMode->SetDimensions(m_optionsWindowWidth - 32 - 300, 0, 75, 32);
	m_pGraphicsMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pGraphicsMode->GetLabel().GetText().c_str());
	m_pGraphicsMode->SetLabelPosition((int)(75 * 0.5f - textWidth*0.5f), 8);

	m_pSoundMode->SetDisplayLabel(false);
	m_pSoundMode->SetDimensions(m_optionsWindowWidth - 32 - 225, 0, 75, 32);
	m_pSoundMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pSoundMode->GetLabel().GetText().c_str());
	m_pSoundMode->SetLabelPosition((int)(75 * 0.5f - textWidth*0.5f), 8);

	m_pInterfaceMode->SetDisplayLabel(false);
	m_pInterfaceMode->SetDimensions(m_optionsWindowWidth - 32 - 150, 0, 75, 32);
	m_pInterfaceMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pInterfaceMode->GetLabel().GetText().c_str());
	m_pInterfaceMode->SetLabelPosition((int)(75 * 0.5f - textWidth*0.5f), 8);

	m_pControlsMode->SetDisplayLabel(false);
	m_pControlsMode->SetDimensions(m_optionsWindowWidth - 32 - 75, 0, 75, 32);
	m_pControlsMode->SetDisplayLabel(true);
	textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_18_Outline(), "%s", m_pControlsMode->GetLabel().GetText().c_str());
	m_pControlsMode->SetLabelPosition((int)(75 * 0.5f - textWidth*0.5f), 8);

	m_pFrontendManager->SetCheckboxIcons(m_pInvertedMouseMode);
	Dimensions dimensions = m_pInvertedMouseMode->GetDimensions();
	m_pInvertedMouseMode->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);

	m_pFrontendManager->SetOptionboxIcons(m_pNormalCamOption);
	dimensions = m_pNormalCamOption->GetDimensions();
	m_pNormalCamOption->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetOptionboxIcons(m_pFollowCamOption);
	dimensions = m_pFollowCamOption->GetDimensions();
	m_pFollowCamOption->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);

	m_pFrontendManager->SetCheckboxIcons(m_pShadowsCheckBox);
	dimensions = m_pShadowsCheckBox->GetDimensions();
	m_pShadowsCheckBox->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	
	m_pFrontendManager->SetCheckboxIcons(m_pFogRenderCheckBox);
	dimensions = m_pFogRenderCheckBox->GetDimensions();
	m_pFogRenderCheckBox->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);

	m_pFrontendManager->SetCheckboxIcons(m_pWaterRenderCheckBox);
	dimensions = m_pWaterRenderCheckBox->GetDimensions();
	m_pWaterRenderCheckBox->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);

	m_pFrontendManager->SetCheckboxIcons(m_pSoundEffects);
	dimensions = m_pSoundEffects->GetDimensions();
	m_pSoundEffects->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pMusic);
	dimensions = m_pMusic->GetDimensions();
	m_pMusic->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);

	m_pFrontendManager->SetCheckboxIcons(m_pRenderGUI);
	dimensions = m_pRenderGUI->GetDimensions();
	m_pRenderGUI->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pRenderCrosshair);
	dimensions = m_pRenderCrosshair->GetDimensions();
	m_pRenderCrosshair->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pHUDAnimations);
	dimensions = m_pHUDAnimations->GetDimensions();
	m_pHUDAnimations->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pCustomCursors);
	dimensions = m_pCustomCursors->GetDimensions();
	m_pCustomCursors->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pEquipHoverIcon);
	dimensions = m_pEquipHoverIcon->GetDimensions();
	m_pEquipHoverIcon->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pToolTipAppearDelay);
	dimensions = m_pToolTipAppearDelay->GetDimensions();
	m_pToolTipAppearDelay->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetCheckboxIcons(m_pConfirmDeleteItem);
	dimensions = m_pConfirmDeleteItem->GetDimensions();
	m_pConfirmDeleteItem->SetDimensions(dimensions.m_x, dimensions.m_y, 20, 20);
	m_pFrontendManager->SetButtonIcons(m_pResetGUIToDefault, ButtonSize_110x47);

	m_pFrontendManager->SetSliderIcons(m_pMouseSensativitySlider);
	m_pFrontendManager->SetSliderIcons(m_pGamepadSensativitySlider);
	m_pFrontendManager->SetSliderIcons(m_pSoundEffectsVolume);
	m_pFrontendManager->SetSliderIcons(m_pMusicVolume);

	m_pGameplayMode->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pGameplayMode->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pGameplayMode->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pGameplayMode->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());

	m_pGraphicsMode->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pGraphicsMode->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pGraphicsMode->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pGraphicsMode->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());

	m_pSoundMode->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pSoundMode->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pSoundMode->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pSoundMode->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());

	m_pControlsMode->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pControlsMode->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pControlsMode->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pControlsMode->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());

	m_pInterfaceMode->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pInterfaceMode->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pInterfaceMode->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pInterfaceMode->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());

	m_pFrontendManager->SetButtonIcons(m_pFullscreenButton, ButtonSize_110x47);
	m_pFullscreenButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pFullscreenButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pFullscreenButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pFullscreenButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());

	m_pInvertedMouseMode->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pInvertedMouseMode->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pInvertedMouseMode->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pInvertedMouseMode->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pNormalCamOption->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pNormalCamOption->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pNormalCamOption->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pNormalCamOption->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pFollowCamOption->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pFollowCamOption->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pFollowCamOption->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pFollowCamOption->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pShadowsCheckBox->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pShadowsCheckBox->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pShadowsCheckBox->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pShadowsCheckBox->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pFogRenderCheckBox->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pFogRenderCheckBox->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pFogRenderCheckBox->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pFogRenderCheckBox->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pWaterRenderCheckBox->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pWaterRenderCheckBox->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pWaterRenderCheckBox->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pWaterRenderCheckBox->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pSoundEffects->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pSoundEffects->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pSoundEffects->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pSoundEffects->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pMusic->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pMusic->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pMusic->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pMusic->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pRenderGUI->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pRenderGUI->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pRenderGUI->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pRenderGUI->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pRenderCrosshair->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pRenderCrosshair->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pRenderCrosshair->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pRenderCrosshair->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pHUDAnimations->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pHUDAnimations->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pHUDAnimations->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pHUDAnimations->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pCustomCursors->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pCustomCursors->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pCustomCursors->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pCustomCursors->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pEquipHoverIcon->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pEquipHoverIcon->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pEquipHoverIcon->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pEquipHoverIcon->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pToolTipAppearDelay->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pToolTipAppearDelay->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pToolTipAppearDelay->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pToolTipAppearDelay->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pConfirmDeleteItem->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pConfirmDeleteItem->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pConfirmDeleteItem->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pConfirmDeleteItem->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pResetGUIToDefault->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pResetGUIToDefault->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pResetGUIToDefault->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pResetGUIToDefault->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
}

void OptionsMenu::UnSkinGUI()
{
}

// Loading and saving options to file
void OptionsMenu::LoadOptions()
{
	VoxSettings* pSettings = VoxGame::GetInstance()->GetVoxSettings();

	// Gameplay
	m_pInvertedMouseMode->SetToggled(pSettings->m_invertedMouse);
	m_pMouseSensativitySlider->SetCurrentValue(pSettings->m_mouseSensitivity);
	m_pGamepadSensativitySlider->SetCurrentValue(pSettings->m_gamepadSensitivity);

	// Graphics
	m_pShadowsCheckBox->SetToggled(pSettings->m_shadows);
	m_pFogRenderCheckBox->SetToggled(pSettings->m_fogRendering);
	m_pWaterRenderCheckBox->SetToggled(pSettings->m_waterRendering);

	// Sound
	m_pSoundEffects->SetToggled(pSettings->m_audio);
	m_pSoundEffectsVolume->SetCurrentValue(pSettings->m_audioVolume);
	m_pMusic->SetToggled(pSettings->m_music);
	m_pMusicVolume->SetCurrentValue(pSettings->m_musicVolume);

	// Interface
	m_pRenderGUI->SetToggled(pSettings->m_renderGUI);
	m_pRenderCrosshair->SetToggled(pSettings->m_renderCrosshair);
	m_pHUDAnimations->SetToggled(pSettings->m_HUDAnimations);
	m_pCustomCursors->SetToggled(pSettings->m_customCursors);
	m_pEquipHoverIcon->SetToggled(pSettings->m_equipHelper);
	m_pToolTipAppearDelay->SetToggled(pSettings->m_tooltipDelay);
	m_pConfirmDeleteItem->SetToggled(pSettings->m_confirmItemDelete);

	// Controls
}

void OptionsMenu::SaveOptions()
{
	VoxSettings* pSettings = VoxGame::GetInstance()->GetVoxSettings();

	// Gameplay
	pSettings->m_invertedMouse = m_pInvertedMouseMode->GetToggled();
	pSettings->m_mouseSensitivity = m_pMouseSensativitySlider->GetCurrentValue();
	pSettings->m_gamepadSensitivity = m_pGamepadSensativitySlider->GetCurrentValue();

	// Graphics
	pSettings->m_shadows = m_pShadowsCheckBox->GetToggled();
	pSettings->m_fogRendering = m_pFogRenderCheckBox->GetToggled();
	pSettings->m_waterRendering = m_pWaterRenderCheckBox->GetToggled();

	// Sound
	pSettings->m_audio = m_pSoundEffects->GetToggled();
	pSettings->m_audioVolume = m_pSoundEffectsVolume->GetCurrentValue();
	pSettings->m_music = m_pMusic->GetToggled();
	pSettings->m_musicVolume= m_pMusicVolume->GetCurrentValue();

	// Interface
	pSettings->m_renderGUI = m_pRenderGUI->GetToggled();
	pSettings->m_renderCrosshair = m_pRenderCrosshair->GetToggled();
	pSettings->m_HUDAnimations = m_pHUDAnimations->GetToggled();
	pSettings->m_customCursors = m_pCustomCursors->GetToggled();
	pSettings->m_equipHelper = m_pEquipHoverIcon->GetToggled();
	pSettings->m_tooltipDelay = m_pToolTipAppearDelay->GetToggled();
	pSettings->m_confirmItemDelete = m_pConfirmDeleteItem->GetToggled();

	// Controls

	// Save the options file
	pSettings->SaveOptions();
}

// Load unload
void OptionsMenu::Load()
{
	// Load options to GUI
	LoadOptions();

	// Cache if we are using custom cursors
	m_initiallyUsingCustomCursors = m_pCustomCursors->GetToggled();

	m_pGameplayMode->SetToggled(true);
	GameplayTabPressed();

	m_loaded = true;
}

void OptionsMenu::Unload()
{
	// Save GUI to options
	SaveOptions();

	// Depending on if we have changed the custom cursors option, we need to force the cursor to appear or disappear.
	if (m_initiallyUsingCustomCursors != m_pCustomCursors->GetToggled())
	{
		if (m_pCustomCursors->GetToggled())
		{
			VoxGame::GetInstance()->TurnCursorOff(true);
			VoxGame::GetInstance()->TurnCursorOn(false, false);
		}
		else
		{
			VoxGame::GetInstance()->TurnCursorOn(false, true);
		}
	}	

	// Remove ALL tab sections
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGameplayComponents[i]);
	}
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGraphicsComponents[i]);
	}
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpSoundComponents[i]);
	}
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpControlsComponents[i]);
	}
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpInterfaceComponents[i]);
	}

	m_pGUI->RemoveWindow(m_pOptionsWindow);

	m_loaded = false;
}

// Disable options
void OptionsMenu::DisableShadowOption()
{
	m_pShadowsCheckBox->SetToggled(false);
	m_pShadowsCheckBox->SetDisabled(true);
	VoxGame::GetInstance()->GetVoxSettings()->m_shadows = false;
}

// Update
void OptionsMenu::Update(float dt)
{
	FrontendPage::Update(dt);

	if (VoxGame::GetInstance()->IsPaused() == false)
	{
		float orbitTimer = m_pFrontendManager->GetCameraOrbitTimer();
		orbitTimer += dt;

		float orbitTime = 120.0f;
		if (orbitTimer >= orbitTime)
		{
			orbitTimer = 0.0f;
		}
		m_pFrontendManager->SetCameraOrbitTimer(orbitTimer);

		float ratio = orbitTimer / orbitTime;
		float radius = 125.0f;
		float angle = DegToRad((ratio * 360.0f));
		vec3 position = vec3(cos(angle) * radius, radius*0.75f, sin(angle) * radius);

		m_cameraPosition = position;
		m_cameraView = vec3(0.0f, 8.0f, 0.0f);
	}

	VoxGame::GetInstance()->SetGlobalBlurAmount(0.00125f);

	// Always update the music and sound settings so that we can dynamically change audio settings in the options menu
	VoxGame::GetInstance()->GetVoxSettings()->m_music = m_pMusic->GetToggled();
	VoxGame::GetInstance()->GetVoxSettings()->m_musicVolume = m_pMusicVolume->GetCurrentValue();
	VoxGame::GetInstance()->GetVoxSettings()->m_audio = m_pSoundEffects->GetToggled();
	VoxGame::GetInstance()->GetVoxSettings()->m_audioVolume = m_pSoundEffectsVolume->GetCurrentValue();

	// Always update these graphical settings as soon as we change the toggles
	VoxGame::GetInstance()->GetVoxSettings()->m_shadows = m_pShadowsCheckBox->GetToggled();
	VoxGame::GetInstance()->GetVoxSettings()->m_fogRendering = m_pFogRenderCheckBox->GetToggled();
	VoxGame::GetInstance()->GetVoxSettings()->m_waterRendering = m_pWaterRenderCheckBox->GetToggled();
}

// Render
void OptionsMenu::Render()
{
	FrontendPage::Render();
}

void OptionsMenu::Render2D()
{
	FrontendPage::Render2D();
}

// Static functionality
void OptionsMenu::_CloseExitPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->CloseExitPressed();
}

void OptionsMenu::CloseExitPressed()
{
	if(m_returnToMainMenu)
	{
		m_pFrontendManager->SetFrontendScreen(FrontendScreen_MainMenu);
	}
	else
	{
		m_pFrontendManager->SetFrontendScreen(FrontendScreen_PauseMenu);
	}
}

void OptionsMenu::_GameplayTabPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->GameplayTabPressed();
}

void OptionsMenu::GameplayTabPressed()
{
	if(m_loaded)
	{
		m_pGUI->RemoveWindow(m_pOptionsWindow);
	}

	// Remove
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGameplayComponents[i]);
	}
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGraphicsComponents[i]);
	}
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpSoundComponents[i]);
	}
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpControlsComponents[i]);
	}
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpInterfaceComponents[i]);
	}

	// Add
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->AddComponent(m_vpGameplayComponents[i]);
	}

	m_pGUI->AddWindow(m_pOptionsWindow);
	m_pOptionsWindow->Show();
}

void OptionsMenu::_GraphicsTabPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->GraphicsTabPressed();
}

void OptionsMenu::GraphicsTabPressed()
{
	if(m_loaded)
	{
		m_pGUI->RemoveWindow(m_pOptionsWindow);
	}

	// Remove
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGameplayComponents[i]);
	}
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGraphicsComponents[i]);
	}
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpSoundComponents[i]);
	}
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpControlsComponents[i]);
	}
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpInterfaceComponents[i]);
	}

	// Add
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->AddComponent(m_vpGraphicsComponents[i]);
	}

	m_pGUI->AddWindow(m_pOptionsWindow);
	m_pOptionsWindow->Show();
}

void OptionsMenu::_SoundTabPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->SoundTabPressed();
}

void OptionsMenu::SoundTabPressed()
{
	if(m_loaded)
	{
		m_pGUI->RemoveWindow(m_pOptionsWindow);
	}

	// Remove
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGameplayComponents[i]);
	}
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGraphicsComponents[i]);
	}
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpSoundComponents[i]);
	}
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpControlsComponents[i]);
	}
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpInterfaceComponents[i]);
	}

	// Add
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->AddComponent(m_vpSoundComponents[i]);
	}

	m_pGUI->AddWindow(m_pOptionsWindow);
	m_pOptionsWindow->Show();
}

void OptionsMenu::_InterfaceTabPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->InterfaceTabPressed();
}

void OptionsMenu::InterfaceTabPressed()
{
	if(m_loaded)
	{
		m_pGUI->RemoveWindow(m_pOptionsWindow);
	}

	// Remove
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGameplayComponents[i]);
	}
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGraphicsComponents[i]);
	}
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpSoundComponents[i]);
	}
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpControlsComponents[i]);
	}
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpInterfaceComponents[i]);
	}

	// Add
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->AddComponent(m_vpInterfaceComponents[i]);
	}

	m_pGUI->AddWindow(m_pOptionsWindow);
	m_pOptionsWindow->Show();
}

void OptionsMenu::_ControlsTabPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->ControlsTabPressed();
}

void OptionsMenu::ControlsTabPressed()
{
	if(m_loaded)
	{
		m_pGUI->RemoveWindow(m_pOptionsWindow);
	}

	// Remove
	for(int i = 0; i < m_vpGameplayComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGameplayComponents[i]);
	}
	for(int i = 0; i < m_vpGraphicsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpGraphicsComponents[i]);
	}
	for(int i = 0; i < m_vpSoundComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpSoundComponents[i]);
	}
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpControlsComponents[i]);
	}
	for(int i = 0; i < m_vpInterfaceComponents.size(); i++)
	{
		m_pOptionsWindow->RemoveComponent(m_vpInterfaceComponents[i]);
	}

	// Add
	for(int i = 0; i < m_vpControlsComponents.size(); i++)
	{
		m_pOptionsWindow->AddComponent(m_vpControlsComponents[i]);
	}

	m_pGUI->AddWindow(m_pOptionsWindow);
	m_pOptionsWindow->Show();
}

void OptionsMenu::_ToggleFullScreenPressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->ToggleFullScreenPressed();
}

void OptionsMenu::ToggleFullScreenPressed()
{
	VoxGame::GetInstance()->ToggleFullScreenPressed();
}

void OptionsMenu::_CustomCursorsTogglePressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->CustomCursorsTogglePressed();
}

void OptionsMenu::CustomCursorsTogglePressed()
{
	// TODO : Make it so that the custom cursors are turned on/off immediately when toggling the option
}

void OptionsMenu::_RenderHUDTogglePressed(void *pData)
{
	OptionsMenu* lpOptionsMenu = (OptionsMenu*)pData;
	lpOptionsMenu->RenderHUDTogglePressed();
}

void OptionsMenu::RenderHUDTogglePressed()
{
	if (m_pRenderGUI->GetToggled())
	{
		if (VoxGame::GetInstance()->GetHUD()->IsLoaded() == false)
		{
			VoxGame::GetInstance()->GetHUD()->Load();
		}
		if (VoxGame::GetInstance()->GetActionBar()->IsLoaded() == false)
		{
			VoxGame::GetInstance()->GetActionBar()->Load();
		}
	}
	else
	{
		if (VoxGame::GetInstance()->GetHUD()->IsLoaded() == true)
		{
			VoxGame::GetInstance()->GetHUD()->Unload();
		}
		if (VoxGame::GetInstance()->GetActionBar()->IsLoaded() == true)
		{
			VoxGame::GetInstance()->GetActionBar()->Unload();
		}
	}
}