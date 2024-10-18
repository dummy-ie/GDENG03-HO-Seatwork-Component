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
	GameObject::update(deltaTime);
	this->updateViewMatrix();
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam;
	worldCam.setIdentity();

	Matrix4x4 temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setTranslation(this->localPosition);
	worldCam *= temp;

	worldCam.inverse();
	this->localMatrix = worldCam;
}

void Camera::onDestroy()
{
	GameObject::onDestroy();
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}
