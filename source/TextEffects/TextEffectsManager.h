#pragma once

#include "AnimatedText.h"
#include "Renderer/Renderer.h"
#include "Renderer/camera.h"

#include "../tinythread/tinythread.h"
using namespace tthread;

#include <vector>
#include <string>
using namespace std;

typedef vector<AnimatedText*> AnimatedTextList;


class TextEffectsManager
{
public:
	TextEffectsManager(Renderer* pRenderer);
	~TextEffectsManager();

	void SetCamera(Camera* pCamera);

	AnimatedText* CreateTextEffect(unsigned int lFontID, unsigned int lOutlineFontID, unsigned int lViewportID, TextDrawMode lDrawMode, TextEffect lEffect, TextDrawStyle lDrawStyle, vec3 lPosition, Colour lColour, Colour lOutlineColour, const string &lText, float lifeTime);

	void Update(float lDeltaTime);
	void Render();

private:
	Renderer* mpRenderer;
	Camera* mpCamera;
	
	tthread::mutex m_animatedTextMutexLock;
	AnimatedTextList m_vpAnimatedTextList;
};
