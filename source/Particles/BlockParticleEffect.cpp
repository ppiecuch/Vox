// ******************************************************************************
// Filename:    BlockParticleEffect.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 09/11/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "BlockParticleEffect.h"
#include "BlockParticleEmitter.h"
#include "BlockParticleManager.h"

#include "../utils/Random.h"

#include <fstream>
#include <ostream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


BlockParticleEffect::BlockParticleEffect(Renderer* pRenderer, BlockParticleManager* pBlockParticleManager)
{
	m_pRenderer = pRenderer;
	m_pBlockParticleManager = pBlockParticleManager;

	m_particleEffectId = -1;

	m_erase = false;

	m_started = false;
	m_paused = false;

	m_endless = true;
	m_lifeTime = 1.0f;
	m_lifeTimer = m_lifeTime;

	m_renderNoWoldOffsetViewport = false;
}

BlockParticleEffect::~BlockParticleEffect()
{
	ClearEmitters();
}

void BlockParticleEffect::ClearEmitters()
{
	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		if(m_vpBlockParticleEmittersList[i]->m_erase == false)
		{
			m_pBlockParticleManager->RemoveEmitterLinkage(m_vpBlockParticleEmittersList[i]);
			m_vpBlockParticleEmittersList[i]->m_pParent = NULL; // Remove parent link, since we have deleted this effect
			m_vpBlockParticleEmittersList[i]->m_erase = true;
		}
	}
}

void BlockParticleEffect::SetPosition(vec3 pos)
{
	m_position = pos;
}

vec3 BlockParticleEffect::GetPosition()
{
	return m_position;
}

