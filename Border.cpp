#include "Border.h"
#include "AppWindow.h"
#include "Camera.h"
#include "EngineTime.h"
#include "InputSystem.h"

using namespace engine;
using namespace application;

Border::Border(std::string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex list[] =
	{
		{ Vector3D(-1.0f,-1.0f,0.0f),   Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(-1.0f,1.0f,0.0f),   Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(1.0f,1.0f,0.0f),Vector3D(0,0,0),  Vector3D(0,0,0) },
		{ Vector3D(1.0f,-1.0f,0.0f),    Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(-1.0f,-1.0f,0.0f),    Vector3D(0,0,0), Vector3D(0,0,0) }
	};

	CBData cbData;
	cbData.time = 0.0f;

	constantBuffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constantBuffer->load(&cbData, sizeof(CBData));

	UINT sizeList = ARRAYSIZE(list);

	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();
	vertexBuffer->load(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);
}

Border::~Border()
{
}

void Border::onCreate()
{
	GameObject::onCreate();
}

void Border::update(float deltaTime)
{
	CBData cbData;
	cbData.time = 0.0f;

	cbData.worldMatrix.setIdentity();

	cbData.viewMatrix.setIdentity();

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	cbData.projMatrix.setIdentity();

	constantBuffer->update(GraphicsEngine::getInstance()->getImmediateDeviceContext(), &cbData);
}

// Sets shaders and draws afterwards
void Border::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawLineStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Border::onDestroy()
{
	constantBuffer->release();
	vertexBuffer->release();
}
