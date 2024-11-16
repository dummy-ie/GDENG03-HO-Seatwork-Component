#include "TexturedCube.h"

#include "AppWindow.h"
#include "CameraManager.h"
#include "ShaderLibrary.h"
#include "TexturedVertexBuffer.h"

using namespace graphics;

TexturedCube::TexturedCube(std::string name) : Cube(name)
{
	Vector3D positionList[] =
	{
		Vector3D(-0.5f,-0.5f,-0.5f),
		Vector3D(-0.5f,0.5f, -0.5f),
		Vector3D(0.5f, 0.5f, -0.5f),
		Vector3D(0.5f, -0.5f,-0.5f),

		Vector3D(0.5f, -0.5f,0.5f),
		Vector3D(0.5f, 0.5f, 0.5f),
		Vector3D(-0.5f,0.5f, 0.5f),
		Vector3D(-0.5f,-0.5f,0.5f)
	};

	Vector2D texCoordList[] =
	{
		Vector2D(0.0f, 0.0f),
		Vector2D(0.0f, 1.0f),
		Vector2D(1.0f, 0.0f),
		Vector2D(1.0f, 1.0f),
	};

	vertex vertexList[] =
	{
		{positionList[0], texCoordList[1]},
		{positionList[1], texCoordList[0]},
		{positionList[2], texCoordList[2]},
		{positionList[3], texCoordList[3]},

		{positionList[4], texCoordList[1]},
		{positionList[5], texCoordList[0]},
		{positionList[6], texCoordList[2]},
		{positionList[7], texCoordList[3]},

		{positionList[1], texCoordList[1]},
		{positionList[6], texCoordList[0]},
		{positionList[5], texCoordList[2]},
		{positionList[2], texCoordList[3]},

		{positionList[7], texCoordList[1]},
		{positionList[0], texCoordList[0]},
		{positionList[3], texCoordList[2]},
		{positionList[4], texCoordList[3]},

		{positionList[3], texCoordList[1]},
		{positionList[2], texCoordList[0]},
		{positionList[5], texCoordList[2]},
		{positionList[4], texCoordList[3]},

		{positionList[7], texCoordList[1]},
		{positionList[6], texCoordList[0]},
		{positionList[1], texCoordList[2]},
		{positionList[0], texCoordList[3]},
	};

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	ShaderNames shaderNames;

	void* shaderByteCode = NULL;
	size_t sizeShader = 0;

	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	vertexBuffer = renderSystem->createTexturedVertexBuffer(vertexList, sizeof(vertex), ARRAYSIZE(vertexList), shaderByteCode, sizeShader);

	unsigned int indexList[] = {
		0,1,2,
		2,3,0,

		4,5,6,
		6,7,4,

		8,9,10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20
	};

	indexBuffer = renderSystem->createIndexBuffer(indexList, ARRAYSIZE(indexList));

	CBObjectData cbData;
	angle = 0.0f;
	cbData.time = angle;

	constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBObjectData));

	speed = 1.0f;
	deltaRotation = 0.0f;
}

TexturedCube::~TexturedCube()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete constantBuffer;
}

void TexturedCube::onCreate()
{
}

void TexturedCube::update(float deltaTime)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	CBObjectData cbObjectData;

	cbObjectData.time = 0.0f;

	elapsedTime += EngineTime::getDeltaTime() / 2.0f;

	Matrix4x4 transform, rotation;
	Matrix4x4 temp;

	this->updateLocalMatrix();

	cbObjectData.worldMatrix.setMatrix(this->localMatrix);

	constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cbObjectData);
}

// Sets shaders and draws afterwards
void TexturedCube::draw(int width, int height)
{
	ShaderNames shaderNames;
	DeviceContext* deviceContext = GraphicsEngine::getInstance()->getRenderSystem()->getImmediateDeviceContext();

	Texture* woodTex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"assets/textures/wood.jpg");

	VertexShader* vertexShader = ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME);
	PixelShader* pixelShader = ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME);

	deviceContext->setTexture(woodTex);
	deviceContext->setConstantBuffer(constantBuffer, 0);

	deviceContext->setVertexShader(vertexShader);
	deviceContext->setPixelShader(pixelShader);

	deviceContext->setVertexBuffer(vertexBuffer);
	deviceContext->setIndexBuffer(indexBuffer);

	deviceContext->drawIndexedTriangleList(indexBuffer->getSizeIndexList(), 0, 0);
}

void TexturedCube::onDestroy()
{
}