void BlockParticleEffect::Import(const char* fileName)
{
	ifstream importFile;

	// Open the file
	importFile.open(fileName, ios::in);

	if(importFile.is_open())
	{
		string tempString;

		string effectName;
		importFile >> tempString >> effectName;
		m_effectName = effectName;

		importFile >> tempString >> m_endless;
		importFile >> tempString >> m_lifeTime;
		m_lifeTimer = m_lifeTime;

		int numEmitters;
		importFile >> tempString >> numEmitters;
		for(int i = 0; i < numEmitters; i++)
		{
			string emitterName;
			importFile >> tempString >> emitterName;
			float x, y, z;
			importFile >> tempString >> x >> y >> z;
			vec3 position = vec3(x, y, z);
			float creationTime;
			importFile >> tempString >> creationTime;
			int numParticlesToSpawn;
			importFile >> tempString >> numParticlesToSpawn;
			bool particlesFollowEmitter;
			importFile >> tempString >> particlesFollowEmitter;
			bool orbit;
			importFile >> tempString >> orbit;
			bool  orbitReverse;
			importFile >> tempString >> orbitReverse;
			float orbitRadius;
			importFile >> tempString >> orbitRadius;
			float orbitTime;
			importFile >> tempString >> orbitTime;
			int eType;
			importFile >> tempString >> eType;
			EmitterType emitterType = (EmitterType)eType;
			float emitterRadius;
			importFile >> tempString >> emitterRadius;
			float emitterLengthX;
			importFile >> tempString >> emitterLengthX;
			float emitterLengthY;
			importFile >> tempString >> emitterLengthY;
			float emitterLengthZ;
			importFile >> tempString >> emitterLengthZ;
			bool spawnOutline;
			importFile >> tempString >> spawnOutline;
			importFile >> tempString >> x >> y >> z;
			vec3 gravityDirection = vec3(x, y, z);
			float gravityMultiplier;
			importFile >> tempString >> gravityMultiplier;
			importFile >> tempString >> x >> y >> z;
			vec3 pointOrigin = vec3(x, y, z);
			float startScale;
			importFile >> tempString >> startScale;
			float startScaleVariance;
			importFile >> tempString >> startScaleVariance;
			float endScale;
			importFile >> tempString >> endScale;
			float endScaleVariance;
			importFile >> tempString >> endScaleVariance;
			float startRed;
			importFile >> tempString >> startRed;
			float startRedVariance;
			importFile >> tempString >> startRedVariance;
			float endRed;
			importFile >> tempString >> endRed;
			float endRedVariance;
			importFile >> tempString >> endRedVariance;
			float startGreen;
			importFile >> tempString >> startGreen;
			float startGreenVariance;
			importFile >> tempString >> startGreenVariance;
			float endGreen;
			importFile >> tempString >> endGreen;
			float endGreenVariance;
			importFile >> tempString >> endGreenVariance;
			float startBlue;
			importFile >> tempString >> startBlue;
			float startBlueVariance;
			importFile >> tempString >> startBlueVariance;
			float endBlue;
			importFile >> tempString >> endBlue;
			float endBlueVariance;
			importFile >> tempString >> endBlueVariance;
			float startAlpha;
			importFile >> tempString >> startAlpha;
			float startAlphaVariance;
			importFile >> tempString >> startAlphaVariance;
			float endAlpha;
			importFile >> tempString >> endAlpha;
			float endAlphaVariance;
			importFile >> tempString >> endAlphaVariance;
			float lifeTime;
			importFile >> tempString >> lifeTime;
			float lifeTimeVariance;
			importFile >> tempString >> lifeTimeVariance;
			float velocityTowardsPoint;
			importFile >> tempString >> velocityTowardsPoint;
			float accelerationTowardsPoint;
			importFile >> tempString >> accelerationTowardsPoint;
			bool checkWorldCollisions;
			importFile >> tempString >> checkWorldCollisions;
			bool destoryOnCollision;
			importFile >> tempString >> destoryOnCollision;
			bool startLifeDecayOnCollision;
			importFile >> tempString >> startLifeDecayOnCollision;
			importFile >> tempString >> x >> y >> z;
			vec3 startVelocity = vec3(x, y, z);
			importFile >> tempString >> x >> y >> z;
			vec3 startVelocityVariance = vec3(x, y, z);
			bool randomStartRotation;
			importFile >> tempString >> randomStartRotation;
			importFile >> tempString >> x >> y >> z;
			vec3 startRotation = vec3(x, y, z);
			importFile >> tempString >> x >> y >> z;
			vec3 startAngularVelocity = vec3(x, y, z);
			importFile >> tempString >> x >> y >> z;
			vec3 startAngularVelocityVariance = vec3(x, y, z);
			float tangentialVelocityXY;
			importFile >> tempString >> tangentialVelocityXY;
			float tangentialAccelerationXY;
			importFile >> tempString >> tangentialAccelerationXY;
			float tangentialVelocityXZ;
			importFile >> tempString >> tangentialVelocityXZ;
			float tangentialAccelerationXZ;
			importFile >> tempString >> tangentialAccelerationXZ;
			float tangentialVelocityYZ;
			importFile >> tempString >> tangentialVelocityYZ;
			float tangentialAccelerationYZ;
			importFile >> tempString >> tangentialAccelerationYZ;

			bool createEmitters;
			importFile >> tempString >> createEmitters;
			string createEmitterName;
			importFile >> tempString >> createEmitterName;
			bool isReferenceEmitter;
			importFile >> tempString >> isReferenceEmitter;

			// Create temp emitter
			BlockParticleEmitter* pNewEmitter = m_pBlockParticleManager->CreateBlockParticleEmitter(emitterName, position);

			pNewEmitter->m_emitterName = emitterName;

			pNewEmitter->m_startingPosition = position;
			pNewEmitter->m_position = position;

			pNewEmitter->m_creationTime = creationTime;
			pNewEmitter->m_creationTimer = 0.0f;

			pNewEmitter->m_numParticlesToSpawn = numParticlesToSpawn;

			pNewEmitter->m_particlesFollowEmitter = particlesFollowEmitter;

			pNewEmitter->m_orbit = orbit;
			pNewEmitter->m_orbitReverse = orbitReverse;
			pNewEmitter->m_orbitRadius = orbitRadius;
			pNewEmitter->m_orbitTime = orbitTime;
			pNewEmitter->m_orbitTimer = orbitTime;
			pNewEmitter->m_emitterType = emitterType;

			pNewEmitter->m_emitterRadius = emitterRadius;
			pNewEmitter->m_emitterLengthX = emitterLengthX;
			pNewEmitter->m_emitterLengthY = emitterLengthY;
			pNewEmitter->m_emitterLengthZ = emitterLengthZ;

			pNewEmitter->m_spawnOutline = spawnOutline;
			pNewEmitter->m_gravityDirection = gravityDirection;
			pNewEmitter->m_gravityMultiplier = gravityMultiplier;
			pNewEmitter->m_pointOrigin = pointOrigin;
			pNewEmitter->m_startScale = startScale;
			pNewEmitter->m_startScaleVariance = startScaleVariance;
			pNewEmitter->m_endScale = endScale;
			pNewEmitter->m_endScaleVariance = endScaleVariance;
			pNewEmitter->m_startRed = startRed;
			pNewEmitter->m_startRedVariance = startRedVariance;
			pNewEmitter->m_endRed = endRed;
			pNewEmitter->m_endRedVariance = endRedVariance;
			pNewEmitter->m_startGreen = startGreen;
			pNewEmitter->m_startGreenVariance = startGreenVariance;
			pNewEmitter->m_endGreen = endGreen;
			pNewEmitter->m_endGreenVariance = endGreenVariance;
			pNewEmitter->m_startBlue = startBlue;
			pNewEmitter->m_startBlueVariance = startBlueVariance;
			pNewEmitter->m_endBlue = endBlue;
			pNewEmitter->m_endBlueVariance = endBlueVariance;
			pNewEmitter->m_startAlpha = startAlpha;
			pNewEmitter->m_startAlphaVariance = startAlphaVariance;
			pNewEmitter->m_endAlpha = endAlpha;
			pNewEmitter->m_endAlphaVariance = endAlphaVariance;
			pNewEmitter->m_lifeTime = lifeTime;
			pNewEmitter->m_lifeTimeVariance = lifeTimeVariance;
			pNewEmitter->m_velocityTowardsPoint = velocityTowardsPoint;
			pNewEmitter->m_accelerationTowardsPoint = accelerationTowardsPoint;
			pNewEmitter->m_checkWorldCollisions = checkWorldCollisions;
			pNewEmitter->m_destoryOnCollision = destoryOnCollision;
			pNewEmitter->m_startLifeDecayOnCollision = startLifeDecayOnCollision;
			pNewEmitter->m_startVelocity = startVelocity;
			pNewEmitter->m_startVelocityVariance = startVelocityVariance;
			pNewEmitter->m_randomStartRotation = randomStartRotation;
			pNewEmitter->m_startRotation = startRotation;
			pNewEmitter->m_startAngularVelocity = startAngularVelocity;
			pNewEmitter->m_startAngularVelocityVariance = startAngularVelocityVariance;
			pNewEmitter->m_tangentialVelocityXY = tangentialVelocityXY;
			pNewEmitter->m_tangentialAccelerationXY = tangentialAccelerationXY;
			pNewEmitter->m_tangentialVelocityXZ = tangentialVelocityXZ;
			pNewEmitter->m_tangentialAccelerationXZ = tangentialAccelerationXZ;
			pNewEmitter->m_tangentialVelocityYZ = tangentialVelocityYZ;
			pNewEmitter->m_tangentialAccelerationYZ = tangentialAccelerationYZ;

			pNewEmitter->m_createEmitters = createEmitters;
			pNewEmitter->m_createEmitterName = createEmitterName;
			pNewEmitter->m_isReferenceEmitter = isReferenceEmitter;

			pNewEmitter->m_pParent = this;

			m_vpBlockParticleEmittersList.push_back(pNewEmitter);
		}
	}
}

