#include "AppWindow.h"

#include <Windows.h>

#include "GameObjectManager.h"
#include "CameraManager.h"
#include "UIManager.h"

#include "InputSystem.h"
#include "EngineTime.h"
#include "imgui.h"
#include "Logger.h"
#include "Random.h"

__declspec(align(16))
struct CBEditor
{
	int32_t wireframe;
};

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::initialize();
	initializeEngine();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::getInstance()->update();

	float deltaTime = EngineTime::getDeltaTime();

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	renderSystem->getImmediateDeviceContext()->setViewportSize(width, height);

	GameObjectManager::getInstance()->update(deltaTime);

	CameraManager::getInstance()->updateSceneCamera(deltaTime);

	UIManager::getInstance()->draw();

	if (UIManager::RESIZE_WIDTH != 0 && UIManager::RESIZE_HEIGHT != 0)
	{
		swapChain->cleanRenderTarget();
		swapChain->resizeBuffers(0, UIManager::RESIZE_WIDTH, UIManager::RESIZE_HEIGHT);
		UIManager::RESIZE_WIDTH = UIManager::RESIZE_HEIGHT = 0;
		swapChain->createRenderTarget();
	}

	swapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	InputSystem::getInstance()->removeListener(this);

	GameObjectManager::getInstance()->deleteAllObjects();

	delete swapChain;

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
	// Try Initializing Managers
	try
	{
		GraphicsEngine::initialize();
		Random::initialize();
		InputSystem::getInstance()->addListener(this);
		GameObjectManager::initialize();
		CameraManager::initialize();
		UIManager::initialize(m_hwnd);
	}
	catch (...)
	{
		m_is_running = false;
	}

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	// Initialize the Swap Chain
	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	this->swapChain = renderSystem->createSwapChain(this->m_hwnd, width, height);

	// Initialize the Constant Buffer
	CBEditor cbData;
	cbData.wireframe = false;

	this->constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBEditor));

	// Initialize the Shaders
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;

	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	this->vertexShader = renderSystem->createVertexShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &shaderByteCode, &sizeShader);
	this->pixelShader = renderSystem->createPixelShader(shaderByteCode, sizeShader);
	renderSystem->releaseCompiledShader();

	// Initialize Rasterizer States
	this->solidState = renderSystem->createRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK);
	this->wireframeState = renderSystem->createRasterizerState(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);

	debug::Logger::log(this, "Initialized Engine");
}

void AppWindow::draw(EFillMode fillMode)
{
	DeviceContext* context = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	CBEditor cbData;
	switch (fillMode)
	{
	default:
		context->setRasterizerState(solidState);
		cbData.wireframe = false;
		break;
	case WIREFRAME:
		context->setRasterizerState(wireframeState);
		cbData.wireframe = true;
		break;
	case SOLID_WIREFRAME:
		context->setRasterizerState(solidState);
		this->draw(SOLID);
		context->setRasterizerState(wireframeState);
		cbData.wireframe = true;
		break;
	}

	context->setConstantBuffer(constantBuffer, 1);
	this->constantBuffer->update(context, &cbData);

	GameObjectManager::getInstance()->draw(this, vertexShader, pixelShader);
}

void AppWindow::update()
{
}

SwapChain* AppWindow::getSwapChain()
{
	return this->swapChain;
}

AppWindow* AppWindow::P_SHARED_INSTANCE = NULL;
AppWindow::AppWindow()
{
	debug::Logger::log(this, "Initialized");
}
AppWindow::~AppWindow() {}
AppWindow::AppWindow(const AppWindow&) {}

AppWindow* AppWindow::getInstance() {
	return P_SHARED_INSTANCE;
}

void AppWindow::initialize()
{
	if (P_SHARED_INSTANCE)
		throw std::exception("App Window already created");
	P_SHARED_INSTANCE = new AppWindow();
	
}

void AppWindow::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE->constantBuffer;
		debug::Logger::log(P_SHARED_INSTANCE, "Released");
	}
}
