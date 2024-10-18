#include "AppWindow.h"

#include <string>
#include <Windows.h>

#include "Border.h"
#include "Camera.h"
#include "CameraManager.h"
#include "Cube.h"
#include "Circle.h"
#include "Quad.h"
#include "EngineTime.h"
#include "SceneCamera.h"
#include "GameObjectManager.h"
#include "Vector3D.h"
#include "InputSystem.h"
#include "OrbitCamera.h"
#include "Plane.h"
#include "Random.h"
#include "SceneCameraHandler.h"

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

		GameObjectManager::getInstance()->update(EngineTime::getDeltaTime());
		//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer, 1);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer, 1);
		GameObjectManager::getInstance()->draw(this, vertexShader, pixelShader);
	}

	swapChain->present(false);
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
	CameraManager::initialize();
	GraphicsEngine::initialize();

	swapChain = GraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	swapChain->init(this->m_hwnd, width, height);
	
	//viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));

	CBEditor cbData;
	cbData.wireframe = false;

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constantBuffer->load(&cbData, sizeof(CBEditor));

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	vertexShader = GraphicsEngine::getInstance()->createVertexShader(shaderByteCode, sizeShader);

	/*for (int i = 0; i < 100; i++)
	{
		float x = Random::range(-0.75f, 0.75f);
		float y = Random::range(-0.75f, 0.75f);

		Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
		cube->setSpeed(Random::range(-3.75f, 3.75f));
		cube->setPosition(x, y, 0.0f);
		cube->setScale(0.25f, 0.25f, 0.25f);
		GameObjectManager::getInstance()->addObject(cube);
	}*/

	Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
	cube->setPosition(0.0f, -0.5f, 0.0f);
	cube->setScale(0.25f, 0.25f, 0.25f);
	GameObjectManager::getInstance()->addObject(cube);

	Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
	plane->setPosition(0.0f, -0.5f, 0.0f);
	GameObjectManager::getInstance()->addObject(plane);

	//Border* border = new Border("Border", shaderByteCode, sizeShader);
	//GameObjectManager::getInstance()->addObject(border);

	/*OrbitCamera* camera1 = new OrbitCamera("Camera 1");
	camera1->setPosition(0, 0, -2);
	camera1->setObjectToOrbit(cube);
	camera1->setSpeed(10.0f);
	GameObjectManager::getInstance()->addObject(camera1);
	CameraManager::getInstance()->addCamera(camera1);

	OrbitCamera* camera2 = new OrbitCamera("Camera 2");
	camera2->setPosition(0, 0, -2);
	camera2->setObjectToOrbit(cube);
	camera2->setSpeed(-10.0f);
	GameObjectManager::getInstance()->addObject(camera2);
	CameraManager::getInstance()->addCamera(camera2);

	Camera* camera3 = new Camera("Camera 3");
	camera3->setPosition(0, 0, -2);
	GameObjectManager::getInstance()->addObject(camera3);
	CameraManager::getInstance()->addCamera(camera3);*/

	//InputSystem::getInstance()->showCursor(false);

	/*SceneCamera* camera4 = new SceneCamera("Camera 4");
	camera4->setPosition(0, 0.75, -0.75f);
	Vector3D newRotation = camera4->getLocalRotation();
	newRotation.x = 45;
	camera4->setRotation(newRotation);
	GameObjectManager::getInstance()->addObject(camera4);
	CameraManager::getInstance()->addCamera(camera4);*/
	//CameraManager::getInstance()->addCamera(camera4);

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
}

void AppWindow::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		P_SHARED_INSTANCE->constantBuffer->release();
		P_SHARED_INSTANCE->release();
	}
}
