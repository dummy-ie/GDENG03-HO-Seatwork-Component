#include "AppWindow.h"

#include <string>
#include <Windows.h>

#include "Cube.h"
#include "Circle.h"
#include "Quad.h"
#include "EngineTime.h"
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

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 
		0.0, 0.0, 0.0, 1);

	//RECT rc = this->getClientWindowRect();
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top, 0);

	//updateQuadPosition();

	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	/*GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);*/

	for (int i = 0; i < viewPorts.size(); i++)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport(viewPorts[i]);
		if (i % 2 == 1)
			viewPorts[i]->setRasterizerWireframeState();
		else
			viewPorts[i]->setRasterizerSolidState();
		

		for (GameObject* obj : objectList) {
			obj->update(EngineTime::getDeltaTime());
			obj->draw();
		}
	}
	
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top, 1);
	int frames = 1 / EngineTime::getDeltaTime();
	std::string title = "[CABLAYAN] DirectXApplication | FPS : " + std::to_string(frames);
	SetWindowTextA(m_hwnd, title.c_str());
	m_swap_chain->present(true);

	
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	InputSystem::getInstance()->removeListener(this);

	for (int i = 0; i > objectList.size(); i++) {
		objectList[i]->onDestroy();
	}

	for (auto vp : viewPorts)
	{
		vp->release();
	}
	m_cb->release();
	viewPorts.clear();
	objectList.clear();
	m_swap_chain->release();
	
	GraphicsEngine::destroy();
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f * EngineTime::getDeltaTime();
	}
	else if (key == VK_SPACE) {
		Circle* circle = new Circle(50.0f, 100, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1, 0, 0 });
		circle->onCreate();
		objectList.push_back(circle);
		objectStack.push(circle);
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == VK_ESCAPE) {
		m_is_running = false;
	}
	else if (key == VK_BACK) {
		if (!objectList.empty())
		{
			objectList.back()->onDestroy();
			objectList.pop_back();
		}
	}
	else if (key == VK_SPACE) {
		Circle* circle = new Circle(50.0f, 100, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f}, { 1, 0, 0 });
		circle->onCreate();
		objectList.push_back(circle);
		objectStack.push(circle);
	}
}

void AppWindow::initializeEngine()
{
	InputSystem::initialize();
	Random::initialize();

	InputSystem::getInstance()->addListener(this);

	GraphicsEngine::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	// Quads added to object list
	/*objectList.push_back(new Quad({0.6f, 0.6f, 0 }, {0.25f, 0.25f, 0.25f }, {1, 0, 0}));
	objectList.push_back(new Quad({0,0,0},  {0.25f, 0.25f, 0.25f }, {0, 1, 0}));
	objectList.push_back(new Quad({-0.6,-0.6,0}, { 0.25f, 0.25f, 0.25f }, {0, 0, 1}));*/

	//objectList.push_back(new Quad({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1, 0, 0 }));

	//objectList.push_back(new Cube({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1, 0, 0 }));
	//objectList.push_back(new Circle(0.5f, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1, 0, 0 }));

	for (GameObject* gameObject : objectList) {
		gameObject->onCreate();
	}

	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));

	/*viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, height / 2, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, height / 2, width / 2, height / 2, 0.0f, 1.0f));*/
}

void AppWindow::updateQuadPosition()
{
	constant cc;

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
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
