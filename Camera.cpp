#include "Camera.h"

#include "EngineTime.h"
#include "InputSystem.h"

Camera::Camera(std::string name) : GameObject(name)
{
}

Camera::~Camera()
{
}

void Camera::onCreate()
{
	GameObject::onCreate();
}

void Camera::update(float deltaTime)
{
	if (InputSystem::getInstance()->getKey('E'))
		this->localPosition.y += 1.0f * EngineTime::getDeltaTime();
	if (InputSystem::getInstance()->getKey('Q'))
		this->localPosition.y -= 1.0f * EngineTime::getDeltaTime();
}

void Camera::onDestroy()
{
	GameObject::onDestroy();
}
