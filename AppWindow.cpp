#include "AppWindow.h"

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


	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	//m_angle += 1.57f * m_delta_time;

	//constant cc;
	//cc.m_angle = m_angle;

	//m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	/*GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);*/

	for (Viewport* vp : viewPorts)
	{
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport(vp);
		//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
		/*GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb2->getSizeVertexList(), 0);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb3);
		GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb3->getSizeVertexList(), 0);*/

		for (int i = 0; i < objectList.size(); i++) {
			objectList[i]->update(m_delta_time);
			objectList[i]->draw();
		}
	}
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewport()
	
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top, 1);

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
	
	const vec3 scale = { 0.25, 0.25, 0.25 };

	objectList.push_back(new Quad({ 0.6f, 0.6f, 0 }, { 0.25f, 0.25f, 0.25f }, {1, 0, 0}));
	objectList.push_back(new Quad({0,0,0},  {0.25f, 0.25f, 0.25f }, {0, 1, 0}));
	objectList.push_back(new Quad({-0.6,-0.6,0}, { 0.25f, 0.25f, 0.25f }, {0, 0, 1}));

	for (GameObject* gameObject : objectList) {
		gameObject->onCreate();
	}

	//viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f));

	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, 0.0f, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(0.0f, height / 2, width / 2, height / 2, 0.0f, 1.0f));
	viewPorts.push_back(GraphicsEngine::getInstance()->createViewport(width / 2, height / 2, width / 2, height / 2, 0.0f, 1.0f));
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
