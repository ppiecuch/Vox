// ******************************************************************************
// Filename:    MainMenu.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Revision History:
//   Initial Revision - 12/10/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "MainMenu.h"
#include "../FrontendManager.h"
#include "../../gui/openglgui.h"
#include "../../VoxGame.h"
#include "../../utils/Interpolator.h"


MainMenu::MainMenu(Renderer* pRenderer, OpenGLGUI* pGUI, FrontendManager* pFrontPageManager, int windowWidth, int windowHeight)
  : FrontendPage(pRenderer, pGUI, pFrontPageManager, FrontendScreen_MainMenu, windowWidth, windowHeight)
{
	m_logoTexture = -1;
	int ltexturewidth2, ltextureheight2;
	m_pRenderer->LoadTexture("media/textures/vox_logo.tga", &m_logoWidth, &m_logoHeight, &ltexturewidth2, &ltextureheight2, &m_logoTexture);	

	m_pCreditLabel = new Label(m_pRenderer, m_pFrontendManager->GetFrontendFont_35(), "A game by @AlwaysGeeky", Colour(1.0f, 1.0f, 1.0f, 1.0f));
	m_pCreditLabel->SetOutlineFont(m_pFrontendManager->GetFrontendFont_35_Outline());
	m_pCreditLabel->SetOutlineColour(Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pCreditLabel->SetOutline(true);

	m_pSinglePlayerButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_50(), m_pFrontendManager->GetFrontendFont_50_Outline(), "Single Player", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pSinglePlayerButton->SetLabelOffset(0, 5);
	m_pSinglePlayerButton->SetPressedOffset(0, -4);
	m_pSinglePlayerButton->SetCallBackFunction(_SinglePlayerPressed);
	m_pSinglePlayerButton->SetCallBackData(this);

	m_pMultiPlayerButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_50(), m_pFrontendManager->GetFrontendFont_50_Outline(), "Multiplayer", Colour(0.75f, 0.75f, 0.75f, 1.0f), Colour(0.25f, 0.25f, 0.25f, 1.0f));
	m_pMultiPlayerButton->SetLabelOffset(0, 5);
	m_pMultiPlayerButton->SetPressedOffset(0, -4);
	m_pMultiPlayerButton->SetCallBackFunction(_MultiPlayerPressed);
	m_pMultiPlayerButton->SetCallBackData(this);

	m_pOptionsButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_50(), m_pFrontendManager->GetFrontendFont_50_Outline(), "Options", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pOptionsButton->SetLabelOffset(0, 5);
	m_pOptionsButton->SetPressedOffset(0, -4);
	m_pOptionsButton->SetCallBackFunction(_OptionsPressed);
	m_pOptionsButton->SetCallBackData(this);

	m_pModsButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_50(), m_pFrontendManager->GetFrontendFont_50_Outline(), "Mods", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pModsButton->SetLabelOffset(0, 5);
	m_pModsButton->SetPressedOffset(0, -4);
	m_pModsButton->SetCallBackFunction(_ModsPressed);
	m_pModsButton->SetCallBackData(this);

	m_pCreditsButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_50(), m_pFrontendManager->GetFrontendFont_50_Outline(), "Credits", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pCreditsButton->SetLabelOffset(0, 5);
	m_pCreditsButton->SetPressedOffset(0, -4);
	m_pCreditsButton->SetCallBackFunction(_CreditsPressed);
	m_pCreditsButton->SetCallBackData(this);

	m_pQuitButton = new Button(m_pRenderer, m_pFrontendManager->GetFrontendFont_50(), m_pFrontendManager->GetFrontendFont_50_Outline(), "Quit", Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f));
	m_pQuitButton->SetLabelOffset(0, 5);
	m_pQuitButton->SetPressedOffset(0, -4);
	m_pQuitButton->SetCallBackFunction(_QuitPressed);
	m_pQuitButton->SetCallBackData(this);

	m_blurAmount = 0.0f;

	Reset();

	SetWindowDimensions(m_windowWidth, m_windowHeight);
}

MainMenu::~MainMenu()
{
	delete m_pCreditLabel;
	delete m_pSinglePlayerButton;
	delete m_pMultiPlayerButton;
	delete m_pOptionsButton;
	delete m_pModsButton;
	delete m_pCreditsButton;
	delete m_pQuitButton;
}