void BlockParticleEffect::Export(const char* fileName)
{
	ofstream exportFile;

	// Open the file
	exportFile.open(fileName, ios::out);

	if(exportFile.is_open())
	{
		exportFile << "effectName: " << m_effectName << "\n\n";

		int numEmitters = (int)m_vpBlockParticleEmittersList.size();
		exportFile << "numEmitters: " << numEmitters << "\n";
		for(int i = 0; i < numEmitters; i++)
		{
			exportFile << "emitterName: " << m_vpBlockParticleEmittersList[i]->m_emitterName << "\n";
			exportFile << "emitterPosition: " << m_vpBlockParticleEmittersList[i]->m_position.x << " " << m_vpBlockParticleEmittersList[i]->m_position.y << " " << m_vpBlockParticleEmittersList[i]->m_position.z << "\n";
			exportFile << "creationTime: " << m_vpBlockParticleEmittersList[i]->m_creationTime << "\n";
			exportFile << "numParticles: " << m_vpBlockParticleEmittersList[i]->m_numParticlesToSpawn << "\n";
			exportFile << "followEmitter: " << m_vpBlockParticleEmittersList[i]->m_particlesFollowEmitter << "\n";
			exportFile << "orbit: " << m_vpBlockParticleEmittersList[i]->m_orbit << "\n";
			exportFile << "orbitReverse: " << m_vpBlockParticleEmittersList[i]->m_orbitReverse << "\n";
			exportFile << "orbitRadius: " << m_vpBlockParticleEmittersList[i]->m_orbitRadius << "\n";
			exportFile << "orbitTime: " << m_vpBlockParticleEmittersList[i]->m_orbitTime << "\n";
			exportFile << "emitterType: " << (int)m_vpBlockParticleEmittersList[i]->m_emitterType << "\n";
			exportFile << "emitterRadius: " << m_vpBlockParticleEmittersList[i]->m_emitterRadius << "\n";
			exportFile << "emitterLengthX: " << m_vpBlockParticleEmittersList[i]->m_emitterLengthX << "\n";
			exportFile << "emitterLengthY: " << m_vpBlockParticleEmittersList[i]->m_emitterLengthY << "\n";
			exportFile << "emitterLengthZ: " << m_vpBlockParticleEmittersList[i]->m_emitterLengthZ << "\n";
			exportFile << "spawnOutline: " << m_vpBlockParticleEmittersList[i]->m_spawnOutline << "\n";
			exportFile << "gravityDir: " << m_vpBlockParticleEmittersList[i]->m_gravityDirection.x << " " << m_vpBlockParticleEmittersList[i]->m_gravityDirection.y << " " << m_vpBlockParticleEmittersList[i]->m_gravityDirection.z << "\n";
			exportFile << "gravityMultiplier: " << m_vpBlockParticleEmittersList[i]->m_gravityMultiplier << "\n";
			exportFile << "pointOrigin: " << m_vpBlockParticleEmittersList[i]->m_pointOrigin.x << " " << m_vpBlockParticleEmittersList[i]->m_pointOrigin.y << " " << m_vpBlockParticleEmittersList[i]->m_pointOrigin.z << "\n";
			exportFile << "startScale: " << m_vpBlockParticleEmittersList[i]->m_startScale << "\n";
			exportFile << "startScaleVariance: " << m_vpBlockParticleEmittersList[i]->m_startScaleVariance << "\n";
			exportFile << "endScale: " << m_vpBlockParticleEmittersList[i]->m_endScale << "\n";
			exportFile << "endScaleVariance: " << m_vpBlockParticleEmittersList[i]->m_endScaleVariance << "\n";
			exportFile << "startRed: " << m_vpBlockParticleEmittersList[i]->m_startRed << "\n";
			exportFile << "startRedVariance: " << m_vpBlockParticleEmittersList[i]->m_startRedVariance << "\n";
			exportFile << "endRed: " << m_vpBlockParticleEmittersList[i]->m_endRed << "\n";
			exportFile << "endRedVariance: " << m_vpBlockParticleEmittersList[i]->m_endRedVariance << "\n";
			exportFile << "startGreen: " << m_vpBlockParticleEmittersList[i]->m_startGreen << "\n";
			exportFile << "startGreenVariance: " << m_vpBlockParticleEmittersList[i]->m_startGreenVariance << "\n";
			exportFile << "endGreen: " << m_vpBlockParticleEmittersList[i]->m_endGreen << "\n";
			exportFile << "endGreenVariance: " << m_vpBlockParticleEmittersList[i]->m_endGreenVariance << "\n";
			exportFile << "startBlue: " << m_vpBlockParticleEmittersList[i]->m_startBlue << "\n";
			exportFile << "startBlueVariance: " << m_vpBlockParticleEmittersList[i]->m_startBlueVariance << "\n";
			exportFile << "endBlue: " << m_vpBlockParticleEmittersList[i]->m_endBlue << "\n";
			exportFile << "endBlueVariance: " << m_vpBlockParticleEmittersList[i]->m_endBlueVariance << "\n";
			exportFile << "startAlpha: " << m_vpBlockParticleEmittersList[i]->m_startAlpha << "\n";
			exportFile << "startAlphaVariance: " << m_vpBlockParticleEmittersList[i]->m_startAlphaVariance << "\n";
			exportFile << "endAlpha: " << m_vpBlockParticleEmittersList[i]->m_endAlpha << "\n";
			exportFile << "endAlphaVariance: " << m_vpBlockParticleEmittersList[i]->m_endAlphaVariance << "\n";
			exportFile << "lifeTime: " << m_vpBlockParticleEmittersList[i]->m_lifeTime << "\n";
			exportFile << "lifeTimeVariance: " << m_vpBlockParticleEmittersList[i]->m_lifeTimeVariance << "\n";
			exportFile << "velocityTowardsPoint: " << m_vpBlockParticleEmittersList[i]->m_velocityTowardsPoint << "\n";
			exportFile << "accelerationTowardsPoint: " << m_vpBlockParticleEmittersList[i]->m_accelerationTowardsPoint << "\n";
			exportFile << "worldCollisions: " << m_vpBlockParticleEmittersList[i]->m_checkWorldCollisions << "\n";
			exportFile << "destoryOnCollision: " << m_vpBlockParticleEmittersList[i]->m_destoryOnCollision << "\n";
			exportFile << "decayOnCollision: " << m_vpBlockParticleEmittersList[i]->m_startLifeDecayOnCollision << "\n";
			exportFile << "startVelocity: " << m_vpBlockParticleEmittersList[i]->m_startVelocity.x << " " << m_vpBlockParticleEmittersList[i]->m_startVelocity.y << " " << m_vpBlockParticleEmittersList[i]->m_startVelocity.z << "\n";
			exportFile << "startVelocityVariance: " << m_vpBlockParticleEmittersList[i]->m_startVelocityVariance.x << " " << m_vpBlockParticleEmittersList[i]->m_startVelocityVariance.y << " " << m_vpBlockParticleEmittersList[i]->m_startVelocityVariance.z << "\n";
			exportFile << "randomStartRotation: " << m_vpBlockParticleEmittersList[i]->m_randomStartRotation << "\n";
			exportFile << "startAngularVelocity: " << m_vpBlockParticleEmittersList[i]->m_startAngularVelocity.x << " " << m_vpBlockParticleEmittersList[i]->m_startAngularVelocity.y << " " << m_vpBlockParticleEmittersList[i]->m_startAngularVelocity.z << "\n";
			exportFile << "startAngularVelocityVariance: " << m_vpBlockParticleEmittersList[i]->m_startAngularVelocityVariance.x << " " << m_vpBlockParticleEmittersList[i]->m_startAngularVelocityVariance.y << " " << m_vpBlockParticleEmittersList[i]->m_startAngularVelocityVariance.z << "\n";
			exportFile << "tangentialVelocityXY: " << m_vpBlockParticleEmittersList[i]->m_tangentialVelocityXY << "\n";
			exportFile << "tangentialAccelerationXY: " << m_vpBlockParticleEmittersList[i]->m_tangentialAccelerationXY << "\n";
			exportFile << "tangentialVelocityXZ: " << m_vpBlockParticleEmittersList[i]->m_tangentialVelocityXZ << "\n";
			exportFile << "tangentialAccelerationXZ: " << m_vpBlockParticleEmittersList[i]->m_tangentialAccelerationXZ << "\n";
			exportFile << "tangentialVelocityYZ: " << m_vpBlockParticleEmittersList[i]->m_tangentialVelocityYZ << "\n";
			exportFile << "tangentialAccelerationYZ: " << m_vpBlockParticleEmittersList[i]->m_tangentialAccelerationYZ << "\n";
			exportFile << "creteEmitter: " << m_vpBlockParticleEmittersList[i]->m_createEmitters << "\n";
			exportFile << "createEmitterName: " << m_vpBlockParticleEmittersList[i]->m_createEmitterName << "\n";
			exportFile << "isReferenceEmitter: " << m_vpBlockParticleEmittersList[i]->m_isReferenceEmitter << "\n";
		}
	}
}

