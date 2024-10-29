#include "Plane.h"

#include "AppWindow.h"
#include "CameraManager.h"

Plane::Plane(std::string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{

	Vector3D color1 = Vector3D(255.0f / 255.0f, 227.0f / 255.0f, 222.0f / 255.0f);
	Vector3D color2 = Vector3D(241.0f / 255.0f, 204.0f / 255.0f, 202.0f / 255.0f);
	Vector3D color3 = Vector3D(226.0f / 255.0f, 180.0f / 255.0f, 181.0f / 255.0f);
	Vector3D color4 = Vector3D(212.0f / 255.0f, 157.0f / 255.0f, 161.0f / 255.0f);

	/*Vector3D color1 = Vector3D(1, 1, 1);
	Vector3D color2 = Vector3D(1, 1, 1);
	Vector3D color3 = Vector3D(1, 1, 1);
	Vector3D color4 = Vector3D(1, 1, 1);*/

	vertex list[] =
	{
		{ Vector3D(-8.0f,0.0f,-8.0f),   color1, color1 },
		{ Vector3D(-8.0f,0.0f,8.0f),   color2, color2 },
		{ Vector3D(8.0f,0.0f,-8.0f), color3,  color3 },
		{ Vector3D(8.0f,0.0f,8.0f),    color4, color4 },

		{ Vector3D(-8.0f,0.0f,-8.0f),   color1, color1 },
		{ Vector3D(-8.0f,0.0f,8.0f),   color2, color2 },
		{ Vector3D(8.0f,0.0f,-8.0f), color3,  color3 },
		{ Vector3D(8.0f,0.0f,8.0f),    color4, color4 }
	};

	/*vertex list[] =
	{
		{ Vector3D(-0.5f,-0.5f,0.0f),   Vector3D(1, 1, 1), Vector3D(1, 1, 1) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(1, 1, 1), Vector3D(1, 1, 1) },
		{ Vector3D(0.5f,-0.5f,0.0f), Vector3D(1, 1, 1),  Vector3D(1, 1, 1) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(1, 1, 1), Vector3D(1, 1, 1) }
	};*/
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	CBData cbData;
	cbData.time = 0.0f;

	constantBuffer = renderSystem->createConstantBuffer(&cbData, sizeof(CBData));

	UINT sizeList = ARRAYSIZE(list);

	vertexBuffer = renderSystem->createVertexBuffer(list, sizeof(vertex), sizeList, shaderByteCode, sizeShader);
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
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

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

	cbData.viewMatrix = CameraManager::getInstance()->getSceneCameraViewMatrix();

	//RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	//FLOAT width = windowRect.right - windowRect.left;
	//FLOAT height = windowRect.bottom - windowRect.top;

	////cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	//cbData.projMatrix.setPerspectiveFovLH(1.57f, width / height, 0.1f, 100.0f);
	cbData.projMatrix = CameraManager::getInstance()->getSceneCameraProjMatrix();

	constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cbData);
}

// Sets shaders and draws afterwards
void Plane::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(constantBuffer);

	renderSystem->getImmediateDeviceContext()->setVertexShader(vertexShader);
	renderSystem->getImmediateDeviceContext()->setPixelShader(pixelShader);

	renderSystem->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	renderSystem->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Plane::onDestroy()
{
	delete constantBuffer;
	delete vertexBuffer;
}
