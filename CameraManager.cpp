#include "CameraManager.h"

#include <iostream>

CameraManager* CameraManager::P_SHARED_INSTANCE = NULL;

Camera* CameraManager::getMainCamera()
{
	return mainCamera;
}

void CameraManager::setMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void CameraManager::setMainCameraByIndex(int index)
{
	if (index > cameras.size())
	{
		std::cout << "Camera Index over Cameras in system" << std::endl;
		return;
	}
	setMainCamera(cameras[index]);
}

void CameraManager::addCamera(Camera* camera)
{
	if (mainCamera == NULL)
		setMainCamera(camera);
	this->cameras.push_back(camera);
}

void CameraManager::removeCamera(Camera* camera)
{
	std::string name = camera->getName();
	int index = -1;

	for (int i = 0; i < this->cameras.size() && index == -1; i++)
	{
		if (this->cameras[i] == camera)
			index = i;
	}

	if (index != -1)
	{
		this->cameras.erase(this->cameras.begin() + index);
	}
}


CameraManager::CameraManager() {}
CameraManager::CameraManager(const CameraManager&) {}

CameraManager* CameraManager::getInstance() {
	if (P_SHARED_INSTANCE == NULL)
		P_SHARED_INSTANCE = new CameraManager();

	return P_SHARED_INSTANCE;
}

void CameraManager::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}