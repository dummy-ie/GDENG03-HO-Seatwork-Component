#include "AppWindow.h"

#include <Windows.h>

#include "Quad.h"
#include "EngineTime.h"
#include "Vector3D.h"

using namespace application;

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

void AppWindow::onCreate()
{
	Window::onCreate();
	
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 
		0.3, 0.3, 0.6, 1);

	//RECT rc = this->getClientWindowRect();
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top, 0);

	updateQuadPosition();

	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	/*GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);*/

	for (Viewport* vp : viewPorts)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport(vp);

		for (int i = 0; i < objectList.size(); i++) {
			objectList[i]->update(EngineTime::getDeltaTime());
			objectList[i]->draw(m_cb);
		}
	}
	
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top, 1);

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	for (int i = 0; i > objectList.size(); i++) {
		objectList[i]->onDestroy();
	}

	m_cb->release();

	for (auto vp : viewPorts)
	{
		vp->release();
	}

	viewPorts.clear();
	objectList.clear();
	m_swap_chain->release();
	
	GraphicsEngine::destroy();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	m_swap_chain->init(this->m_hwnd, width, height);
	
	constant cc;
	cc.m_angle = 0.0f;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	// Quads added to object list

	/*const vec3 scale = { 0.25, 0.25, 0.25 };

	objectList.push_back(new Quad({ 0.6f, 0.6f, 0 }, { 0.25f, 0.25f, 0.25f }, {1, 0, 0}));
	objectList.push_back(new Quad({0,0,0},  {0.25f, 0.25f, 0.25f }, {0, 1, 0}));
	objectList.push_back(new Quad({-0.6,-0.6,0}, { 0.25f, 0.25f, 0.25f }, {0, 0, 1}));*/

	objectList.push_back(new Quad({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }, { 1, 0, 0 }));

	for (GameObject* gameObject : objectList) {
		gameObject->onCreate();
	}

	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));

	//viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	//viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	//viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, height / 2, width / 2, height / 2, 0.0f, 1.0f));
	//viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, height / 2, width / 2, height / 2, 0.0f, 1.0f));
}

void AppWindow::updateQuadPosition()
{
	m_angle += 1.57f * EngineTime::getDeltaTime();

	constant cc;
	cc.m_angle = m_angle;

	m_delta_pos += EngineTime::getDeltaTime() / 10.0f;
	m_delta_scale += EngineTime::getDeltaTime() / 1.0f;

	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	Matrix4x4 temp;

	cc.m_world.setScale (Vector3D::lerp(Vector3D(0.5f, 0.5, 0), Vector3D(1, 1, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));
	cc.m_world *= temp;


	cc.m_view.setIdentity();

	RECT windowRect = this->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	cc.m_proj.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

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
