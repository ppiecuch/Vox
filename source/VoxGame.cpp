// ******************************************************************************
// Filename:    VoxGame.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#include "glew/include/GL/glew.h"

#include "VoxGame.h"
#include "utils/Interpolator.h"
#include <glm/detail/func_geometric.hpp>

#if defined(__linux__) || defined(__APPLE__)
# include <sys/time.h>
#endif //__linux__ || __APPLE__


// Initialize the singleton instance
VoxGame *VoxGame::c_instance = 0;

VoxGame* VoxGame::GetInstance()
{
	if (c_instance == 0)
		c_instance = new VoxGame;

	return c_instance;
}

// Creation
void VoxGame::Create(VoxSettings* pVoxSettings)
{
	m_pRenderer = NULL;
	m_pGameCamera = NULL;
	m_pQubicleBinaryManager = NULL;
	m_pPlayer = NULL;
	m_pChunkManager = NULL;
	m_pFrontendManager = NULL;

	m_pInventoryGUI = NULL;
	m_pCharacterGUI = NULL;
	m_pLootGUI = NULL;
	m_pCraftingGUI = NULL;
	m_pQuestGUI = NULL;
	m_pActionBar = NULL;
	m_pHUD = NULL;

	m_GUICreated = false;

	m_pVoxSettings = pVoxSettings;
	m_pVoxWindow = new VoxWindow(this, m_pVoxSettings);

	// Create the window
	m_pVoxWindow->Create();

	/* Setup the FPS and deltatime counters */
#ifdef _WIN32
	QueryPerformanceCounter(&m_fpsPreviousTicks);
	QueryPerformanceCounter(&m_fpsCurrentTicks);
	QueryPerformanceFrequency(&m_fpsTicksPerSecond);
#else
	struct timeval tm;
	gettimeofday(&tm, NULL);
	m_fpsCurrentTicks = (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
	m_fpsPreviousTicks = (double)tm.tv_sec + (double)tm.tv_usec / 1000000.0;
#endif //_WIN32
	m_deltaTime = 0.0f;
	m_fps = 0.0f;

	/* Mouse name picking */
	m_pickedObject = -1;
	m_bNamePickingSelected = false;

	/* Paper doll viewport dimensions */
	m_paperdollViewportX = 0;
	m_paperdollViewportY = 0;
	m_paperdollViewportWidth = 800;
	m_paperdollViewportHeight = 800;

	/* Setup the initial starting wait timing */
	m_initialWaitTimer = 0.0f;
	m_initialWaitTime = 0.5f;
	m_initialStartWait = true;

	/* Create the renderer */
	m_windowWidth = m_pVoxWindow->GetWindowWidth();
	m_windowHeight = m_pVoxWindow->GetWindowHeight();
	m_pRenderer = new Renderer(m_windowWidth, m_windowHeight, 32, 8);

	/* Pause and quit */
	m_bGameQuit = false;
	m_bPaused = false;

	/* Interactions */
	m_pInteractItem = NULL;

	/* Create the GUI */
	m_pGUI = new OpenGLGUI(m_pRenderer);

	/* Create cameras */
	m_pGameCamera = new Camera(m_pRenderer);
	m_pGameCamera->SetPosition(vec3(8.0f, 8.25f, 15.5f));
	m_pGameCamera->SetFakePosition(m_pGameCamera->GetPosition());
	m_pGameCamera->SetFacing(vec3(0.0f, 0.0f, -1.0f));
	m_pGameCamera->SetUp(vec3(0.0f, 1.0f, 0.0f));
	m_pGameCamera->SetRight(vec3(1.0f, 0.0f, 0.0f));

	/* Create viewports */
	m_pRenderer->CreateViewport(0, 0, m_windowWidth, m_windowHeight, 60.0f, &m_defaultViewport);
	m_pRenderer->CreateViewport(0, 0, m_windowWidth, m_windowHeight, 60.0f, &m_firstpersonViewport);
	m_pRenderer->CreateViewport(m_paperdollViewportY, m_paperdollViewportX, m_paperdollViewportWidth, m_paperdollViewportHeight, 60.0f, &m_paperdollViewport);

	/* Create fonts */
	m_pRenderer->CreateFreeTypeFont("media/fonts/arial.ttf", 12, &m_defaultFont);

	/* Create lights */
	m_defaultLightPosition = vec3(300.0f, 300.0f, 300.0f);
	m_defaultLightView = vec3(0.0f, 0.0f, 0.0f);
	vec3 lightDirection = m_defaultLightView - m_defaultLightPosition;
	m_pRenderer->CreateLight(Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f),
							 m_defaultLightPosition, lightDirection, 0.0f, 0.0f, 2.0f, 0.001f, 0.0f, true, false, &m_defaultLight);

	/* Create materials */
	m_pRenderer->CreateMaterial(Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(1.0f, 1.0f, 1.0f, 1.0f), Colour(0.0f, 0.0f, 0.0f, 1.0f), 64, &m_defaultMaterial);

	/* Create the frame buffers */
	bool frameBufferCreated = false;
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "SSAO", &m_SSAOFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 5.0f, "Shadow", &m_shadowFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Deferred Lighting", &m_lightingFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Transparency", &m_transparencyFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FXAA", &m_FXAAFrameBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 1st Pass", &m_firstPassFullscreenBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 2nd Pass", &m_secondPassFullscreenBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, 800, 800, 1.0f, "Paperdoll", &m_paperdollBuffer);
	frameBufferCreated = m_pRenderer->CreateFrameBuffer(-1, true, true, true, true, 800, 800, 1.0f, "Paperdoll SSAO Texture", &m_paperdollSSAOTextureBuffer);

	/* Create the shaders */
	bool shaderLoaded = false;
	m_defaultShader = -1;
	m_phongShader = -1;
	m_SSAOShader = -1;
	m_shadowShader = -1;
	m_lightingShader = -1;
	m_cubeMapShader = -1;
	m_textureShader = -1;
	m_fxaaShader = -1;
	m_blurVerticalShader = -1;
	m_blurHorizontalShader = -1;
	m_paperdollShader = -1;
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/default.vertex", "media/shaders/default.pixel", &m_defaultShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/phong.vertex", "media/shaders/phong.pixel", &m_phongShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/shadow.vertex", "media/shaders/shadow.pixel", &m_shadowShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/texture.vertex", "media/shaders/texture.pixel", &m_textureShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/SSAO.vertex", "media/shaders/fullscreen/SSAO.pixel", &m_SSAOShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/fxaa.vertex", "media/shaders/fullscreen/fxaa.pixel", &m_fxaaShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/lighting.vertex", "media/shaders/fullscreen/lighting.pixel", &m_lightingShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/cube_map.vertex", "media/shaders/cube_map.pixel", &m_cubeMapShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/blur_vertical.vertex", "media/shaders/fullscreen/blur_vertical.pixel", &m_blurVerticalShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/fullscreen/blur_horizontal.vertex", "media/shaders/fullscreen/blur_horizontal.pixel", &m_blurHorizontalShader);
	shaderLoaded = m_pRenderer->LoadGLSLShader("media/shaders/paperdoll.vertex", "media/shaders/paperdoll.pixel", &m_paperdollShader);

	/* Create the mods manager */
	m_pModsManager = new ModsManager();
	m_pModsManager->LoadMods();

	/* Create the qubicle binary file manager */
	m_pQubicleBinaryManager = new QubicleBinaryManager(m_pRenderer);

	/* Create the chunk manager*/
	m_pChunkManager = new ChunkManager(m_pRenderer, m_pVoxSettings, m_pQubicleBinaryManager);
	m_pChunkManager->SetStepLockEnabled(m_pVoxSettings->m_stepUpdating);

	/* Create the biome manager */
	m_pBiomeManager = new BiomeManager(m_pRenderer);

	/* Create the lighting manager */
	m_pLightingManager = new LightingManager(m_pRenderer);

	/* Create the scenery manager */
	m_pSceneryManager = new SceneryManager(m_pRenderer, m_pChunkManager);

	/* Create the skybox */
	m_pSkybox = new Skybox(m_pRenderer);

	/* Create the block particle manager */
	m_pBlockParticleManager = new BlockParticleManager(m_pRenderer, m_pChunkManager);

	/* Create the text effects manager */
	m_pTextEffectsManager = new TextEffectsManager(m_pRenderer);
	m_pTextEffectsManager->SetCamera(m_pGameCamera);

	/* Create the instance manager */
	m_pInstanceManager = new InstanceManager(m_pRenderer);

	/* Create the player */
	m_pPlayer = new Player(m_pRenderer, m_pChunkManager, m_pQubicleBinaryManager, m_pLightingManager, m_pBlockParticleManager);

	/* Create the NPC manager */
	m_pNPCManager = new NPCManager(m_pRenderer, m_pChunkManager);

	/* Create the enemy manager */
	m_pEnemyManager = new EnemyManager(m_pRenderer, m_pChunkManager, m_pPlayer);

	/* Create the quest manager */
	m_pQuestManager = new QuestManager();

	/* Create the quest journal */
	m_pQuestJournal = new QuestJournal(m_pQuestManager);

	/* Create the inventory manager */
	m_pInventoryManager = new InventoryManager();

	/* Create the item manager */
	m_pItemManager = new ItemManager(m_pRenderer, m_pChunkManager, m_pPlayer);

	/* Create the projectile manager */
	m_pProjectileManager = new ProjectileManager(m_pRenderer, m_pChunkManager);

	/* Create the frontend manager */
	m_pFrontendManager = new FrontendManager(m_pRenderer, m_pGUI);
	m_pFrontendManager->SetWindowDimensions(m_windowWidth, m_windowHeight);
	m_pFrontendManager->SetCamera(m_pGameCamera);

	/* Create the game GUI pages */
	m_pInventoryGUI = new InventoryGUI(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);
	m_pCharacterGUI = new CharacterGUI(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);
	m_pLootGUI = new LootGUI(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);
	m_pCraftingGUI = new CraftingGUI(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);
	m_pQuestGUI = new QuestGUI(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);
	m_pActionBar = new ActionBar(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);
	m_pHUD = new HUD(m_pRenderer, m_pGUI, m_pFrontendManager, m_pChunkManager, m_pPlayer, m_pInventoryManager, m_windowWidth, m_windowHeight);

	/* Create module and manager linkage */
	m_pChunkManager->SetPlayer(m_pPlayer);
	m_pChunkManager->SetSceneryManager(m_pSceneryManager);
	m_pChunkManager->SetBiomeManager(m_pBiomeManager);
	m_pChunkManager->SetEnemyManager(m_pEnemyManager);
	m_pChunkManager->SetNPCManager(m_pNPCManager);
	m_pChunkManager->SetBlockParticleManager(m_pBlockParticleManager);
	m_pPlayer->SetInventoryManager(m_pInventoryManager);
	m_pPlayer->SetItemManager(m_pItemManager);
	m_pPlayer->SetProjectileManager(m_pProjectileManager);
	m_pPlayer->SetTextEffectsManager(m_pTextEffectsManager);
	m_pPlayer->SetEnemyManager(m_pEnemyManager);
	m_pPlayer->SetInventoryGUI(m_pInventoryGUI);
	m_pPlayer->SetCharacterGUI(m_pCharacterGUI);
	m_pPlayer->SetCraftingGUI(m_pCraftingGUI);
	m_pPlayer->SetLootGUI(m_pLootGUI);
	m_pPlayer->SetActionBar(m_pActionBar);
	m_pNPCManager->SetPlayer(m_pPlayer);
	m_pNPCManager->SetLightingManager(m_pLightingManager);
	m_pNPCManager->SetBlockParticleManager(m_pBlockParticleManager);
	m_pNPCManager->SetTextEffectsManager(m_pTextEffectsManager);
	m_pNPCManager->SetItemManager(m_pItemManager);
	m_pNPCManager->SetQubicleBinaryManager(m_pQubicleBinaryManager);
	m_pNPCManager->SetProjectileManager(m_pProjectileManager);
	m_pNPCManager->SetEnemyManager(m_pEnemyManager);
	m_pEnemyManager->SetLightingManager(m_pLightingManager);
	m_pEnemyManager->SetBlockParticleManager(m_pBlockParticleManager);
	m_pEnemyManager->SetTextEffectsManager(m_pTextEffectsManager);
	m_pEnemyManager->SetItemManager(m_pItemManager);
	m_pEnemyManager->SetProjectileManager(m_pProjectileManager);
	m_pEnemyManager->SetHUD(m_pHUD);
	m_pEnemyManager->SetQubicleBinaryManager(m_pQubicleBinaryManager);
	m_pEnemyManager->SetNPCManager(m_pNPCManager);
	m_pInventoryManager->SetPlayer(m_pPlayer);
	m_pInventoryManager->SetInventoryGUI(m_pInventoryGUI);
	m_pInventoryManager->SetLootGUI(m_pLootGUI);
	m_pInventoryManager->SetActionBar(m_pActionBar);
	m_pItemManager->SetLightingManager(m_pLightingManager);
	m_pItemManager->SetBlockParticleManager(m_pBlockParticleManager);
	m_pItemManager->SetQubicleBinaryManager(m_pQubicleBinaryManager);
	m_pItemManager->SetInventoryManager(m_pInventoryManager);
	m_pProjectileManager->SetLightingManager(m_pLightingManager);
	m_pProjectileManager->SetBlockParticleManager(m_pBlockParticleManager);
	m_pProjectileManager->SetPlayer(m_pPlayer);
	m_pProjectileManager->SetQubicleBinaryManager(m_pQubicleBinaryManager);
	m_pQuestManager->SetNPCManager(m_pNPCManager);
	m_pQuestManager->SetInventoryManager(m_pInventoryManager);
	m_pQuestManager->SetQuestJournal(m_pQuestJournal);
	m_pQuestJournal->SetPlayer(m_pPlayer);
	m_pInventoryGUI->SetCharacterGUI(m_pCharacterGUI);
	m_pInventoryGUI->SetLootGUI(m_pLootGUI);
	m_pInventoryGUI->SetActionBar(m_pActionBar);
	m_pInventoryGUI->SetItemManager(m_pItemManager);
	m_pCharacterGUI->SetInventoryGUI(m_pInventoryGUI);
	m_pCharacterGUI->SetLootGUI(m_pLootGUI);
	m_pCharacterGUI->SetActionBar(m_pActionBar);
	m_pLootGUI->SetInventoryGUI(m_pInventoryGUI);
	m_pLootGUI->SetCharacterGUI(m_pCharacterGUI);
	m_pLootGUI->SetActionBar(m_pActionBar);
	m_pActionBar->SetInventoryGUI(m_pInventoryGUI);
	m_pActionBar->SetCharacterGUI(m_pCharacterGUI);
	m_pActionBar->SetLootGUI(m_pLootGUI);
	m_pQuestGUI->SetQuestJournal(m_pQuestJournal);
	m_pHUD->SetInventoryGUI(m_pInventoryGUI);
	m_pHUD->SetCharacterGUI(m_pCharacterGUI);
	m_pHUD->SetQuestGUI(m_pQuestGUI);
	m_pHUD->SetCraftingGUI(m_pCraftingGUI);

	/* Initial chunk creation (Must be after player pointer sent to chunks) */
	m_pChunkManager->InitializeChunkCreation();

	// Keyboard movement
	m_bKeyboardForward = false;
	m_bKeyboardBackward = false;
	m_bKeyboardStrafeLeft = false;
	m_bKeyboardStrafeRight = false;
	m_bKeyboardLeft = false;
	m_bKeyboardRight = false;
	m_bKeyboardUp = false;
	m_bKeyboardDown = false;
	m_bKeyboardSpace = false;
	m_bKeyboardMenu = false;

	// Joystick flags
	m_bJoystickJump = false;

	// Combat flags
	m_bAttackPressed_Mouse = false;
	m_bAttackReleased_Mouse = false;
	m_bAttackPressed_Joystick = false;
	m_bAttackReleased_Joystick = false;
	m_bCanDoAttack_Mouse = true;
	m_bCanDoAttack_Joystick = true;
	m_bTargetEnemyPressed_Joystick = false;
	m_bTargetEnemyReleased_Joystick = false;

	// Camera movement
	m_bCameraRotate = false;
	m_pressedX = 0;
	m_pressedY = 0;
	m_currentX = 0;
	m_currentY = 0;
	m_cameraDistance = m_pGameCamera->GetZoomAmount();
	m_maxCameraDistance = m_cameraDistance;

	// Auto camera mode
	m_autoCameraMovingModifier = 1.0f;

	// Enemy target camera mode
	m_targetCameraXAxisAmount = 0.0f;
	m_targetCameraXAxisAmount_Target = 0.0f;
	m_targetCameraYRatio = 0.0f;
	m_targetCameraForwardRatio = 0.0f;

	// Player movement
	m_keyboardMovement = false;
	m_gamepadMovement = false;
	m_movementSpeed = 0.0f;
	m_movementDragTime = 0.45f;
	m_movementIncreaseTime = 0.25f;
	m_maxMovementSpeed = 10.0f;
	m_movementStopThreshold = 0.05f;

	// Blur
	m_globalBlurAmount = 0.0f;

	// Cinematic letterbox mode
	m_letterBoxRatio = 0.0f;

	// Paperdoll rendering
	m_paperdollRenderRotation = 0.0f;

	// Toggle flags
	m_deferredRendering = true;
	m_modelWireframe = false;
	m_modelAnimationIndex = 0;
	m_multiSampling = true;
	m_ssao = true;
	m_blur = false;
	m_shadows = true;
	m_dynamicLighting = true;
	m_animationUpdate = true;
	m_fullscreen = m_pVoxSettings->m_fullscreen;
	m_debugRender = false;
	m_instanceRender = true;

	// Camera mode
	m_cameraMode = CameraMode_Debug;
	m_previousCameraMode = CameraMode_Debug;
	m_shouldRestorePreviousCameraMode = false;

	// Game mode
	m_gameMode = GameMode_Loading;
	m_allowToChangeToGame = true;
	m_allowToChangeToFrontend = true;
	SetGameMode(m_gameMode);

	// Create, setup and skin the GUI components
	CreateGUI();
	SetupGUI();
	SkinGUI();
}

