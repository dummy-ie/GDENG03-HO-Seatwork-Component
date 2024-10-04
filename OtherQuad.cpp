#include "OtherQuad.h"

#include "EngineTime.h"
#include "Quad.h"

using namespace engine;

OtherQuad::OtherQuad(vec3 position, vec3 scale, vec3 color) : GameObject(position, scale)
{
	m_vb = nullptr;
	m_vs = nullptr;
	m_ps = nullptr;
	this->color = color;
}

OtherQuad::~OtherQuad()
{
}

void OtherQuad::onCreate()
{
	// Initialize Constant Position and Colors (White)
	//this->list[0] = { -0.5f,-0.5f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0, 0,1,0 };
	//this->list[1] = { -0.5f,0.5f,0.0f,     -0.11f,0.78f,0.0f,   1,1,0, 0,1,1 };
	//this->list[2] = { 0.5f,-0.5f,0.0f,     0.75f,-0.73f,0.0f, 0,0,1,  1,0,0 };
	//this->list[3] = { 0.5f,0.5f,0.0f,     0.88f,0.77f,0.0f,    1,1,1, 0,0,1 };

	this->list[0] = { -0.66f,-0.78f,0.0f,    -0.32f,-0.11f,0.0f,   0,0,0, 0,1,0 };
	this->list[1] = { -0.8f,0.2f,0.0f,     -0.1f,0.84f,0.0f,   1,1,0, 0,1,1 };
	this->list[2] = { 0.88f,-0.3f,0.0f,     0.0f,-0.73f,0.0f, 0,0,1,  1,0,0 };
	this->list[3] = { -0.66f,-0.78f,0.0f,     0.88f,0.8f,0.0f,    1,1,1, 0,0,1 };

	this->setPosition(position);
	this->setScale(scale);
	//this->setColor(color);

	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	constant cc;
	cc.m_angle = 29.83f;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void OtherQuad::update()
{
	m_angle += 1.57 * EngineTime::getDeltaTime();

	constant cc;
	cc.m_angle = m_angle;

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

// Sets shaders and draws afterwards
void OtherQuad::draw()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void OtherQuad::onDestroy()
{
	m_cb->release();
	m_vb->release();
	m_vs->release();
	m_ps->release();
}

void OtherQuad::setPosition(vec3 position)
{
	GameObject::setPosition(position);

	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.x += position.x;
		this->list[i].position.y += position.y;
		this->list[i].position.z += position.z;
		this->list[i].position1.x += position.x;
		this->list[i].position1.y += position.y;
		this->list[i].position1.z += position.z;
	}
}

// Too lazy to create a matrix
void OtherQuad::setScale(vec3 scale)
{
	GameObject::setScale(scale);
	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.x -= position.x;
		this->list[i].position.y -= position.y;
		this->list[i].position.z -= position.z;
		this->list[i].position1.x -= position.x;
		this->list[i].position1.y -= position.y;
		this->list[i].position1.z -= position.z;
	}
	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.x *= scale.x;
		this->list[i].position.y *= scale.y;
		this->list[i].position.z *= scale.z;
		this->list[i].position1.x *= scale.x;
		this->list[i].position1.y *= scale.y;
		this->list[i].position1.z *= scale.z;
	}
	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.x += position.x;
		this->list[i].position.y += position.y;
		this->list[i].position.z += position.z;
		this->list[i].position1.x += position.x;
		this->list[i].position1.y += position.y;
		this->list[i].position1.z += position.z;
	}
}

void OtherQuad::setColor(vec3 color)
{
	for (int i = 0; i < 4; i++)
	{
		this->list[i].color = color;
		this->list[i].color1 = color;
	}
}

