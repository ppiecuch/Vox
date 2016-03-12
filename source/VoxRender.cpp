// ******************************************************************************
// Filename:    VoxRender.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Revision History:
//   Initial Revision - 27/10/15
//
// Copyright (c) 2005-2015, Steven Ball
// ******************************************************************************

#include "VoxGame.h"

#include <glm/detail/func_geometric.hpp>


// Rendering
void VoxGame::PreRender()
{
	// Update matrices for game objects
	m_pPlayer->CalculateWorldTransformMatrix();
	m_pItemManager->CalculateWorldTransformMatrix();
	m_pProjectileManager->CalculateWorldTransformMatrix();
}

void VoxGame::BeginShaderRender()
{
	glShader* pShader = NULL;

	if (m_shadows)
	{
		m_pRenderer->BeginGLSLShader(m_shadowShader);

		pShader = m_pRenderer->GetShader(m_shadowShader);
		GLuint shadowMapUniform = glGetUniformLocationARB(pShader->GetProgramObject(), "ShadowMap");
		m_pRenderer->PrepareShaderTexture(7, shadowMapUniform);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_shadowFrameBuffer));
		glUniform1iARB(glGetUniformLocationARB(pShader->GetProgramObject(), "renderShadow"), m_shadows);
		glUniform1iARB(glGetUniformLocationARB(pShader->GetProgramObject(), "alwaysShadow"), false);
	}
	else
	{
		m_pRenderer->BeginGLSLShader(m_defaultShader);
	}
}

void VoxGame::EndShaderRender()
{
	if (m_shadows)
	{
		m_pRenderer->EndGLSLShader(m_shadowShader);
	}
	else
	{
		m_pRenderer->EndGLSLShader(m_defaultShader);
	}
}