// Destruction
void VoxGame::Destroy()
{
	if (c_instance)
	{
		delete m_pSkybox;
		delete m_pChunkManager;
		delete m_pItemManager;
		delete m_pInventoryManager;
		delete m_pPlayer;
		delete m_pNPCManager;
		delete m_pEnemyManager;
		delete m_pLightingManager;
		delete m_pSceneryManager;
		delete m_pBlockParticleManager;
		delete m_pTextEffectsManager;
		delete m_pInstanceManager;
		delete m_pBiomeManager;
		delete m_pQubicleBinaryManager;
		delete m_pFrontendManager;
		delete m_pModsManager;
		delete m_pGameCamera;
		delete m_pQuestManager;
		delete m_pQuestJournal;
		delete m_pInventoryGUI;
		delete m_pCharacterGUI;
		delete m_pLootGUI;
		delete m_pCraftingGUI;
		delete m_pQuestGUI;
		delete m_pActionBar;
		DestroyGUI();  // Destroy the GUI components before we delete the GUI manager object.
		delete m_pGUI;
		delete m_pRenderer;

		m_pVoxWindow->Destroy();

		delete m_pVoxWindow;

		delete c_instance;
	}
}

// Quitting
void VoxGame::CancelQuitPopup()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_None);

	SetPaused(false);

	SetGlobalBlurAmount(0.0f);

	TurnCursorOff();
}