void BlockParticleEffect::PlayEffect()
{
	if(m_endless == false)
	{
		m_lifeTimer = m_lifeTime;
	}

	m_started = true;

	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		if(m_vpBlockParticleEmittersList[i]->m_started == false)
		{
			m_vpBlockParticleEmittersList[i]->m_creationTimer = 0.0f;
		}

		m_vpBlockParticleEmittersList[i]->m_started = true;
	}
}

void BlockParticleEffect::StopEffect()
{
	m_started = false;

	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		if(m_vpBlockParticleEmittersList[i]->m_pParentParticle != NULL)
		{
			// Don't stop emitters that are connected to a particle
			continue;
		}

		m_vpBlockParticleEmittersList[i]->m_started = false;
	}
}

void BlockParticleEffect::PauseEffect()
{
	m_paused = !m_paused;

	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		m_vpBlockParticleEmittersList[i]->m_paused = m_paused;
	}
}

bool BlockParticleEffect::IsStarted()
{
	return m_started;
}

bool BlockParticleEffect::IsPaused()
{
	return m_paused;
}

void BlockParticleEffect::AddEmitterToParticleEffect(BlockParticleEmitter* pEmitter)
{
	m_vpBlockParticleEmittersList.push_back(pEmitter);
}

void BlockParticleEffect::RemoveEmitterFromParticleEffect(BlockParticleEmitter* pEmitter)
{
	BlockParticlesEmitterList::iterator iter = std::find(m_vpBlockParticleEmittersList.begin(), m_vpBlockParticleEmittersList.end(), pEmitter);
	if(iter != m_vpBlockParticleEmittersList.end())
	{
		m_vpBlockParticleEmittersList.erase(iter);
	}
}

