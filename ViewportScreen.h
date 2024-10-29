#pragma once

#include "UIScreen.h"

#include "RenderTexture.h"
#include "Prerequisites.h"
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
	EFillMode currentFillMode = SOLID;
	RenderTexture* renderTexture;

private:
	ViewportScreen();
	~ViewportScreen();

private:
	friend class UIManager;

private:
	virtual void draw() override;
};