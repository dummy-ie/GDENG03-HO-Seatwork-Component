#include "Circle.h"

#include "AppWindow.h"
#include "Random.h"

Circle::Circle(std::string name, float radius, int sides, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	this->radius = radius;
	this->sides = sides;
	vertexBuffer = nullptr;

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	float orthoWidth = width / 300.0f;
	float orthoHeight = height / 300.0f;

	this->radius /= 300.0f;

	float deltaTheta = 2 * (atan(1) * 4) / sides; // Change in theta for each vertex
	for (int i = 0; i < sides; i++) {
		float theta = i * deltaTheta; // Theta is the angle for that triangle
		float index = 3 * i;
		list.push_back({ Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0,0,0), Vector3D(0,0,0) });
		list.push_back({ Vector3D(cos(theta) * radius, sin(theta) * radius, 0.0f), Vector3D(1,i % 2,1), Vector3D(0,0,1) });
		list.push_back({ Vector3D(cos(theta + deltaTheta) * radius, sin(theta + deltaTheta) * radius, 0.0f), Vector3D(1,i % 2,1), Vector3D(0,0,1) });
	}

	CBData cc;

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	constantBuffer = renderSystem->createConstantBuffer();
	constantBuffer->load(&cc, sizeof(CBData));

	UINT size_list = list.size();

	vertexBuffer = renderSystem->createVertexBuffer();
	vertexBuffer->load(list.data(), sizeof(vertex), size_list, shaderByteCode, sizeShader);
}

Circle::~Circle()
{
}

void Circle::onCreate()
{
	//Vector3D direction
	float xDirection = Random::range(-100, 100);
	float yDirection = Random::range(-100, 100);

	direction = Vector3D(xDirection, yDirection, 0.0f);
	direction = direction.normalize();
	speed = 1.0f;
}

void Circle::update(float deltaTime)
{
	CBData cc;

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	float orthoWidth = width / 300.0f;
	float orthoHeight = height / 300.0f;

	if (localPosition.y + this->radius >= orthoHeight / 2)
	{
		direction.y = direction.y * -1.0f;
		localPosition.y = (orthoHeight / 2) - this->radius;
	}
		
	if (localPosition.y - this->radius <= -orthoHeight / 2)
	{
		direction.y = direction.y * -1.0f;
		localPosition.y = -(orthoHeight / 2) + this->radius;
	}

	if (localPosition.x + this->radius >= orthoWidth / 2)
	{
		direction.x = direction.x * -1.0f;
		localPosition.x = (orthoWidth / 2) - this->radius;
	}
		
	if (localPosition.x - this->radius <= -orthoWidth / 2)
	{
		direction.x = direction.x * -1.0f;
		localPosition.x = -(orthoWidth / 2) + this->radius;
	}
		

	localPosition += direction * speed * EngineTime::getDeltaTime();

	cc.worldMatrix.setTranslation(localPosition);

	cc.viewMatrix.setIdentity();

	cc.projMatrix.setOrthoLH(orthoWidth, orthoHeight, -4.0f, 4.0f);

	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	constantBuffer->update(renderSystem->getImmediateDeviceContext(), &cc);
}

// Sets shaders and draws afterwards
void Circle::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	renderSystem->getImmediateDeviceContext()->setConstantBuffer(vertexShader, constantBuffer);
	renderSystem->getImmediateDeviceContext()->setConstantBuffer(pixelShader, constantBuffer);

	renderSystem->getImmediateDeviceContext()->setVertexShader(vertexShader);
	renderSystem->getImmediateDeviceContext()->setPixelShader(pixelShader);

	renderSystem->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	renderSystem->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}

void Circle::onDestroy()
{
	vertexBuffer->release();
	constantBuffer->release();
	delete this;
}