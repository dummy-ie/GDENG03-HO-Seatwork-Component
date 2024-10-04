#include "AppWindow.h"

#include "OtherQuad.h"

using namespace application;

/*__declspec(align(16))
struct constant
{
	float m_angle;
};*/

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

	for (Viewport* vp : viewPorts)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport(vp);

		for (int i = 0; i < objectList.size(); i++) {
			objectList[i]->update();
			objectList[i]->draw();
		}
	}

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	for (int i = 0; i > objectList.size(); i++) {
		objectList[i]->onDestroy();
	}

	for (auto vp : viewPorts)
	{
		vp->release();
	}

	viewPorts.clear();
	objectList.clear();

	//m_cb->release();
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

	// Quads added to object list
	//objectList.push_back(new Quad({ 0.6f, 0.6f, 0 }, { 0.25f, 0.25f, 0.25f }, {1, 0, 0}));
	//objectList.push_back(new Quad({0,0,0},  {0.25f, 0.25f, 0.25f }, {0, 1, 0}));
	//objectList.push_back(new Quad({-0.6,-0.6,0}, { 0.25f, 0.25f, 0.25f }, {0, 0, 1}));

	//objectList.push_back(new Quad({ -0.5f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }, { 1, 0, 0 }));
	//objectList.push_back(new OtherQuad({ 0.5f, 0.0f, 0.0f }, { 0.5f, 0.5f, 0.5f }, { 1, 0, 0 }));
	objectList.push_back(new OtherQuad({ 0.0, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { 1, 0, 0 }));

	for (GameObject* gameObject : objectList) {
		gameObject->onCreate();
	}

	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));
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
