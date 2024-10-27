#include "Quad.h"

#include "AppWindow.h"

Quad::Quad(std::string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex list[] =
	{
		{ Vector3D(-0.5f,-0.5f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) },
		{ Vector3D(0.5f,-0.5f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) }
	};

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	CBData cc;
	cc.time = 0.0f;

	constantBuffer = renderSystem->createConstantBuffer(&cc, sizeof(CBData));

	UINT sizeList = ARRAYSIZE(list);

	vertexBuffer = renderSystem->createVertexBuffer(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);
}

Quad::~Quad()
{
}

void Quad::onCreate()
{
	GameObject::onCreate();
}

void Quad::update(float deltaTime)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	angle += 1.57f * EngineTime::getDeltaTime();

	CBData cc;
	cc.time = angle;
	
	deltaPosition += EngineTime::getDeltaTime() / 10.0f;
	deltaScale += EngineTime::getDeltaTime() / 1.0f;

	if (deltaPosition > 1.0f)
		deltaPosition = 0;

	Matrix4x4 temp;

	cc.worldMatrix.setIdentity();

	cc.worldMatrix.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5, 0), Vector3D(1, 1, 0), (sin(deltaScale) + 1.0f) / 2.0f));

	temp.setIdentity();
	temp.setTranslation(Vector3D::lerp(Vector3D(0.1f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), deltaPosition));
	cc.worldMatrix *= temp;

	cc.viewMatrix.setIdentity();

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	cc.projMatrix.setOrthoLH(width / 300.0f, height / 300.0f, -4.0f, 4.0f);

	constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cc);
}

// Sets shaders and draws afterwards
void Quad::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	renderSystem->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	renderSystem->getImmediateDeviceContext()->setVertexShader(vertexShader);
	renderSystem->getImmediateDeviceContext()->setPixelShader(pixelShader);

	renderSystem->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	renderSystem->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Quad::onDestroy()
{
	delete constantBuffer;
	delete vertexBuffer;
}
