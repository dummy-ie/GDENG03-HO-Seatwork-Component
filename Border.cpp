#include "Border.h"

#include "AppWindow.h"
#include "Camera.h"
#include "ShaderLibrary.h"

Border::Border(std::string name) : GameObject(name)
{
	vertex list[] =
	{
		{ Vector3D(-1.0f,-1.0f,0.0f),   Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(-1.0f,1.0f,0.0f),   Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(1.0f,1.0f,0.0f),Vector3D(0,0,0),  Vector3D(0,0,0) },
		{ Vector3D(1.0f,-1.0f,0.0f),    Vector3D(0,0,0), Vector3D(0,0,0) },
		{ Vector3D(-1.0f,-1.0f,0.0f),    Vector3D(0,0,0), Vector3D(0,0,0) }
	};

	CBObjectData cbData;
	cbData.time = 0.0f;

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	this->constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBObjectData));

	UINT sizeList = ARRAYSIZE(list);

	ShaderNames shaderNames;

	void* shaderByteCode = NULL;
	size_t sizeShader = 0;

	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

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

	CBObjectData cbData;
	cbData.time = 0.0f;

	cbData.worldMatrix.setIdentity();

	this->constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cbData);
}

// Sets shaders and draws afterwards
void Border::draw(int width, int height)
{
	ShaderNames shaderNames;

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	VertexShader* vertexShader = ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME);
	PixelShader* pixelShader = ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME);

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(constantBuffer, 0);

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
