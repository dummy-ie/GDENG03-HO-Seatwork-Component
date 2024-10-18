#include "Cube.h"

#include "AppWindow.h"
#include "Camera.h"
#include "CameraManager.h"
#include "EngineTime.h"
#include "InputSystem.h"

using namespace engine;
using namespace application;

Cube::Cube(std::string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	/*
	this->vertex_list[0] = { Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) };
	this->vertex_list[1] = { Vector3D(-0.5f, 0.5f, -0.5f), Vector3D(1, 1, 0), Vector3D(0.2f, 0.2f, 0) };
	this->vertex_list[2] = { Vector3D(0.5f, 0.5f, -0.5f), Vector3D(1, 1, 0), Vector3D(0.2f, 0.2f, 0) };
	this->vertex_list[3] = { Vector3D(0.5f, -0.5f, -0.5f), Vector3D(1, 0, 0), Vector3D(0.2f, 0, 0) };

	this->vertex_list[4] = { Vector3D(0.5f, -0.5f, 0.5f), Vector3D(0, 1, 0), Vector3D(0, 0.2f, 0) };
	this->vertex_list[5] = { Vector3D(0.5f, 0.5f, 0.5f), Vector3D(0, 1, 1), Vector3D(0, 0.2f, 0.2f) };
	this->vertex_list[6] = { Vector3D(-0.5f, 0.5f, 0.5f), Vector3D(0, 1, 1), Vector3D(0, 0.2f, 0.2f) };
	this->vertex_list[7] = { Vector3D(-0.5f, -0.5f, 0.5f), Vector3D(0, 1, 0), Vector3D(0, 0.2f, 0) };
	*/

	Vector3D color1 = Vector3D(230.0f / 255.0f, 230.0f / 255.0f, 250.0f / 255.0f);
	Vector3D color2 = Vector3D(214.0f / 255.0f, 209.0f / 255.0f, 236.0f / 255.0f);
	Vector3D color3 = Vector3D(182.0f / 255.0f, 166.0f / 255.0f, 209.0f / 255.0f);
	Vector3D color4 = Vector3D(150.0f / 255.0f, 123.0f / 255.0f, 182.0f / 255.0f);

	vertex vertexList[] =
	{
		{Vector3D(-0.5f,-0.5f,-0.5f),color3, color3 },
		{Vector3D(-0.5f,0.5f, -0.5f),color1, color1 },
		{Vector3D(0.5f, 0.5f, -0.5f),color1, color1 },
		{Vector3D(0.5f, -0.5f,-0.5f),color3, color3 },
																									
		{Vector3D(0.5f, -0.5f,0.5f), color4, color4 },
		{Vector3D(0.5f, 0.5f, 0.5f), color2, color2 },
		{Vector3D(-0.5f,0.5f, 0.5f), color2, color2 },
		{Vector3D(-0.5f,-0.5f,0.5f), color4, color4 }
	};

	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	vertexBuffer->load(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, sizeShader);

	unsigned int indexList[] = {
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

	indexBuffer = GraphicsEngine::getInstance()->createIndexBuffer();
	indexBuffer->load(indexList, ARRAYSIZE(indexList));

	CBData cbData;
	angle = 0.0f;
	cbData.time = angle;

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constantBuffer->load(&cbData, sizeof(CBData));

	InputSystem::getInstance()->addListener(this);

	speed = 0.0f;
}

Cube::~Cube()
{
}

void Cube::onCreate()
{

}

void Cube::update(float deltaTime)
{
	CBData cbData;

	//if (startRotate)
	//	deltaRotation += EngineTime::getDeltaTime() * speed;

	cbData.time = 0.0f;
	//setRotation(deltaRotation, deltaRotation, deltaRotation);

	elapsedTime += EngineTime::getDeltaTime() / 2.0f;

	this->localPosition = Vector3D::lerp(Vector3D(0.0f, 0.25f, 0.0f), Vector3D(0.0f, -1.25f, 0.0f), (sin(elapsedTime) + 1.0f) / 2.0f);

	Matrix4x4 transform;
	Matrix4x4 temp;

	// Scale
	transform.setIdentity();
	transform.setScale(this->localScale);

	// Scale * Rotation
	temp.setIdentity();
	temp.setRotationZ(0.0f);
	transform *= temp;

	temp.setIdentity();
	temp.setRotationY(0.0f);
	transform *= temp;

	temp.setIdentity();
	temp.setRotationX(0.0f);
	transform *= temp;

	// Scale * Rotation * Translation
	temp.setIdentity();
	temp.setTranslation(this->localPosition);
	transform *= temp;

	cbData.worldMatrix.setMatrix(transform);

	cbData.viewMatrix = CameraManager::getInstance()->getMainCameraViewMatrix();

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	cbData.projMatrix.setPerspectiveFovLH(1.57f, width / height, 0.1f, 100.0f);

	constantBuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cbData);
}

// Sets shaders and draws afterwards
void Cube::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setIndexBuffer(indexBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawIndexedTriangleList(indexBuffer->getSizeIndexList(),0,0);
}

void Cube::onDestroy()
{
	InputSystem::getInstance()->removeListener(this);
	vertexBuffer->release();
	indexBuffer->release();
	constantBuffer->release();
}

void Cube::onKeyDown(int key)
{
	/*if (key == 'W')
	{
		this->startRotate = true;
		this->localRotation.x += atan(1) * 4 * EngineTime::getDeltaTime();
	}
	else if (key == 'S')
	{
		this->localRotation.x -= atan(1) * 4 * EngineTime::getDeltaTime();
	}
	else if (key == 'A')
	{
		this->localRotation.y += atan(1) * 4 * EngineTime::getDeltaTime();
	}
	else if (key == 'D')
	{
		this->localRotation.y -= atan(1) * 4 * EngineTime::getDeltaTime();
	}*/

}

void Cube::onKeyUp(int key)
{
}

void Cube::onMouseMove(const Vector2D& deltaMousePosition)
{
	localRotation.x -= deltaMousePosition.y * EngineTime::getDeltaTime();
	localRotation.y -= deltaMousePosition.x * EngineTime::getDeltaTime();
}

void Cube::onLeftMouseDown(const Vector2D& mousePosition)
{
	//this->localScale = Vector3D(0.5f, 0.5f, 0.5f);
}

void Cube::onLeftMouseUp(const Vector2D& mousePosition)
{
	//this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
}

void Cube::onRightMouseDown(const Vector2D& mousePosition)
{
	//this->localScale = Vector3D(2.0f, 2.0f, 2.0f);
}

void Cube::onRightMouseUp(const Vector2D& mousePosition)
{
	//this->localScale = Vector3D(1.0f, 1.0f, 1.0f);
}

void Cube::setSpeed(float speed)
{
	this->speed = speed;
}
