#include "Quad.h"

#include "AppWindow.h"
#include "CameraManager.h"
#include "ShaderLibrary.h"

Quad::Quad(std::string name) : GameObject(name)
{
	vertex list[] =
	{
		{ Vector3D(-0.5f,-0.5f,0.0f),   Vector3D(0,0,0), Vector3D(0,1,0) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1,1,0), Vector3D(0,1,1) },
		{ Vector3D(0.5f,-0.5f,0.0f), Vector3D(0,0,1),  Vector3D(1,0,0) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(1,1,1), Vector3D(0,0,1) }
	};

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	CBObjectData cc;
	cc.time = 0.0f;

	constantBuffer = renderSystem->createConstantBuffer(&cc, sizeof(CBObjectData));

	UINT sizeList = ARRAYSIZE(list);

	ShaderNames shaderNames;

	void* shaderByteCode = NULL;
	size_t sizeShader = 0;

	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.BASE_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

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

	CBObjectData cc;
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

	constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cc);
}

// Sets shaders and draws afterwards
void Quad::draw(int width, int height)
{
	ShaderNames shaderNames;
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	VertexShader* vertexShader = ShaderLibrary::getInstance()->getVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME);
	PixelShader* pixelShader = ShaderLibrary::getInstance()->getPixelShader(shaderNames.BASE_PIXEL_SHADER_NAME);

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(constantBuffer);

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