void VoxGame::Render()
{
	if (m_pVoxWindow->GetMinimized())
	{
		// Don't call any render functions if minimized
		return;
	}

	// Begin rendering
	m_pRenderer->BeginScene(true, true, true);

		// Shadow rendering to the shadow frame buffer
		if (m_shadows)
		{
			RenderShadows();
		}

		// SSAO frame buffer rendering start
		if (m_deferredRendering)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_SSAOFrameBuffer);
		}

		// ---------------------------------------
		// Render 3d
		// ---------------------------------------
		m_pRenderer->PushMatrix();
			// Set the default projection mode
			m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);

			// Set back culling as default
			m_pRenderer->SetCullMode(CM_BACK);

			// Set default depth test
			m_pRenderer->EnableDepthTest(DT_LESS);

			// Set the lookat camera
			m_pGameCamera->Look();

			// Enable the lights
			m_pRenderer->PushMatrix();
				m_pRenderer->EnableLight(m_defaultLight, 0);
			m_pRenderer->PopMatrix();

			// Multisampling MSAA
			if (m_multiSampling)
			{
				m_pRenderer->EnableMultiSampling();
			}
			else
			{
				m_pRenderer->DisableMultiSampling();
			}

			// Render the lights (DEBUG)
			m_pRenderer->PushMatrix();
				m_pRenderer->SetCullMode(CM_BACK);
				m_pRenderer->SetRenderMode(RM_SOLID);
				m_pRenderer->RenderLight(m_defaultLight);
			m_pRenderer->PopMatrix();

			// Render the skybox
			RenderSkybox();

			BeginShaderRender();
			{
				// Render the chunks
				m_pChunkManager->Render(false);
			}
			EndShaderRender();

			// Render items outline and silhouette before the world/chunks
			m_pItemManager->Render(true, false, false, false);
			m_pItemManager->Render(false, false, true, false);

			BeginShaderRender();
			{
				// Scenery
				m_pSceneryManager->Render(false, false, false, false, false);

				// Projectiles
				m_pProjectileManager->Render();

				// Items
				m_pItemManager->Render(false, false, false, false);
			}
			EndShaderRender();

			// Render the block particles
			m_pBlockParticleManager->Render();

			// Render the instanced objects
			if(m_instanceRender)
			{
				m_pInstanceManager->Render();
			}

			BeginShaderRender();
			{

				if (m_gameMode != GameMode_FrontEnd)
				{
					// Render the player
					if (m_cameraMode == CameraMode_FirstPerson)
					{
						m_pPlayer->RenderFirstPerson();
					}
					else
					{
						m_pPlayer->Render();
					}
				}
			}
			EndShaderRender();

			// Debug rendering
			if(m_debugRender)
			{
				m_pLightingManager->DebugRender();

				m_pBlockParticleManager->RenderDebug();

				if (m_gameMode != GameMode_FrontEnd)
				{
					m_pPlayer->RenderDebug();
				}

				m_pSceneryManager->RenderDebug();

				m_pItemManager->RenderDebug();

				m_pChunkManager->RenderDebug();

				m_pProjectileManager->RenderDebug();

				if (m_gameMode == GameMode_FrontEnd)
				{
					m_pFrontendManager->RenderDebug();
				}
			}
		m_pRenderer->PopMatrix();

		// Render the deferred lighting pass
		if (m_dynamicLighting)
		{
			RenderDeferredLighting();
		}

		// SSAO frame buffer rendering stop
		if (m_deferredRendering)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_SSAOFrameBuffer);
		}

		// Render other viewports
		// Paperdoll for CharacterGUI
		RenderPaperdollViewport();

		// ---------------------------------------
		// Render transparency
		// ---------------------------------------
		RenderTransparency();

		// Render the SSAO texture
		if (m_deferredRendering)
		{
			RenderSSAOTexture();

			if (m_multiSampling && m_fxaaShader != -1)
			{
				RenderFXAATexture();
			}

			if(m_blur)
			{
				RenderFirstPassFullScreen();
				RenderSecondPassFullScreen();
			}
		}

		// ---------------------------------------
		// Render 2d
		// ---------------------------------------
		m_pRenderer->PushMatrix();
			// Crosshair
			if (m_cameraMode == CameraMode_FirstPerson)
			{
				RenderCrosshair();
			}

			// Text effects
			m_pTextEffectsManager->Render();

			// Cinematic mode (letter box)
			RenderCinematicLetterBox();
		m_pRenderer->PopMatrix();

		// Disable multisampling for 2d gui and text
		m_pRenderer->DisableMultiSampling();

		// Render other deferred rendering pipelines
		// Paperdoll SSAO for CharacterGUI
		RenderDeferredRenderingPaperDoll();

		// Render debug information and text
		RenderDebugInformation();

		// Render the chunks 2d
		if (m_debugRender)
		{
			//m_pChunkManager->Render2D(m_pGameCamera, m_defaultViewport, m_defaultFont);
		}

		// Frontend 2D
		if(m_gameMode == GameMode_FrontEnd)
		{			
			m_pRenderer->PushMatrix();
				m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
				m_pRenderer->SetCullMode(CM_BACK);

				m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

				m_pFrontendManager->Render2D();
			m_pRenderer->PopMatrix();
		}

		// Render the GUI
		RenderGUI();

	// End rendering
	m_pRenderer->EndScene();


	// Pass render call to the window class, allow to swap buffers
	m_pVoxWindow->Render();
}

