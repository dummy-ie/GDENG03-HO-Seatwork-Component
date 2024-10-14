#include "FirstPersonCamera.h"

#include "AppWindow.h"
#include "EngineTime.h"
#include "InputSystem.h"

FirstPersonCamera::FirstPersonCamera(std::string name) : Camera(name)
{
	localMatrix.setIdentity();
}

FirstPersonCamera::~FirstPersonCamera()
{
}

void FirstPersonCamera::update(float deltaTime)
{
	forward = 0.0f;
	right = 0.0f;
	if (InputSystem::getInstance()->getKey('W'))
	{
		forward = 1.0f;
	}
	if (InputSystem::getInstance()->getKey('A'))
	{
		right = -1.0f;
	}
	if (InputSystem::getInstance()->getKey('S'))
	{
		forward = -1.0f;
	}
	if (InputSystem::getInstance()->getKey('D'))
	{
		right = 1.0f;
	}
	if (InputSystem::getInstance()->getKey('E'))
	{
		localPosition.y += 1.0f * EngineTime::getDeltaTime();
	}
	if (InputSystem::getInstance()->getKey('Q'))
	{
		localPosition.y -= 1.0f * EngineTime::getDeltaTime();
	}

	RECT windowRect = application::AppWindow::getInstance()->getClientWindowRect();

	float width = windowRect.right - windowRect.left;
	float height = windowRect.bottom - windowRect.top;

	Vector2D deltaMousePosition = InputSystem::getInstance()->getDeltaMousePosition();
	Vector2D mousePosition = InputSystem::getInstance()->getMousePosition();
	
	if (deltaMousePosition != Vector2D::zero())
	{
		localRotation.x += (mousePosition.y - (height / 2.0f)) * 0.1f * EngineTime::getDeltaTime();
		localRotation.y += (mousePosition.x - (width / 2.0f)) * 0.1f * EngineTime::getDeltaTime();

		InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2, height / 2));
	}

	Matrix4x4 temp;
	localMatrix.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	localMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	localMatrix *= temp;

	localMatrix.setTranslation(localPosition);
	Vector3D newPosition = localMatrix.getTranslation() + localMatrix.getZDirection() * (forward * speed * EngineTime::getDeltaTime());
	newPosition = newPosition + localMatrix.getXDirection() * (right * speed * EngineTime::getDeltaTime());
	setPosition(newPosition);
}

void FirstPersonCamera::setSpeed(float speed)
{
	this->speed = speed;
}