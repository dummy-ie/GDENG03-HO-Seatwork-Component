#pragma once

#include "UIScreen.h"

#include "RenderTexture.h"
#include "Prerequisites.h"
#include "SceneCamera.h"
#include "Viewport.h"

enum EFillMode
{
	SOLID,
	WIREFRAME,
	SOLID_WIREFRAME
};

using namespace graphics;
class ViewportScreen : public UIScreen
{
private:
	int index;
	int camIndex;

	SceneCamera* currentCamera;

	EFillMode currentFillMode = SOLID;
	RenderTexture* renderTexture;

	bool isRightMouseDown = false;

public:
	ViewportScreen(int index);
	~ViewportScreen();
	virtual void draw() override;

private:
	friend class UIManager;

	
};