void VoxGame::RenderSkybox()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->BeginGLSLShader(m_cubeMapShader);

		glShader* pShader = m_pRenderer->GetShader(m_cubeMapShader);
		unsigned int cubemapTexture1 = glGetUniformLocationARB(pShader->GetProgramObject(), "cubemap1");
		m_pRenderer->PrepareShaderTexture(0, cubemapTexture1);
		m_pRenderer->BindCubeTexture(m_pSkybox->GetCubeMapTexture1());

		//unsigned int cubemapTexture2 = glGetUniformLocationARB(pShader->GetProgramObject(), "cubemap2");
		//m_pRenderer->PrepareShaderTexture(1, cubemapTexture2);
		//m_pRenderer->BindCubeTexture(m_pSkybox->GetCubeMapTexture2());

		pShader->setUniform1f("skyboxRatio", 0.0f);

		m_pRenderer->TranslateWorldMatrix(m_pPlayer->GetCenter().x, m_pPlayer->GetCenter().y, m_pPlayer->GetCenter().z);
		m_pSkybox->Render();
				
		m_pRenderer->EmptyCubeTextureIndex(0);
		//m_pRenderer->EmptyCubeTextureIndex(1);

		m_pRenderer->EmptyTextureIndex(2);
		m_pRenderer->EmptyTextureIndex(1);
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_cubeMapShader);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderShadows()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->StartRenderingToFrameBuffer(m_shadowFrameBuffer);
		m_pRenderer->SetColourMask(false, false, false, false);

		float loaderRadius = m_pChunkManager->GetLoaderRadius();
		m_pRenderer->SetupOrthographicProjection(-loaderRadius, loaderRadius, -loaderRadius, loaderRadius, 0.01f, 1000.0f);
		vec3 lightPos = m_defaultLightPosition + m_pPlayer->GetCenter(); // Make sure our light is always offset from the player
		m_pRenderer->SetLookAtCamera(vec3(lightPos.x, lightPos.y, lightPos.z), m_pPlayer->GetCenter(), vec3(0.0f, 1.0f, 0.0f));

		m_pRenderer->PushMatrix();
			m_pRenderer->SetCullMode(CM_FRONT);

			// Render the chunks
			m_pChunkManager->Render(true);

			if (m_gameMode != GameMode_FrontEnd)
			{
				// Render the player
				m_pPlayer->Render();
			}

			// Projectiles
			m_pProjectileManager->Render();

			// Scenery
			m_pSceneryManager->Render(false, false, true, false, false);

			// Items
			m_pItemManager->Render(false, false, false, true);

			// Render the block particles
			m_pBlockParticleManager->Render();

			// Render the instanced objects
			if(m_instanceRender)
			{
				m_pInstanceManager->Render();
			}

			m_pRenderer->SetTextureMatrix();
			m_pRenderer->SetCullMode(CM_BACK);
		m_pRenderer->PopMatrix();

		m_pRenderer->SetColourMask(true, true, true, true);
		m_pRenderer->StopRenderingToFrameBuffer(m_shadowFrameBuffer);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderDeferredLighting()
{
	// Render deferred lighting to light frame buffer
	m_pRenderer->PushMatrix();
		m_pRenderer->StartRenderingToFrameBuffer(m_lightingFrameBuffer);

		m_pRenderer->SetFrontFaceDirection(FrontFaceDirection_CW);
		m_pRenderer->EnableTransparency(BF_ONE, BF_ONE);
		m_pRenderer->DisableDepthTest();

		// Set the default projection mode
		m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);

		// Set the lookat camera
		m_pGameCamera->Look();

		m_pRenderer->PushMatrix();
			m_pRenderer->BeginGLSLShader(m_lightingShader);

			glShader* pLightShader = m_pRenderer->GetShader(m_lightingShader);
			unsigned NormalsID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "normals");
			unsigned PositionssID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "positions");
			unsigned DepthsID = glGetUniformLocationARB(pLightShader->GetProgramObject(), "depths");

			m_pRenderer->PrepareShaderTexture(0, NormalsID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetNormalTextureFromFrameBuffer(m_SSAOFrameBuffer));

			m_pRenderer->PrepareShaderTexture(1, PositionssID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetPositionTextureFromFrameBuffer(m_SSAOFrameBuffer));

			m_pRenderer->PrepareShaderTexture(2, DepthsID);
			m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_SSAOFrameBuffer));

			pLightShader->setUniform1i("screenWidth", m_windowWidth);
			pLightShader->setUniform1i("screenHeight", m_windowHeight);
			pLightShader->setUniform1f("nearZ", 0.01f);
			pLightShader->setUniform1f("farZ", 1000.0f);

			for (int i = 0; i < m_pLightingManager->GetNumLights(); i++)
			{
				DynamicLight* lpLight = m_pLightingManager->GetLight(i);
				float lightRadius = lpLight->m_radius;

				vec3 cameraPos = vec3(m_pGameCamera->GetPosition().x, m_pGameCamera->GetPosition().y, m_pGameCamera->GetPosition().z);
				float length = glm::distance(cameraPos, lpLight->m_position);
				if (length < lightRadius + 0.5f) // Small change to account for differences in circle render (with slices) and circle radius
				{
					m_pRenderer->SetCullMode(CM_BACK);
				}
				else
				{
					m_pRenderer->SetCullMode(CM_FRONT);
				}

				pLightShader->setUniform1f("radius", lightRadius);
				pLightShader->setUniform1f("diffuseScale", lpLight->m_diffuseScale);

				float r = lpLight->m_colour.GetRed();
				float g = lpLight->m_colour.GetGreen();
				float b = lpLight->m_colour.GetBlue();
				float a = lpLight->m_colour.GetAlpha();
				pLightShader->setUniform4f("diffuseLightColor", r, g, b, a);

				m_pRenderer->PushMatrix();
					m_pRenderer->SetRenderMode(RM_SOLID);
					m_pRenderer->TranslateWorldMatrix(lpLight->m_position.x, lpLight->m_position.y + 0.5f, lpLight->m_position.z);
					m_pRenderer->DrawSphere(lightRadius, 30, 30);
				m_pRenderer->PopMatrix();
			}

			m_pRenderer->EmptyTextureIndex(2);
			m_pRenderer->EmptyTextureIndex(1);
			m_pRenderer->EmptyTextureIndex(0);

			m_pRenderer->EndGLSLShader(m_lightingShader);

		m_pRenderer->PopMatrix();

		m_pRenderer->SetFrontFaceDirection(FrontFaceDirection_CCW);
		m_pRenderer->DisableTransparency();
		m_pRenderer->SetCullMode(CM_BACK);
		m_pRenderer->EnableDepthTest(DT_LESS);

		m_pRenderer->StopRenderingToFrameBuffer(m_lightingFrameBuffer);

	m_pRenderer->PopMatrix();
}

