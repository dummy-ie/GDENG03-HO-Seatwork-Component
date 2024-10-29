#include "Camera.h"

#include "EngineTime.h"
#include "InputSystem.h"
#include "AppWindow.h"

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
	this->updateProjectionMatrix();
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
	this->viewMatrix = worldCam;
}

void Camera::updateProjectionMatrix()
{
	RECT viewport = AppWindow::getInstance()->getClientWindowRect();
	int width = (viewport.right - viewport.left);
	int height = (viewport.bottom - viewport.top);

	switch (type) {
		case 0:
			this->projMatrix.setOrthoLH(
				width / 100.0f,
				height / 100.0f,
				-100.0f, 100.0f
			);
			break;
		case 1:
			this->projMatrix.setPerspectiveFovLH(
				1.57f, // fov
				(float)width / (float)height, // aspect
				0.1f, // near
				100.0f // far
			);
			break;
		default:
			this->projMatrix.setPerspectiveFovLH(
				1.57f, // fov
				(float)width / (float)height, // aspect
				0.1f, // near
				100.0f // far
			);
			break;
	}
}

void Camera::onDestroy()
{
	GameObject::onDestroy();
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->viewMatrix;
}

Matrix4x4 Camera::getProjMatrix()
{
	return this->projMatrix;
}

void Camera::setProjectionType(int type)
{
	this->type = type;
}