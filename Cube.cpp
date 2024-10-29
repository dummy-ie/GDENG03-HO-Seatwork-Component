#include "Cube.h"

#include "AppWindow.h"
#include "CameraManager.h"

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

	Vector3D color5 = Vector3D(230.0f / 255.0f, 230.0f / 255.0f, 250.0f / 255.0f);
	Vector3D color6 = Vector3D(214.0f / 255.0f, 209.0f / 255.0f, 236.0f / 255.0f);
	Vector3D color7 = Vector3D(182.0f / 255.0f, 166.0f / 255.0f, 209.0f / 255.0f);
	Vector3D color8 = Vector3D(150.0f / 255.0f, 123.0f / 255.0f, 182.0f / 255.0f);

	//RAINBOW COLOR
	/*Vector3D color1 = Vector3D(1, 1, 0);
	Vector3D color2 = Vector3D(0, 1, 1);
	Vector3D color3 = Vector3D(1, 0, 0);
	Vector3D color4 = Vector3D(0, 1, 0);

	Vector3D color5 = Vector3D(0.2f, 0.2f, 0);
	Vector3D color6 = Vector3D(0, 0.2f, 0.2f);
	Vector3D color7 = Vector3D(0.2f, 0, 0);
	Vector3D color8 = Vector3D(0, 0.2f, 0);*/

	// WHITE COLOR
	/*Vector3D color1 = Vector3D(1, 1, 1);
	Vector3D color2 = Vector3D(1, 1, 1);
	Vector3D color3 = Vector3D(1, 1, 1);
	Vector3D color4 = Vector3D(1, 1, 1);

	Vector3D color5 = Vector3D(1, 1, 1);
	Vector3D color6 = Vector3D(1, 1, 1);
	Vector3D color7 = Vector3D(1, 1, 1);
	Vector3D color8 = Vector3D(1, 1, 1);*/

	vertex vertexList[] =
	{
		{Vector3D(-0.5f,-0.5f,-0.5f),color3, color7 },
		{Vector3D(-0.5f,0.5f, -0.5f),color1, color5 },
		{Vector3D(0.5f, 0.5f, -0.5f),color1, color5 },
		{Vector3D(0.5f, -0.5f,-0.5f),color3, color7 },
																									
		{Vector3D(0.5f, -0.5f,0.5f), color4, color8 },
		{Vector3D(0.5f, 0.5f, 0.5f), color2, color6 },
		{Vector3D(-0.5f,0.5f, 0.5f), color2, color6 },
		{Vector3D(-0.5f,-0.5f,0.5f), color4, color8 }
	};

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	vertexBuffer = renderSystem->createVertexBuffer(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, sizeShader);

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

	indexBuffer = renderSystem->createIndexBuffer(indexList, ARRAYSIZE(indexList));

	CBObjectData cbData;
	angle = 0.0f;
	cbData.time = angle;

	constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBObjectData));

	InputSystem::getInstance()->addListener(this);

	speed = 1.0f;
	deltaRotation = 0.0f;
}

Cube::~Cube()
{
}

void Cube::onCreate()
{
	GameObject::onCreate();
}

void Cube::update(float deltaTime)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	CBObjectData cbObjectData;

	cbObjectData.time = 0.0f;

	elapsedTime += EngineTime::getDeltaTime() / 2.0f;

	Matrix4x4 transform, rotation;
	Matrix4x4 temp;

	// Scale
	transform.setIdentity();
	transform.setScale(this->localScale);

	// Scale * Rotation
	rotation.setIdentity();
	rotation.setRotationZ(this->localRotation.z);

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	rotation *= temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	rotation *= temp;

	transform *= rotation;
	// Scale * Rotation * Translation
	temp.setIdentity();
	temp.setTranslation(this->localPosition);
	transform *= temp;

	cbObjectData.worldMatrix.setMatrix(transform);

	constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cbObjectData);
}

// Sets shaders and draws afterwards
void Cube::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(constantBuffer, 0);

	renderSystem->getImmediateDeviceContext()->setVertexShader(vertexShader);
	renderSystem->getImmediateDeviceContext()->setPixelShader(pixelShader);

	renderSystem->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);
	renderSystem->getImmediateDeviceContext()->setIndexBuffer(indexBuffer);

	renderSystem->getImmediateDeviceContext()->drawIndexedTriangleList(indexBuffer->getSizeIndexList(),0,0);
}

void Cube::onDestroy()
{
	InputSystem::getInstance()->removeListener(this);
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
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
	//localRotation.x -= deltaMousePosition.y * EngineTime::getDeltaTime();
	//localRotation.y -= deltaMousePosition.x * EngineTime::getDeltaTime();
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