void VoxGame::RenderTransparency()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_defaultViewport);
		m_pRenderer->SetCullMode(CM_BACK);

		// Set the lookat camera
		m_pGameCamera->Look();

		if (m_deferredRendering)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_transparencyFrameBuffer);
		}

		if (m_gameMode != GameMode_FrontEnd)
		{
			// Render the player's face
			if (m_cameraMode != CameraMode_FirstPerson)
			{
				m_pPlayer->RenderFace();
			}

			// Render the player's weapon trails
			m_pPlayer->RenderWeaponTrails();
		}

		// Projectile trails
		m_pProjectileManager->RenderWeaponTrails();

		if (m_deferredRendering)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_transparencyFrameBuffer);
		}
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderSSAOTexture()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		if (m_multiSampling)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_FXAAFrameBuffer);
		}
		else if (m_blur)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_firstPassFullscreenBuffer);
		}

		// SSAO shader
		m_pRenderer->BeginGLSLShader(m_SSAOShader);
		glShader* pShader = m_pRenderer->GetShader(m_SSAOShader);

		unsigned int textureId0 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_DepthTexture");
		m_pRenderer->PrepareShaderTexture(0, textureId0);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_SSAOFrameBuffer));

		unsigned int textureId1 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_RenderedTexture");
		m_pRenderer->PrepareShaderTexture(1, textureId1);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_SSAOFrameBuffer));

		unsigned int textureId2 = glGetUniformLocationARB(pShader->GetProgramObject(), "light");
		m_pRenderer->PrepareShaderTexture(2, textureId2);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_lightingFrameBuffer));

		unsigned int textureId3 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_TransparentTexture");
		m_pRenderer->PrepareShaderTexture(3, textureId3);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_transparencyFrameBuffer));

		unsigned int textureId4 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_TransparentDepthTexture");
		m_pRenderer->PrepareShaderTexture(4, textureId4);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_transparencyFrameBuffer));

		pShader->setUniform1i("screenWidth", m_windowWidth);
		pShader->setUniform1i("screenHeight", m_windowHeight);
		pShader->setUniform1f("nearZ", 0.01f);
		pShader->setUniform1f("farZ", 1000.0f);

		pShader->setUniform1f("samplingMultiplier", 0.5f);

		pShader->setUniform1i("lighting_enabled", m_dynamicLighting);
		pShader->setUniform1i("ssao_enabled", m_ssao);

		m_pRenderer->SetRenderMode(RM_TEXTURED);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->EmptyTextureIndex(4);
		m_pRenderer->EmptyTextureIndex(3);
		m_pRenderer->EmptyTextureIndex(2);
		m_pRenderer->EmptyTextureIndex(1);
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_SSAOShader);

		if (m_multiSampling)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_FXAAFrameBuffer);
		}
		else if (m_blur)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_firstPassFullscreenBuffer);
		}
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderFXAATexture()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		if (m_blur)
		{
			m_pRenderer->StartRenderingToFrameBuffer(m_firstPassFullscreenBuffer);
		}

		m_pRenderer->BeginGLSLShader(m_fxaaShader);
		glShader* pShader = m_pRenderer->GetShader(m_fxaaShader);

		pShader->setUniform1i("screenWidth", m_windowWidth);
		pShader->setUniform1i("screenHeight", m_windowHeight);

		unsigned int textureId0 = glGetUniformLocationARB(pShader->GetProgramObject(), "texture");
		m_pRenderer->PrepareShaderTexture(0, textureId0);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_FXAAFrameBuffer));

		m_pRenderer->SetRenderMode(RM_TEXTURED);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_fxaaShader);

		if (m_blur)
		{
			m_pRenderer->StopRenderingToFrameBuffer(m_firstPassFullscreenBuffer);
		}
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderFirstPassFullScreen()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		// Blur first pass (Horizontal)
		m_pRenderer->StartRenderingToFrameBuffer(m_secondPassFullscreenBuffer);
		m_pRenderer->BeginGLSLShader(m_blurHorizontalShader);
		glShader* pShader = m_pRenderer->GetShader(m_blurHorizontalShader);

		float blurSize = 0.0015f;

		// Override any blur amount if we have global blur set
		if (m_globalBlurAmount > 0.0f)
		{
			blurSize = m_globalBlurAmount;
		}

		unsigned int textureId0 = glGetUniformLocationARB(pShader->GetProgramObject(), "texture");
		m_pRenderer->PrepareShaderTexture(0, textureId0);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_firstPassFullscreenBuffer));

		pShader->setUniform1f("blurSize", blurSize);

		m_pRenderer->SetRenderMode(RM_TEXTURED);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_blurHorizontalShader);
		m_pRenderer->StopRenderingToFrameBuffer(m_secondPassFullscreenBuffer);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderSecondPassFullScreen()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		// Blur second pass (Vertical)
		m_pRenderer->BeginGLSLShader(m_blurVerticalShader);
		glShader* pShader = m_pRenderer->GetShader(m_blurVerticalShader);

		float blurSize = 0.0015f;

		unsigned int textureId0 = glGetUniformLocationARB(pShader->GetProgramObject(), "texture");
		m_pRenderer->PrepareShaderTexture(0, textureId0);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_secondPassFullscreenBuffer));

		pShader->setUniform1f("blurSize", blurSize);

		m_pRenderer->SetRenderMode(RM_TEXTURED);
		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.0f);
		m_pRenderer->DisableImmediateMode();

		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->EndGLSLShader(m_blurVerticalShader);
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderGUI()
{
	m_pRenderer->EmptyTextureIndex(0);

	// Render the GUI
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetCullMode(CM_BACK);

		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		m_pGUI->Render();
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderCinematicLetterBox()
{
	float letterboxHeight = 100.0f * m_letterBoxRatio;

	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);

		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		m_pRenderer->SetRenderMode(RM_SOLID);

		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateColourAlpha(0.0f, 0.0f, 0.0f, 1.0f);
			// Bottom
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 1.5f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 1.5f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, letterboxHeight, 1.5f);
			m_pRenderer->ImmediateVertex(0.0f, letterboxHeight, 1.5f);
			// Top
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight - letterboxHeight, 1.5f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight - letterboxHeight, 1.5f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 1.5f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 1.5f);
		m_pRenderer->DisableImmediateMode();
	m_pRenderer->PopMatrix();
}

