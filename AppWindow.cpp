#include "AppWindow.h"

#include <string>
#include <Windows.h>

#include "Cube.h"
#include "Circle.h"
#include "Quad.h"
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "Vector3D.h"
#include "InputSystem.h"
#include "Random.h"

using namespace application;


void AppWindow::onCreate()
{
	Window::onCreate();
	
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->swapChain, 
		0.0, 0.0, 0.0, 1);

	for (int i = 0; i < viewPorts.size(); i++)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport(viewPorts[i]);
		if (i % 2 == 1)
			viewPorts[i]->setRasterizerWireframeState();
		else
			viewPorts[i]->setRasterizerSolidState();
		
		GameObjectManager::getInstance()->update(EngineTime::getDeltaTime());
		GameObjectManager::getInstance()->draw(this, vertexShader, pixelShader);
	}

	swapChain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	InputSystem::getInstance()->removeListener(this);
	InputSystem::destroy();

	GameObjectManager::getInstance()->deleteAllObjects();

	for (auto vp : viewPorts)
	{
		vp->release();
	}

	viewPorts.clear();
	swapChain->release();
	
	GraphicsEngine::destroy();
	GameObjectManager::destroy();
}

void AppWindow::onKeyDown(int key)
{
	
}

void AppWindow::onKeyUp(int key)
{
	if (key == VK_ESCAPE) {
		//m_is_running = false;
	}
	else if (key == VK_BACK) {
		//GameObjectManager::getInstance()->deleteLastObject();
	}
	else if (key == VK_SPACE) {
		//Circle* circle = new Circle(50.0f, 100);
		//GameObjectManager::getInstance()->addObject(circle);
	}
	else if (key == VK_DELETE)
	{
		//GameObjectManager::getInstance()->deleteAllObjects();
	}
}

void AppWindow::initializeEngine()
{
	InputSystem::initialize();
	Random::initialize();

	InputSystem::getInstance()->addListener(this);

	GraphicsEngine::initialize();

	swapChain = GraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	swapChain->init(this->m_hwnd, width, height);
	
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shaderByteCode, sizeShader);

	for (int i = 0; i < 100; i++)
	{
		float x = Random::range(-0.75f, 0.75f);
		float y = Random::range(-0.75f, 0.75f);

		Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
		cube->setSpeed(Random::range(-3.75f, 3.75f));
		cube->setPosition(x, y, 0.0f);
		cube->setScale(0.25f, 0.25f, 0.25f);
		GameObjectManager::getInstance()->addObject(cube);
	}

	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	pixelShader = GraphicsEngine::getInstance()->createPixelShader(shaderByteCode, sizeShader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	
	/*viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, height / 2, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, height / 2, width / 2, height / 2, 0.0f, 1.0f));*/
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
}

void AppWindow::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		P_SHARED_INSTANCE->release();
	}
}
