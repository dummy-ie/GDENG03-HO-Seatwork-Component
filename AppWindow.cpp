#include "AppWindow.h"

using namespace application;

__declspec(align(16))
struct constant
{
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

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	unsigned long new_time = 0;
	if (m_old_time)
		new_time = ::GetTickCount() - m_old_time;
	m_delta_time = new_time / 1000.0f;
	m_old_time = ::GetTickCount();

	m_angle += 1.57f * m_delta_time;

	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	/*GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb2);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb2->getSizeVertexList(), 0);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb3);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb3->getSizeVertexList(), 0);*/

	/*for (int i = 0; i < objectList.size(); i++) {
		objectList[i]->update();
		objectList[i]->draw();
	}*/
		
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb->release();
	//m_vb2->release();
	//m_vb3->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();

	//for (int i = 0; i > objectList.size(); i++) {
	//	objectList[i]->onDestroy();
	//}

	//objectList.clear();

	GraphicsEngine::destroy();
}

void AppWindow::initializeEngine()
{
	GraphicsEngine::initialize();

	m_swap_chain = GraphicsEngine::getInstance()->createSwapChain();

	RECT windowRect = this->getClientWindowRect();

	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;

	m_swap_chain->init(this->m_hwnd, width, height);

	vertex list[] =
	{
		/* // RECTANGLE USING TRIANGLE LIST
		{-0.5f, -0.5f, 0.0f}, // POS 1
		{-0.5f, 0.5f, 0.0f}, // POS 2
		{0.5f, 0.5f, 0.0f}, // POS 3

		{0.5f, 0.5f, 0.0f}, // POS 4
		{0.5f, -0.5f, 0.0f}, // POS 5
		{-0.5f, -0.5f, 0.0f}, // POS 6 */

		{-0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0,  0,1,0 }, // POS1
		{-0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,    1,1,0,  0,1,1 }, // POS2
		{ 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f,   0,0,1,  1,0,0 },// POS2
		{ 0.5f,0.5f,0.0f,      0.88f,0.77f,0.0f,    1,1,1,  0,0,1 }
		/*// RAINBOW RECTANGLE
		{-0.5f, -0.5f, 0.0f, -0.32f, -0.11f, 0.0f,1, 0, 0},
		{-0.5f,  0.5f, 0.0f, -0.11f,  0.78f, 0.0f, 0, 1, 0},
		{ 0.5f, -0.5f, 0.0f, 0.75f, -0.73f, 0.0f,0, 0, 1},
		{ 0.5f,  0.5f, 0.0f, 0.88f,  0.77f, 0.0f,1, 1, 0}*/

		/*// RAINBOW TRIANGLE
		{-0.5f, -0.5f, 0.0f, 1, 0, 0},
		{0.0f,  0.5f, 0.0f, 0, 1, 0},
		{ 0.5f, -0.5f, 0.0f, 0, 0, 1}*/

		/*// GREEN RECTANGLE
		{-0.5f, -0.5f, 0.0f, 0, 1, 0},
		{-0.5f,  0.5f, 0.0f, 0, 1, 0},
		{ 0.5f, -0.5f, 0.0f, 0, 1, 0},
		{ 0.5f,  0.5f, 0.0f, 0, 1, 0}*/
	};

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();


	/*
	const vec3 scale = { 0.25, 0.25, 0.25 };

	objectList.push_back(new Quad(
							{ 0.6, 0.6 , 0 },
							{},
							{ 0.25f, 0.25f, 0.25f },
							{}
							{}));
	objectList.push_back(new Quad({0,0,0},  {0.25f, 0.25f, 0.25f }, green));
	objectList.push_back(new Quad({-0.6,-0.6,0}, { 0.25f, 0.25f, 0.25f }, blue));

	for (int i = 0; i < objectList.size(); i++) {
		objectList[i]->onCreate();
	}*/

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
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
