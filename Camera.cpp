#include "Camera.h"

#include "EngineTime.h"
#include "InputSystem.h"

Camera* Camera::main = NULL;

Camera::Camera(std::string name) : GameObject(name)
{
}

Camera::~Camera()
{
}

void Camera::onCreate()
{
	GameObject::onCreate();
	InputSystem::getInstance()->addListener(this);
}

void Camera::update(float deltaTime)
{
}

void Camera::onDestroy()
{
	GameObject::onDestroy();
	InputSystem::getInstance()->removeListener(this);
}

void Camera::onKeyDown(int key)
{
	if (key == 'E')
	{
		this->localPosition.y += 1.0f * EngineTime::getDeltaTime();
	}
	else if (key == 'Q')
	{
		this->localPosition.y -= 1.0f * EngineTime::getDeltaTime();
	}

}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Vector2D& deltaMousePosition)
{
	localRotation.x -= deltaMousePosition.y * 0.5f * EngineTime::getDeltaTime();
	localRotation.y -= deltaMousePosition.x * 0.5f * EngineTime::getDeltaTime();
}

void Camera::onLeftMouseDown(const Vector2D& mousePosition)
{
}

void Camera::onLeftMouseUp(const Vector2D& mousePosition)
{
}

void Camera::onRightMouseDown(const Vector2D& mousePosition)
{
}

void Camera::onRightMouseUp(const Vector2D& mousePosition)
{
}
