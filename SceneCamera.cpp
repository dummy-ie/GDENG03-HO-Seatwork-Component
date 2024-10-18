#include "SceneCamera.h"

#include "AppWindow.h"
#include "EngineTime.h"
#include "InputSystem.h"

SceneCamera::SceneCamera(std::string name) : Camera(name)
{
	localMatrix.setIdentity();
	InputSystem::getInstance()->addListener(this);
}

SceneCamera::~SceneCamera()
{
}

void SceneCamera::update(float deltaTime)
{
	Vector3D newPosition = this->getLocalPosition();

	Matrix4x4 viewMatrix = this->localMatrix;
	viewMatrix.inverse();

	if (InputSystem::getInstance()->getKey('W'))
	{
		newPosition += viewMatrix.getZDirection() * (speed * deltaTime);
	}
	else if (InputSystem::getInstance()->getKey('S'))
	{
		newPosition -= viewMatrix.getZDirection() * (speed * deltaTime);
	}
	if (InputSystem::getInstance()->getKey('A'))
	{
		newPosition -= viewMatrix.getXDirection() * (speed * deltaTime);
	}
	else if (InputSystem::getInstance()->getKey('D'))
	{
		newPosition += viewMatrix.getXDirection() * (speed * deltaTime);
	}
	if (InputSystem::getInstance()->getKey('E'))
	{
		newPosition += viewMatrix.getYDirection() * (speed * deltaTime);
	}
	else if (InputSystem::getInstance()->getKey('Q'))
	{
		newPosition -= viewMatrix.getYDirection() * (speed * deltaTime);
	}

	setPosition(newPosition);
	this->updateViewMatrix();
}

void SceneCamera::setSpeed(float speed)
{
	this->speed = speed;
}

void SceneCamera::onKeyDown(int key)
{
}

void SceneCamera::onKeyUp(int key)
{
}

void SceneCamera::onMouseMove(const Vector2D& deltaMousePosition)
{
	if (isRightMouseDown)
	{
		RECT windowRect = application::AppWindow::getInstance()->getClientWindowRect();

		float width = windowRect.right - windowRect.left;
		float height = windowRect.bottom - windowRect.top;

		InputSystem::getInstance()->setCursorPosition(Vector2D(width / 2, height / 2));
		localRotation.x += (deltaMousePosition.y - (height / 2.0f)) * 0.1f * EngineTime::getDeltaTime();
		localRotation.y += (deltaMousePosition.x - (width / 2.0f)) * 0.1f * EngineTime::getDeltaTime();
	}
}

void SceneCamera::onLeftMouseDown(const Vector2D& mousePosition)
{
}

void SceneCamera::onLeftMouseUp(const Vector2D& mousePosition)
{
}

void SceneCamera::onRightMouseDown(const Vector2D& mousePosition)
{
	isRightMouseDown = true;
	InputSystem::getInstance()->showCursor(false);
}

void SceneCamera::onRightMouseUp(const Vector2D& mousePosition)
{
	isRightMouseDown = false;
	InputSystem::getInstance()->showCursor(true);
}
