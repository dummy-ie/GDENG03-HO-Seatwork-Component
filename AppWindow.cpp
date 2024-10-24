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
#include "Logger.h"
#include "OrbitCamera.h"
#include "Plane.h"
#include "Random.h"
#include "SceneCameraHandler.h"

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

	float freq = 1.0f;
	count += EngineTime::getDeltaTime();
	Vector4D rainbow = Vector4D(
		std::sin(freq * count + 0) * 127 + 128,
		std::sin(freq * count + 2) * 127 + 128,
		std::sin(freq * count + 4) * 127 + 128,
		255);

	Vector4D rainbow2 = Vector4D(
		std::sin(freq * count + 2) * 127 + 128,
		std::sin(freq * count + 0) * 127 + 128,
		std::sin(freq * count + 4) * 127 + 128,
		255);

	Vector4D rainbow3 = Vector4D(
		std::sin(freq * count + 4) * 127 + 128,
		std::sin(freq * count + 2) * 127 + 128,
		std::sin(freq * count + 0) * 127 + 128,
		255);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (my_tool_active)
	{
		ImGui::Begin("About", &my_tool_active);

		ImVec4 vec4 = ImVec4(rainbow.x / 255.0f, rainbow.y / 255.0f, rainbow.z / 255.0f, rainbow.w / 255.0f);
		ImVec4 vec4_2 = ImVec4(rainbow2.x / 255.0f, rainbow2.y / 255.0f, rainbow2.z / 255.0f, rainbow2.w / 255.0f);
		ImVec4 vec4_3 = ImVec4(rainbow3.x / 255.0f, rainbow3.y / 255.0f, rainbow3.z / 255.0f, rainbow3.w / 255.0f);

		ImGui::TextColored(vec4, "Scene Editor v0.01");
		ImGui::TextColored(vec4_2, "Created by Shane Laurenze Cablayan");
		ImGui::TextColored(vec4_3, "Soon with Ray Tracing");
		if (ImGui::Button("Close"))
		{
			my_tool_active = false;
		}
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

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
	
	GraphicsEngine::destroy();
	GameObjectManager::destroy();
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

	/*for (int i = 1; i <= 50; i++)
	{
		float x = Random::range(-1.5f, 1.5f);
		float y = Random::range(-1.5f, 1.5f);

		Cube* cube = new Cube("Cube " + std::to_string(i), shaderByteCode, sizeShader);
		cube->setSpeed(Random::range(-3.75f, 3.75f));
		cube->setPosition(x, y, 0.0f);
		cube->setScale(0.5f, 0.5f, 0.5f);
		GameObjectManager::getInstance()->addObject(cube);
	}*/

	Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
	cube->setPosition(0.0f, 0.4f, 0.0f);
	cube->setScale(0.25f, 0.25f, 0.25f);
	GameObjectManager::getInstance()->addObject(cube);

	Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
	GameObjectManager::getInstance()->addObject(plane);

	// Test Case 6
	/*Cube* cube = new Cube("Cube 1", shaderByteCode, sizeShader);
	cube->setPosition(0.0f, 0.9f, 0.0f);
	GameObjectManager::getInstance()->addObject(cube);

	cube = new Cube("Cube 2", shaderByteCode, sizeShader);
	cube->setPosition(-1.5f, 2.0f, 0.0f);
	GameObjectManager::getInstance()->addObject(cube);

	cube = new Cube("Cube 3", shaderByteCode, sizeShader);
	cube->setPosition(-1.5f, 3.0f, -2.0f);
	GameObjectManager::getInstance()->addObject(cube);

	Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
	plane->setPosition(0.0f, 0.0f, 0.0f);
	plane->setScale(4.0f, 1.0f, 4.0f);
	GameObjectManager::getInstance()->addObject(plane);*/

	// Test Case 7
	/*float xOffset = 0.8f;
	float yOffset = 0.925f;
	float startXPos = -0.6f;
	float startYPos = 3.0f;
	int rows = 3;
	int spaces = rows + 4 - 1;
	int cubeCount = 1;
	for (int i = 1; i <= rows;i++)
	{
		int xSpaceOffset = 0;
		for (int k = spaces; k >= 1; k--) {
			xSpaceOffset += 1;
		}
		for (int j = 1; j <= i; j++)
		{
			Cube* cube = new Cube("Card " + std::to_string(cubeCount), shaderByteCode, sizeShader);
			cube->setPosition(startXPos + xOffset * j + xSpaceOffset * 0.4f, startYPos - (yOffset * i), 0.0f);
			cube->setScale(0.01f, 1.0f, 0.5f);
			cube->setRotation(0.0f, 0.0f, -0.4f);
			GameObjectManager::getInstance()->addObject(cube);
			cubeCount++;

			cube = new Cube("Card " + std::to_string(cubeCount), shaderByteCode, sizeShader);
			cube->setPosition(startXPos + xOffset * j + 0.4f + xSpaceOffset * 0.4f, startYPos - (yOffset * i), 0.0f);
			cube->setScale(0.01f, 1.0f, 0.5f);
			cube->setRotation(0.0f, 0.0f, 0.4f);
			GameObjectManager::getInstance()->addObject(cube);
			cubeCount++;

			if (i != rows) {
				cube = new Cube("Card " + std::to_string(cubeCount), shaderByteCode, sizeShader);
				cube->setPosition(startXPos + 1.0f * j + 0.4f * xSpaceOffset - 0.2f * (j - 1), (startYPos - 0.475f) - (yOffset * i), 0.0f);
				cube->setScale(0.01f, 1.0f, 0.5f);
				cube->setRotation(0.0f, 0.0f, 1.5708f);
				GameObjectManager::getInstance()->addObject(cube);
				cubeCount++;
			}
		}
		spaces--;
	}*/

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

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

	// Setup Platform/Renderer backends
	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getDirectXDevice(), GraphicsEngine::getInstance()->getImmediateDeviceContext()->getContext());
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
