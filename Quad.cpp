#include "Quad.h"

Quad::Quad(Vector3D position, Vector3D scale, Vector3D color) : GameObject(position, scale)
{
	m_vb = nullptr;
	m_vs = nullptr;
	m_ps = nullptr;
	this->color = color;
}

Quad::~Quad()
{
}

void Quad::onCreate()
{
	// Initialize Constant Position and Colors (White)
	/*this->list[0] = { Vector3D(- 1.0f, -1.0f, 0.0f) , Vector3D( - 0.64f, -0.22f,  0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1)};
	this->list[1] = { Vector3D(-1.0f,  1.0f, 0.0f), Vector3D(-0.22f, 1.56f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1)};
	this->list[2] = { Vector3D(1.0f, -1.0f, 0.0f), Vector3D(1.5f, -1.46f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
	this->list[3] = { Vector3D(1.0f,  1.0f, 0.0f), Vector3D(1.76f, 1.54f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };*/

	this->list[0] = { Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(-0.32f,-0.11f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) };
	this->list[1] = { Vector3D(-0.5f,0.5f,0.0f),     Vector3D(-0.11f,0.78f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) };
	this->list[2] = { Vector3D(0.5f,-0.5f,0.0f),     Vector3D(0.75f,-0.73f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) };
	this->list[3] = { Vector3D(0.5f,0.5f,0.0f),     Vector3D(0.88f,0.77f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) };

	this->setPosition(position);
	this->setScale(scale);
	//this->setColor(color);

	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();
}

void Quad::update(float deltaTime)
{
	
}

// Sets shaders and draws afterwards
void Quad::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
}

void Quad::onDestroy()
{
	m_vb->release();
	m_vs->release();
	m_ps->release();
}

void Quad::setPosition(Vector3D position)
{
	GameObject::setPosition(position);

	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.m_x += position.m_x;
		this->list[i].position.m_y += position.m_y;
		this->list[i].position.m_z += position.m_z;
		this->list[i].position1.m_x += position.m_x;
		this->list[i].position1.m_y += position.m_y;
		this->list[i].position1.m_z += position.m_z;
	}
}

// Too lazy to create a matrix
void Quad::setScale(Vector3D scale)
{
	GameObject::setScale(scale);
	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.m_x -= position.m_x;
		this->list[i].position.m_y -= position.m_y;
		this->list[i].position.m_z -= position.m_z;
		this->list[i].position1.m_x -= position.m_x;
		this->list[i].position1.m_y -= position.m_y;
		this->list[i].position1.m_z -= position.m_z;
	}
	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.m_x *= scale.m_x;
		this->list[i].position.m_y *= scale.m_y;
		this->list[i].position.m_z *= scale.m_z;
		this->list[i].position1.m_x *= scale.m_x;
		this->list[i].position1.m_y *= scale.m_y;
		this->list[i].position1.m_z *= scale.m_z;
	}
	for (int i = 0; i < 4; i++)
	{
		this->list[i].position.m_x += position.m_x;
		this->list[i].position.m_y += position.m_y;
		this->list[i].position.m_z += position.m_z;
		this->list[i].position1.m_x += position.m_x;
		this->list[i].position1.m_y += position.m_y;
		this->list[i].position1.m_z += position.m_z;
	}
}

void Quad::setColor(Vector3D color)
{
	for (int i = 0; i < 4; i++)
	{
		this->list[i].color = color;
		this->list[i].color1 = color;
	}
} 

