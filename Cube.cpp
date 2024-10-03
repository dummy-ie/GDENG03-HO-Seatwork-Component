#include "Cube.h"

Cube::Cube(Vector3D position, Vector3D scale, Vector3D color) : GameObject(position, scale)
{
	m_vb = nullptr;
	m_vs = nullptr;
	m_ps = nullptr;
	this->color = color;
}

Cube::~Cube()
{
}

void Cube::onCreate()
{
	// Initialize Constant Position and Colors (White)
	/*this->list[0] = { Vector3D(- 1.0f, -1.0f, 0.0f) , Vector3D( - 0.64f, -0.22f,  0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1)};
	this->list[1] = { Vector3D(-1.0f,  1.0f, 0.0f), Vector3D(-0.22f, 1.56f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1)};
	this->list[2] = { Vector3D(1.0f, -1.0f, 0.0f), Vector3D(1.5f, -1.46f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };
	this->list[3] = { Vector3D(1.0f,  1.0f, 0.0f), Vector3D(1.76f, 1.54f, 0.0f), Vector3D(1, 1, 1), Vector3D(1, 1, 1) };*/

	
	this->vertex_list[0] = { Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) };
	this->vertex_list[1] = {Vector3D(-0.5f, 0.5f, -0.5f), Vector3D(1, 1, 0), Vector3D(0.2f, 0.2f, 0) };
	this->vertex_list[2] = { Vector3D(0.5f, 0.5f, -0.5f), Vector3D(1, 1, 0), Vector3D(0.2f, 0.2f, 0) };
	this->vertex_list[3] = { Vector3D(0.5f, -0.5f, -0.5f), Vector3D(1, 0, 0), Vector3D(0.2f, 0, 0) };

	this->vertex_list[4] = { Vector3D(0.5f, -0.5f, 0.5f), Vector3D(0, 1, 0), Vector3D(0, 0.2f, 0) };
	this->vertex_list[5] = { Vector3D(0.5f, 0.5f, 0.5f), Vector3D(0, 1, 1), Vector3D(0, 0.2f, 0.2f) };
	this->vertex_list[6] = { Vector3D(-0.5f, 0.5f, 0.5f), Vector3D(0, 1, 1), Vector3D(0, 0.2f, 0.2f) };
	this->vertex_list[7] = { Vector3D(-0.5f, -0.5f, 0.5f), Vector3D(0, 1, 0), Vector3D(0, 0.2f, 0) };

	m_vb = GraphicsEngine::getInstance()->createVertexBuffer();
	UINT size_vertex_list = ARRAYSIZE(vertex_list);

	unsigned int index_list[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		1,6,5,
		5,2,1,

		7,0,3,
		3,4,7,

		3,2,5,
		5,4,3,

		7,6,1,
		1,0,7
	};

	m_ib = GraphicsEngine::getInstance()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::getInstance()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertex_list, sizeof(vertex), size_vertex_list, shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	GraphicsEngine::getInstance()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::getInstance()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::getInstance()->releaseCompiledShader();

	//this->setPosition(position);
	//this->setScale(scale);
}

void Cube::update(float deltaTime)
{

}

// Sets shaders and draws afterwards
void Cube::draw(ConstantBuffer* cb)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(),0,0);
}

void Cube::onDestroy()
{
	m_vb->release();
	m_ib->release();
	m_vs->release();
	m_ps->release();
}

void Cube::setPosition(Vector3D position)
{
	GameObject::setPosition(position);

	for (int i = 0; i < 8; i++)
	{
		this->vertex_list[i].position.m_x += position.m_x;
		this->vertex_list[i].position.m_y += position.m_y;
		this->vertex_list[i].position.m_z += position.m_z;
	}
}

// Too lazy to create a matrix
void Cube::setScale(Vector3D scale)
{
	GameObject::setScale(scale);
	for (int i = 0; i < 4; i++)
	{
		this->vertex_list[i].position.m_x -= position.m_x;
		this->vertex_list[i].position.m_y -= position.m_y;
		this->vertex_list[i].position.m_z -= position.m_z;
	}
	for (int i = 0; i < 4; i++)
	{
		this->vertex_list[i].position.m_x *= scale.m_x;
		this->vertex_list[i].position.m_y *= scale.m_y;
		this->vertex_list[i].position.m_z *= scale.m_z;
	}
	for (int i = 0; i < 4; i++)
	{
		this->vertex_list[i].position.m_x += position.m_x;
		this->vertex_list[i].position.m_y += position.m_y;
		this->vertex_list[i].position.m_z += position.m_z;
	}
}

void Cube::setColor(Vector3D color)
{
	for (int i = 0; i < 4; i++)
	{
		this->vertex_list[i].color = color;
		this->vertex_list[i].color1 = color;
	}
}