void MainMenu::Reset()
{
	m_textFadeInTime = 3.0f;
	m_textFadeInTimer = m_textFadeInTime;
	m_titleFadeInTime = 1.0f;
	m_titleFadeInTimer = m_titleFadeInTime;
	m_textAlpha = 0.0f;
	m_titleAlpha = 0.0f;
}

void MainMenu::SetWindowDimensions(int width, int height)
{
	FrontendPage::SetWindowDimensions(width, height);

	m_pSinglePlayerButton->SetDimensions(30, 490, 225, 75);
	m_pMultiPlayerButton->SetDimensions(30, 405, 225, 75);
	m_pOptionsButton->SetDimensions(30, 320, 225, 75);
	m_pModsButton->SetDimensions(30, 235, 225, 75);
	m_pCreditsButton->SetDimensions(30, 150, 225, 75);
	m_pQuitButton->SetDimensions(30, 30, 225, 75);

	int borderSpacer = 8;
	int textWidth = m_pRenderer->GetFreeTypeTextWidth(m_pFrontendManager->GetFrontendFont_35(), "%s", m_pCreditLabel->GetText().c_str());
	m_pCreditLabel->SetLocation(m_windowWidth - textWidth - borderSpacer, borderSpacer);
}

void MainMenu::SkinGUI()
{
	m_pFrontendManager->SetButtonIcons(m_pSinglePlayerButton, ButtonSize_225x75);
	m_pFrontendManager->SetButtonIcons(m_pMultiPlayerButton, ButtonSize_225x75);
	m_pFrontendManager->SetButtonIcons(m_pOptionsButton, ButtonSize_225x75);
	m_pFrontendManager->SetButtonIcons(m_pModsButton, ButtonSize_225x75);
	m_pFrontendManager->SetButtonIcons(m_pCreditsButton, ButtonSize_225x75);
	m_pFrontendManager->SetButtonIcons(m_pQuitButton, ButtonSize_225x75);

	m_pSinglePlayerButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pSinglePlayerButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pSinglePlayerButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pMultiPlayerButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pMultiPlayerButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pMultiPlayerButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pOptionsButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pOptionsButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pOptionsButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pModsButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pModsButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pModsButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pCreditsButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pCreditsButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pCreditsButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
	m_pQuitButton->SetNormalLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pQuitButton->SetHoverLabelColour(m_pFrontendManager->GetHoverFontColour());
	m_pQuitButton->SetPressedLabelColour(m_pFrontendManager->GetPressedFontColour());
}

void MainMenu::UnSkinGUI()
{
	m_pSinglePlayerButton->SetDefaultIcons(m_pRenderer);
	m_pMultiPlayerButton->SetDefaultIcons(m_pRenderer);
	m_pOptionsButton->SetDefaultIcons(m_pRenderer);
	m_pModsButton->SetDefaultIcons(m_pRenderer);
	m_pCreditsButton->SetDefaultIcons(m_pRenderer);
	m_pQuitButton->SetDefaultIcons(m_pRenderer);
}

void MainMenu::Load()
{
	m_pSinglePlayerButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pMultiPlayerButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pOptionsButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pModsButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pCreditsButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());
	m_pQuitButton->SetLabelColour(m_pFrontendManager->GetNormalFontColour());

	//m_blurAmount = 0.0f;
	//Interpolator::GetInstance()->AddFloatInterpolation(&m_blurAmount, 0.0f, 0.00125f, 3.0f, 0.0f);
	//VoxGame::GetInstance()->SetLightingShader(false);

	m_pGUI->AddComponent(m_pCreditLabel);
	m_pGUI->AddComponent(m_pSinglePlayerButton);
	//m_pGUI->AddComponent(m_pMultiPlayerButton);
	m_pGUI->AddComponent(m_pOptionsButton);
	m_pGUI->AddComponent(m_pModsButton);
	m_pGUI->AddComponent(m_pCreditsButton);
	m_pGUI->AddComponent(m_pQuitButton);

	Reset();
}