void VoxGame::ShowQuitPopup()
{
	CloseAllGUIWindows();

	m_pFrontendManager->SetFrontendScreen(FrontendScreen_QuitPopup);

	SetPaused(true);

	SetGlobalBlurAmount(0.0015f);

	TurnCursorOn(true);
}

void VoxGame::SetGameQuit(bool quit)
{
	m_bGameQuit = quit;
}

// Pause
bool VoxGame::IsPaused()
{
	return m_bPaused;
}

void VoxGame::SetPaused(bool pause)
{
	m_bPaused = pause;
}

void VoxGame::SetPauseMenu()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_PauseMenu);

	SetPaused(true);

	SetGlobalBlurAmount(0.0015f);

	TurnCursorOn(true);
}

void VoxGame::UnsetPauseMenu()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_None);

	SetPaused(false);

	SetGlobalBlurAmount(0.0f);

	TurnCursorOff();
}

// Blur
void VoxGame::SetGlobalBlurAmount(float blurAmount)
{
	m_globalBlurAmount = blurAmount;
	m_pBlurCheckBox->SetToggled(m_globalBlurAmount > 0.0f);
}

// Cinematic letterbox
void VoxGame::OpenLetterBox()
{
	Interpolator::GetInstance()->AddFloatInterpolation(&m_letterBoxRatio, m_letterBoxRatio, 1.0f, 0.25f, -100.0f);
}

