#pragma once

#include <vector>

#include "Window.h"
#include "GraphicsEngine.h"
#include "Viewport.h"
#include "SwapChain.h"
#include "IndexBuffer.h"
#include "DeviceContext.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

#include "InputListener.h"
#include "ViewportScreen.h"

using namespace graphics;

class AppWindow : public Window, public InputListener
{
private:
	SwapChain* swapChain;

	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ConstantBuffer* constantBuffer;

	RasterizerState* solidState;
	RasterizerState* wireframeState;

public:
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Vector2D& deltaMousePosition) override;

	virtual void onLeftMouseDown(const Vector2D& mousePosition) override;
	virtual void onLeftMouseUp(const Vector2D& mousePosition) override;

	virtual void onRightMouseDown(const Vector2D& mousePosition) override;
	virtual void onRightMouseUp(const Vector2D& mousePosition) override;

	void initializeEngine();
	void drawOnRenderTexture(RenderTexture* renderTexture, EFillMode fillMode);

public:
	void draw(EFillMode fillMode);
	void update();
	SwapChain* getSwapChain();
private:
	static AppWindow* P_SHARED_INSTANCE;

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&);
	AppWindow& operator = (AppWindow const&);

public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();
};