void MainMenu::Unload()
{
	m_pGUI->RemoveComponent(m_pCreditLabel);
	m_pGUI->RemoveComponent(m_pSinglePlayerButton);
	m_pGUI->RemoveComponent(m_pMultiPlayerButton);
	m_pGUI->RemoveComponent(m_pOptionsButton);
	m_pGUI->RemoveComponent(m_pModsButton);
	m_pGUI->RemoveComponent(m_pCreditsButton);
	m_pGUI->RemoveComponent(m_pQuitButton);

	VoxGame::GetInstance()->SetGlobalBlurAmount(0.0f);
	//m_pFrontendManager->GetGameWindow()->SetLightingShader(true);
}

void MainMenu::Update(float dt)
{
	FrontendPage::Update(dt);

	VoxGame::GetInstance()->SetGlobalBlurAmount(0.00125f);

	if(VoxGame::GetInstance()->IsPaused() == false)
	{
		float orbitTimer = m_pFrontendManager->GetCameraOrbitTimer();
		orbitTimer += dt;

		float orbitTime = 120.0f;
		if(orbitTimer >= orbitTime)
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

		// Text fade in
		if(m_textFadeInTimer >= 0.0f)
		{
			m_textFadeInTimer -= dt;

			m_textAlpha = 1.0f - (m_textFadeInTimer / m_textFadeInTime);

			m_pCreditLabel->SetColour(Colour(1.0f, 1.0f, 1.0f, m_textAlpha));
			m_pCreditLabel->SetOutlineColour(Colour(0.0f, 0.0f, 0.0f, m_textAlpha));
		}
		// Title fade in 
		if(m_titleFadeInTimer >= 0.0f)
		{
			m_titleFadeInTimer -= dt;

			m_titleAlpha = 1.0f - (m_titleFadeInTimer / m_titleFadeInTime);
		}
	}
}

void MainMenu::Render()
{
	FrontendPage::Render();
}

void MainMenu::Render2D()
{
	FrontendPage::Render2D();

	float logoScale = 1.25f;
	int top_logo_spacer = 25;

	float length = m_logoWidth * logoScale;
	float height = m_logoHeight * logoScale;

	m_pRenderer->PushMatrix();
		m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, m_titleAlpha);
		m_pRenderer->SetRenderMode(RM_TEXTURED);
		m_pRenderer->BindTexture(m_logoTexture);
		m_pRenderer->EnableTransparency(BF_SRC_ALPHA, BF_ONE_MINUS_SRC_ALPHA);

		// Bring to front of full screen shader textures
		m_pRenderer->TranslateWorldMatrix(0.0f, 0.0f, 5.0f);

		// Center
		m_pRenderer->TranslateWorldMatrix((float)(m_windowWidth*0.5f - length*0.5f), (float)(m_windowHeight - top_logo_spacer - height), 0.0f);

		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)length, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)length, (float)height, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)height, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->DisableTransparency();
	m_pRenderer->PopMatrix();
}

void MainMenu::_SinglePlayerPressed(void *apData)
{
	MainMenu* lpMainMenu = (MainMenu*)apData;
	lpMainMenu->SinglePlayerPressed();
}

void MainMenu::SinglePlayerPressed()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_SelectCharacter);
}

void MainMenu::_MultiPlayerPressed(void *apData)
{
	MainMenu* lpMainMenu = (MainMenu*)apData;
	lpMainMenu->MultiPlayerPressed();
}

void MainMenu::MultiPlayerPressed()
{

}

void MainMenu::_OptionsPressed(void *apData)
{
	MainMenu* lpMainMenu = (MainMenu*)apData;
	lpMainMenu->OptionsPressed();
}

void MainMenu::OptionsPressed()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_OptionsMenu);
	m_pFrontendManager->SetOptionsReturnToMainMenu(true);
}

void MainMenu::_ModsPressed(void *apData)
{
	MainMenu* lpMainMenu = (MainMenu*)apData;
	lpMainMenu->ModsPressed();
}

void MainMenu::ModsPressed()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_ModMenu);
	m_pFrontendManager->SetModsMenuReturnToMainMenu(true);
}

void MainMenu::_CreditsPressed(void *apData)
{
	MainMenu* lpMainMenu = (MainMenu*)apData;
	lpMainMenu->CreditsPressed();
}

void MainMenu::CreditsPressed()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_Credits);
}

void MainMenu::_QuitPressed(void *apData)
{
	MainMenu* lpMainMenu = (MainMenu*)apData;
	lpMainMenu->QuitPressed();
}

void MainMenu::QuitPressed()
{
	VoxGame::GetInstance()->SetGameQuit(true);
}