void VoxGame::CloseLetterBox()
{
	Interpolator::GetInstance()->AddFloatInterpolation(&m_letterBoxRatio, m_letterBoxRatio, 0.0f, 0.25f, 100.0f);
}

// Paperdoll rendering
void VoxGame::SetPaperdollRotation(float rotation)
{
	m_paperdollRenderRotation = rotation;
}

void VoxGame::RotatePaperdollModel(float rot)
{
	m_paperdollRenderRotation += rot;// * m_deltaTime;
}

unsigned int VoxGame::GetDynamicPaperdollTexture()
{
	return m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_paperdollSSAOTextureBuffer);
}

// Events
void VoxGame::PollEvents()
{
	m_pVoxWindow->PollEvents();
}

bool VoxGame::ShouldClose()
{
	return m_bGameQuit;
}

// Window functionality
int VoxGame::GetWindowCursorX()
{
	return m_pVoxWindow->GetCursorX();
}

int VoxGame::GetWindowCursorY()
{
	return m_pVoxWindow->GetCursorY();
}

void VoxGame::ResizeWindow(int width, int height)
{
	m_windowWidth = width;
	m_windowHeight = height;

	m_pVoxWindow->ResizeWindow(m_windowWidth, m_windowHeight);

	if(m_pRenderer)
	{
		// Let the renderer know we have resized the window
		m_pRenderer->ResizeWindow(m_windowWidth, m_windowHeight);

		// Resize the main viewport
		m_pRenderer->ResizeViewport(m_defaultViewport, 0, 0, m_windowWidth, m_windowHeight, 60.0f);
		m_pRenderer->ResizeViewport(m_firstpersonViewport, 0, 0, m_windowWidth, m_windowHeight, 60.0f);
		m_pRenderer->ResizeViewport(m_paperdollViewport, m_paperdollViewportY, m_paperdollViewportX, m_paperdollViewportWidth, m_paperdollViewportHeight, 60.0f);

		// Resize the frame buffers
		bool frameBufferResize = false;
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_SSAOFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "SSAO", &m_SSAOFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_shadowFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 5.0f, "Shadow", &m_shadowFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_lightingFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Deferred Lighting", &m_lightingFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_transparencyFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "Transparency", &m_transparencyFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_FXAAFrameBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FXAA", &m_FXAAFrameBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_firstPassFullscreenBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 1st Pass", &m_firstPassFullscreenBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_secondPassFullscreenBuffer, true, true, true, true, m_windowWidth, m_windowHeight, 1.0f, "FullScreen 2nd Pass", &m_secondPassFullscreenBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_paperdollBuffer, true, true, true, true, 800, 800, 1.0f, "Paperdoll", &m_paperdollBuffer);
		frameBufferResize = m_pRenderer->CreateFrameBuffer(m_paperdollSSAOTextureBuffer, true, true, true, true, 800, 800, 1.0f, "Paperdoll SSAO Texture", &m_paperdollSSAOTextureBuffer);
		
		// Give the new windows dimensions to the GUI components also
		m_pMainWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
		m_pGameWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
		m_pConsoleWindow->SetApplicationDimensions(m_windowWidth, m_windowHeight);
	}

	// Frontend
	if (m_pFrontendManager)
	{
		m_pFrontendManager->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}

	// Resize game GUI
	if (m_pInventoryGUI)
	{
		m_pInventoryGUI->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
	if (m_pCharacterGUI)
	{
		m_pCharacterGUI->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
	if (m_pLootGUI)
	{
		m_pLootGUI->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
	if (m_pCraftingGUI)
	{
		m_pCraftingGUI->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
	if (m_pActionBar)
	{
		m_pActionBar->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
	if (m_pHUD)
	{
		m_pHUD->SetWindowDimensions(m_windowWidth, m_windowHeight);
	}
}

void VoxGame::CloseWindow()
{
	if (m_gameMode == GameMode_Game)
	{
		ShowQuitPopup();
	}
	else
	{
		m_bGameQuit = true;
	}
}

void VoxGame::UpdateJoySticks()
{
	m_pVoxWindow->UpdateJoySticks();
}

// Game functions
void VoxGame::QuitToFrontEnd()
{
	TurnCursorOn(true);
	SetGameMode(GameMode_FrontEnd);

	m_pFrontEndOptionBox->SetToggled(true);
	m_pFrontendCameraOptionBox->SetToggled(true);
	m_pMouseRotateCameraOptionBox->SetDisabled(true);
	m_pAutoCameraOptionBox->SetDisabled(true);
	m_pFrontendCameraOptionBox->SetDisabled(false);
	m_pDebugCameraOptionBox->SetDisabled(false);
	m_pVoxWindow->Update(m_deltaTime);
	GameModeChanged();
	CameraModeChanged();

	// Make sure that movement speed drag is reset, so that we dont carry on moving after quitting and restarting game
	m_movementSpeed = 0.0f;

	// Set front-end page to intro
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_MainMenu);
}

void VoxGame::SetupDataForGame()
{
	// Items
	Item* pFurnace = m_pItemManager->CreateItem(vec3(25.0f, 10.0f, -5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), "media/gamedata/items/Furnace/Furnace.item", eItem_Furnace, "Furnace", true, false, 0.16f);
	pFurnace->SetInteractionPositionOffset(vec3(0.0f, 0.0f, -2.0f));
	Item* pAnvil = m_pItemManager->CreateItem(vec3(32.0f, 9.0f, -1.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), "media/gamedata/items/Anvil/Anvil.item", eItem_Anvil, "Anvil", true, false, 0.14f);
	pAnvil->SetInteractionPositionOffset(vec3(0.0f, 0.0f, -1.5f));
	Item* pChest = m_pItemManager->CreateItem(vec3(24.0f, 12.0f, 13.5f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 180.0f, 0.0f), "media/gamedata/items/Chest/Chest.item", eItem_Chest, "Chest", true, false, 0.08f);

	// Npcs
	NPC* pCharacter1 = m_pNPCManager->CreateNPC("Mage", "Human", "Mage", vec3(21.0f, 8.5f, 20.0f), 0.08f, false, true);
	pCharacter1->SetTargetForwards(vec3(0.0f, 0.0f, -1.0f));
	pCharacter1->SetNPCCombatType(eNPCCombatType_Staff, true);

	// Enemies
	Enemy* pEnemy0 = m_pEnemyManager->CreateEnemy(vec3(35.5f, 12.0f, 5.5f), eEnemyType_RedSlime, 0.08f);

	// Quests
	// Quest 1
	string startText1 = "Hello there brave adventurer, my name is [C=Custom(00A2E8)]Melinda The Witch[C=White] and I have stumbled across a 'valuable treasure'. I can give you this treasure if you will do a quest for me...\nI need you to kill these pesky [C=Red]slimes[C=White] that are overrunning this place. If you do this for me, the treasure is yours. What do you say?";
	string completedText1 = "You have completed the quest, and destroyed the sliminess of these lands, well done!";
	string denyText1 = "You are already on a quest, come back to me once you have finished.";
	Quest* pSlimeQuest = m_pQuestManager->CreateQuest("A Simple Task", startText1, completedText1, denyText1);
	pSlimeQuest->AddQuestObjective("Kill 5 Slimes", QuestType_KillX, 5, eEnemyType_GreenSlime, eItem_None, NULL, "", NULL);
	InventoryItem* pQuestReward1 = m_pInventoryManager->CreateInventoryItem("media/gamedata/weapons/Sword/Sword.weapon", "media/textures/items/sword.tga", InventoryType_Weapon_Sword, eItem_None, ItemStatus_None, EquipSlot_RightHand, ItemQuality_Common, false, false, "Sword", "Attacking enemies.", 1.0f, 1.0f, 1.0f, -1, -1, -1, -1, -1);
	pSlimeQuest->SetQuestReward(pQuestReward1);
	pSlimeQuest->ExportQuest();
	// Quest 2
	string startText2 = "You look like the type of adventurer who really needs some copper, Please could you be a good fella and collect some copper nuggets for me, they are required for refining into copper bars.";
	string completedText2 = "Wow... thank you for collecting the copper nuggets, you can keep it as a reward.";
	string denyText2 = "You are already on a quest, come back to me once you have finished.";
	Quest* pCollectQuest = m_pQuestManager->CreateQuest("A Simple Collection", startText2, completedText2, denyText2);
	pCollectQuest->AddQuestObjective("Collect 5 Copper Nuggets", QuestType_CollectX, 5, eEnemyType_None, eItem_CopperOre, NULL, "", NULL);
	InventoryItem* pQuestReward2 = m_pInventoryManager->CreateInventoryItem("media/gamedata/items/CopperOre/CopperOre.item", "media/textures/items/copper_ore.tga", InventoryType_Item, eItem_CopperOre, ItemStatus_None, EquipSlot_LeftHand, ItemQuality_Common, false, false, "Copper Nugget", "", 1.0f, 1.0f, 1.0f, 5, -1, -1, -1, -1);
	pCollectQuest->SetQuestReward(pQuestReward2);
	pCollectQuest->ExportQuest();

	m_pQuestJournal->AddQuestJournalEntry(pSlimeQuest);
	m_pQuestJournal->AddQuestJournalEntry(pCollectQuest);
}

void VoxGame::SetupDataForFrontEnd()
{
}

void VoxGame::StartGameFromFrontEnd()
{
	m_pFrontendManager->SetFrontendScreen(FrontendScreen_None);

	m_previousCameraMode = CameraMode_MouseRotate;
	m_pGameOptionBox->SetToggled(true);
	m_pMouseRotateCameraOptionBox->SetToggled(true);
	m_pFrontendCameraOptionBox->SetDisabled(true);
	GameModeChanged();
	CameraModeChanged();

	// Start game from player
	m_pPlayer->StartGame();
}

void VoxGame::PlayerRespawned()
{
	// Stop any movement drag when we respawn
	m_movementSpeed = 0.0f;
}

void VoxGame::SetGameMode(GameMode mode)
{
	GameMode previousgameMode = m_gameMode;
	m_gameMode = mode;

	if (m_gameMode == GameMode_Debug)
	{
	}

	if (m_gameMode == GameMode_FrontEnd)
	{
		if (previousgameMode == GameMode_Game || previousgameMode == GameMode_Loading)
		{
			// Close all open GUI windows
			CloseAllGUIWindows();

			// Clear the items
			m_pItemManager->ClearItems();

			// Clear the NPCs
			m_pNPCManager->ClearNPCs();

			// Clear the enemies and enemy spawners
			m_pEnemyManager->ClearEnemies();
			m_pEnemyManager->ClearEnemySpawners();

			// Reset the inventory manager
			m_pInventoryManager->Reset();

			// Reset the player
			m_pPlayer->ResetPlayer();

			// Unload actionbar
			if (m_pActionBar->IsLoaded())
			{
				m_pActionBar->Unload();
			}

			// Unload the HUD
			if (m_pHUD->IsLoaded())
			{
				m_pHUD->Unload();
			}

			// Setup the gamedata since we have just loaded fresh into the frontend.
			SetupDataForFrontEnd();
		}
	}

	if (m_gameMode == GameMode_Game)
	{
		if (previousgameMode == GameMode_FrontEnd || previousgameMode == GameMode_Loading)
		{
			// Close all open GUI windows
			CloseAllGUIWindows();

			// Clear the items
			m_pItemManager->ClearItems();

			// Clear the NPCs
			m_pNPCManager->ClearNPCs();

			// Clear the enemies and enemy spawners
			m_pEnemyManager->ClearEnemies();
			m_pEnemyManager->ClearEnemySpawners();

			// Reset the player
			m_pPlayer->ResetPlayer();

			// Load action bar
			if (m_pActionBar->IsLoaded() == false)
			{
				m_pActionBar->Load();
			}

			// Load the HUD
			if (m_pHUD->IsLoaded() == false)
			{
				m_pHUD->Load();
			}

			// Setup the gamedata since we have just loaded fresh into a game.
			SetupDataForGame();
		}
	}
}

GameMode VoxGame::GetGameMode()
{
	return m_gameMode;
}

void VoxGame::SetCameraMode(CameraMode mode)
{
	m_cameraMode = mode;
}

CameraMode VoxGame::GetCameraMode()
{
	return m_cameraMode;
}

// Interactions
bool VoxGame::CheckInteractions()
{
	bool interaction = false;

	if (m_bPaused)
	{
		return false;
	}

	if (m_pPlayer->CanJump() == false)
	{
		// Don't allow interactions if we are jumping
		return false;
	}

	if (m_pPlayer->IsDead())
	{
		// Don't allow interactions if the player is dead.
		return false;
	}

	if (m_pPlayer->GetTargetEnemy() != NULL)
	{
		// Don't allow interactions while we are in target mode
		return false;
	}

	// Check item interactions
	m_interactItemMutex.lock();
	if (interaction == false && m_pInteractItem != NULL)
	{
		// Stop any movement drag when we interact with item
		m_movementSpeed = 0.0f;

		// Dropped items become collectible by the player and magnet towards him
		if (m_pInteractItem->GetItemType() == eItem_DroppedItem)
		{
			if (m_pInventoryManager->CanAddInventoryItem(m_pInteractItem->GetDroppedInventoryItem()->m_title.c_str(), m_pInteractItem->GetDroppedInventoryItem()->m_item, m_pInteractItem->GetDroppedInventoryItem()->m_quantity))
			{
				m_pInteractItem->SetIsCollectible(true);
				m_pInteractItem->SetCollectionDelay(0.0f);
			}

			interaction = true;
		}

		// Open/close door
		if (m_pInteractItem->GetItemType() == eItem_Door)
		{
			m_pInteractItem->Interact();

			interaction = true;
		}

		// Sitting in chair
		if (m_pInteractItem->GetItemType() == eItem_Chair)
		{
			m_pInteractItem->Interact();
			m_pPlayer->StopMoving();

			interaction = true;
		}

		// Crafting stations
		if (m_pInteractItem->GetItemType() == eItem_Anvil || m_pInteractItem->GetItemType() == eItem_Furnace)
		{
			m_pPlayer->StopMoving();

			// Load crafting GUI
			if (m_pCraftingGUI->IsLoaded() == false)
			{
				m_pCraftingGUI->SetCraftingRecipesForItem(m_pInteractItem->GetItemType());
				m_pCraftingGUI->Load(true, 0.9f);
				m_pCraftingGUI->SetInteractionitem(m_pInteractItem);

				SavePreviousCameraMode();
				m_shouldRestorePreviousCameraMode = true;
				TurnCursorOn(true);
			}

			// Set NPC dialog camera mode
			SetCameraMode(CameraMode_NPCDialog);

			// Figure out which way to position the camera, based on how we are looking at the NPC when interacting
			vec3 toItem = normalize(m_pInteractItem->GetCenter() - m_pInteractItem->GetInteractionPosition());
			vec3 crossResult = cross(vec3(0.0f, 1.0f, 0.0f), toItem);
			float dotAngle = dot(m_pGameCamera->GetFacing(), crossResult);
			if (dotAngle > 0.5f)
			{
				vec3 center = (m_pInteractItem->GetCenter() - m_pInteractItem->GetInteractionPosition());
				vec3 crossRight = cross(normalize(center), vec3(0.0f, 1.0f, 0.0f));
				m_targetCameraPosition_NPCDialog = (m_pInteractItem->GetInteractionPosition() + center*2.0f + crossRight*4.0f + vec3(0.0f, 1.0f, 0.0f)*2.5f);
				m_targetCameraView_NPCDialog = (m_pInteractItem->GetInteractionPosition() + center*0.0f - crossRight*4.0f);
			}
			else
			{
				vec3 center = (m_pInteractItem->GetCenter() - m_pInteractItem->GetInteractionPosition());
				vec3 crossRight = cross(normalize(center), vec3(0.0f, 1.0f, 0.0f));
				m_targetCameraPosition_NPCDialog = (m_pInteractItem->GetInteractionPosition() + center*2.0f - crossRight*4.0f + vec3(0.0f, 1.0f, 0.0f)*2.5f);
				m_targetCameraView_NPCDialog = (m_pInteractItem->GetInteractionPosition() + center*0.0f + crossRight*4.0f);
			}

			// Player move to interaction point and look at interaction item
			m_pPlayer->SetMoveToTargetPosition(m_pInteractItem->GetInteractionPosition());
			m_pPlayer->SetLookAtTargetAfterMoveToPosition(m_pInteractItem->GetCenter());

			// Set player alpha to full opacity
			m_pPlayer->SetPlayerAlpha(1.0f);

			// Open cinematic letterbox
			OpenLetterBox();

			interaction = true;
		}

		// Chest interaction
		if (m_pInteractItem->GetItemType() == eItem_Chest)
		{
			if (m_pInteractItem->IsStillAnimating() == false)
			{
				m_pInteractItem->Interact();

				interaction = true;

				if (m_pInteractItem->IsInteracting() == true) // Only open the GUI screens if we are opening a chest
				{
					m_pPlayer->StopMoving();

					if (m_pLootGUI->IsLoaded())
					{
						m_pLootGUI->Unload();

						if (IsGUIWindowStillDisplayed() == false)
						{
							TurnCursorOff();
						}
					}
					else if (m_pFrontendManager->GetFrontendScreen() == FrontendScreen_None)
					{
						m_pLootGUI->LoadItems(m_pInteractItem);

						m_pLootGUI->Load(true, 1.0f);

						if (m_pInventoryGUI->IsLoaded() == false)
						{
							m_pInventoryGUI->Load(true, 1.0f);
						}

						m_pPlayer->StopMoving();

						TurnCursorOn(true);
					}
				}
			}
		}
	}
	m_interactItemMutex.unlock();

	return interaction;
}

Item* VoxGame::GetInteractItem()
{
	return m_pInteractItem;
}

// Enemy Targeting
void VoxGame::SetEnemyTarget()
{
	if (m_pPlayer->IsDead() == false && m_pPlayer->GetTargetEnemy() == NULL)
	{
		// Get the enemy based on the cursor
		int cursorX = (int)(m_windowWidth*0.5f);
		int cursorY = (int)(m_windowHeight*0.5f);

		Enemy* pEnemy = NULL;
		pEnemy = m_pEnemyManager->GetCursorEnemy(m_pGameCamera, cursorX, cursorY);

		if (pEnemy != NULL && pEnemy->GetErase() == false)
		{
			// Set the player's enemy pointer
			m_pPlayer->SetTargetEnemy(pEnemy);
			pEnemy->SetOutlineRender(true);

			// Set player alpha
			m_pPlayer->SetPlayerAlpha(0.6f);

			// Set target camera
			SavePreviousCameraMode();
			m_shouldRestorePreviousCameraMode = true;
			SetCameraMode(CameraMode_EnemyTarget);

			// Open cinematic letter box
			OpenLetterBox();
		}
	}
}

void VoxGame::ReleaseEnemyTarget()
{
	if (m_pPlayer->GetTargetEnemy() != NULL)
	{
		m_pPlayer->GetTargetEnemy()->SetOutlineRender(false);
		m_pPlayer->SetTargetEnemy(NULL);

		// Reset player alpha
		m_pPlayer->SetPlayerAlpha(1.0f);

		// Return back to the previous camera state
		if (ShouldRestorePreviousCameraMode())
		{
			RestorePreviousCameraMode();
			InitializeCameraRotation();
		}

		// Close cinematic letter box
		CloseLetterBox();
	}
}

// GUI Helper functions
bool VoxGame::IsGUIWindowStillDisplayed()
{
	if (m_pInventoryGUI->IsLoaded())
	{
		return true;
	}

	if (m_pCharacterGUI->IsLoaded())
	{
		return true;
	}

	if (m_pLootGUI->IsLoaded())
	{
		return true;
	}

	if (m_pCraftingGUI->IsLoaded())
	{
		return true;
	}

	if (m_pQuestGUI->IsLoaded())
	{
		return true;
	}

	return false;
}

void VoxGame::CloseAllGUIWindows()
{
	if (m_pInventoryGUI->IsLoaded() && m_pInventoryGUI->IsLoadDelayed() == false)
	{
		m_pInventoryGUI->Unload();
	}

	if (m_pCharacterGUI->IsLoaded() && m_pCharacterGUI->IsLoadDelayed() == false)
	{
		m_pCharacterGUI->Unload();
	}

	if (m_pLootGUI->IsLoaded() && m_pLootGUI->IsLoadDelayed() == false)
	{
		m_pLootGUI->Unload();
	}

	if (m_pCraftingGUI->IsLoaded() && m_pCraftingGUI->IsLoadDelayed() == false)
	{
		m_pCraftingGUI->Unload();
	}

	if (m_pQuestGUI->IsLoaded() && m_pQuestGUI->IsLoadDelayed() == false)
	{
		m_pQuestGUI->Unload();
	}
	
	// Reset focus, also resets any text entry that we might have been doing.
	m_pGUI->ResetFocus();
}

void VoxGame::TurnCursorOn(bool resetCursorPosition)
{
	m_pVoxWindow->TurnCursorOn(resetCursorPosition);
}

void VoxGame::TurnCursorOff()
{
	m_pVoxWindow->TurnCursorOff();

	// Make sure to set the current X and Y when we turn the cursor off, so that camera controls don't glitch.
	m_currentX = m_pVoxWindow->GetCursorX();
	m_currentY = m_pVoxWindow->GetCursorY();
}

// Accessors
unsigned int VoxGame::GetDefaultViewport()
{
	return m_defaultViewport;
}

Player* VoxGame::GetPlayer()
{
	return m_pPlayer;
}

FrontendManager* VoxGame::GetFrontendManager()
{
	return m_pFrontendManager;
}

BlockParticleManager* VoxGame::GetBlockParticleManager()
{
	return m_pBlockParticleManager;
}

NPCManager* VoxGame::GetNPCManager()
{
	return m_pNPCManager;
}

ItemManager* VoxGame::GetItemManager()
{
	return m_pItemManager;
}

ModsManager* VoxGame::GetModsManager()
{
	return m_pModsManager;
}

CharacterGUI* VoxGame::GetCharacterGUI()
{
	return m_pCharacterGUI;
}

QuestGUI* VoxGame::GetQuestGUI()
{
	return m_pQuestGUI;
}

HUD* VoxGame::GetHUD()
{
	return m_pHUD;
}

VoxSettings* VoxGame::GetVoxSettings()
{
	return m_pVoxSettings;
}