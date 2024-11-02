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

private:
	ViewportScreen(int index);
	~ViewportScreen();

public:
	virtual void draw() override;

private:
	void drawViewportUI();

private:
	friend class UIManager;
	friend class ViewportManager;
};