void VoxGame::RenderCrosshair()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);

		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		m_pRenderer->TranslateWorldMatrix(m_windowWidth*0.5f, m_windowHeight*0.5f, 0.0f);

		float crosshairSize = 1.0f;
		float crosshairBorder = 2.0f;
		float crosshairLength = 4.0f;

		m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);
			m_pRenderer->ImmediateVertex(-crosshairSize, -crosshairSize, 3.0f);
			m_pRenderer->ImmediateVertex(crosshairSize, -crosshairSize, 3.0f);
			m_pRenderer->ImmediateVertex(crosshairSize, crosshairSize, 3.0f);
			m_pRenderer->ImmediateVertex(-crosshairSize, crosshairSize, 3.0f);

			m_pRenderer->ImmediateColourAlpha(0.0f, 0.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(-crosshairBorder, -crosshairBorder, 3.0f);
			m_pRenderer->ImmediateVertex(crosshairBorder, -crosshairBorder, 3.0f);
			m_pRenderer->ImmediateVertex(crosshairBorder, crosshairBorder, 3.0f);
			m_pRenderer->ImmediateVertex(-crosshairBorder, crosshairBorder, 3.0f);
		m_pRenderer->DisableImmediateMode();

	m_pRenderer->PopMatrix();
}

void VoxGame::RenderPaperdollViewport()
{
	if(m_pCharacterGUI->IsLoaded())
	{
		m_pRenderer->StartRenderingToFrameBuffer(m_paperdollBuffer);

		m_pRenderer->PushMatrix();
			glLoadIdentity();

			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glClearDepth(1.0);
			glClear(GL_DEPTH_BUFFER_BIT);

			m_pRenderer->SetProjectionMode(PM_PERSPECTIVE, m_paperdollViewport);

			m_pRenderer->SetLookAtCamera(vec3(0.0f, 1.3f, 2.85f), vec3(0.0f, 1.3f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

			// Render the player
			m_pRenderer->PushMatrix();
				m_pRenderer->StartMeshRender();

				if(m_modelWireframe == false)
				{
					m_pRenderer->BeginGLSLShader(m_paperdollShader);
				}

				m_pRenderer->RotateWorldMatrix(0.0f, m_paperdollRenderRotation, 0.0f);

				m_pPlayer->RenderPaperdoll();

				if(m_modelWireframe == false)
				{
					m_pRenderer->EndGLSLShader(m_paperdollShader);
				}

				m_pRenderer->EndMeshRender();
				
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glDisable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, 0);

				if(m_modelWireframe == false)
				{
					m_pRenderer->BeginGLSLShader(m_textureShader);
				}
				
				m_pPlayer->RenderPaperdollFace();

				if(m_modelWireframe == false)
				{
					m_pRenderer->EndGLSLShader(m_textureShader);
				}
			m_pRenderer->PopMatrix();
		m_pRenderer->PopMatrix();

		m_pRenderer->StopRenderingToFrameBuffer(m_paperdollBuffer);
	}
}

void VoxGame::RenderDeferredRenderingPaperDoll()
{
	m_pRenderer->StartRenderingToFrameBuffer(m_paperdollSSAOTextureBuffer);

	m_pRenderer->PushMatrix();
		m_pRenderer->SetProjectionMode(PM_2D, m_paperdollViewport);

		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

		m_pRenderer->BeginGLSLShader(m_SSAOShader);
		glShader* pShader = m_pRenderer->GetShader(m_SSAOShader);

		unsigned int textureId = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_DepthTexture");
		glActiveTextureARB(GL_TEXTURE0_ARB);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDepthTextureFromFrameBuffer(m_paperdollBuffer));
		glUniform1iARB(textureId, 0);

		unsigned int textureId2 = glGetUniformLocationARB(pShader->GetProgramObject(), "bgl_RenderedTexture");
		glActiveTextureARB(GL_TEXTURE1_ARB);
		m_pRenderer->BindRawTextureId(m_pRenderer->GetDiffuseTextureFromFrameBuffer(m_paperdollBuffer));
		glUniform1iARB(textureId2, 1);

		pShader->setUniform1i("screenWidth", m_windowWidth);
		pShader->setUniform1i("screenHeight", m_windowHeight);
		pShader->setUniform1f("nearZ", 0.01f);
		pShader->setUniform1f("farZ", 1000.0f);

		pShader->setUniform1f("samplingMultiplier", 0.5f);
		pShader->setUniform1i("lighting_enabled", false);

		m_pRenderer->SetRenderMode(RM_TEXTURED);
			m_pRenderer->EnableImmediateMode(IM_QUADS);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, 2.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 0.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, 0.0f, 2.0f);
			m_pRenderer->ImmediateTextureCoordinate(1.0f, 1.0f);
			m_pRenderer->ImmediateVertex((float)m_windowWidth, (float)m_windowHeight, 2.0f);
			m_pRenderer->ImmediateTextureCoordinate(0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(0.0f, (float)m_windowHeight, 2.0f);
		m_pRenderer->DisableImmediateMode();

		glActiveTextureARB(GL_TEXTURE3_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTextureARB(GL_TEXTURE2_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_pRenderer->EndGLSLShader(m_SSAOShader);
	m_pRenderer->PopMatrix();

	m_pRenderer->StopRenderingToFrameBuffer(m_paperdollSSAOTextureBuffer);
}

void VoxGame::RenderDebugInformation()
{
	char lCameraBuff[256];
	sprintf(lCameraBuff, "Pos(%.2f, %.2f, %.2f), Facing(%.2f, %.2f, %.2f) = %.2f, Up(%.2f, %.2f, %.2f) = %.2f, Right(%.2f, %.2f, %.2f) = %.2f, View(%.2f, %.2f, %.2f), Zoom=%.2f",
		m_pGameCamera->GetPosition().x, m_pGameCamera->GetPosition().y, m_pGameCamera->GetPosition().z,
		m_pGameCamera->GetFacing().x, m_pGameCamera->GetFacing().y, m_pGameCamera->GetFacing().z, length(m_pGameCamera->GetFacing()),
		m_pGameCamera->GetUp().x, m_pGameCamera->GetUp().y, m_pGameCamera->GetUp().z, length(m_pGameCamera->GetUp()),
		m_pGameCamera->GetRight().x, m_pGameCamera->GetRight().y, m_pGameCamera->GetRight().z, length(m_pGameCamera->GetRight()),
		m_pGameCamera->GetView().x, m_pGameCamera->GetView().y, m_pGameCamera->GetView().z,
		m_pGameCamera->GetZoomAmount());

	char lDrawingBuff[256];
	sprintf(lDrawingBuff, "Vertices: %i, Faces: %i", 0, 0); // TODO : Debug rendering Metrics
	char lChunksBuff[256];
	sprintf(lChunksBuff, "Chunks: %i, Render: %i", m_pChunkManager->GetNumChunksLoaded(), m_pChunkManager->GetNumChunksRender());
	char lParticlesBuff[256];
	sprintf(lParticlesBuff, "Particles: %i, Render: %i, Emitters: %i, Effects: %i", m_pBlockParticleManager->GetNumBlockParticles(), m_pBlockParticleManager->GetNumRenderableParticles(), m_pBlockParticleManager->GetNumBlockParticleEmitters(), m_pBlockParticleManager->GetNumBlockParticleEffects());
	char lItemsBuff[256];
	sprintf(lItemsBuff, "Items: %i, Render: %i", m_pItemManager->GetNumItems(), m_pItemManager->GetNumRenderItems());
	char lProjectilesBuff[256];
	sprintf(lProjectilesBuff, "Projectiles: %i, Render: %i", m_pProjectileManager->GetNumProjectiles(), m_pProjectileManager->GetNumRenderProjectiles());
	char lInstancesBuff[256];
	sprintf(lInstancesBuff,  "Instance Parents: %i, Instance Objects: %i, Instance Render: %i", m_pInstanceManager->GetNumInstanceParents(), m_pInstanceManager->GetTotalNumInstanceObjects(), m_pInstanceManager->GetTotalNumInstanceRenderObjects());

	char lFPSBuff[128];
	float fpsWidthOffset = 65.0f;
	if (m_debugRender)
	{
		sprintf(lFPSBuff, "Delta: %.4f  FPS: %.0f", m_deltaTime, m_fps);
		fpsWidthOffset = 135.0f;
	}
	else
	{
		sprintf(lFPSBuff, "FPS: %.0f", m_fps);
	}

	char lBuildInfo[128];
#if defined(_DEBUG) || defined(NDEBUG)
	sprintf(lBuildInfo, "DEV %s", m_pVoxSettings->m_version.c_str());
#else
	sprintf(lBuildInfo, "RELEASE %s", m_pVoxSettings->m_version.c_str());
#endif //defined(_DEBUG) || defined(NDEBUG)

	int l_nTextHeight = m_pRenderer->GetFreeTypeTextHeight(m_defaultFont, "a");

	m_pRenderer->PushMatrix();
		m_pRenderer->EmptyTextureIndex(0);

		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->SetProjectionMode(PM_2D, m_defaultViewport);
		m_pRenderer->SetLookAtCamera(vec3(0.0f, 0.0f, 250.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
		if (m_debugRender)
		{
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight * 1) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lCameraBuff);
			//m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight*2) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lDrawingBuff);
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight * 3) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lChunksBuff);
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight * 4) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lParticlesBuff);
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight * 5) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lItemsBuff);
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight * 6) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lProjectilesBuff);
			m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, m_windowHeight - (l_nTextHeight * 7) - 10.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lInstancesBuff);
		}

		m_pRenderer->RenderFreeTypeText(m_defaultFont, m_windowWidth-fpsWidthOffset, 15.0f, 1.0f, Colour(1.0f, 1.0f, 1.0f), 1.0f, lFPSBuff);
		m_pRenderer->RenderFreeTypeText(m_defaultFont, 15.0f, 15.0f, 1.0f, Colour(0.75f, 0.75f, 0.75f), 1.0f, lBuildInfo);

	m_pRenderer->PopMatrix();
}
