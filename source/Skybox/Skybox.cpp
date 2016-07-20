// ******************************************************************************
// Filename:    Skybox.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Revision History:
//   Initial Revision - 22/09/14
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "Skybox.h"
#include "../VoxGame.h"


Skybox::Skybox(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	SetSkybox1("glacier");
	SetSkybox2("delirious");

	m_skyBoxNames[Biome_None] = "glacier";
	m_skyBoxNames[Biome_GrassLand] = "glacier";
	m_skyBoxNames[Biome_Desert] = "desert";
	m_skyBoxNames[Biome_Tundra] = "blue_sky";
	m_skyBoxNames[Biome_AshLand] = "delirious";
}

Skybox::~Skybox()
{
}

void Skybox::SetSkybox1(string name)
{
	m_skyBox1Name = name;

	string front = "media/textures/Skyboxes/" + m_skyBox1Name + "/front.tga";
	string back = "media/textures/Skyboxes/" + m_skyBox1Name + "/back.tga";
	string top = "media/textures/Skyboxes/" + m_skyBox1Name + "/top.tga";
	string bottom = "media/textures/Skyboxes/" + m_skyBox1Name + "/bottom.tga";
	string left = "media/textures/Skyboxes/" + m_skyBox1Name + "/left.tga";
	string right = "media/textures/Skyboxes/" + m_skyBox1Name + "/right.tga";

	int ltexturewidth, ltextureheight;
	m_pRenderer->LoadCubeTexture(&ltexturewidth, &ltextureheight, front.c_str(), back.c_str(), top.c_str(), bottom.c_str(), left.c_str(), right.c_str(), &m_cubeTextureId1);
}

void Skybox::SetSkybox2(string name)
{
	m_skyBox2Name = name;

	string front = "media/textures/Skyboxes/" + m_skyBox2Name + "/front.tga";
	string back = "media/textures/Skyboxes/" + m_skyBox2Name + "/back.tga";
	string top = "media/textures/Skyboxes/" + m_skyBox2Name + "/top.tga";
	string bottom = "media/textures/Skyboxes/" + m_skyBox2Name + "/bottom.tga";
	string left = "media/textures/Skyboxes/" + m_skyBox2Name + "/left.tga";
	string right = "media/textures/Skyboxes/" + m_skyBox2Name + "/right.tga";

	int ltexturewidth, ltextureheight;
	m_pRenderer->LoadCubeTexture(&ltexturewidth, &ltextureheight, front.c_str(), back.c_str(), top.c_str(), bottom.c_str(), left.c_str(), right.c_str(), &m_cubeTextureId2);
}

unsigned int Skybox::GetCubeMapTexture1()
{
	return m_cubeTextureId1;
}

unsigned int Skybox::GetCubeMapTexture2()
{
	return m_cubeTextureId2;
}

void Skybox::SetCurrentBiome(Biome currentBiome)
{
	SetSkybox1(m_skyBoxNames[currentBiome]);
}

void Skybox::Render()
{
	float width = 4000.0f;
	float height = 4000.0f;
	float length = 4000.0f;

	// Center the Skybox around the given x,y,z position
	float x = -(width*0.5f);
	float y = -(height*0.5f);
	float z = -(length*0.5f);


	m_pRenderer->SetRenderMode(RM_TEXTURED);
	m_pRenderer->ImmediateColourAlpha(1.0f, 1.0f, 1.0f, 1.0f);

	// Draw Front side
	//m_pRenderer->BindTexture(m_front);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	//m_pRenderer->BindTexture(m_back);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Right side
	//m_pRenderer->BindTexture(m_right);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Left side
	//m_pRenderer->BindTexture(m_left);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Top side
	//m_pRenderer->BindTexture(m_top);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Bottom side
	//m_pRenderer->BindTexture(m_bottom);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
}
