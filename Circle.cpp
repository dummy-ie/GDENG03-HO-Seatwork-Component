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
	m_ib = nullptr;
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
	// Initialize Constant Position and Colors (White)
	/*this->list[0] = { Vector3D(- 1.0f, -1.0f, 0.0f) , Vector3D( - 0.64f, -0.22f,  0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1)};
	this->list[1] = { Vector3D(-1.0f,  1.0f, 0.0f), Vector3D(-0.22f, 1.56f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1)};
	this->list[2] = { Vector3D(1.0f, -1.0f, 0.0f), Vector3D(1.5f, -1.46f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
	this->list[3] = { Vector3D(1.0f,  1.0f, 0.0f), Vector3D(1.76f, 1.54f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };*/

	/*this->list[0] = {Vector3D(-0.5f,-0.5f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0)};
	this->list[1] = { Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) };
	this->list[2] = { Vector3D(0.5f,-0.5f,0.0f), Vectssor3D(0,0,1),  Vector3D(1,0,0) };
	this->list[3] = { Vector3D(0.5f,0.5f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) };*/
	int segments = 5;
	/*list.push_back({Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0,0,0), Vector3D(0,0,0)});

	int segments = 5;
	float deltaTheta = 2 * 3.14f / segments;
	for (int i = 0; i <= segments; i++) {
		float theta = i * deltaTheta;
		float x = 0.5F * cos(theta);
		float y = 0.5F * sin(theta);
		list.push_back( { Vector3D(x, y, 0.0f), Vector3D(1,i%2,1), Vector3D(0,0,1) });
	}*/

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	this->radius /= width;

	float deltaTheta = 2 * (atan(1) * 4) / sides; // Change in theta for each vertex
	for (int i = 0; i < sides; i++) {
		float theta = i * deltaTheta; // Theta is the angle for that triangle
		float index = 3 * i;
		list.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0,0,0), Vector3D(0,0,0) });
		list.push_back({ Vector3D(cos(theta) * radius, sin(theta) * radius, 0.0f), Vector3D(1,i % 2,1), Vector3D(0,0,1) });
		list.push_back({ Vector3D(cos(theta + deltaTheta) * radius, sin(theta + deltaTheta) * radius, 0.0f), Vector3D(1,i % 2,1), Vector3D(0,0,1) });
	}

	for (int i = 0; i < segments - 1; i++) {
		indices.push_back(0); // Center vertex
		indices.push_back(i + 1);
		indices.push_back((i + 2) % (segments + 1)); // Wrap around for the last vertex
	}
	indices.push_back(0); // Center vertex
	indices.push_back(segments);
	indices.push_back(1);

	for (int i = 0; i < indices.size(); i+=3)
	{
		std::cout << indices[i] << " : " << list[indices[i]].position.m_x << ", " << list[indices[i]].position.m_y << std::endl;
		std::cout << indices[i+1] << " : " << list[indices[i+1]].position.m_x << ", " << list[indices[i+1]].position.m_y << std::endl;
		std::cout << indices[i+2] << " : " << list[indices[i+2]].position.m_x << ", " << list[indices[i+2]].position.m_y << std::endl;
	}

	//indices.push_back(0);
	//indices.push_back(1);
	//indices.push_back(2);
	
	this->setPosition(position);
	//this->setScale(scale);
	//this->setColor(color);

	constant cc;
	cc.m_angle = 0.0f;

	m_cb = GraphicsEngine::getInstance()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));

	unsigned int index_list[] = {
		0,1,2,
		0,2,3,

		0,3,4,
		0,4,5,

		0,5,6,
		0,6,7,

		0,7,8,
		0,8,9,

		0,9,10,
		0,10,1,
	};


	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = indices.size();

	m_ib->load(index_list, size_index_list);

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
	direction = m_direction;
	m_speed = 1.0f;
}

void Circle::update(float deltaTime)
{
	constant cc;

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;
	/*if (position.m_y - this->radius >= 1.0f)
		m_direction.m_y = m_direction.m_y * -1.0f;
	if (position.m_y + this->radius <= -1.0f)
		m_direction.m_y = m_direction.m_y * -1.0f;
	if (position.m_x >= 1.0f + height / width)
		m_direction.m_x = m_direction.m_x * -1.0f;
	if (position.m_x <= -1.0f - height / width)
		m_direction.m_x = m_direction.m_x * -1.0f;*/

	if (position.m_y > 1.0f)
		direction.m_y = -m_direction.m_y;
	if (position.m_y < -1.0f)
		direction.m_y = m_direction.m_y;
	if (position.m_x > 1.0f)
		direction.m_x = -m_direction.m_x;
	if (position.m_x < -1.0f)
		direction.m_x = m_direction.m_x;

	position += direction * m_speed * EngineTime::getDeltaTime();

	cc.m_world.setTranslation(position);
	//cc.m_world *= temp;
	//cc.m_world.setIdentity();
	cc.m_view.setIdentity();

	std::cout << position.m_x << "," << position.m_y << std::endl;

	cc.m_proj.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);

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
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);
}

void Circle::onDestroy()
{
	m_vb->release();
	m_ib->release();
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

