// ******************************************************************************
// Filename:    BlockParticle.h
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

#pragma once

#include "../Maths/3dmaths.h"

class BlockParticleEmitter;
class Chunk;
class ChunkManager;


class BlockParticle
{
public:
	/* Public methods */
	BlockParticle();
	~BlockParticle();

	void ClearParticleChunkCacheForChunk(Chunk* pChunk);

	void CreateStartingParams();

	void CalculateWorldTransformMatrix();

	void UpdateGridPosition();
	Chunk* GetCachedGridChunkOrFromPosition(vec3 pos);

	void SetFreezeDelayTimer(float timer);
	void SetWaitAfterUpdateCompleteTimer(float timer);

	// Update
	void Update(float dt);

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */
	bool m_erase;

	// Floor Sliding flag (set manually)
	bool m_allowFloorSliding;

	// Position
	vec3 m_position;

	// Position with no world offset
	vec3 m_position_NoWorldOffset;

	// Velocity
	vec3 m_velocity;
	vec3 m_startVelocityVariance;

	// Rotation
	vec3 m_rotation;
	vec3 m_startRotation;
	bool m_randomStartRotation;

	// Angular velocity
	vec3 m_angularVelocity;
	vec3 m_startAngularVelocityVariance;

	// Gravity
	vec3 m_gravityDirection;
	float m_gravityMultiplier;

	// World matrix
	Matrix4x4 m_worldMatrix;

	// World matrix with no positional offset, used for viewport rendering without world movements (i.e. characterGUI)
	Matrix4x4 m_worldMatrix_NoPositionOffset;

	// Particle colour
	float m_currentRed;
	float m_startRed;
	float m_startRedVariance;
	float m_endRed;
	float m_endRedVariance;
	float m_currentGreen;
	float m_startGreen;
	float m_startGreenVariance;
	float m_endGreen;
	float m_endGreenVariance;
	float m_currentBlue;
	float m_startBlue;
	float m_startBlueVariance;
	float m_endBlue;
	float m_endBlueVariance;
	float m_currentAlpha;
	float m_startAlpha;
	float m_startAlphaVariance;
	float m_endAlpha;
	float m_endAlphaVariance;

	// Particle scale
	float m_currentScale;
	float m_startScale;
	float m_startScaleVariance;
	float m_endScale;
	float m_endScaleVariance;

	// Velocity towards point origin
	vec3 m_pointOrigin;
	vec3 m_pointVelocity;
	float m_velocityTowardsPoint;
	float m_accelerationTowardsPoint;

	// Tangential velocity
	vec3 m_tangentialVelocity;
	float m_tangentialVelocityXY;
	float m_tangentialAccelerationXY;
	float m_tangentialVelocityXZ;
	float m_tangentialAccelerationXZ;
	float m_tangentialVelocityYZ;
	float m_tangentialAccelerationYZ;

	// Lifetime
	float m_lifeTime;
	float m_maxLifeTime;
	float m_lifeTimeVariance;

	// Freeze update / delay
	float m_freezeUpdateTimer;

	// Wait after complete
	float m_waitAfterUpdateCompleteTimer;

	// Does particle collide with the world
	bool m_checkWorldCollisions;

	// Do we destroy this particle instantly on collision with world
	bool m_destoryOnCollision;
	
	// Do we only start the life decay after we collide
	bool m_startLifeDecayOnCollision;
	bool m_hasCollided;

	// Grid
	int m_gridPositionX;
	int m_gridPositionY;
	int m_gridPositionZ;

	// Cached chunk pointer
	Chunk* m_pCachedGridChunk;

	// Emitter parent
	BlockParticleEmitter* m_pParent;

	// Create Emitters instead of particles
	bool m_createEmitters;
	BlockParticleEmitter* m_pCreatedEmitter;

protected:
	/* Protected members */

public:
	/* Private members */
	ChunkManager* m_pChunkManager;
};