BlockParticleEmitter* BlockParticleEffect::GetEmitter(string emitterName)
{
	for(unsigned int i = 0; i < m_vpBlockParticleEmittersList.size(); i++)
	{
		if(m_vpBlockParticleEmittersList[i]->m_emitterName == emitterName)
		{
			BlockParticleEmitter* pReturn = m_vpBlockParticleEmittersList[i];

			return pReturn;
		}
	}

	return NULL;
}

// Update
void BlockParticleEffect::Update(float dt)
{
	if(m_started == false || m_paused == true)
	{
		return;
	}

	if(m_endless == false)
	{
		if(m_lifeTimer <= 0.0f)
		{
			StopEffect();
			
			m_erase = true;
		}
		else
		{
			m_lifeTimer -= dt;
		}
	}
}

// Rendering
void BlockParticleEffect::Render()
{
	m_pRenderer->PushMatrix();
		m_pRenderer->TranslateWorldMatrix(m_position.x, m_position.y, m_position.z);

		float l_length = 0.5f;

		m_pRenderer->SetRenderMode(RM_SOLID);
		m_pRenderer->SetLineWidth(2.0f);
		m_pRenderer->EnableImmediateMode(IM_LINES);
			m_pRenderer->ImmediateColourAlpha(0.0f, 1.0f, 0.0f, 1.0f);
			m_pRenderer->ImmediateVertex(-l_length, 0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(l_length, 0.0f, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, -l_length, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, l_length, 0.0f);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, -l_length);
			m_pRenderer->ImmediateVertex(0.0f, 0.0f, l_length);
		m_pRenderer->DisableImmediateMode();
	m_pRenderer->PopMatrix();
}
