#include "Circle.h"
#include <iostream>
#include "math.h"
#include "AppWindow.h"
#include "EngineTime.h"
#include "Random.h"

using namespace application;

Circle::Circle(float radius, int sides, Vector3D position, Vector3D scale, Vector3D color) : GameObject(position, scale)
{
	this->radius = radius;
	this->sides = sides;
	m_vb = nullptr;
	m_vs = nullptr;
	m_ps = nullptr;
	this->color = color;
}

Circle::~Circle()
{
}

void Circle::onCreate()
{
	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	float orthoWidth = width / 300.0f;
	float orthoHeight = height / 300.0f;

	this->radius /= 300.0f;

	float deltaTheta = 2 * (atan(1) * 4) / sides; // Change in theta for each vertex
	for (int i = 0; i < sides; i++) {
		float theta = i * deltaTheta; // Theta is the angle for that triangle
		float index = 3 * i;
		list.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0,0,0), Vector3D(0,0,0) });
		list.push_back({ Vector3D(cos(theta) * radius, sin(theta) * radius, 0.0f), Vector3D(1,i % 2,1), Vector3D(0,0,1) });
		list.push_back({ Vector3D(cos(theta + deltaTheta) * radius, sin(theta + deltaTheta) * radius, 0.0f), Vector3D(1,i % 2,1), Vector3D(0,0,1) });
	}

	this->setPosition(position);
	//this->setScale(scale);
	//this->setColor(color);

	constant cc;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	UINT size_list = list.size();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list.data(), sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	//Vector3D direction
	float xDirection = Random::range(-100, 100);
	float yDirection = Random::range(-100, 100);

	m_direction = Vector3D(xDirection, yDirection, 0.0f);
	m_direction = m_direction.normalize();
	m_speed = 1.0f;
}

void Circle::update(float deltaTime)
{
	constant cc;

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	float orthoWidth = width / 300.0f;
	float orthoHeight = height / 300.0f;

	if (position.m_y + this->radius >= orthoHeight / 2 && !inTop)
	{
		inTop = true;
		m_direction.m_y = m_direction.m_y * -1.0f;
	}
	else
		inTop = false;
		
	if (position.m_y - this->radius <= -orthoHeight / 2 && !inBottom)
	{
		inBottom = true;
		m_direction.m_y = m_direction.m_y * -1.0f;
	}
	else
		inBottom = false;

	if (position.m_x + this->radius >= orthoWidth / 2 && !inRight)
	{
		inRight = true;
		m_direction.m_x = m_direction.m_x * -1.0f;
	}
	else
		inRight = false;
		
	if (position.m_x - this->radius <= -orthoWidth / 2 && !inLeft)
	{
		inLeft = true;
		m_direction.m_x = m_direction.m_x * -1.0f;
	}
	else
		inLeft = false;
		

	position += m_direction * m_speed * EngineTime::getDeltaTime();

	cc.m_world.setTranslation(position);

	cc.m_view.setIdentity();

	cc.m_proj.setOrthoLH(orthoWidth, orthoHeight, -4.0f, 4.0f);

	m_cb->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cc);
}

// Sets shaders and draws afterwards
void Circle::draw()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Circle::onDestroy()
{
	m_vb->release();
	m_cb->release();
	m_vs->release();
	m_ps->release();
	delete this;
}

void Circle::setPosition(Vector3D position)
{
	GameObject::setPosition(position);

	for (int i = 0; i < list.size(); i++)
	{
		this->list[i].position.m_x += position.m_x;
		this->list[i].position.m_y += position.m_y;
		this->list[i].position.m_z += position.m_z;
	}
}

// Too lazy to create a matrix
void Circle::setScale(Vector3D scale)
{
	GameObject::setScale(scale);
	for (int i = 0; i < list.size(); i++)
	{
		this->list[i].position.m_x -= position.m_x;
		this->list[i].position.m_y -= position.m_y;
		this->list[i].position.m_z -= position.m_z;
	}
	for (int i = 0; i < list.size(); i++)
	{
		this->list[i].position.m_x *= scale.m_x;
		this->list[i].position.m_y *= scale.m_y;
		this->list[i].position.m_z *= scale.m_z;
	}
	for (int i = 0; i < list.size(); i++)
	{
		this->list[i].position.m_x += position.m_x;
		this->list[i].position.m_y += position.m_y;
		this->list[i].position.m_z += position.m_z;
	}
}

void Circle::setColor(Vector3D color)
{
	for (int i = 0; i < list.size(); i++)
	{
		this->list[i].color = color;
		this->list[i].color1 = color;
	}
}

