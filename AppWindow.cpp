#include "AppWindow.h"

#include <Windows.h>

#include "Camera.h"
#include "CameraManager.h"
#include "Cube.h"
#include "Circle.h"
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "InputSystem.h"
#include "Logger.h"
#include "Random.h"
#include "UIManager.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

using namespace application;

__declspec(align(16))
struct CBEditor
{
	int32_t wireframe;
};

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	float deltaTime = EngineTime::getDeltaTime();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 
		0.83, 0.58, 0.895, 1);

	for (int i = 0; i < viewPorts.size(); i++)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport(viewPorts[i]);
		CBEditor cbData;
		cbData.wireframe = false;
		viewPorts[i]->setRasterizerSolidState();
		if (i == 1 || i == 2 || i ==4)
		{
			viewPorts[i]->setRasterizerWireframeState();
			cbData.wireframe = true;
		}

		CameraManager::getInstance()->setMainCameraByIndex(i);

		constantBuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cbData);

		GameObjectManager::getInstance()->update(deltaTime);
		//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer, 1);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer, 1);
		GameObjectManager::getInstance()->draw(this, vertexShader, pixelShader);
	}
	CameraManager::getInstance()->updateSceneCamera(deltaTime);

	UIManager::getInstance()->draw();

	swapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	InputSystem::getInstance()->removeListener(this);

	GameObjectManager::getInstance()->deleteAllObjects();

	for (auto vp : viewPorts)
	{
		vp->release();
	}

	viewPorts.clear();
	swapChain->release();

	UIManager::destroy();
	CameraManager::destroy();
	GameObjectManager::destroy();
	GraphicsEngine::destroy();
	InputSystem::destroy();
}

void AppWindow::onFocus()
{
	Window::onFocus();
	InputSystem::getInstance()->startUpdate();
}

void AppWindow::onKillFocus()
{
	Window::onKillFocus();
	InputSystem::getInstance()->stopUpdate();
}

void AppWindow::onKeyDown(int key)
{
	
}

void AppWindow::onKeyUp(int key)
{
	if (key == VK_ESCAPE) {
		//m_is_running = false;
	}
}

void AppWindow::onMouseMove(const Vector2D& deltaMousePosition)
{
}

void AppWindow::onLeftMouseDown(const Vector2D& mousePosition)
{
}

void AppWindow::onLeftMouseUp(const Vector2D& mousePosition)
{
}

void AppWindow::onRightMouseDown(const Vector2D& mousePosition)
{
}

void AppWindow::onRightMouseUp(const Vector2D& mousePosition)
{
}

void AppWindow::initializeEngine()
{
	Random::initialize();
	InputSystem::getInstance()->addListener(this);
	GameObjectManager::initialize();
	CameraManager::initialize();
	GraphicsEngine::initialize();
	UIManager::initialize(m_hwnd);

	swapChain = GraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	swapChain->init(this->m_hwnd, width, height);

	CBEditor cbData;
	cbData.wireframe = false;

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constantBuffer->load(&cbData, sizeof(CBEditor));

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::getInstance()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));
	
	/*viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, height / 2, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, height / 2, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, height / 2, width / 2, height / 2, 0.0f, 1.0f));*/
}

void AppWindow::update()
{
}

AppWindow* AppWindow::P_SHARED_INSTANCE = NULL;
AppWindow::AppWindow() {}
AppWindow::~AppWindow() {}
AppWindow::AppWindow(const AppWindow&) {}

AppWindow* AppWindow::getInstance() {
	return P_SHARED_INSTANCE;
}

void AppWindow::initialize()
{
	P_SHARED_INSTANCE = new AppWindow();
	P_SHARED_INSTANCE->init();
	debug::Logger::log(P_SHARED_INSTANCE, "Initialized");
}

void AppWindow::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		P_SHARED_INSTANCE->constantBuffer->release();
		P_SHARED_INSTANCE->release();
	}
}
