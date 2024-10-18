#include "Plane.h"
#include "AppWindow.h"
#include "Camera.h"
#include "CameraManager.h"
#include "EngineTime.h"
#include "InputSystem.h"

using namespace engine;
using namespace application;

Plane::Plane(std::string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{

	Vector3D color1 = Vector3D(255.0f / 255.0f, 227.0f / 255.0f, 222.0f / 255.0f);
	Vector3D color2 = Vector3D(241.0f / 255.0f, 204.0f / 255.0f, 202.0f / 255.0f);
	Vector3D color3 = Vector3D(226.0f / 255.0f, 180.0f / 255.0f, 181.0f / 255.0f);
	Vector3D color4 = Vector3D(212.0f / 255.0f, 157.0f / 255.0f, 161.0f / 255.0f);

	vertex list[] =
	{
		{ Vector3D(-1.0f,0.0f,-1.0f),   color1, color1 },
		{ Vector3D(-1.0f,0.0f,1.0f),   color2, color2 },
		{ Vector3D(1.0f,0.0f,-1.0f), color3,  color3 },
		{ Vector3D(1.0f,0.0f,1.0f),    color4, color4 }
	};

	/*vertex list[] =
	{
		{ Vector3D(-0.5f,-0.5f,0.0f),   Vector3D(1, 1, 1), Vector3D(1, 1, 1) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1, 1, 1), Vector3D(1, 1, 1) },
		{ Vector3D(0.5f,-0.5f,0.0f), Vector3D(1, 1, 1),  Vector3D(1, 1, 1) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(1, 1, 1), Vector3D(1, 1, 1) }
	};*/

	CBData cbData;
	cbData.time = 0.0f;

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constantBuffer->load(&cbData, sizeof(CBData));

	UINT sizeList = ARRAYSIZE(list);

	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	vertexBuffer->load(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);
}

Plane::~Plane()
{
}

void Plane::onCreate()
{
	GameObject::onCreate();
}

void Plane::update(float deltaTime)
{
	CBData cbData;

	cbData.time = 0.0f;

	Matrix4x4 transform;
	Matrix4x4 temp;

	// Scale
	transform.setIdentity();
	transform.setScale(this->localScale);

	// Scale * Rotation
	temp.setIdentity();
	temp.setRotationZ(this->localRotation.z);
	transform *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	transform *= temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
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
void Plane::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Plane::onDestroy()
{
	constantBuffer->release();
	vertexBuffer->release();
}
