#include "Border.h"

#include "AppWindow.h"
#include "Camera.h"

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

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	this->constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBData));

	UINT sizeList = ARRAYSIZE(list);

	this->vertexBuffer = renderSystem->createVertexBuffer(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);
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
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	CBData cbData;
	cbData.time = 0.0f;

	cbData.worldMatrix.setIdentity();

	cbData.viewMatrix.setIdentity();

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	cbData.projMatrix.setIdentity();

	this->constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cbData);
}

// Sets shaders and draws afterwards
void Border::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(vertexShader, this->constantBuffer);
	renderSystem->getImmediateDeviceContext()->setConstantBuffer(pixelShader, this->constantBuffer);

	renderSystem->getImmediateDeviceContext()->setVertexShader(vertexShader);
	renderSystem->getImmediateDeviceContext()->setPixelShader(pixelShader);

	renderSystem->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);

	renderSystem->getImmediateDeviceContext()->drawLineStrip(this->vertexBuffer->getSizeVertexList(), 0);
}

void Border::onDestroy()
{
	delete this->constantBuffer;
	delete this->vertexBuffer;
}
